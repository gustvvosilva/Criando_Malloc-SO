#include "lista.h"

LISTA *init_lista() {
    LISTA *nova = (LISTA *) aloca(sizeof(LISTA));
    nova->dado = 0;
    nova->prox = NULL;
    return nova;
}

void inserir(LISTA *lista, int dado) {

    // Primeiro nó.
    if(lista->prox == NULL && lista->dado == 0) {
        lista->dado = dado;
        return;
    }

    if(lista->prox != NULL) {
        inserir(lista->prox, dado);
        return;
    }

    LISTA *nova = (LISTA *) aloca(sizeof(LISTA));
    nova->dado = dado;
    nova->prox = NULL;
    lista->prox = nova;
    return;
}

void remover(LISTA **lista, int dado) {

    LISTA *lista_aux = *lista;

    // Primeiro item da lista.
    if(lista_aux->dado == dado) {
        *lista = lista_aux->prox;
        libera(lista_aux);
        return;
    }

    LISTA *apagar;

    while(lista_aux->prox != NULL) {
        if(lista_aux->prox->dado == dado) {
            apagar = lista_aux->prox;
            lista_aux->prox = lista_aux->prox->prox;
            libera(apagar);
            return;
        }
        lista_aux = lista_aux->prox;
    }
    printf("Dado nao encontrado.\n");
    return;
}

void imprimir(LISTA *lista) {

    LISTA *lista_aux = lista;

    printf("Lista: ");
    while (lista_aux != NULL) {
        printf("%d ", lista_aux->dado);
        lista_aux = lista_aux->prox;
    }
    printf("\n");
    return;
}

void excluir(LISTA *lista) {

    LISTA *lista_apagar;
    LISTA *lista_aux = lista;

    while (lista_aux != NULL) {
        lista_apagar = lista_aux;
        lista_aux = lista_aux->prox;
        libera(lista_apagar);
    }

    printf("Lista apagada com sucesso.\n");
    return;
}

void imprimir_memoria() {
    imprime_memoria();
    return;
}