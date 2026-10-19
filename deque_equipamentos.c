#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int equipamento;
    struct No *prox;
    struct No *ant;
} No;

No *ini;
No *fim;

void inserirFim() {
    int equipamento;

    printf("Digite o equipamento: ");
    scanf("%i", &equipamento);
    No *novo = (No *)calloc(1, sizeof(No));

    novo->equipamento = equipamento;

    if (ini == NULL) {
        ini = novo;
        fim = novo;
        novo->ant = NULL;
    } else {
        fim->prox = novo;
        novo->ant = fim;
        fim = novo;
    }
}

void inserirInicio() {
    int equipamento;

    printf("Digite o equipamento: ");
    scanf("%i", &equipamento);
    No *novo = (No *)calloc(1, sizeof(No));

    novo->equipamento = equipamento;

    if (ini == NULL) {
        ini = novo;
        fim = novo;
        novo->ant = NULL;
    } else {
        ini->ant = novo;
        novo->prox = ini;
        ini = novo;
    }
}

void removerFim() {
    if (ini == NULL) {
        printf("fila vazia \n");
        return;
    }

    if (ini == fim) {
        printf("removido: %i\n", fim->equipamento);
        free(ini);
        ini = NULL;
        fim = NULL;
        return;
    }

    No *aux = fim;
    printf("removido: %i\n", aux->equipamento);
    fim = aux->ant;
    fim->prox = NULL;
    free(aux);
}

void removerInicio() {
    if (ini == NULL) {
        printf("fila vazia \n");
        return;
    }

    if (ini == fim) {
        printf("removido: %i\n", ini->equipamento);
        free(ini);
        ini = NULL;
        fim = NULL;
        return;
    }

    No *aux = ini;
    printf("removido: %i\n", aux->equipamento);
    ini = aux->prox;
    ini->ant = NULL;
    free(aux);
}

void consultInicio() {
    if (ini == NULL) {
        printf("fila vazia \n");
        return;
    } else {
        printf("O PRIMEIRO DA FILA EH: %i\n", ini->equipamento);
    }
}

void consultFim() {
    if (ini == NULL) {
        printf("fila vazia \n");
        return;
    } else {
        printf("O ULTIMO DA FILA EH: %i\n", fim->equipamento);
    }
}

void vazia() {
    if (ini == NULL) {
        printf("fila vazia \n");
        return;
    } else {
        printf("fila nao esta vazia\n");
    }
}

void exibirInicio() {
    No *aux = ini;
    while (aux != NULL) {
        printf("%i -> ", aux->equipamento);
        aux = aux->prox;
    }
    printf("NULL\n");
}

void exibirFim() {
    No *aux = fim;
    while (aux != NULL) {
        printf("%i -> ", aux->equipamento);
        aux = aux->ant;
    }
    printf("NULL\n");
}

void liberar() {
    No *aux = ini;
    while (aux != NULL) {
        No *prox = aux->prox;
        free(aux);
        aux = prox;
    }
    ini = NULL;
    fim = NULL;
}

int main() {
    int opcao;
    do {
        printf("\n=== MENU FILA DUPLAMENTE ENCADEADA (DEQUE) ===\n");
        printf("1. Inserir no Inicio\n");
        printf("2. Inserir no Fim\n");
        printf("3. Remover do Inicio\n");
        printf("4. Remover do Fim\n");
        printf("5. Consultar Inicio\n");
        printf("6. Consultar Fim\n");
        printf("7. Exibir do Inicio ao Fim\n");
        printf("8. Exibir do Fim ao Inicio\n");
        printf("9. Verificar se esta Vazia\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirInicio();
                break;
            case 2:
                inserirFim();
                break;
            case 3:
                removerInicio();
                break;
            case 4:
                removerFim();
                break;
            case 5:
                consultInicio();
                break;
            case 6:
                consultFim();
                break;
            case 7:
                exibirInicio();
                break;
            case 8:
                exibirFim();
                break;
            case 9:
                vazia();
                break;
            case 0:
                liberar();
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida! \n");
        }
    } while (opcao != 0);

    return 0;
}
