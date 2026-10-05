#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *esq;
    struct node *dir;
} No;

No *remove(No *raiz, int valor) {

    if (raiz == NULL) {
        return NULL;
    }

    if (valor == raiz->data) {

        // Caso 1: nó folha
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }

        // Caso 2: nó com apenas um filho
        if (raiz->esq == NULL || raiz->dir == NULL) {

            No *aux;

            if (raiz->esq != NULL) {
                aux = raiz->esq;
            }
            else {
                aux = raiz->dir;
            }

            free(raiz);

            return aux;
        }

        // Caso 3: nó com dois filhos
        else {

            No *aux = raiz->dir;

            while (aux->esq != NULL) {
                aux = aux->esq;
            }

            raiz->data = aux->data;

            raiz->dir = remove(raiz->dir, aux->data);
        }
    }

    else if (valor < raiz->data) {
        raiz->esq = remove(raiz->esq, valor);
    }

    else {
        raiz->dir = remove(raiz->dir, valor);
    }

    return raiz;
}
