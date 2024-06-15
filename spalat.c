#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef enum
  {
    frontala = 0,
    verticala = 1
  }incarcare;

typedef struct
{
  int capacitate;
  char clasa;
  char *programe;
}caract_front;

typedef struct
{
  int afisaj;
  int nr_prog;
  int centrifugare;
  int nivel_zgomot;
}caract_vert;

typedef union
{
  caract_vert vertical;
  caract_front frontal;
}caract;
  
typedef struct
{
  char *producator;
  char *model;
  int pret_furnizor;
  int pret_vanzare;
  int greutate;
  incarcare tip;
  caract caracteristici;
}masina;

void eliberare(masina element)
{
  free(element.producator);
  free(element.model);
  if(element.tip == frontala){
    free(element.caracteristici.frontal.programe);
  }
}

masina initialize(void)
{
  return (masina){.producator = NULL, .model = NULL, .pret_furnizor = 0, .pret_vanzare = 0, .greutate = 0, .tip = frontala};
}

int din_mem(int old_size)
{
  if(old_size < 4){
    return old_size + 1;
  }
  else{
    return old_size / 2 * 3;
  }
}

char *read_string(FILE *buffer)
{
  char *string = malloc(sizeof(char));
  int size = 0;
  int max_size = 1;
  char ch = 0;
  if(buffer != stdin){
    while((fread(&ch, 1, 1, buffer) == 1) && (ch != '\0')){
      string[size] = ch;
      size++;
      if(size == max_size){
	max_size = din_mem(max_size);
	string = realloc(string, max_size * sizeof(char));
	assert(string != NULL);
      }
    }
  }
  else{
    while(((ch = fgetc(buffer)) != EOF) && (ch != '\n')){
      string[size] = ch;
      size++;
      if(size == max_size){
	max_size = din_mem(max_size);
	string = realloc(string, max_size * sizeof(char));
	assert(string != NULL);
      }
    }
  }
  string[size] = '\0';
  if(size == 0){
    free(string);
    return NULL;
  }
  else{
    return string;
  }
}

caract_vert get_vert(FILE *buffer)
{
  caract_vert caract;
  if(buffer != stdin){
    fread(&caract.afisaj, 4, 1, buffer);
    fread(&caract.nr_prog, 4, 1, buffer);
    fread(&caract.centrifugare, 4, 1, buffer);
    fread(&caract.nivel_zgomot, 4, 1, buffer);
  }
  else{
    fscanf(buffer, "%d", &caract.afisaj);
    fscanf(buffer, "%d", &caract.nr_prog);
    fscanf(buffer, "%d", &caract.centrifugare);
    fscanf(buffer, "%d", &caract.nivel_zgomot);
  }
  return caract;
}

caract_front get_frontal(FILE *buffer)
{
  caract_front caract;
  if(buffer != stdin){
    fread(&caract.capacitate, 4, 1, buffer);
    fread(&caract.clasa, 1, 1, buffer);
  }
  else{
    fscanf(buffer, "%d", &caract.capacitate);
    fgetc(buffer);
    caract.clasa = fgetc(buffer);
    fgetc(buffer);
  }
  caract.programe = read_string(buffer);
  return caract;
}

caract get_caract(FILE *buffer, incarcare type)
{
  caract caracteristica;
  switch(type){
  case frontala:
    caracteristica.frontal = get_frontal(buffer);
    break;
  case verticala:
    caracteristica.vertical = get_vert(buffer);
    break;
  }
  return caracteristica;
}

masina read_data(FILE *buffer)
{
  masina element = initialize();
  element.producator = read_string(buffer);
  if(element.producator == NULL){
    return initialize();
  }
  
  element.model = read_string(buffer);
  if(element.model == NULL){
    free(element.producator);
    return initialize();
  }
  
  if(buffer != stdin){
    fread(&element.pret_furnizor, 4, 1, buffer);
    fread(&element.pret_vanzare, 4, 1, buffer);
    fread(&element.greutate, 4, 1, buffer);
  }
  else{
    fscanf(buffer, "%d", &element.pret_furnizor);
    fscanf(buffer, "%d", &element.pret_vanzare);
    fscanf(buffer, "%d", &element.greutate);
  }
  char *type = NULL;
  if(buffer == stdin){
    fgetc(buffer);
    type = read_string(buffer);
    if(strcmp(type, "frontala") == 0){
      element.tip = frontala;
    }
    else{
      element.tip = verticala;
    }
    free(type);
  }
  else{
    fread(&element.tip, sizeof(incarcare), 1, buffer);
  }
  element.caracteristici = get_caract(buffer, element.tip);
  return element;
}

void show_verticala(caract_vert caract)
{
  printf("%d %d %d %d\n", caract.afisaj, caract.nr_prog, caract.centrifugare, caract.nivel_zgomot);
}

void show_frontala(caract_front caract)
{
  printf("%d %c %s\n", caract.capacitate, caract.clasa, caract.programe);
}

void show_caract(incarcare type, caract caracteristici)
{
  switch(type){
  case frontala:
    show_frontala(caracteristici.frontal);
    break;
  case verticala:
    show_verticala(caracteristici.vertical);
    break;
  }
}

void afisare(masina element)
{
  printf("%s\n", element.producator);
  printf("%s\n", element.model);
  printf("%d %d %d\n", element.pret_furnizor, element.pret_vanzare, element.greutate);
  show_caract(element.tip, element.caracteristici);
}

void afisare_produse_fisier(char *file_path)
{
  
  FILE *buffer = fopen(file_path, "rb");
  assert(buffer != NULL);
  masina element = initialize();
  element = read_data(buffer);
  while(element.model != NULL){
    afisare(element);
    eliberare(element);
    element = read_data(buffer);
  }
  fclose(buffer);
}

void add_frontal_caract(FILE *output, caract_front caract)
{
  fwrite(&caract.capacitate, 4, 1, output);
  fwrite(&caract.clasa, 1, 1, output);
  fwrite(caract.programe, 1, strlen(caract.programe) + 1, output);
}

void add_vertical_caract(FILE *output, caract_vert caract)
{
  fwrite(&caract.afisaj, 4, 1, output);
  fwrite(&caract.nr_prog, 4, 1, output);
  fwrite(&caract.centrifugare, 4, 1, output);
  fwrite(&caract.nivel_zgomot, 4, 1, output);
}

void add_caract(FILE *output, incarcare type, caract caracteristici)
{
  switch(type){
  case frontala:
    add_frontal_caract(output, caracteristici.frontal);
    break;
  case verticala:
    add_vertical_caract(output, caracteristici.vertical);
    break;
  }
}

void add_data_to_file(char *file_path)
{
  FILE *output = fopen(file_path, "ab");
  assert(output != NULL);
  masina new_element = read_data(stdin);
  fseek(output, 1, SEEK_END);
  fwrite(new_element.producator, 1, strlen(new_element.producator) + 1, output);
  fwrite(new_element.model, 1, strlen(new_element.model) + 1, output);
  fwrite(&new_element.pret_furnizor, 4, 1, output);
  fwrite(&new_element.pret_vanzare, 4, 1, output);
  fwrite(&new_element.greutate, 4, 1, output);
  fwrite(&new_element.tip, sizeof(incarcare), 1, output);
  add_caract(output, new_element.tip, new_element.caracteristici);
  eliberare(new_element);
  fclose(output);
}

int main(void)
{
  //add_data_to_file("magazin.bin");
  afisare_produse_fisier("magazin.bin");
}
