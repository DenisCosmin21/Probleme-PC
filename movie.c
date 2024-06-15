#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct
{
  char *titlu;//este alocat dinamic deoarece nu cunoastem dimensiunea
  int year;
  int buget;
}list;

int din_mem(size_t size)
{
  return (size > 4 ? size / 2 * 3 : size + 1);
}

char *read_file(char *path)//functia va citi din fisier toate liniile si le va adauga in variabila alocata dinamic text
{
  FILE *buffer = fopen(path, "r");
  assert(buffer != NULL);//functia de assert va verifica ca o conditie sa fie respectata, altfel ii va da exit la program. Se poate schimba cu un if
  char c = 0;
  char *text = NULL;
  size_t size = 0;
  size_t max_size = 0;
  while((c = fgetc(buffer)) != EOF){
    if(size == max_size){
      max_size = din_mem(max_size);
      text = realloc(text, max_size * sizeof(char));
      assert(text != NULL);
    }
    text[size++] = c;
  }

  fclose(buffer);
  
  if(text != NULL){
    if(size == max_size){
      text = realloc(text, (max_size + 1) * sizeof(char));
      assert(text != NULL);
    }
    text[size] = '\0';
  }
  
  return text;
}

char *get_line(char *text)
{
  char *end_line = strchr(text, '\n');//finalul unei linii este determinat de un '\n', asa ca vom cauta acest caracter.
  if(end_line == NULL){
    return NULL;
  }
  char *line = malloc(((end_line - text) + 1) * sizeof(char));//diferenta end_line - text ne va determina cate caractere se afla intre caracterul '\n' si inceputul liniei, si vom aloca aceasta dimensiune.
  assert(line != NULL);
  memcpy(line, text, (end_line - text));//aceasta functie va copia n bytes din zona de memorie src in zona de memorie dest.
  line[end_line - text] = '\0'; 
  return line;//returnam linie care este alocata dinamic, deci sa nu uitam sa o eliberam
}

list parse_string(char *line)
{
  list element;
  char *data_parsed = strtok(line, ",");//vom avea primul field in variabila, care este un numar deci folosim strtol pentru a-l pune in int;
  element.year = strtol(data_parsed, NULL, 10);
  strtok(NULL, ",");
  data_parsed = strtok(NULL, ",");
  //am dat strtok pana am ajuns la campul de care avem nevoie adica title, deci in data_parsed avem salvat titlul. Un mic detaliu de care ar trebui sa tinem cont este faptyul ca anumite titluri pot avea caracterul , in ele, deci strtok nu ar functiona asa cum dorim, si ar trb sa identifiam acest lucru. Titlurile cu caracterul , in ele vor incepe cu " deci verificam daca avem " la inceput
  if(data_parsed[0] == '"'){
    data_parsed[strlen(data_parsed)] = ','; //functia de strtok va adauga '\0' unde va gasi caracterul cautat, deci pe pozitia respectivs vrem sa punem inapoi virgula
    char *end_title = strrchr(data_parsed, '"');
    *(end_title) = '\0';
    element.titlu = malloc((strlen(data_parsed) + 1) * sizeof(char));
    strcpy(element.titlu, data_parsed + 1);
    strtok(end_title + 2, ",");
  }
  else{
    element.titlu = malloc((strlen(data_parsed) + 1) * sizeof(char));
    strcpy(element.titlu, data_parsed);
  }
  assert(element.titlu != NULL);
  strtok(NULL, ",");
  strtok(NULL, ",");
  strtok(NULL, ",");
  data_parsed = strtok(NULL, ",");
  element.buget = strtol(data_parsed, NULL, 10);
  return element;
}

void show_element(list element, FILE *output)
{
  fprintf(output, "%d %s %d\n", element.year, element.titlu, element.buget);
}

void afisare(list *movie_list, size_t size, char *path)
{
  FILE *output = fopen(path, "w");
  assert(output != NULL);
  for(int i = 0;i < size;i++){
    show_element(movie_list[i], output);
  }
  fclose(output);
}

void sort_an(list *movie_list, size_t size)
{
  list aux;
  for(int i = 0;i < size - 1;i++){
    for(int j = i + 1;j < size;j++){
      if(movie_list[i].year > movie_list[j].year){
	aux = movie_list[i];
	movie_list[i] = movie_list[j];
	movie_list[j] = aux;
      }
    }
  }
  afisare(movie_list, size, "out1.txt");
}

void sort_titlu(list *movie_list, size_t size)
{
  list aux;
  for(int i = 0;i < size - 1;i++){
    for(int j = i + 1;j < size;j++){
      if(strcasecmp(movie_list[i].titlu, movie_list[j].titlu) > 0){
	aux = movie_list[i];
	movie_list[i] = movie_list[j];
	movie_list[j] = aux;
      }
    }
  }
  afisare(movie_list, size, "out2.txt");
}

void sort_buget(list *movie_list, size_t size)
{
  list aux;
  for(int i = 0;i < size - 1;i++){
    for(int j = i + 1;j < size;j++){
      if(movie_list[i].buget > movie_list[j].buget){
	aux = movie_list[i];
	movie_list[i] = movie_list[j];
	movie_list[j] = aux;
      }
    }
  }
  afisare(movie_list, size, "out3.txt");
}

int main(void)
{
  char *text = read_file("movies.csv");
  if(text != NULL){
    char *line = NULL;
    char *start_line = text;
    list *movie_list = NULL;
    size_t size = 0;
    line = get_line(start_line); //preluam prima linia care este reprezentarea tabelului, deci nu contine informatii
    start_line = strchr(start_line, '\n') + 1;
    free(line);
    while((line = get_line(start_line)) != NULL){
      movie_list = realloc(movie_list, (size + 1) * sizeof(list));//alocam spatiu in memorie pentru a adauga in structura datele necesare, daca exista date de preluat
      assert(movie_list != NULL);
      movie_list[size] = parse_string(line);
      size++;
      free(line);
      start_line = strchr(start_line, '\n') + 1;
    }
    sort_an(movie_list, size);
    sort_titlu(movie_list, size);
    sort_buget(movie_list, size);
    free(text);
    for(int i = 0;i < size;i++){
      free(movie_list[i].titlu);
    }
    free(movie_list);
  }
  return 0;
}
