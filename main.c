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

//Criação da lista ligada de utilizadores
struct nodeUser {
    UTILIZADOR data;
    struct nodeUser *next;
};

struct nodeUser *headUsers = NULL;

//Funcões e procedimentos
int menuAdministrador(){
    int opcao;

    printf("/----------- MENU DE ADMINISTRADOR -----------/\n\n");
    printf("\t1-Gestao de utilizadores\n");
    printf("\t2-Gestao das propriedades.\n");
    printf("\t3-Informacao sobre as propriedades.\n");
    printf("\t0-Sair\n\n");

    printf("Digite>> "); scanf(" %d", &opcao); //Leitura da opção do utilizaddor
    printf("\n");
    return opcao;
}

int menuGestaoUtilizadores(){
    int opcao;

    printf("/---------- GESTOR DE UTILIZADORES ------------/\n\n");
    printf("\t1-Inserir novo utilizador.\n");
    printf("\t2-Editar dados de um utilizador.\n");
    printf("\t3-Remover utilizador.\n");
    printf("\t4-Pesquisar utilizador.\n");
    printf("\t5-Listar utilizadores inseridos.\n");
    printf("\t0-Sair\n\n");

    printf("Digite>> "); scanf(" %d", &opcao); //Leitura da opção do utilizaddor
    printf("\n");
    return opcao;
}

char loginForm(UTILIZADOR input){
    struct nodeUser *aux;
    aux = headUsers;
    printf("/---------------- LOGIN FORM -----------------/\n\n");
    //Pedindo nome de utilizador 
    printf("\tNome de utilizador: ");
    scanf("%s", input.username);
    while (aux != NULL){
        if ((strcmp(aux->data.username, input.username)) == 0){
            printf("\tPassword: ");
            scanf("%s", input.password);
            if ((strcmp(aux->data.password, input.password))==0){
                printf("\n\tEntrou com sucesso!!\n\n");
                return aux->data.tipo;
                break;  
            } else {
                
                printf("\n\tERRO: Password incorreta.\n");
                printf("\n");
                return 'i';
            }
            break;
        } else {
            printf("\n\tERRO: Utilizador nao existe\n");
            printf("\n");
            return 'i';
        }
        aux = aux->next;
    }  
}



//Funções reservadas aos Administradores

UTILIZADOR inserirDadosUtilizador(){
    UTILIZADOR utilizador;
    printf("/------------ INSERIR UTILIZADOR -----------/\n\n");
    printf("\tNome: ");
    scanf("%s", utilizador.nome);
    printf("\tUsername: ");
    scanf("%s", utilizador.username);
    printf("\tPassword: ");
    scanf("%s", utilizador.password);
    printf("\tTipo(a ou e): ");
    scanf("%s", &utilizador.tipo);

    return utilizador;
}

void salvarUtilizadorFich(struct nodeUser *utilizador,FILE *fp){
    fseek(fp,0L,SEEK_END);
    if((fwrite(&utilizador,sizeof(struct nodeUser),1,fp)) != 1){
        printf("\tErro ao guardar os dados do utilizador.\n");
    }
}

void inserirUtilizador(){
    UTILIZADOR utilizador;
    struct nodeUser *novo, *aux;
    novo = (struct nodeUser*) malloc(sizeof(struct nodeUser));
    novo->data = inserirDadosUtilizador();
    novo->next = NULL;
    aux = headUsers;
    while (aux->next != NULL){
        aux = aux->next;
    }
    aux->next = novo;
}



void inserirSuperUtilizador(UTILIZADOR utilizador) {
    struct nodeUser *novo;
    novo = (struct nodeUser*) malloc(sizeof(struct nodeUser));
    novo->data = utilizador;
    novo->next = headUsers;
    headUsers = novo;

}

void imprimirLista() {
    struct nodeUser *aux;
    if (headUsers == NULL) {
        printf("\nLista vazia");
    } else {
        aux = headUsers;
        printf("\nLista: ");
        while(aux != NULL) {
            printf("%s \n", aux->data.username);
            aux = aux->next;
        }
    }
}



int main () {

    setlocale(LC_ALL ,"Portuguese");
    
    //Declaração das variaveis
    FILE *fusers;
    char tipo_utilizador;
    

    //Declaração da estrutura de utilizadores e do superutilizador
    UTILIZADOR utilizadores, superuser = {
        .nome = "Superuser\0",
        .username = "Superuser\0",
        .password = "Passwd123!\0",
        .tipo = 'a'
    };

    inserirSuperUtilizador(superuser); //Adicionar o superutilizador a lista de utilizadores
    
    

    
    //Abertura e verificação do ficheiro binário
    if((fusers = fopen("Dados_Utilizadores.dat", "a+b")) == NULL){
        printf("Erro na abertura do ficheiro binario!!!\n");
        exit(EXIT_FAILURE);
    }

    //Loop do Menu
    do{
        tipo_utilizador = loginForm(utilizadores);
    } while (tipo_utilizador == 'i');
 
    
    int opAdmin, opAvali, opcao;; //Variaveis que armazenam a opção dos administradores e avaliadores respetivamente

    while(1){
        switch (tipo_utilizador)
        {
            //Menu e submenus reservados ao administrador
        case 'a':
            imprimirLista();
            opAdmin = menuAdministrador();
            switch (opAdmin)
            {
            case 1:
                while (1)
                {
                    opcao = menuGestaoUtilizadores();
                    if(opcao == 0) break;
                    switch (opcao){
                    case 1:
                        inserirUtilizador();
                        break;
                    case 5:
                        imprimirLista();
                        break;
                    default:
                        break;
                    }
                }
                break;
            case 0:
                break;
            default:
                break;
            }
            break;
            //Menu e submenus reservados aos avaliadores
        case 'e':

            break;

        default:
            break;
        }
    }

    return 0;
}