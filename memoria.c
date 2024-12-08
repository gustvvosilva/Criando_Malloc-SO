#include "memoria.h"

// Cria efetivamente a memória.
__uint8_t memoria[MEM_SIZE];

// Imita o funcionamento do malloc().
void *aloca(int tamanho) {

    void *ponteiro;

    // Resgata na memória todas as informações necessárias para operar sobre ela.
    __uint32_t inic[64], term[64];
    __uint64_t pont[64];
    ler_memoria(inic, term, pont);

    // Se for o primeiro item na memória.
    if(pont[0] == 0 && (inic[1] >= tamanho || pont[1] == 0)) {  
        inic[0] = 0;
        term[0] = tamanho - 1;
        pont[0] = (__uint64_t) &memoria[inic[0] + MEM_OFFSET];
        ponteiro = (void *) pont[0];
    } else {
        for(int i = 1; i < 64; i++) {
            if(pont[i] == 0 && ((inic[i + 1] - term[i - 1]) >= tamanho || pont[i + 1] == 0)) {
                inic[i] = term[i - 1] + 1;
                term[i] = inic[i] + tamanho - 1;
                pont[i] = (__uint64_t) &memoria[inic[i] + MEM_OFFSET];
                ponteiro = (void *) pont[i];
                break;
            }
        }
    }

    // Grava na memória os dados recebidos.
    gravar_memoria(inic, term, pont);
    return ponteiro;
}

// Imita o free().
void libera(void *ponteiro) {

    __uint32_t inic[64], term[64];
    __uint64_t pont[64];
    ler_memoria(inic, term, pont);

    for(int i = 0; i < 64; i++) {
        if(pont[i] == (__uint64_t) ponteiro){
            inic[i] = 0;
            term[i] = 0;
            pont[i] = 0;
            gravar_memoria(inic, term, pont);
            return;
        }
    }
    printf("ERRO! Ponteiro %p nao encontrado.\n", ponteiro);
    return;
}

// Aqui, usei manipulação de bits (Bitwise) para obter os dados que estão gravados na memória byte a byte
// e estou transformando eles para uma estrutura de inteiros não sinalizados a fim de
// facilitar a manipulação desses dados no código.
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

// Após manipular esses dados, faço o caminho contrário do ler_memoria(), ou seja,
// transformo os dados de inteiros em bytes.
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

// Imprime a memória na tela para facilitar a compreensão do seu comportamento.
void imprime_memoria() {

    __uint32_t inic[64], term[64];
    __uint64_t pont[64];
    ler_memoria(inic, term, pont);

    int qtd = 0;

    printf("\nMEMORIA: \n");
    for(int i = 0; i < 64; i++) {
        if(inic[i] || term[i] || pont[i] != 0) {
            printf("item %d: inicio %d e termino %d -> ponteiro %ld\n", i, inic[i], term[i], pont[i]);
            qtd++;
        }
    }
    printf("Encontrou %d itens na memoria.\n\n", qtd);
    return;
}