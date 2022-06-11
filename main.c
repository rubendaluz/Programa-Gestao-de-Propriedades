#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//maximo de culturas por propriedade
#define MAX_CT 20 
#define ID 10000
//Declaração das estruturas
typedef struct utilizador{
    char nome[20];
    char username[20];
    char password[20];
    char tipo; // a/A->administrador e e/E->(evaluator)avaliador
}UTILIZADOR;

typedef struct cultura{
    char nome[15];
    char descricao[50];
    float area_cultivo;
}CULTURA;

typedef struct propAvaliada
{
    float valAvaliacao;
    //date
    char avaliador[20];
}PROP_AVALIADA;

typedef struct propriedade{
    int numero, identificador;
    char nome_proprietario[20];
    char descricao[50];
    float area;
    CULTURA culturas[MAX_CT];
    int numCulturas;
    char estado[15];
    PROP_AVALIADA propAvaliada;
}PROPRIEDADE;

//Criação da lista ligada de utilizadores
struct nodeUser {
    UTILIZADOR data;
    struct nodeUser *next;
};

struct nodeUser *headUsers = NULL;

//Lista de propriedades
struct nodeProp {
    PROPRIEDADE data;
    struct nodeProp *next;
};

struct nodeProp *headProps = NULL;
//Fila de propriedades a avaliar

struct queue{
	struct node *front;
	struct node *rear;
};

struct queue *fila;


void headerListaPropsAvaliar(FILE *out){
    fprintf(out, "\t+---+--------------------+--------------+\n");
    fprintf(out, "\t|Num|Proprietario        |Identificador |\n");
    fprintf(out, "\t+---+--------------------+--------------+\n");
}

void footerListaPropsAvaliar(FILE *out){
    fprintf(out, "\t+---+--------------------+--------------+\n");
}


//Funcões e procedimentos

char loginForm(){
    struct nodeUser *aux; 
    UTILIZADOR input;
    int sair;
    aux = headUsers;
    system("cls");
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
                printf("\tDeseja sair (0-Nao | 1-Sim): ");
                scanf("%d", &sair);
                if(sair == 1){
                    exit(0);
                }
                return 'i';
            }
        }else if((strcmp(aux->data.username, input.username)) != 0){
            aux = aux->next;
        }else{
            return 'i';
        }
    }
    printf("\n\tUtilizador inexistente\n\n");
    printf("\tDeseja sair (0-Nao | 1-Sim): ");
    scanf("%d", &sair);
    if(sair == 1){
        exit(0);
    }
}   

int menuAdministrador(){
    int opcao;
    system("cls");
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
    system("cls");
    printf("/------- GERENCIADOR DE UTILIZADORES -------/\n\n");
    printf("\t1-Inserir novo utilizador.\n");
    printf("\t2-Listar utilizadores inseridos.\n");
    printf("\t0-Sair\n\n");

    printf("Digite>> "); scanf(" %d", &opcao); //Leitura da opção do utilizaddor
    printf("\n");
    return opcao;
}

int menuGestaoPropriedades(){
    int opcao;
    system("cls");
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

int menuInfoPropriedades(){
    int opcao;
    system("cls");
    printf("/------------ INFORMACAO/RELATORIOS DAS PROPRIEDADES -----------/\n\n");
    printf("\t1-Propriedades por analisar.\n");
    printf("\t2-Propriedades avaliadas.\n");
    printf("\t3-Listar propriedades por avaliador.\n");
    printf("\t4-Pesquisar propriedades (Proprietario).\n");
    printf("\t5-Exportar relatorio das propriedades avaliadas.\n");
    printf("\t6-Ranking de utilizadores.\n");
    printf("\t0-Sair\n\n");

    printf("Digite>> "); scanf(" %d", &opcao); //Leitura da opção do utilizaddor
    printf("\n");
    return opcao;
}

/***********Funções reservadas aos Administradores***************/

int numUtilizadoresRegistados(FILE *fp){
    rewind(fp);
    int num;
    fseek(fp,0L,SEEK_END);
    num = ftell(fp) / sizeof(UTILIZADOR);
    return num;
}

void lerUtilizadoresFicheiro(FILE *fp, UTILIZADOR utilizadores[], int qtdusers){
    rewind(fp);
    if(qtdusers != 0){
        fseek(fp,0L,SEEK_SET);
        for(int i = 0; i < qtdusers; ++i){
            fread(utilizadores,sizeof(UTILIZADOR),qtdusers,fp);
        }
    }
}

void salvarUtilizadorFich(UTILIZADOR utilizador,FILE *fp){
    fseek(fp,0L,SEEK_END);
    if((fwrite(&utilizador,sizeof(UTILIZADOR),1,fp)) != 1){
        printf("\tErro ao guardar os dados do utilizador.\n");
    }
}

UTILIZADOR inserirDadosUtilizador(){
    UTILIZADOR utilizador;
    printf("\tNome: ");
    fflush(stdin);
    gets(utilizador.nome);
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
    int success, sair;
    novo = (struct nodeUser*) malloc(sizeof(struct nodeUser));
    system("cls");
    printf("/------------ INSERIR UTILIZADOR -----------/\n\n");
    do{
        novo->data = inserirDadosUtilizador();
        aux = headUsers;
        while (aux != NULL){
            if((strcmp(aux->data.username, novo->data.username)) == 0 ){
                printf("\n\tO username inserido ja exite.\n");
                system("pause");
                success = 0;
                break;
            }else{
                aux = aux->next;
                success = 1;
            }
        }
        if(success == 0){
            printf("\n\tQuer sair (0-Nao | 1-Sim): ");
            scanf("%d", &sair);
            printf("\n");
        } else{
            sair = 1;
        }
        if (sair == 1) break;
    } while(success == 0 || sair == 0);

    if (success == 1){
         printf("\n");
        novo->next = NULL;
        aux = headUsers;
        while (aux->next != NULL){
            aux = aux->next;
        }
        aux->next = novo;
        salvarUtilizadorFich(novo->data,fp);
    }
   
}

void inserirSuperUtilizador(UTILIZADOR utilizador) {
    struct nodeUser *novo;
    novo = (struct nodeUser*) malloc(sizeof(struct nodeUser));
    novo->data = utilizador;
    novo->next = headUsers;
    headUsers = novo;
}

void imprimirListaUtilizadores() {
    struct nodeUser *aux;
    printf("/------------- LISTA DE UTILIZADORES -----------/\n");
    if (headUsers == NULL) {
        printf("\nLista vazia\n\n");
    } else {
        aux = headUsers;
        printf("\n\tUsername\t\tTipo \n\n");
        while(aux != NULL) {
            printf("\t%-20s", aux->data.nome);
            if(aux->data.tipo == 'a'){
                printf("\tAdministrador\n");
            }else if(aux->data.tipo == 'e'){
                printf("\tAvaliador\n");
            }
            aux = aux->next;
        }
    }
    printf("\n");
}

//Funções reservadas ao Gereciador de Propriedades
int numPropriedadesRegistadas(FILE *fp){
    int num;
    fseek(fp,0L,SEEK_END);
    num = ftell(fp) / sizeof(PROPRIEDADE);
    printf("%d", num);
    return num;
}

void lerPropriedadesFicheiro(FILE *fp, PROPRIEDADE propriedades[], int qtdprops){
    rewind(fp);
    if(qtdprops != 0){
        fseek(fp,0L,SEEK_SET);
        for(int i = 0; i < qtdprops; ++i){
            fread(propriedades,sizeof(PROPRIEDADE),qtdprops,fp);
        }
    }
}

PROPRIEDADE inserirDadosPropriedade(FILE *fp){
    int resp;
    PROPRIEDADE propriedade;
    propriedade.numero = numPropriedadesRegistadas(fp) + 1;
    printf("\tProprietario: ");
    fflush(stdin);
    gets(propriedade.nome_proprietario);
    printf("\tDescricao: ");
    fflush(stdin);
    gets(propriedade.descricao);
    printf("\tArea: ");
    scanf("%f", &propriedade.area);
    printf("\nPretende adicionar culturas (0-Nao | 1-Sim):");
    scanf("%d", &resp);
    if(resp == 1){
        int i = 0; //index
        int cont; //Saber se o utilizador quer continuar (0-Nao e 1-Sim)
        do{
           printf("\n\tInsira os dados da cultura [%d]\n\n", (i+1));
           printf("\tNome da cultura: ");
           scanf("%s", propriedade.culturas[i].nome);
           printf("\tDescricao: ");
           fflush(stdin);
           gets(propriedade.culturas[i].descricao);
           printf("\tArea de cultivo: ");
           scanf("%f", &propriedade.culturas[i].area_cultivo);
           propriedade.numCulturas = i+1;
           ++i;
           printf("\nPretende adicionar mais (0-Nao | 1-Sim): ");
           scanf("%d", &cont);
        }while(i < MAX_CT && cont == 1);
    } else if(resp == 0){
        propriedade.numCulturas = 0;
    }
    strcpy(propriedade.estado, "nao avaliado");

    printf("\n");
    return propriedade;
}

void salvarPropriedadeFich(PROPRIEDADE propriedade,FILE *fp){
    fseek(fp,0L,SEEK_END);
    if((fwrite(&propriedade,sizeof(PROPRIEDADE),1,fp)) != 1){
        printf("\tErro ao guardar os dados da propriedade.\n");
    }
}



void inserirPropriedade(FILE *fp){
    PROPRIEDADE propriedade;
    struct nodeProp *novo, *aux;
    novo = (struct nodeProp*) malloc(sizeof(struct nodeProp));
    system("cls");
    printf("/------------ INSERIR PROPRIEDADE -----------/\n\n");
    novo->data = inserirDadosPropriedade(fp);
    novo->data.identificador = ID + novo->data.numero;
    novo->next = NULL;
    if(headProps == NULL){
		headProps = novo;
	}else{
		aux = headProps;
		while(aux->next != NULL){
			aux = aux->next;
		}
		aux->next = novo;
	}
    salvarPropriedadeFich(novo->data,fp);
}

void editarPropriedade(FILE *fp){
	struct nodeProp *aux;
	int userInput;
    system("cls");
    printf("/------------- EDITAR UTILIZADOR -----------/\n\n");
	printf("\tInsira o identificador : ");
	scanf("%d", userInput);
	aux = headProps;
    while(aux != NULL){
        if(userInput == aux->data.identificador){
            printf("\nInsira os novos dados do utilizador\n\n");
            aux->data = inserirDadosPropriedade(fp);
            printf("\n\tDados atualizados\n\n");
            break;
        }else{
            aux = aux->next;
        }
    }
    if(aux == NULL && userInput != aux->data.identificador){
        printf("\n\tPropriedade não foi encontrada\n\n");
    }
}

void pesquisarPropriedade(){
	struct nodeProp *aux;
	char userInput[20];
    system("cls");
    printf("/----------- PESQUISAR PROPRIEDADE ---------/\n\n");
	printf("\tInsira o nome do proprietario : ");
    fflush(stdin);
	gets(userInput);
	aux = headProps;
    while(aux != NULL){
        if(strcmp(aux->data.nome_proprietario, userInput) == 0){
            printf("\n\tINFORMACOES DA PROPRIEDADE:\n\n");
            printf("\tPropriedade n.%d\n", aux->data.numero);
            printf("\tIdentificador: \t%d\n", aux->data.identificador);
            printf("\tProprietario: \t%s\n", aux->data.nome_proprietario);
            printf("\tDescricao: \t%s\n", aux->data.descricao);
            printf("\tArea: \t%.1f m2\n", aux->data.area);
            printf("\tNumero de culturas cultivadas: \t%d\n", aux->data.numCulturas);
            printf("\tCulturas cultivadas: \t");
            if(aux->data.numCulturas != 0){
                for(int i = 0; i < aux->data.numCulturas;++i){
                printf("%s ", aux->data.culturas[i].nome);
                }
            }else{
                printf("A propriedade carece de culturas cultivadas.");
            }
            
            printf("\n\tEstado de avaliacao: %s\n", aux->data.estado); 
            aux = aux->next;
        } else if(aux == NULL && strcmp(aux->data.nome_proprietario, userInput) != 0)
        {
            printf("\n\tPropriedade não foi encontrada\n\n");
        }
        printf("\n");
        system("pause");
    }
}

void imprimirListaPropriedades(){ //Usar esqueleto para outras funções
	struct nodeProp *aux;
	aux = headProps;
	printf("/-----------LISTA DE PROPRIEDADES --------------/\n\n");
    if(aux == NULL){
        printf("\tNao existem quaisquer propriedades!!!\n\n");
    }else{
        headerListaPropsAvaliar(stdout);
	    while(aux != NULL){
            printf("\t|%-3d|%-14s|%-14d|\n", aux->data.numero, aux->data.nome_proprietario, aux->data.identificador);
		    aux = aux->next;
	    }
        footerListaPropsAvaliar(stdout);
    }
    system("pause");
}

void imprimirListaPropriedadesAvaliar(){ //Usar esqueleto para outras funções
	struct nodeProp *aux;
	aux = headProps;
	printf("/-----------LISTA DE PROPRIEDADES A AVALIAR --------------/\n\n");
    headerListaPropsAvaliar(stdout);
	while(aux != NULL){
		if ((strcmp(aux->data.estado, "nao avaliado")) == 0){
            printf("\t|%-3d|%-20s|%-14d|\n", aux->data.numero, aux->data.nome_proprietario, aux->data.identificador);
        } else {
            printf("\tNao existem quaisquer propriedades por avaliar!!!\n\n");
        }
		aux = aux->next;
	}
    footerListaPropsAvaliar(stdout);
    system("pause");
}

// Funções reservadas para os Avaliadores

int menuAvaliadores(){
    int opcao;
    system("cls");
    printf("/------------------- MENU DE AVALIADOR -------------------/\n\n");
    printf("\t1-Adicionar propriedade a lista para avaliar.\n");
    printf("\t2-Avaliar propriedades da lista.\n");
    printf("\t2-Voltar ao Formulario de login.\n");
    printf("\t0-Encerrar o programa.\n\n");

    printf("Digite>> "); scanf(" %d", &opcao); //Leitura da opção do utilizaddor
    printf("\n");
    return opcao;
}

void FilaPropriedadesAvaliar(){
    fila = (struct queue*) malloc(sizeof(struct queue)); 
    fila->front = NULL; 
    fila->rear = NULL;
}



int main () {

    setlocale(LC_ALL ,"Portuguese");
    
    //Declaração das variaveis
    FILE *fusers;
    FILE *fprops;
    


    //Abertura e verificação do ficheiro binário
    if((fusers = fopen("Dados_Utilizadores.dat", "a+b")) == NULL){
        printf("Erro na abertura do ficheiro que guarda os dados dos utilizadores!!!\n");
        exit(EXIT_FAILURE);
    }

    if((fprops = fopen("Dados_Propriedades.dat", "a+b")) == NULL){
        printf("Erro na abertura do ficheiro que guarda os dados das Propriedades!!!\n");
        exit(EXIT_FAILURE);
    }

    int qtdusers = numUtilizadoresRegistados(fusers);
    
    //Declaração da estrutura do superutilizador
    UTILIZADOR utilizadores[qtdusers], superuser = {
        .nome = "Superuser\0",
        .username = "Superuser\0",
        .password = "Passwd123!\0",
        .tipo = 'a',
    };

    inserirSuperUtilizador(superuser); //Adicionar o superutilizador a lista de utilizadores

    lerUtilizadoresFicheiro(fusers, utilizadores,qtdusers); //Atualizar lista de utilizadores com os que estão salvos no ficheiro
    for (int i = 0; i < qtdusers;++i){
        struct nodeUser *novo, *aux;
        novo = (struct nodeUser*) malloc(sizeof(struct nodeUser));
        novo->data = utilizadores[i];
        novo->next = NULL;
        aux = headUsers;
        while (aux->next != NULL){
            aux = aux->next;
        }
        aux->next = novo;

    }

    int qtdprops = numPropriedadesRegistadas(fprops);
    PROPRIEDADE propriedades[qtdprops];

    lerPropriedadesFicheiro(fusers,propriedades, qtdprops);
    for (int i = 0; i < qtdusers;++i){
        struct nodeProp *novo, *aux;
        novo = (struct nodeProp*) malloc(sizeof(struct nodeProp));
        novo->data = propriedades[i];
        novo->next = NULL;
        if(headProps == NULL){
            headProps = novo;
        }else{
            aux = headProps;
            while(aux->next != NULL){
                aux = aux->next;
            }
            aux->next = novo;
        }
    }

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
                            switch (opcao){
                            case 1:
                                inserirUtilizador(fusers);
                                break;
                            case 2:
                                imprimirListaUtilizadores();
                                system("pause");
                                break;
                            case 0:
                                fclose(fusers);
                                break;
                            default:
                                printf("\tOpcao invalida!!! Tente novamente\n");
                                break;
                            }
                            if(opcao == 0) break;
                        }
                        break;
                    case 2:
                        while(1){
                            int opcao;
                            opcao = menuGestaoPropriedades();
                            switch (opcao){
                                case 1:
                                    inserirPropriedade(fprops);
                                    break;
                                case 2:
                                    editarPropriedade(fprops);
                                    break;
                                case 3:
                                    //apagarPropriedade();
                                    break;
                                case 4:
                                    imprimirListaPropriedades();
                                    break;
                                case 0:
                                    fclose(fprops);
                                    break;
                                default:
                                    printf("\tOpcao invalida!!! Tente novamente\n");
                                    break;
                            }
                            if(opcao == 0) break;
                        }
                        break;
                    case 3:
                        while (1){
                            int opcao;
                            opcao = menuInfoPropriedades();
                            if(opcao == 0) break;
                            switch (opcao){
                                case 1:
                                    imprimirListaPropriedadesAvaliar();
                                    break;
                                case 4:
                                    pesquisarPropriedade();
                                    break;
                            }
                        }
                        
                        break;
                    case 0:
                        printf("\tPrograma encerrado!!!\n");
                        exit(0);
                        break;
                    default:
                        printf("\tOpcao invalida!!! Tente novamente\n");
                        break;
                    }
                }
                break;
                //Menu e submenus reservados aos avaliadores
            case 'e':
                while (1){
                    int opcao;
                    opcao = menuAvaliadores();
                    if (opcao == 3)break;
                    switch (opcao){
                    case 1:
                        break;
                    case 0:
                        exit(EXIT_SUCCESS);
                        break;
                    default:
                        printf("\tOpcao invalida!!! Tente novamente\n");
                        break;
                    }
                }
                break;
        }
    }
    return 0;
}