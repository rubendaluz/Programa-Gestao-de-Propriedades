#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//maximo de culturas por propriedade
#define MAX_CT 20 

//Declaração das estruturas
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

//Funcões e procedimentos
int menu(){
    int opcao;

    printf("MENU:\n");
    //printf("");
    //printf("");
    scanf(" %d", &opcao); //Leitura da opção do utilizaddor

    return opcao;
}


int main () {
    
    //Declaração das variaveis
    FILE *file;
    int op; //Coleta a opção
    
    
    
    //Abertura e verificação do ficheiro binário
    if((file = fopen("dados.dat", "a+b")) == NULL){
        printf("Erro na abertura do ficheiro binario!!!\n");
        exit(EXIT_FAILURE);
    }

    //Loop do Menu
    while (1)
    op = menu();
    {
        switch (op)
        {
        case 1:
            break;
    
        default:
            printf("Opcao invalida!!\n");
            break;
        }
    }
    


    return 0;
}