#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int linha;
    int coluna;
    int valor;
    struct No *prox;
} No;

No *ini;
No *atual;

void inserir() {
    int linha, coluna, valor;

    printf("Digite a linha, coluna e valor do veiculo: ");
    scanf("%i %i %i", &linha, &coluna, &valor);

    if (valor == 0) {
        printf("valor 0 representa posicao vazia, nada foi inserido\n");
        return;
    }

    No *novo = (No *)calloc(1, sizeof(No));

    novo->linha = linha;
    novo->coluna = coluna;
    novo->valor = valor;

    if (ini == NULL) {
        ini = novo;
        atual = novo;
    } else {
        atual->prox = novo;
        atual = atual->prox;
    }
}

void consultar() {
    int linha, coluna;
    No *aux = ini;
    printf("insira a linha e a coluna a serem pesquisadas: ");
    scanf("%i %i", &linha, &coluna);

    while (aux != NULL) {
        if (aux->linha == linha && aux->coluna == coluna) {
            printf("o valor pesquisado eh: %i\n", aux->valor);
            return;
        } else {
            aux = aux->prox;
        }
    }
    printf("posicao vazia\n");
}

void contador() {
    int c = 0;
    No *aux = ini;
    while (aux != NULL) {
        c++;
        aux = aux->prox;
    }
    printf("numero de carros encontrados: %i\n", c);
}

void remover() {
    int linha, coluna;
    No *aux = ini;
    No *ant = NULL;
    printf("insira a linha e a coluna a serem apagadas: ");
    scanf("%i %i", &linha, &coluna);

    while (aux != NULL) {
        if (aux->linha == linha && aux->coluna == coluna) {
            if (ant == NULL) {
                ini = aux->prox;
            } else {
                ant->prox = aux->prox;
            }
            if (aux == atual) {
                atual = ant;
            }
            free(aux);
            return;
        } else {
            ant = aux;
            aux = aux->prox;
        }
    }
    printf("nenhum veiculo nessa posicao\n");
}

void exibir() {
    printf("\n--- MAPA DO ESTACIONAMENTO (10x10) ---\n\n");
    for (int l = 0; l < 10; l++) {
        for (int c = 0; c < 10; c++) {
            No *aux = ini;

            while (aux != NULL) {
                if (aux->linha == l && aux->coluna == c) {
                    printf("%i\t", aux->valor);
                    break;
                }
                aux = aux->prox;
            }

            if (aux == NULL) {
                printf("0\t");
            }
        }
        printf("\n");
    }
}

void liberar() {
    No *aux = ini;
    while (aux != NULL) {
        No *prox = aux->prox;
        free(aux);
        aux = prox;
    }
    ini = NULL;
    atual = NULL;
}

int main() {
    int esc;
    do {
        printf("\nESCOLHA A OPCAO DESEJADA:\n");
        printf("1 - Inserir veiculo\n");
        printf("2 - Consultar posicao\n");
        printf("3 - Remover veiculo\n");
        printf("4 - Contar veiculos\n");
        printf("5 - Exibir matriz 10x10\n");
        printf("6 - Sair\n");
        printf("Opcao: ");
        scanf("%i", &esc);

        switch (esc) {
            case 1:
                inserir();
                break;
            case 2:
                consultar();
                break;
            case 3:
                remover();
                break;
            case 4:
                contador();
                break;
            case 5:
                exibir();
                break;
            case 6:
                break;
            default:
                printf("opcao invalida\n");
                break;
        }
    } while (esc != 6);

    liberar();
    return 0;
}
