#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main() {

    LISTA *lista = init_lista();

    inserir(lista, 10);
    inserir(lista, 20);
    inserir(lista, 30);
    inserir(lista, 45);
    inserir(lista, 87);

    imprimir(lista);

    imprimir_memoria();

    remover(&lista, 30);

    imprimir(lista);

    imprimir_memoria();

    excluir(lista);

    imprimir_memoria();

    return 0;
}
