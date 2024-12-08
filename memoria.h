#ifndef __MEMORIA_H
#define __MEMORIA_H

#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 8192  // 8 kB --> Tamanho de memória solicitado pelo professor.
#define MEM_OFFSET 1024  // 1 kB --> Separei 1/8 dessa memória para guardar as localizações dos itens.

// A memória foi estruturada da seguinte forma:
// bytesInicio - bytesTermino -> Descrição;
// 0 - 255 -> Onde está o início de cada item na memória;
// 256 - 511 -> Até que byte vai cada item na memória;
// 512 - 1023 -> Ponteiros de cada item na memória;
// 1024 - 8191 -> Espaço dedicado para a memória em si.

void *aloca(int tamanho);
void libera(void *ponteiro);
void ler_memoria(__uint32_t *inic, __uint32_t *term, __uint64_t *pont);
void gravar_memoria(__uint32_t *inic, __uint32_t *term, __uint64_t *pont);
void imprime_memoria();

#endif