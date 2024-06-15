#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef enum
  {
    Benzina,
    Motorina
  }carburant;

typedef enum
  {
    Electrica,
    Combustibil
  }CarType;

typedef struct
{
  uint8_t ChargingTime;
  uint8_t CapacitateBaterie;
}ECarSpec;
  
typedef union
{
  carburant TipCarburant;
  ECarSpec SpecificatiiMasinaElectrica;
}CarSpec;
  
typedef struct
{
  char Model[21];
  CarType tip;
  uint8_t MaxSpeed;
  uint8_t SeatCount;
  CarSpec Specificatii;
}Masina;

CarSpec SetSpecs(CarType CurrentCarType)
{
  CarSpec CurrentCarSpecification;
  switch(CurrentCarType)
    {
    case Electrica:
      printf("Introduceti timpul de incarcare : ");
      scanf("%hhd", &CurrentCarSpecification.SpecificatiiMasinaElectrica.ChargingTime);
      printf("Introduceti Capacitatea bateriei : ");
      scanf("%hhd", &CurrentCarSpecification.SpecificatiiMasinaElectrica.CapacitateBaterie);
      break;
    case Combustibil:
      char ReadCombustibilType[10];
      printf("Introduceti tipul de combusitbil : ");
      fgets(ReadCombustibilType, 9, stdin);
      ReadCombustibilType[strlen(ReadCombustibilType) - 1] = '\0';
      if(strcasecmp(ReadCombustibilType, "Benzina") == 0){
	CurrentCarSpecification.TipCarburant = Benzina;
      }
      else if(strcasecmp(ReadCombustibilType, "Motorina") == 0){
	CurrentCarSpecification.TipCarburant = Motorina;
      }
      break;
    }
  return CurrentCarSpecification;
}

void SetCarType(char *ReadType, Masina *CurrentCar)
{
  if(strcasecmp(ReadType, "Electrica") == 0){
    CurrentCar->tip = Electrica;
    CurrentCar->Specificatii = SetSpecs(CurrentCar->tip);
  }
  else if(strcasecmp(ReadType, "Combustibil") == 0){
    CurrentCar->tip = Combustibil;
    CurrentCar->Specificatii = SetSpecs(CurrentCar->tip);
  }
}

Masina *AddCar(Masina *CarList, int *size)
{
  CarList = realloc(CarList, (*size + 1) * sizeof(Masina));
  printf("Introduceti marca masinii : ");
  fgets(CarList[0].Model, 20, stdin);
  fgets(CarList[0].Model, 20, stdin);
  char ReadType[14];
  printf("Introduceti tipul masinii(Combustibil/Electrica) : ");
  fgets(ReadType, 13, stdin);
  ReadType[strlen(ReadType) - 1] = '\0';
  printf("%s\n", ReadType);
  SetCarType(ReadType, &CarList[(*size)]);
  printf("Introduceti numarul de scaune : ");
  scanf("%hhd", &CarList[*size].SeatCount);
  printf("Introduceti viteza maxima : ");
  scanf("%hhd", &CarList[*size].MaxSpeed);
  *size += 1;
  return CarList;
}

void ShowElectricSpecs(CarSpec CurrentCarSpec)
{
  printf("Masina Electrica\n");
  printf("Timp incarcare : %d\n", CurrentCarSpec.SpecificatiiMasinaElectrica.ChargingTime);
  printf("Capacitate Baterie : %d\n", CurrentCarSpec.SpecificatiiMasinaElectrica.CapacitateBaterie);
}

void ShowCarburantSpecs(CarSpec CurrentCarSpec)
{
  printf("Masina pe combustibil\n");
  printf("Tip Carburant : ");
  switch(CurrentCarSpec.TipCarburant)
    {
    case Benzina:
      printf("Benzina\n");
      break;
    case Motorina:
      printf("Motorina\n");
      break;
    }
}

void ShowCarSpecs(Masina Car)
{
  switch(Car.tip)
    {
    case Electrica:
      ShowElectricSpecs(Car.Specificatii);
      break;
    case Combustibil:
      ShowCarburantSpecs(Car.Specificatii);
      break;
    }
  printf("Nr. locuri : %d\n", Car.SeatCount);
  printf("Top speed : %d\n", Car.MaxSpeed);
}

Masina *SearchInList(Masina *CarList, int *size, CarType SearchedType)
{
  for(int i = 0;i < *size;i++){
      if(CarList[i].tip == SearchedType){
	*size = (*size - i) - 1;
	return &CarList[i];
      }
    }
    return NULL;
}

Masina *SearchCarType(Masina *CarList, int *size, char *SearchType)
{
  if(strcasecmp(SearchType, "Combustibil") == 0){
    return SearchInList(CarList, size, Combustibil);
  }
  else if(strcasecmp(SearchType, "Electrica") == 0){
    return SearchInList(CarList, size, Electrica);
  }
  else{
    return NULL;
  }
}

void ShowCarByType(Masina *CarList, int size)
{
  Masina *SearchedCar;
  char SearchType[14];
  fgets(SearchType, 13, stdin);
  fgets(SearchType, 13, stdin);
  SearchType[strlen(SearchType) - 1] = '\0';
  int ShowCount = 0;
  SearchedCar = SearchCarType(CarList, &size, SearchType);
  while(SearchedCar != NULL){
    ShowCount++;
    ShowCarSpecs(*SearchedCar);
    printf("\n");
    if(size >= 1){
      SearchedCar = SearchCarType(SearchedCar + 1, &size, SearchType);
    }
    else{
      break;
    }
  }
  if(ShowCount == 0){
    printf("Nu exista inregistrari de astfel de vehicule\n");
  }
}

int main(void)
{
  Masina *CarList = NULL;
  int size = 0;
  uint8_t MenuOption = 0;
  do{
    printf("Introduceti optiunea meniului\n1.Adaugare masina\n2.Afisare masina dupa tipul ei\n3.Exit\n");
    if(scanf("%hhd", &MenuOption) != 1){
      MenuOption = 3;
    }
    switch(MenuOption)
      {
      case 1:
	CarList = AddCar(CarList, &size);
	break;
      case 2:
	ShowCarByType(CarList, size);
	break;
      default:
	MenuOption = 4;
	break;
      }
  }while((MenuOption < 4) && (MenuOption > 0));
  free(CarList);
  return 0;
}

 
