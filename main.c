#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 8192
// #define ESP_END 512

__uint8_t memoria[7164];
__uint64_t ponteiros[64];
__uint32_t comecos[64];
__uint32_t terminos[64];
__uint32_t qtd = 0;

typedef struct lista {
    int dado;
    struct lista *prox;
} LISTA;

void *aloca(int tamanho) {

    void *ponteiro;

    if(qtd == 0) {
        comecos[0] = 0;
        terminos[0] = tamanho - 1;
        ponteiros[0] = (__uint64_t) &memoria[comecos[0]];
        ponteiro = (void *) ponteiros[0];
        qtd++;
    } else {
        for(int i = 1; i < 64; i++) {
            if(terminos[i] == 0) {
                comecos[i] = terminos[i - 1] + 1;
                terminos[i] = comecos[i] + tamanho - 1;
                ponteiros[i] = (__uint64_t) &memoria[comecos[i]];
                ponteiro = (void *) ponteiros[i];
                qtd++;
                break;
            }
        }
    }

    return ponteiro;
}

void libera(void *ponteiro) {

    for(int i = 0; i < 64; i++) {
        if(ponteiros[i] == (__uint64_t) ponteiro){

            comecos[i] = 0;
            terminos[i] = 0;
            ponteiros[i] = 0;
            qtd--;
            return;
        }
    }
    printf("ERRO no libera %d\n", qtd);
    return;
}

LISTA *init_lista() {
    LISTA *nova = (LISTA *) aloca(sizeof(LISTA));
    nova->dado = 123;
    nova->prox = NULL;

    return nova;
}

void inserir(LISTA *lista, int dado) {

    if(lista->prox != NULL){
        inserir(lista->prox, dado);
        return;
    }

    LISTA *nova = (LISTA *) aloca(sizeof(LISTA));
    nova->dado = dado;
    nova->prox = NULL;
    lista->prox = nova;
    return;
}

void remover(LISTA *lista, int dado) {

    LISTA *lista_aux = lista;

    if(lista_aux->dado == dado) { //TODO: arrumar o primeiro elemento.
        lista = lista->prox;
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

    return;
}

int main() {

    // int teste = 83548;

    // int *pont = &teste;

    // __uint8_t a = ((__uint64_t) pont) & 0xff;
    // __uint8_t b = ((__uint64_t) pont >> 8) & 0xff;
    // __uint8_t c = ((__uint64_t) pont >> 16) & 0xff;
    // __uint8_t d = ((__uint64_t) pont >> 24) & 0xff;
    // __uint8_t e = ((__uint64_t) pont >> 32) & 0xff;
    // __uint8_t f = ((__uint64_t) pont >> 40) & 0xff;
    // __uint8_t g = ((__uint64_t) pont >> 48) & 0xff;
    // __uint8_t h = ((__uint64_t) pont >> 56) & 0xff;

    // int *pont1 = (int *) (((__uint64_t) a) | (((__uint64_t) b) << 8) | (((__uint64_t) c) << 16) | (((__uint64_t) d) << 24) | 
    //              (((__uint64_t) e) << 32) | (((__uint64_t) f) << 40) | (((__uint64_t) g) << 48) | (((__uint64_t) h) << 56));

    // printf("\n%d\n", sizeof(memoria) + sizeof(ponteiros) + sizeof(comecos) + sizeof(terminos) + sizeof(qtd));

    LISTA *lista = init_lista();

    inserir(lista, 10);
    inserir(lista, 20);
    inserir(lista, 30);
    inserir(lista, 45);
    inserir(lista, 87);

    imprimir(lista);

    printf("%d\n", qtd);

    remover(lista, 30);

    imprimir(lista);

    printf("%d\n", qtd);

    excluir(lista);

    printf("%d\n", qtd);

    return 0;
}