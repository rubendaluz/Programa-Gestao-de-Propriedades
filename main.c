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

char loginForm(){
    struct nodeUser *aux;
    UTILIZADOR input;
    aux = headUsers;
    printf("/--------------- LOGIN FORM ----------------/\n\n");
    //Pedindo nome de utilizador 
    printf("\tNome de utilizador: ");
    scanf("%s", input.username);
    while (aux != NULL){
        if((strcmp(aux->data.username, input.username)) == 0){
            printf("\tPassword:");
            scanf("%s", input.password);
            if((strcmp(aux->data.password, input.password)) == 0){
                printf("\n\tEntrou com sucesso!!!\n\n");
                return aux->data.tipo;
            }else{
                printf("\n\tPassword incorreta!!!\n\n");
                return 'i';
            }
        }else if((strcmp(aux->data.username, input.username)) != 0){
            aux = aux->next;
        }else{
            return 'i';
        }
    }
    printf("\n\tUtilizador inexistente\n\n");
}   

int menuAdministrador(){
    int opcao;

    printf("/--------- MENU DE ADMINISTRADOR -----------/\n\n");
    printf("\t1-Gestao de utilizadores\n");
    printf("\t2-Gestao das propriedades.\n");
    printf("\t3-Informacao sobre as propriedades.\n");
    printf("\t4-Voltar ao Formulario de login.\n");
    printf("\t0-Encerrar programa\n\n");

    printf("Digite>> "); scanf(" %d", &opcao); //Leitura da opção do utilizaddor
    printf("\n");
    return opcao;
}

int menuGestaoUtilizadores(){
    int opcao;

    printf("/------- GERENCIADOR DE UTILIZADORES -------/\n\n");
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

int menuGestaoPropriedades(){
    int opcao;

     printf("/------- GERENCIADOR DE PROPRIEDADES -------/\n\n");
    printf("\t1-Inserir nova propriedade.\n");
    printf("\t2-Editar dados de uma propriedade.\n");
    printf("\t3-Remover propriedade.\n");
    printf("\t4-Listar propriedades inseridas.\n");
    printf("\t0-Sair\n\n");

    printf("Digite>> "); scanf(" %d", &opcao); //Leitura da opção do utilizaddor
    printf("\n");
    return opcao;
}


//Funções reservadas aos Administradores
int numUtilizadoresRegistrados(FILE *fp){
    int num;
    fseek(fp,0L,SEEK_END);
    num = ftell(fp) / sizeof(UTILIZADOR);
    printf("%d", num);
    return num;
}

void lerUtilizadoresFicheiro(struct nodeUser *head, FILE *fp){
    int qtdusers;
    qtdusers = numUtilizadoresRegistrados(fp);
    head = headUsers;
}

void salvarUtilizadorFich(struct nodeUser *utilizador,FILE *fp){
    fseek(fp,0L,SEEK_END);
    if((fwrite(utilizador,sizeof(struct nodeUser),1,fp)) != 1){
        printf("\tErro ao guardar os dados do utilizador.\n");
    }
}

UTILIZADOR inserirDadosUtilizador(){
    UTILIZADOR utilizador;
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


void inserirUtilizador(FILE *fp){
    UTILIZADOR utilizador;
    struct nodeUser *novo, *aux;
    novo = (struct nodeUser*) malloc(sizeof(struct nodeUser));
    printf("/------------ INSERIR UTILIZADOR -----------/\n\n");
    novo->data = inserirDadosUtilizador();
    novo->next = NULL;
    aux = headUsers;
    while (aux->next != NULL){
        aux = aux->next;
    }
    aux->next = novo;
    salvarUtilizadorFich(novo,fp);
}

void inserirSuperUtilizador(UTILIZADOR utilizador) {
    struct nodeUser *novo;
    novo = (struct nodeUser*) malloc(sizeof(struct nodeUser));
    novo->data = utilizador;
    novo->next = headUsers;
    headUsers = novo;
}

void *apagarInicio(struct nodeUser *head){
	struct nodeUser *aux;
	aux = head;
	head = aux->next;
	free(aux);
}


void apagarUtilizador(struct nodeUser *head){
	struct nodeUser *aux, *prev;
	char userInput[20];
    printf("/------------- REMOVER UTILIZADOR -----------/\n\n");
	printf("\tInsira o username : ");
	scanf("%s", userInput);
	aux = head;
	if(strcmp(aux->data.username, userInput) == 0){
		head = apagarInicio(head);
	} else {
		while(strcmp(aux->data.username, userInput) != 0){
			prev = aux;
			aux = aux->next;
		}
		prev->next = aux->next;
		free(aux);
	}
}

void editarUtilizador(struct nodeUser *head){
	struct nodeUser *aux;
    UTILIZADOR input;
	char userInput[20];
    printf("/------------- EDITAR UTILIZADOR -----------/\n\n");
	printf("\tInsira o username : ");
	scanf("%s", userInput);
	aux = head;
    while(aux != NULL){
        if(strcmp(aux->data.username, userInput) == 0){
            printf("\nInsira os novos dados do utilizador\n\n");
            input = inserirDadosUtilizador();
            aux->data = input;
            printf("\n\tDados atualizados\n\n");
            break;
        }else{
            aux = aux->next;
        }
    }
    if(aux == NULL && strcmp(aux->data.username, userInput) != 0){
        printf("\n\tUtilizador não foi encontrado\n\n");
    }
}

void pesquisarUtilizador(struct nodeUser *head){
	struct nodeUser *aux;
	char userInput[20];
    printf("/------------- PESQUISAR UTILIZADOR -----------/\n\n");
	printf("\tInsira o nome : ");
	scanf("%s", userInput);
	aux = head;
    while(aux != NULL){
        if(strcmp(aux->data.nome, userInput) == 0){
            printf("\n\tDados do utilizador\n\n");
            printf("\tUsername: %s\n", aux->data.username);
            printf("\tPassword: %s\n", aux->data.password);
            if (aux->data.tipo == 'a')
            {
                printf("\tTipo: Administrador\n\n");
            }else{
                printf("\tTipo: Avaliador\n\n");
            }   
        }else{
            aux = aux->next;
        }
    }
    if(aux == NULL && strcmp(aux->data.nome, userInput) != 0){
        printf("\n\tUtilizador não foi encontrado\n\n");
    }
}

void imprimirListaUtilizadores() {
    struct nodeUser *aux;
    printf("/------------- Lista de Utilizadores -----------/\n");
    if (headUsers == NULL) {
        printf("\nLista vazia\n\n");
    } else {
        aux = headUsers;
        printf("\n\tUsername\tTipo \n\n");
        while(aux != NULL) {
            printf("\t%s\t%c\n", aux->data.username, aux->data.tipo);
            aux = aux->next;
        }
    }
    printf("\n");
}



int main () {

    setlocale(LC_ALL ,"Portuguese");
    
    //Declaração das variaveis
    FILE *fusers;
    


    //Abertura e verificação do ficheiro binário
    if((fusers = fopen("Dados_Utilizadores.dat", "a+b")) == NULL){
        printf("Erro na abertura do ficheiro binario!!!\n");
        exit(EXIT_FAILURE);
    }
    
    numUtilizadoresRegistrados(fusers);

    //Declaração da estrutura de utilizadores e do superutilizador
    UTILIZADOR utilizadores, superuser = {
        .nome = "Superuser\0",
        .username = "Superuser\0",
        .password = "Passwd123!\0",
        .tipo = 'a',
    };

    inserirSuperUtilizador(superuser); //Adicionar o superutilizador a lista de utilizadores

    //Loop do Menu
    int opAdmin, opAvali; //Variaveis que armazenam a opção dos administradores e avaliadores respetivamente
    char tipo_utilizador;
    
    while(1){
        do{
            tipo_utilizador = loginForm();
        } while (tipo_utilizador == 'i');
        switch (tipo_utilizador){
        //Menu e submenus reservados ao administrador
            case 'a':
                while (1){ 
                    opAdmin = menuAdministrador();
                    if(opAdmin == 4) break;
                    switch (opAdmin){
                    case 1:
                        while (1){
                            int opcao = menuGestaoUtilizadores();
                            if(opcao == 0) break;
                            switch (opcao){
                            case 1:
                                inserirUtilizador(fusers);
                                break;
                            case 2:
                                editarUtilizador(headUsers);
                                break;
                            case 3:
                                apagarUtilizador(headUsers);
                                break;
                            case 4:
                                pesquisarUtilizador(headUsers);
                                break;
                            case 5:
                                imprimirListaUtilizadores();
                                break;
                            case 0:
                                fclose(fusers);
                                break;
                            default:
                                break;
                            }
                        }
                        break;
                    case 2:
                        while(1){
                            int opcao;
                            opcao = menuGestaoPropriedades();
                            if(opcao == 0) break;
                            switch (opcao){
                                case 0:
                                    break;
                            }
                        }
                        break;
                    case 0:
                        printf("\tPrograma encerrado!!!\n");
                        fclose(fusers);
                        exit(0);
                        break;
                    default:
                        break;
                    }
                }
                //Menu e submenus reservados aos avaliadores
            case 'e':

                break;

            default:
                break;
            };
    }
    
    return 0;
}