#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i, x, escolha; // declarando as variaveis globais utilizadas no algoritmo

typedef struct Site {
    char url[50];
    struct Site *ant;
    struct Site *prox;
} Site;

Site *ini;
Site *atual;

void WEB() {
    Site *novo = (Site *)calloc(1, sizeof(Site));
    if (novo == NULL) {
        printf("erro ao alocar memoria \n");
        return;
    }
    printf("insira o site que vai acessar \n");
    fflush(stdin);
    fgets(novo->url, 50, stdin);
    novo->url[strcspn(novo->url, "\n")] = '\0';

    if (ini == NULL) {
        ini = novo;
        atual = ini;
        return;
    }

    // ao visitar uma pagina nova estando "no meio" do historico, tudo que esta a frente
    // do ponteiro atual precisa ser descartado (liberado da memoria) antes de encaixar a nova pagina
    if (atual->prox != NULL) {
        Site *lixo = atual->prox;
        while (lixo != NULL) {
            Site *proximoLixo = lixo->prox;
            free(lixo);
            lixo = proximoLixo;
        }
        atual->prox = NULL;
    }

    novo->ant = atual;
    novo->prox = NULL;
    atual->prox = novo;
    atual = novo;
}

void RELATORIO() {
    Site *aux = ini;
    while (aux != NULL) {
        if (atual == aux) {
            printf("ATUAL -> %s", aux->url);
        } else {
            printf("%s", aux->url);
        }
        printf("\n");
        aux = aux->prox;
    }
}

void VOLTAR() {
    Site *aux = ini;
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
    Site *aux = ini;
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
    Site *aux = ini;
    while (aux != NULL) {
        Site *proximo = aux->prox;
        free(aux);
        aux = proximo;
    }
}

int main() {
    do { // abre loop para exibicao do menu principal
        printf("ESCOLHA A OPCAO DESEJADA: \n 1- VISITAR PAG \n 2- VOLTAR \n 3- AVANCAR \n 4- RELATORIO \n 5- SAIR \n");
        printf("selecione a opcao desejada: \n");
        scanf("%i", &escolha); // atribui a opcao desejada a variavel escolha
        while (getchar() != '\n' && !feof(stdin)); // CORRECAO: limpa o \n deixado pelo scanf, senao o proximo fgets le uma linha vazia

        switch (escolha) { // condicional para direcionar a opcao escolhida no menu
            case 1:
                WEB();
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
                FREE();
                printf("saindo do programa...\n");
                break;
            default:
                printf("opcao invalida!!! \n");
                break;
        }
    } while (escolha != 5);

    return 0;
}
