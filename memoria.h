#ifndef __MEMORIA_H
#define __MEMORIA_H

#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 8192  // 8 kB
#define MEM_OFFSET 1024  // 1 kB

void *aloca(int tamanho);
void libera(void *ponteiro);
void ler_memoria(__uint32_t *inic, __uint32_t *term, __uint64_t *pont);
void gravar_memoria(__uint32_t *inic, __uint32_t *term, __uint64_t *pont);
void imprime_memoria();

// __uint64_t ponteiros[64];
// __uint32_t comecos[64];
// __uint32_t terminos[64];

// 0 - 255 -> comeco
// 256 - 511 -> termino
// 512 - 1023 -> ponteiro
// 1024 - 8191 -> memoria

#endif