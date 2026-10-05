#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa{
    char nome[50];
    int idade;
}Pessoa;

typedef struct ABB{
    Pessoa valor;
    struct ABB *esq;
    struct ABB *dir;
}ABB;

typedef struct AVL{

    Pessoa valor;
    struct AVL *esq;
    struct AVL *dir;

}AVL;


AVL *criarNo(Pessoa Pessoa){

AVL *novo = malloc(sizeof(AVL));
if(novo == NULL){

return NULL;
}
novo->valor = Pessoa;
novo->esq = NULL;
novo->dir = NULL;

return novo;
}
int altura(AVL *no){
    if(no == NULL){
        return 0;
    }
    int esq = altura(no->esq);
    int dir = altura(no->dir);
   
    if(esq > dir){
        return esq +1; 
    }
    else if(esq < dir){
        return dir +1;
    }
}


int fatorbalanceamento(AVL *no){
if(no == NULL){
    return 0;
}
return altura(no->esq) - altura(no->dir);
}

AVL *inserirAV(AVL *raiz,Pessoa pessoa){

if(raiz == NULL){
return (criarNo(pessoa));
}
if(pessoa.idade < raiz->valor.idade){
    raiz->esq = inserirAV(raiz->esq, pessoa);
    
}
if(pessoa.idade > raiz->valor.idade){
    raiz->dir = inserirAV(raiz->dir, pessoa);
    
}
int fb = fatorbalanceamento(raiz);
return raiz;
}

ABB *inserirABB(ABB *raiz, Pessoa valor){
if (raiz == NULL){
    ABB *novo = malloc(sizeof(ABB));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
return novo;
}

if(valor.idade < raiz->valor.idade){
raiz->esq = inserirABB(raiz->esq, valor);
}

if(valor.idade > raiz->valor.idade){
raiz->dir = inserirABB(raiz->dir, valor);
}

return raiz;
}

ABB *remover(ABB *raiz, Pessoa valor){
    if(raiz == NULL){
    return NULL;
    }

    if(valor.idade < raiz-> valor.idade){
    raiz->esq = remover(raiz->esq, valor);
    }

    else if(valor.idade > raiz-> valor.idade){
    raiz->dir = remover(raiz->dir,valor);
    }

    else{

        if(raiz->esq == NULL){
            ABB *temp = raiz->dir;
            free(raiz);
            return temp;
        }
        else if(raiz->dir == NULL){
            ABB *temp = raiz->esq;
            free(raiz);
            return temp;
            
        }
        ABB *temp = raiz->dir;
        while(temp->esq != NULL){
            temp = temp->esq;
        }
        raiz->valor = temp->valor;
        raiz->dir = remover(raiz->dir, temp->valor);
    }
    return raiz;

}

void imprimiremOrdem(ABB *No){
if(No == NULL){
    return;
} 
imprimiremOrdem(No->esq);
printf(No->valor.nome, No->valor.idade);

imprimiremOrdem(No->dir);
printf(No->valor.nome, No->valor.idade);




}
int main(){
    ABB *raiz = NULL;
    Pessoa p1;
    Pessoa p2;

strcpy(p1.nome,"joao");
p1.idade = 30;
strcpy(p2.nome,"maria");
p2.idade = 20;
 raiz = inserirABB(raiz,p1);
 raiz = inserirABB(raiz,p2);
 imprimiremOrdem(raiz);
 
printf("nome: %s", p1.nome);
printf("idade: %d", p1.idade);
printf("nome: %s", p2.nome);
printf("idade: %d", p2.idade);
return 0;
}

