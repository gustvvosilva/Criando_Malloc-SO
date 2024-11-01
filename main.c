#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 8192  // 8 kB
#define MEM_OFFSET 1024  // 1 kB

__uint8_t memoria[MEM_SIZE];

__uint32_t qtd = 0;

// __uint64_t ponteiros[64];
// __uint32_t comecos[64];
// __uint32_t terminos[64];

// 0 - 255 -> comeco
// 256 - 511 -> termino
// 512 - 1023 -> ponteiro
// 1024 - 8191 -> memoria

typedef struct lista {
    int dado;
    struct lista *prox;
} LISTA;

void devolve_local(__uint32_t *inic, __uint32_t *term, __uint64_t *pont) {

    int j;

    for(int i = 0; i < 64; i++) {

        j = i * 4;
        memoria[0 + j] = ((__uint32_t) inic[i]) & 0xff;
        memoria[1 + j] = ((__uint32_t) inic[i] >> 8) & 0xff;
        memoria[2 + j] = ((__uint32_t) inic[i] >> 16) & 0xff;
        memoria[3 + j] = ((__uint32_t) inic[i] >> 24) & 0xff;

        memoria[256 + j] = ((__uint32_t) term[i]) & 0xff;
        memoria[257 + j] = ((__uint32_t) term[i] >> 8) & 0xff;
        memoria[258 + j] = ((__uint32_t) term[i] >> 16) & 0xff;
        memoria[259 + j] = ((__uint32_t) term[i] >> 24) & 0xff;

        j = i * 8;
        memoria[512 + j] = ((__uint64_t) pont[i]) & 0xff;
        memoria[513 + j] = ((__uint64_t) pont[i] >> 8) & 0xff;
        memoria[514 + j] = ((__uint64_t) pont[i] >> 16) & 0xff;
        memoria[515 + j] = ((__uint64_t) pont[i] >> 24) & 0xff;
        memoria[516 + j] = ((__uint64_t) pont[i] >> 32) & 0xff;
        memoria[517 + j] = ((__uint64_t) pont[i] >> 40) & 0xff;
        memoria[518 + j] = ((__uint64_t) pont[i] >> 48) & 0xff;
        memoria[519 + j] = ((__uint64_t) pont[i] >> 56) & 0xff;
    }

    return;
}

void obtem_local(__uint32_t *inic, __uint32_t *term, __uint64_t *pont) {

    int j;

    for(int i = 0; i < 64; i++) {

        j = i * 4;
        inic[i] = (__uint32_t) (((__uint32_t) memoria[0 + j]) | (((__uint32_t) memoria[1 + j]) << 8) | 
                        (((__uint32_t) memoria[2 + j]) << 16) | (((__uint32_t) memoria[3 + j]) << 24));
        term[i] = (__uint32_t) (((__uint32_t) memoria[256 + j]) | (((__uint32_t) memoria[257 + j]) << 8) | 
                        (((__uint32_t) memoria[258 + j]) << 16) | (((__uint32_t) memoria[259 + j]) << 24));

        j = i * 8;
        pont[i] = (__uint64_t) (((__uint64_t) memoria[512 + j]) | (((__uint64_t) memoria[513 + j]) << 8) | 
                        (((__uint64_t) memoria[514 + j]) << 16) | (((__uint64_t) memoria[515 + j]) << 24) | 
                        (((__uint64_t) memoria[516 + j]) << 32) | (((__uint64_t) memoria[517 + j]) << 40) | 
                        (((__uint64_t) memoria[518 + j]) << 48) | (((__uint64_t) memoria[519 + j]) << 56));
    
    }

    return;
}

void *aloca(int tamanho) {

    void *ponteiro;

    __uint32_t inic[64], term[64];
    __uint64_t pont[64];
    obtem_local(inic, term, pont);

    if(term[0] == 0) {
        inic[0] = 0;
        term[0] = tamanho - 1;
        pont[0] = (__uint64_t) &memoria[inic[0] + MEM_OFFSET];
        ponteiro = (void *) pont[0];
        qtd++;
    } else {
        for(int i = 1; i < 64; i++) {
            if(term[i] == 0) {
                inic[i] = term[i - 1] + 1;
                term[i] = inic[i] + tamanho - 1;
                pont[i] = (__uint64_t) &memoria[inic[i] + MEM_OFFSET];
                ponteiro = (void *) pont[i];
                qtd++;
                break;
            }
        }
    }

    devolve_local(inic, term, pont);
    // for(int i = 0; i < 64; i++) {
    //     printf("%d: um %d e do %d -> %ld\n", i, inic[i], term[i], pont[i]);
    // }

    return ponteiro;
}

void libera(void *ponteiro) {

    __uint32_t inic[64], term[64];
    __uint64_t pont[64];
    obtem_local(inic, term, pont);

    for(int i = 0; i < 64; i++) {
        if(pont[i] == (__uint64_t) ponteiro){

            inic[i] = 0;
            term[i] = 0;
            pont[i] = 0;
            qtd--;

            devolve_local(inic, term, pont);
            // for(int i = 0; i < 64; i++) {
            //     printf("L %d: um %d e do %d -> %ld\n", i, inic[i], term[i], pont[i]);
            // }

            return;
        }
    }
    printf("ERRO no libera %d - %p\n", qtd, ponteiro);

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

void remover(LISTA **lista, int dado) {

    LISTA *lista_aux = *lista;

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

    // printf("\n%d\n", sizeof(memoria) / 1024);

    LISTA *lista = init_lista();

    inserir(lista, 10);
    inserir(lista, 20);
    inserir(lista, 30);
    inserir(lista, 45);
    inserir(lista, 87);

    imprimir(lista);

    printf("%d\n", qtd);

    remover(&lista, 30);

    imprimir(lista);

    printf("%d\n", qtd);

    excluir(lista);

    printf("%d\n", qtd);

    return 0;
}
