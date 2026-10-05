#include <stdio.h>
#include <stdlib.h>


typedef struct pessoa{
    char nome[100];
    int idade;

}Pessoa;

typedef struct node{
    Pessoa info;
    struct node *esq;
    struct node *dir;
}No;

No *inserir(No *raiz, Pessoa pessoa){

    if(raiz == NULL){
        No *novo = malloc(sizeof(No));
        if(novo == NULL){
            return NULL;
        }
        novo->info = pessoa;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    if(pessoa.idade < raiz->info.idade){
        raiz->esq = inserir(raiz->esq, pessoa);
    }
    else if(pessoa.idade > raiz->info.idade){
        raiz->dir = inserir(raiz->dir, pessoa);
    }else{
        printf("Pessoa com idade %d já existe na árvore.\n", pessoa.idade);
    }
    return raiz;
}

No *remove(No *raiz, Pessoa pessoa){

    if(raiz == NULL){
      return NULL;
    }

    if(pessoa.idade == raiz->info.idade){ 

       if(raiz->esq == NULL && raiz->dir == NULL){
         free(raiz);
           return NULL;
       }

       if(raiz->esq == NULL || raiz->dir == NULL){
        No *aux;
        if(raiz->esq != NULL){
            aux = raiz->esq;
        }
        if(raiz->dir != NULL){
            aux = raiz->dir;
        }
        free(raiz);

         return aux;
     }
     else{
        No *aux = raiz->dir;
         while(aux->esq != NULL){
             aux = aux->esq;
         }
         raiz->info = aux->info;
         aux->info = pessoa;
         raiz->dir = remove(raiz->dir,pessoa);
     }
    else if(pessoa.idade < raiz->info.idade){
        raiz->esq = remove(raiz->esq,pessoa);
    }
    else{
        raiz->dir = remove(raiz->dir,pessoa);

    }
  }
}

No *buscar(No *raiz, Pessoa pessoa){

    if(raiz == NULL){
        return NULL;
    }
    if(pessoa.idade == raiz->info.idade){
        return raiz;
    }
    else if(pessoa.idade < raiz->info.idade){
        return buscar(raiz->esq,pessoa);
    }
    else{
        return buscar(raiz->dir,pessoa);
    }
}

No *maior(No *raiz){
    if (raiz == NULL) {
        return NULL;
    }
    while (raiz->dir != NULL){
        raiz = raiz->dir;
    }
}

No *menor(No *raiz){
    if(raiz == NULL){
        return NULL;
    }
    while(raiz->esq != NULL){
        raiz = raiz->esq;
    }
}

No *altura(No *raiz){



    
}

No *remove(No *raiz, Pessoa pessoa){
    if(raiz == NULL){
        return NULL;
}
if(pessoa.idade == raiz->info.idade){
    if(raiz->esq == NULL && raiz->dir == NULL){
        free(raiz);
        return NULL;
    }
    if(raiz->esq == NULL || raiz->dir == NULL){

        No *aux;
        if(raiz->esq !=NULL){
            aux = raiz->esq;
        }
        if(raiz->dir !=NULL){
            aux = raiz->dir;
        }
        free(raiz);
        return aux;
        }

    }

else{
    No *aux = raiz->dir;
    while(aux->esq != NULL){
        aux = aux->esq;
    }
    raiz->info = aux->info;
    aux->info = pessoa;
    raiz->dir = remove(raiz->dir,pessoa);
}