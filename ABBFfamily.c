#include <stdio.h>
#include <stdlib.h>

typedef struct pessoa{
    char nome[100];
    int idade;
}Pessoa;

typedef struct Neta{
    Pessoa info;
}Naila;

typedef struct filha{
    Naila *neta;
}Adila;

typedef struct node{
    Adila info;
    struct node *esq;
    struct node *dir;
}Node;

typedef struct abb{
    int status;
    struct Node *raiz;
}ABB;

ABB inserir(ABB *arvore, Pessoa parente){

    if (arvore->raiz == NULL){
        Node *novo = malloc(sizeof(Node));
        if (novo == NULL){
            return *arvore;
        }
        novo->info.neta = malloc(sizeof(Naila));
        novo->
    }
}