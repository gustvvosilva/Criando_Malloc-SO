#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int dado;
    struct lista *prox;
} LISTA;

LISTA *init_lista() {
    LISTA *nova = (LISTA *) malloc(sizeof(LISTA));
    nova->dado = 0;
    nova->prox = NULL;

    return nova;
}

void inserir(LISTA *lista, int dado) {

    while(lista->prox != NULL){
        inserir(lista->prox, dado);
        return;
    }

    LISTA *nova = (LISTA *) malloc(sizeof(LISTA));
    nova->dado = dado;
    nova->prox = NULL;
    lista->prox = nova;
    return;
}

void imprimir(LISTA *lista) {

    LISTA *lista_aux = lista->prox;

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
        free(lista_apagar);
    }

    return;
}

int main() {

    printf("Ola mundo\n");

    LISTA *lista = init_lista();

    inserir(lista, 10);
    inserir(lista, 20);
    inserir(lista, 30);
    inserir(lista, 45);
    inserir(lista, 87);

    imprimir(lista);

    excluir(lista);

    printf("foi\n");

    return 0;
}