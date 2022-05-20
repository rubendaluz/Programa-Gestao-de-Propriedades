#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//maximo de culturas por propriedade
#define MAX_CT 20 

typedef struct utilizador{
    char username[20];
    char password[20];
    int tipo; 
}UTILIZADOR;
//1->administrador e 0->avaliador

typedef struct cultura{
    char descricao[150];
    float area_cultivo;
}CULTURA;

typedef struct propriedade{
    int numero;

    char nome_proprietario[40];
    char descricao[150];
    float area_total;
    CULTURA culturas[MAX_CT];

}PROPRIEDADE;


int main () {
 



    return 0;
}