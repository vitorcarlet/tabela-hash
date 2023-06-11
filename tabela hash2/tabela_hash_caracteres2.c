#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#define TAM 53

typedef struct nodo {
    struct nodo *proximo;
    struct nodo *anterior;
    char nome[50];
} Nodo;

typedef struct sLista {
    struct nodo *inicio;
    struct nodo *final;
    int tam;
} Lista;

void inicializarLista(Lista *lista);
void inserir_na_lista(Lista *lista, char nome[]);
bool remover(Lista *lista, char nome[]);
void remover_da_lista(Lista t[], char nome[]);
int inserir_na_lista_com_retorno(Lista *lista, char nome[]);
void imprimir_lista(Lista *lista);
void inicializarTabela(Lista t[]);
int funcaoHash(char nome[]);
char* buscar_na_lista(Lista *lista, char nome[]);
void busca(Lista t[], char nome[]);
void inserir_com_retorno(Lista t[], char nome[]);
void inserir(Lista t[], char nome[]);
void imprimirTabela(Lista t[]);
void troca(Nodo *a, Nodo *b);
Nodo *particao(Nodo *primeiro, Nodo *ultimo);
void quicksort(Nodo *primeiro, Nodo *ultimo);
void ordenarLista(Lista *lista);
void limpar_tela();
int naoDigiteNumeros(char opcao[]);
void exibirHistograma(Lista t[]);
void exportarTamanhoTabelas(Lista t[]);
void ContagemAlfabeto(Lista t[]);
void menu();

void inicializarLista(Lista *lista) {
    lista->inicio = NULL;
    lista->final = NULL;
    lista->tam = 0;
}

void inserir_na_lista(Lista *lista, char nome[]) {
    Nodo *nodo = malloc(sizeof(Nodo));

    if (nodo) {
        strcpy(nodo->nome, nome);
        nodo->proximo = NULL;
        nodo->anterior = NULL;

        if (lista->inicio == NULL) {
            lista->inicio = nodo;
            lista->final = nodo;
        } else {
            nodo->proximo = lista->inicio;
            lista->inicio->anterior = nodo;
            lista->inicio = nodo;
        }
        lista->tam++;
      
    } else {
        printf("\n\tErro ao alocar memória!\n");
      
    }
}

bool remover(Lista *lista, char nome[]) {
    Nodo *aux = lista->inicio;

    // Caso o nó a ser removido seja o primeiro da lista
    if (aux != NULL && strcmp(aux->nome, nome) == 0) {
        lista->inicio = aux->proximo;
        if (lista->inicio != NULL)
            lista->inicio->anterior = NULL;
        free(aux);
        lista->tam--;
        return true;
    }

    while (aux != NULL && strcmp(aux->nome, nome) != 0)
        aux = aux->proximo;

    // Caso o nó a ser removido esteja no meio ou no final da lista
    if (aux != NULL) {
        if (aux->anterior != NULL)
            aux->anterior->proximo = aux->proximo;
        if (aux->proximo != NULL)
            aux->proximo->anterior = aux->anterior;
        if (aux == lista->final)
            lista->final = aux->anterior;
        free(aux);
        lista->tam--;
        return true;
    }
    return false;
    }
    
    void remover_da_lista(Lista t[], char nome[]) {
    int id = funcaoHash(nome);
    if(remover(&t[id], nome)){
    	printf("%s removido com sucesso!\n", nome);
	}else{
		printf("%s Erro ao remover!\n", nome);
	}
    
}



int inserir_na_lista_com_retorno(Lista *lista, char nome[]) {
    Nodo *nodo = malloc(sizeof(Nodo));

    if (nodo) {
        for (int i = 0; i < strlen(nome); i++) {
            nodo->nome[i] = toupper(nome[i]);
        }
        nodo->nome[strlen(nome)] = '\0';  // Adicionar o caractere nulo no final da string
        nodo->proximo = NULL;
        nodo->anterior = NULL;

        if (lista->inicio == NULL) {
            lista->inicio = nodo;
            lista->final = nodo;
        } else {
            nodo->proximo = lista->inicio;
            lista->inicio->anterior = nodo;
            lista->inicio = nodo;
        }
        lista->tam++;
        return 1;
    } else {
        printf("\n\tErro ao alocar memória!\n");
        return 0;
    }
}



void imprimir_lista(Lista *lista) {
    Nodo *aux = lista->inicio;
    int cont=0;
    printf("\n\nTam: %d: ", lista->tam);
    while (aux && cont <=50 ) {
        printf("%s,", aux->nome);
        aux = aux->proximo;
        cont++;
    }
}

void inicializarTabela(Lista t[]) {
    int i;

    for (i = 0; i < TAM; i++) {
        inicializarLista(&t[i]);
    }
}
int funcaoHash(char nome[]) {
    int h = 0;
    for (int i = 0; i < strlen(nome); i++) {
            nome[i] = toupper(nome[i]);
        }
    for (int i = 0; i < strlen(nome); i++)
        h = (31 * h + nome[i]) % TAM;
    return h;
}

char* buscar_na_lista(Lista *lista, char nome[]) {
    Nodo *aux = lista->inicio;
    for (int i = 0; i < strlen(nome); i++) {
            nome[i] = toupper(nome[i]);
        }
    nome[strlen(nome)] = '\0';    
    while (aux && strcmp(aux->nome, nome) != 0)
        aux = aux->proximo;
    if (aux)
        return aux->nome;
        
    return NULL;
}

void busca(Lista t[], char nome[]) {
    int id = funcaoHash(nome);
    if(buscar_na_lista(&t[id], nome) != NULL){
        printf("%s foi encontrado na lista %d", nome,id);
    }else{
    	printf("%s não foi encontrado em nenhuma das listas.", nome);
	};
}


void inserir_com_retorno(Lista t[], char nome[]) {
    int id = funcaoHash(nome);
    if(inserir_na_lista_com_retorno(&t[id], nome)){
    	printf("%s foi inserido na lista %d da tabela hash", nome, id);
	}else{
		printf("não foi possível inserir o %s na tabela", nome);
	}
}

void inserir(Lista t[], char nome[]) {
    int id = funcaoHash(nome);
    inserir_na_lista(&t[id], nome);
}

void imprimirTabela(Lista t[]) {
    int i;
    for (i = 0; i < TAM; i++) {
        printf("%d = ", i);
        imprimir_lista(&t[i]);
        printf("\n");
    }
}

void troca(Nodo *a, Nodo *b) {
    char temp[50];
    strcpy(temp, a->nome);
    strcpy(a->nome, b->nome);
    strcpy(b->nome, temp);
}

Nodo *particao(Nodo *primeiro, Nodo *ultimo) {
    char* pivot = primeiro->nome;
    Nodo *i = primeiro->proximo;
    Nodo *j = ultimo;

    while (i != j->proximo) {
        while (i != j->proximo && strcmp(i->nome, pivot) <= 0)
            i = i->proximo;
        while (j != primeiro && strcmp(j->nome, pivot) > 0)
            j = j->anterior;

        if (i != j->proximo)
            troca(i, j);
    }

    troca(primeiro, j);

    return j;
}

void quicksort(Nodo *primeiro, Nodo *ultimo) {
    if (primeiro != NULL && ultimo != NULL && primeiro != ultimo && primeiro != ultimo->proximo) {
        Nodo *pivot = particao(primeiro, ultimo);
        quicksort(primeiro, pivot->anterior);
        quicksort(pivot->proximo, ultimo);
    }
}

void ordenarLista(Lista *lista) {
    quicksort(lista->inicio, lista->final);
}

void limpar_tela() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

int naoDigiteNumeros(char opcao[]){
	int i, isOnlyNonNumeric = 1;
    for (i = 0; opcao[i] != '\0'; i++) {
        if (isdigit(opcao[i])) {
            isOnlyNonNumeric = 0;
            return 0;
        }
    }

    if (isOnlyNonNumeric) {
        return 1;
    } else {
        printf("Opção inválida. Digite apenas caracteres não numéricos.\n");
    }

}




void exibirHistograma(Lista t[]) {
    int i, j;
    int maxCount = 0;
    int setNum = 15;

    // Encontrar o tamanho máximo das listas
    for (i = 0; i < TAM; i++) {
        if (t[i].tam > maxCount) {
            maxCount = t[i].tam;
        }
    }

    // Exibir o histograma
    printf("Histograma dos números das listas hash:\n");
    for (i = maxCount; i > 0; i -= 50) {
    	if(i < 100)
        printf("%2d   |", i);
        
        if(i >100 && i < 1000)
        printf("%2d  |", i);
        
        if(i > 1000 )
        printf("%2d |", i);

        for (j = 0; j < setNum; j++) {
            if (t[j].tam >= i) {
                printf("  *  ");
            } else {
                printf("     ");
            }
        }

        printf("\n");
    }

    printf("      ");
    for (i = 0; i < setNum; i++) {
        printf("----");
    }
    printf("\n");

    printf("    ");
    for (i = 0; i < setNum; i++) {
        printf("  %2d  ", i);
    }
    printf("\n");
}

void exportarTamanhoTabelas(Lista t[]) {
    FILE *arquivo;
    arquivo = fopen("tamanhos_tabelas.csv", "w");

    if (arquivo == NULL) {
        printf("Erro ao criar arquivo.\n");
        return;
    }

    fprintf(arquivo, "Tabela,Tamanho\n");

    for (int i = 0; i < TAM; i++) {
        fprintf(arquivo, "%d\n", t[i].tam);
    }

    fclose(arquivo);

    printf("Arquivo 'tamanhos_tabelas.csv' criado com sucesso!\n");
}

void ContagemAlfabeto(Lista t[]) {
    int contagem[26] = {0};  // Array para armazenar a contagem de elementos para cada letra do alfabeto

    // Percorre todas as listas e conta quantos elementos começam com cada letra
    for (int i = 0; i < TAM; i++) {
        Nodo *aux = t[i].inicio;
        while (aux != NULL) {
        	char primeiraLetra = aux->nome[0];
            if (primeiraLetra >= 'A' && primeiraLetra <= 'Z') {
                contagem[primeiraLetra - 'A']++;
            }
            aux = aux->proximo;
        }
    }

    // Exibe a tabela com as letras e a contagem
    printf("Tabela de Contagem de Elementos por Letra:\n");
    for (int i = 0; i < 26; i++) {
        printf("%c: %d\n", 'A' + i, contagem[i]);
    }
}




void menu() {
    printf("*********** TABELA HASH ***********\n");
    printf("1. Inserir nome\n");
    printf("2. Remover Nome\n");
    printf("3. Buscar nome\n");
    printf("4. Imprimir listas\n");
    printf("5. Ordenar listas\n");
    printf("6. Exibir Histograma\n");
     printf("7. Exportar Tamanho das Tabelas para arquivo .csv\n");
     printf("8. Exibir tabela de contagem por letra do alfabeto\n");
     printf("9. Sair\n");
    printf("************************************\n");
}

int main() {
    //srand(time(NULL));

    Lista tabela[TAM];
    inicializarTabela(tabela);

    FILE *arquivo;
    char linha[50];
    int verifica=0;
    arquivo = fopen("nomes.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';
        inserir(tabela, linha);
    }

    fclose(arquivo);
    

    int escolha=0;
    char nome[50];

    do {
        limpar_tela();
        menu();
   
       
        printf("Escolha uma opção: ");
		scanf("%d", &escolha);
	

        switch (escolha) {
            case 1:
                limpar_tela();
                verifica = 0;
                while(verifica == 0){
                    printf("Digite o nome para inserir: ");
                    scanf("%s", nome);
                    verifica = naoDigiteNumeros(nome);
                }
                inserir_com_retorno(tabela, nome);
                break;
            case 2:
			    limpar_tela();
			    verifica = 0;
			    while (verifica == 0) {
			        printf("Digite o nome que deseja remover: ");
			        scanf("%s", nome);
			        verifica = naoDigiteNumeros(nome);
			    }
			    remover_da_lista(tabela, nome);
			    
			    break;
            case 3:
                limpar_tela();
                verifica = 0;
                while(verifica == 0){
                    printf("Digite o nome que deseja buscar: ");
                    scanf("%s", nome);
                    verifica = naoDigiteNumeros(nome);
                }
            	busca(tabela,nome);
                break;    
            case 4:
                limpar_tela();
                imprimirTabela(tabela);
                break;
            case 5:
                limpar_tela();
                for (int i = 0; i < TAM; i++) {
                    ordenarLista(&tabela[i]);
                }
                printf("Listas ordenadas!\n");
                break;
            case 6:
                limpar_tela();
				exibirHistograma(tabela);             
                break;
            case 7: {
                exportarTamanhoTabelas(tabela);
                break;
            }
			case 8:
			    limpar_tela();
			    ContagemAlfabeto(tabela);
			    break;    
            case 9:
                limpar_tela();
                printf("Encerrando o programa...\n");
                break;
            default:
                limpar_tela();
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
        

        printf("\nPressione ENTER para continuar...");
        getchar();
        getchar();

    } while (escolha != 9);

    return 0;
}
