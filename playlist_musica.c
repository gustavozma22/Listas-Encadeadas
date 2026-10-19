#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i, x, escolha; // declarando as variaveis globais utilizadas no algoritmo

typedef struct Musica {
    char cantor[50];
    char cancao[50];
    struct Musica *ant;
    struct Musica *prox;
} Musica;

Musica *ini;
Musica *atual;

void AddMusica() {
    Musica *novo = (Musica *)calloc(1, sizeof(Musica));
    if (novo == NULL) {
        printf("erro ao alocar memoria \n");
        return;
    }
    printf("insira o cantor que vai ouvir \n");
    fflush(stdin);
    fgets(novo->cantor, 50, stdin);
    novo->cantor[strcspn(novo->cantor, "\n")] = '\0';

    printf("insira a cancao que vai ouvir \n");
    fflush(stdin);
    fgets(novo->cancao, 50, stdin);
    novo->cancao[strcspn(novo->cancao, "\n")] = '\0';

    if (ini == NULL) {
        ini = novo;
        atual = ini;
        return;
    }

    Musica *aux = ini;
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    novo->ant = aux;
    novo->prox = NULL;
    aux->prox = novo;
}

void RELATORIO() {
    Musica *aux = ini;
    while (aux != NULL) {
        if (atual == aux) {
            printf("ATUAL -> %s de %s", aux->cancao, aux->cantor);
        } else {
            printf("%s de %s", aux->cancao, aux->cantor);
        }
        printf("\n");
        aux = aux->prox;
    }
}

void VOLTAR() {
    Musica *aux = ini;
    while (aux != NULL) {
        if (atual == aux) {
            if (atual->ant == NULL) {
                return;
            }
            atual = atual->ant;
            return;
        }
        aux = aux->prox;
    }
}

void AVANCAR() {
    Musica *aux = ini;
    while (aux != NULL) {
        if (atual == aux) {
            if (atual->prox == NULL) {
                return;
            }
            atual = atual->prox;
            return;
        }
        aux = aux->prox;
    }
}

void FREE() {
    Musica *aux = ini;
    while (aux != NULL) {
        Musica *proximo = aux->prox;
        free(aux);
        aux = proximo;
    }
}

void deletar() {
    char nome[50];
    printf("Digite o nome da musica que deseja remover: ");
    fflush(stdin);
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    Musica *aux = ini;
    while (aux != NULL) {
        if (strcmp(nome, aux->cancao) == 0) {
            if (aux->prox == NULL && aux->ant == NULL) {
                ini = NULL;
                atual = NULL;
                free(aux);
                return;
            }
            if (aux == ini) {
                ini = aux->prox;
                ini->ant = NULL;
                if (aux == atual) {
                    atual = ini;
                }
                free(aux);
                return;
            } else if (aux->prox == NULL) {
                aux->ant->prox = NULL;
                if (aux == atual) {
                    atual = aux->ant;
                }
                free(aux);
                return;
            } else if (aux == atual) {
                atual = aux->ant;
                aux->ant->prox = aux->prox;
                aux->prox->ant = aux->ant;
                free(aux);
                return;
            }
            aux->ant->prox = aux->prox;
            aux->prox->ant = aux->ant;
            free(aux);
            return;
        } else {
            aux = aux->prox;
        }
    }
}

int main() {
    do { // abre loop para exibicao do menu principal
        printf("ESCOLHA A OPCAO DESEJADA: \n 1- ADICIONAR MUSICA \n 2- VOLTAR \n 3- AVANCAR \n 4- PLAYLIST \n 5- REMOVER MUSICA \n 6- SAIR \n");
        printf("selecione a opcao desejada: \n");
        fflush(stdin);
        scanf("%i", &escolha); // atribui a opcao desejada a variavel escolha
        while (getchar() != '\n' && !feof(stdin)); // CORRECAO: limpa o \n deixado pelo scanf, senao o proximo fgets le uma linha vazia

        switch (escolha) { // condicional para direcionar a opcao escolhida no menu
            case 1:
                AddMusica();
                break;
            case 2:
                VOLTAR();
                break;
            case 3:
                AVANCAR();
                break;
            case 4:
                RELATORIO();
                break;
            case 5:
                deletar();
                break;
            case 6:
                FREE();
                printf("saindo do programa...\n");
                break;
            default:
                printf("opcao invalida!!! \n");
                break;
        }
    } while (escolha != 6);

    return 0;
}
