#include <stdio.h>
#include <stdlib.h>


typedef struct No{
    int valor;
    int bal;
    struct No *esq, *dir;
}Node;

typedef struct Abb{
    int status;
    struct No *raiz;
}AVL;

void inserirAVL(AVL *arvore, int valor){

    arvore->status = 0;
    inserirNode(&(arvore->raiz), valor, &(arvore->status));
}

void inserirNode(Node **raiz, int valor, int *status) {

    /* CASO BASE */
    if (*raiz == NULL) {

        Node *novo;

        novo = malloc(sizeof(Node));

        novo->valor = valor;
        novo->bal = 0;
        novo->esq = NULL;
        novo->dir = NULL;

        *raiz = novo;

        *status = 1;

        return;
    }

    if (valor == (*raiz)->valor) {

        printf("Valor repetido!\n");

        *status = 0;

        return;
    }

    if (valor < (*raiz)->valor) {

        inserirNode(&((*raiz)->esq), valor, status);

        if (*status == 1) {

            switch ((*raiz)->bal) {

                case -1:

                    (*raiz)->bal = 0;
                    *status = 0;

                    break;


                case 0:

                    (*raiz)->bal = 1;

                    break;


                case 1:

                    if ((*raiz)->esq->bal == 1) {

                        rotacaoDireita(raiz);

                    }
                    else {

                        rotacaoEsquerdaDireita(raiz);

                    }

                    *status = 0;

                    break;
            }
        }
    }

    else {

        inserirNode(&((*raiz)->dir), valor, status);

        if (*status == 1) {

            switch ((*raiz)->bal) {

                case 1:

                    (*raiz)->bal = 0;
                    *status = 0;

                    break;


                case 0:

                    (*raiz)->bal = -1;

                    break;


                case -1:

                    if ((*raiz)->dir->bal == -1) {

                        rotacaoEsquerda(raiz);

                    }
                    else {

                        rotacaoDireitaEsquerda(raiz);

                    }

                    *status = 0;

                    break;
            }
        }
    }
}

void rotacaoDireita(Node **raiz) {

    Node *b;

    b = (*raiz)->esq;

    (*raiz)->esq = b->dir;

    b->dir = *raiz;

    (*raiz)->bal = 0;
    b->bal = 0;

    *raiz = b;
}

void rotacaoEsquerda(Node **raiz) {

    Node *b;

    b = (*raiz)->dir;

    (*raiz)->dir = b->esq;

    b->esq = *raiz;

    (*raiz)->bal = 0;
    b->bal = 0;

    *raiz = b;
}

void rotacaoEsquerdaDireita(Node **raiz) {

    Node *a;
    Node *b;
    Node *c;

    a = *raiz;
    b = a->esq;
    c = b->dir;


    b->dir = c->esq;
    a->esq = c->dir;

    c->esq = b;
    c->dir = a;


    if (c->bal == 1) {

        a->bal = -1;
        b->bal = 0;

    }
    else if (c->bal == -1) {

        a->bal = 0;
        b->bal = 1;

    }
    else {

        a->bal = 0;
        b->bal = 0;
    }

    c->bal = 0;

    *raiz = c;
}

void rotacaoDireitaEsquerda(Node **raiz) {

    Node *a;
    Node *b;
    Node *c;

    a = *raiz;
    b = a->dir;
    c = b->esq;


    b->esq = c->dir;
    a->dir = c->esq;

    c->dir = b;
    c->esq = a;


    if (c->bal == -1) {

        a->bal = 1;
        b->bal = 0;

    }
    else if (c->bal == 1) {

        a->bal = 0;
        b->bal = -1;

    }
    else {

        a->bal = 0;
        b->bal = 0;
    }

    c->bal = 0;

    *raiz = c;
}

int altura(AVL * arvore){

if(arvore == NULL || arvore->raiz == NULL){
    return -1;
}

Node *atual = arvore->raiz;
int altura = 0;

while(atual->esq != NULL || atual->dir != NULL){

if(atual->bal > 0){
atual = atual->esq;
}
else if(atual->bal < 0){
atual = atual->dir;
}
else{
    if(atual->esq != NULL){
        atual = atual->esq; 
    }
    else{
        atual = atual->dir;
    }
}
altura ++;
}
return altura;
}
void balancear(Node **raiz){

    if(*raiz == NULL){
        return;
    }

    (*raiz)->bal = calcularBal(*raiz);


    // PESADA PARA ESQUERDA
    if((*raiz)->bal > 1){

        (*raiz)->esq->bal = calcularBal((*raiz)->esq);

        // simples à direita
        if((*raiz)->esq->bal >= 0){

            rotacaoDireita(raiz);
        }

        // dupla esquerda-direita
        else{

            rotacaoEsquerdaDireita(raiz);
        }
    }


    // PESADA PARA DIREITA
    else if((*raiz)->bal < -1){

        (*raiz)->dir->bal = calcularBal((*raiz)->dir);

        // simples à esquerda
        if((*raiz)->dir->bal <= 0){

            rotacaoEsquerda(raiz);
        }

        // dupla direita-esquerda
        else{

            rotacaoDireitaEsquerda(raiz);
        }
    }


    if(*raiz != NULL){

        (*raiz)->bal = calcularBal(*raiz);
    }
}

void removerNode(Node **raiz, int valor){

    if(*raiz == NULL){
        return;
    }


    // PROCURA NA ESQUERDA
    if(valor < (*raiz)->valor){

        removerNode(&((*raiz)->esq), valor);
    }


    // PROCURA NA DIREITA
    else if(valor > (*raiz)->valor){

        removerNode(&((*raiz)->dir), valor);
    }


    // ACHOU
    else{

        // CASO 1: FOLHA
        if((*raiz)->esq == NULL &&
           (*raiz)->dir == NULL){

            free(*raiz);

            *raiz = NULL;

            return;
        }


        // CASO 2: SÓ FILHO DA DIREITA
        else if((*raiz)->esq == NULL){

            Node *aux = *raiz;

            *raiz = (*raiz)->dir;

            free(aux);
        }


        // CASO 2: SÓ FILHO DA ESQUERDA
        else if((*raiz)->dir == NULL){

            Node *aux = *raiz;

            *raiz = (*raiz)->esq;

            free(aux);
        }


        // CASO 3: DOIS FILHOS
        else{

            Node *aux = (*raiz)->dir;

            while(aux->esq != NULL){

                aux = aux->esq;
            }

            (*raiz)->valor = aux->valor;

            removerNode(&((*raiz)->dir),
                        aux->valor);
        }
    }


    // DEPOIS DA REMOÇÃO:
    // BALANCEIA A SUBÁRVORE
    if(*raiz != NULL){

        balancear(raiz);
    }
}

void removerAVL(AVL *arvore, int valor){

    if(arvore == NULL){
        return;
    }

    removerNode(&(arvore->raiz), valor);
}


int main() {

AVL arvore;

arvore.raiz = NULL;
arvore.status = 0;

inserirAVL(&arvore, 30);
inserirAVL(&arvore, 20);
inserirAVL(&arvore, 10);
inserirAVL(&arvore, 40);
inserirAVL(&arvore, 50);

printf("Altura: %d\n", altura(&arvore));

return 0;
}
