#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

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
    printf("Listar propriedades por analisar\n");
    printf("Listar propriedades avaliadas e o valor\n");
    printf("Listar propriedades avaliadas acima de um determinado valor\n");
    printf("Listar todas as propriedades avaliadas por um determinado utilizador\n");
    printf("Pesquisar propriedades por nome do proprietário\n");
    printf("Gerar num ficheiro de texto um relatório com propriedades avaliadas, ordenadas por valor\n");
    printf("Gerar o ranking de utilizadores por número de propriedades avaliadas\n");

    printf("Digite>>"); scanf(" %d", &opcao); //Leitura da opção do utilizaddor

    return opcao;
}


int main () {

    setlocale(LC_ALL ,"Portuguese");
    
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
    if((op = menu()) == 0) break;
    
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