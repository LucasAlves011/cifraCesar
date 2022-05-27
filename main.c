#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"
#include <locale.h>
#include <time.h>

#define SENHA "jBLa!523"


char alfabeto[95] = {};


int main() {
    srand(time(NULL));

    setlocale(LC_ALL, "Portuguese");

    for (int i = 32; i < 127 ; i++){
        alfabeto[i-32] = (char )i;
    }

    char *senhaCriptografada = incryptCipraDeCezar(SENHA);

    printf("A senha criptografada é : %s\n",senhaCriptografada);

    time_t t_ini ,t_fim;
    t_ini = time(NULL);
    decryptCipraDeCezar(senhaCriptografada);
    t_fim = time(NULL);
    printf("em %lf segundos ",difftime(t_fim,t_ini));


    return 0;
}

void decryptCipraDeCezar(char * message){
    int tentativa = 0;
    int k = 0;
    for (; message[k] != '\000'; k++);

    char senha[k];

    for (int i = 0; i <95  ; i++){
        for (int j = 0; j < k ; j++){

            senha[j] = auxDecript(message[j],tentativa);
        }

        if (strcmp(senha,SENHA) == 0 ){
            printf("Achou a senha: %s ",senha );
            return;
        }
        else{
            tentativa++;
        }
    }
}

char* incryptCipraDeCezar(char * message){

    int posicao = rand() % 9;

    int index = 95 - posicao;
    char alfa2[95] = {};

    int i=0;
    for (; i < index; i++) {
        alfa2[i] = alfabeto[posicao++];
    }

    char *senha = malloc(sizeof(message));

    if(i < 95){
        for (int j =0; i < 95 ; i++)
            alfa2[i] = alfabeto[j++];

        for (int j=0; j < sizeof(message); j++)
            senha[j] = auxiliar(message[j],alfa2);
    }
    return senha ;
}

char auxiliar(char p,char * alfa2){
    for (int i=0; i < 95; i++)  if (alfabeto[i] == p) return alfa2[i];
    return ' ';
}

char auxDecript(char p , int posi){
    for (int i = 0; i < posi; ++i) {
        if(alfabeto[i] == p)
            return alfabeto[95 -i];
    }

    for (int i = posi; i < 95 ; i++)
         if(alfabeto[i] == p )
            return alfabeto[i-posi];
    return ' ';
}
