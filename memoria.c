#include "memoria.h"

__uint8_t memoria[MEM_SIZE];
__uint32_t qtd = 0;

void *aloca(int tamanho) {

    void *ponteiro;

    __uint32_t inic[64], term[64];
    __uint64_t pont[64];
    ler_memoria(inic, term, pont);

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

    gravar_memoria(inic, term, pont);
    return ponteiro;
}

void libera(void *ponteiro) {

    __uint32_t inic[64], term[64];
    __uint64_t pont[64];
    ler_memoria(inic, term, pont);

    for(int i = 0; i < 64; i++) {
        if(pont[i] == (__uint64_t) ponteiro){
            inic[i] = 0;
            term[i] = 0;
            pont[i] = 0;
            qtd--;
            gravar_memoria(inic, term, pont);
            return;
        }
    }
    // printf("ERRO no libera %p\n", ponteiro);
    printf("ERRO no libera %d - %p\n", qtd, ponteiro);
    return;
}

void ler_memoria(__uint32_t *inic, __uint32_t *term, __uint64_t *pont) {

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

void gravar_memoria(__uint32_t *inic, __uint32_t *term, __uint64_t *pont) {

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

void imprime_memoria() {

    __uint32_t inic[64], term[64];
    __uint64_t pont[64];
    ler_memoria(inic, term, pont);

    printf("qtd: %d\n", qtd);
    for(int i = 0; i < 64; i++) {
        if(inic[i] || term[i] || pont[i] != 0) {
            printf("%d: ini %d e ter %d -> %ld\n", i, inic[i], term[i], pont[i]);
        }
    }
    return;
}