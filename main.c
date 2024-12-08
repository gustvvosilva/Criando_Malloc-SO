#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "memoria.h"

int main() {

    // Inicia a lista encadeada.
    LISTA *lista = init_lista();

    // Insere dados.
    inserir(lista, 10);
    inserir(lista, 20);
    inserir(lista, 30);
    inserir(lista, 40);
    inserir(lista, 50);

    imprimir(lista);     // Imprime apenas a lista e seus dados.
    imprimir_memoria();  // Mostra os itens da memória e alguns dados do seu espaço.

    // Adicionei esse teste para mostrar que a memória se comporta de forma dinâmica,
    // ou seja, ele aloca exatamente o espaço que você solicitar.
    int *inteiro_teste = (int *) aloca(sizeof(int));
    *inteiro_teste = 7;
    imprimir_memoria();

    // Remove o nó "30" da lista.
    remover(&lista, 30);

    imprimir(lista);
    imprimir_memoria();

    inserir(lista, 60);
    inserir(lista, 70);
    inserir(lista, 80);
    imprimir(lista);
    imprimir_memoria();

    // Tirar a lista da memória.
    excluir(lista);
    imprimir_memoria();

    // Agora, libera o teste que fizemos para deixar a memória limpa.
    libera(inteiro_teste);
    imprimir_memoria();

    return 0;
}
