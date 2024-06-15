#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void afisare(char **t, int n){
    for(int i = 0; i<n ; i++){
        printf("%s\n",t[i]);
    }
}

char* read(){
  char *line = malloc(sizeof(char));
    char ch;
    size_t n = 0;
    for(;;){
        n++;
        if( (line = realloc(line,n*sizeof(char))) == NULL){
            exit(-1);
        }
        ch=getchar();
        if(ch == EOF){
            break;
        }
        line[n-1]=ch;
    }
    line[n-1]='\0';
    return line;
}

int main(void){
    char **fazanul= malloc(100 * sizeof(char*));
    char *a;
    char * ant;
    int nrc=0;
    a = read();
    char *tok;
    ant = a;
    tok = strtok(a,"\t\n ");
    while(tok!=NULL){
        nrc++;
	fazanul[nrc-1] = malloc(100 * sizeof(char));
        strcpy(fazanul[nrc-1], tok);
        tok = strtok(NULL,"\t\n ");
    }
    afisare(fazanul,nrc);
    char *rez;
    int s1;
    rez = malloc((sizeof(fazanul[0]+1) * sizeof(char)));
    strcpy(rez,fazanul[0]);
    for(int i = 0; i < nrc ; i++){
        for(int j = i + 1; j < nrc ; j++){
            s1 = strlen(fazanul[i]);
            if((tolower(fazanul[i][s1-2])==tolower(fazanul[j][0]))&&(tolower(fazanul[i][s1-1])==tolower(fazanul[j][1]))){
                rez = realloc(rez,(strlen(rez)+strlen(fazanul[j])+3)*sizeof(char));
                strcat(rez,"-");
                strcat(rez,fazanul[j]);
		i = j - 1;
                break;
            }
        }
    }
    printf("%s", a);
    printf("%s", rez);
    for(int i = 0;i < nrc-1;i++){
      free(fazanul[i]);
    }
    free(fazanul);
    // free(a);
    free(rez);
    free(ant);
    return 0;
}
