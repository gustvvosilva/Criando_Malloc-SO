#include <stdio.h>
#include <stdlib.h>

__uint8_t memoria[8 * 1024];
#define ESP_END 512

typedef struct lista {
    int dado;
    struct lista *prox;
} LISTA;

void *aloca(int tamanho) {
    void *ponteiro;

    __uint8_t qtd_itens = memoria[511];

}

LISTA *init_lista() {
    LISTA *nova = (LISTA *) malloc(sizeof(LISTA));
    nova->dado = 123;
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

    LISTA *lista_aux = lista;

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

    int teste = 83548;

    int *pont = &teste;

    __uint8_t a = ((__uint64_t) pont) & 0xff;
    __uint8_t b = ((__uint64_t) pont >> 8) & 0xff;
    __uint8_t c = ((__uint64_t) pont >> 16) & 0xff;
    __uint8_t d = ((__uint64_t) pont >> 24) & 0xff;
    __uint8_t e = ((__uint64_t) pont >> 32) & 0xff;
    __uint8_t f = ((__uint64_t) pont >> 40) & 0xff;
    __uint8_t g = ((__uint64_t) pont >> 48) & 0xff;
    __uint8_t h = ((__uint64_t) pont >> 56) & 0xff;

    int *pont1 = (int *) (((__uint64_t) a) | (((__uint64_t) b) << 8) | (((__uint64_t) c) << 16) | (((__uint64_t) d) << 24) | 
                 (((__uint64_t) e) << 32) | (((__uint64_t) f) << 40) | (((__uint64_t) g) << 48) | (((__uint64_t) h) << 56));

    printf("\n%ld - %ld\n", &memoria[0], &memoria[1]);

    // LISTA *lista = init_lista();

    // inserir(lista, 10);
    // inserir(lista, 20);
    // inserir(lista, 30);
    // inserir(lista, 45);
    // inserir(lista, 87);

    // imprimir(lista);

    // excluir(lista);

    // printf("foi\n");

    return 0;
}