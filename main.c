#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//maximo de culturas por propriedade
#define MAX_CT 20 

//Declaração das estruturas
typedef struct utilizador{
    char username[20];
    char nome[20];
    char password[20];
    char tipo; // a/A->administrador e e/E->(evaluator)avaliador

}UTILIZADOR;

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

//Criação da lista ligada
struct node {
    UTILIZADOR data;
    struct node *next;
};

struct node *head = NULL;

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
    printf("Gerar o ranking de utilizadores por número de propriedades avaliadas\n\n");

    printf("Digite>>"); scanf(" %d", &opcao); //Leitura da opção do utilizaddor

    return opcao;
}

void loginForm(){
    struct node *aux;
    aux = head;
    //Pedindo nome de utilizador 
    printf("");

}



void inserirInicio(UTILIZADOR data) {
    struct node *novo;
    novo = (struct node*) malloc(sizeof(struct node));
    novo->data = data;
    novo->next = head;
    head = novo;
}

void imprimirLista() {
    struct node *aux;
    if (head == NULL) {
        printf("\nLista vazia");
    } else {
        aux = head;
        printf("\nLista: ");
        while(aux != NULL) {
            printf("%s ", aux->data.username);
            aux = aux->next;
        }
    }
}



int main () {

    setlocale(LC_ALL ,"Portuguese");
    
    //Declaração das variaveis
    FILE *file;
    int op; //Coleta a opção

    //Superutilizador
    UTILIZADOR superuser = {
        .nome = "Superuser\0",
        .username = "Superuser\0",
        .password = "Passwd123!\0",
        .tipo = 'a'
    };

    inserirInicio(superuser);
    imprimirLista();

    
    //Abertura e verificação do ficheiro binário
    if((file = fopen("dados.dat", "a+b")) == NULL){
        printf("Erro na abertura do ficheiro binario!!!\n");
        exit(EXIT_FAILURE);
    }

    //Loop do Menu


    return 0;
}