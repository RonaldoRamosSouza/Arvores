#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUCTS
   ========================= */

typedef struct aluno {
    char matr[20];
    char nome[100];
    int faltas;
    float media;
} Aluno;

typedef struct avlnode {
    Aluno info;
    int fatbal;
    struct avlnode *esq;
    struct avlnode *dir;
} AVLNode;

typedef struct avltree {
    AVLNode *raiz;
    int status;
} AVLTree;


/* =========================
   CRIAR ARVORE
   ========================= */

AVLTree *criarArvore() {

    AVLTree *arvore = malloc(sizeof(AVLTree));

    if (arvore == NULL) {
        return NULL;
    }

    arvore->raiz = NULL;
    arvore->status = 0;

    return arvore;
}


/* =========================
   CRIAR NODE
   ========================= */

AVLNode *criarNode(Aluno aluno) {

    AVLNode *novo = malloc(sizeof(AVLNode));

    if (novo == NULL) {
        return NULL;
    }

    novo->info = aluno;
    novo->fatbal = 0;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}


/* =========================
   ALTURA
   ========================= */

int altura(AVLNode *no) {

    if (no == NULL) {
        return 0;
    }

    int alturaEsq = altura(no->esq);
    int alturaDir = altura(no->dir);

    return 1 + (alturaEsq > alturaDir ? alturaEsq : alturaDir);
}


/* =========================
   FATOR DE BALANCEAMENTO
   ========================= */

int fatorBalanceamento(AVLNode *no) {

    if (no == NULL) {
        return 0;
    }

    return altura(no->esq) - altura(no->dir);
}


/* =========================
   ROTACAO DIREITA
   ========================= */

AVLNode *rotacaoDireita(AVLNode *raiz) {

    AVLNode *x = raiz->esq;
    AVLNode *t2 = x->dir;

    x->dir = raiz;
    raiz->esq = t2;

    raiz->fatbal = fatorBalanceamento(raiz);
    x->fatbal = fatorBalanceamento(x);

    return x;
}


AVLNode *rotacaoEsquerda(AVLNode *raiz) {

    AVLNode *y = raiz->dir;
    AVLNode *t2 = y->esq;

    y->esq = raiz;
    raiz->dir = t2;

    raiz->fatbal = fatorBalanceamento(raiz);
    y->fatbal = fatorBalanceamento(y);

    return y;
}

AVLNode *rotacaoEsquerdaDireita(AVLNode *no) {

    no->esq = rotacaoEsquerda(no->esq);

    return rotacaoDireita(no);
}

AVLNode *rotacaoDireitaEsquerda(AVLNode *no) {

    no->dir = rotacaoDireita(no->dir);

    return rotacaoEsquerda(no);
}


/* =========================
   BALANCEAR
   ========================= */

AVLNode *balancear(AVLNode *no, Aluno aluno) {

    no->fatbal = fatorBalanceamento(no);

    
    if (no->fatbal > 1 &&
        strcmp(aluno.matr, no->esq->info.matr) < 0) {

        return rotacaoDireita(no);
    }

   
    if (no->fatbal > 1 &&
        strcmp(aluno.matr, no->esq->info.matr) > 0) {

        return rotacaoEsquerdaDireita(no);
    }

   
    if (no->fatbal < -1 &&
        strcmp(aluno.matr, no->dir->info.matr) > 0) {

        return rotacaoEsquerda(no);
    }

   
    if (no->fatbal < -1 &&
        strcmp(aluno.matr, no->dir->info.matr) < 0) {

        return rotacaoDireitaEsquerda(no);
    }

    return no;
}


/* =========================
   INSERIR ALUNO
   ========================= */

AVLNode *inserir(AVLNode *raiz, Aluno aluno) {

    if (raiz == NULL) {
        return criarNode(aluno);
    }

    if (strcmp(aluno.matr, raiz->info.matr) < 0) {

        raiz->esq = inserir(raiz->esq, aluno);

    } else if (strcmp(aluno.matr, raiz->info.matr) > 0) {

        raiz->dir = inserir(raiz->dir, aluno);

    } else {

    
        return raiz;
    }

    raiz->fatbal = fatorBalanceamento(raiz);

    return balancear(raiz, aluno);
}


/* =========================
   BUSCAR POR MATRICULA
   ========================= */

AVLNode *buscar(AVLNode *raiz, char matricula[]) {

    if (raiz == NULL) {
        return NULL;
    }

    int comparacao = strcmp(matricula, raiz->info.matr);

    if (comparacao == 0) {

        return raiz;

    } else if (comparacao < 0) {

        return buscar(raiz->esq, matricula);

    } else {

        return buscar(raiz->dir, matricula);
    }
}


/* =========================
   PERCURSO EM ORDEM
   ========================= */

void emOrdem(AVLNode *raiz) {

    if (raiz != NULL) {

        emOrdem(raiz->esq);

        printf("\nNome: %s\n", raiz->info.nome);
        printf("Matricula: %s\n", raiz->info.matr);
        printf("Media: %.2f\n", raiz->info.media);
        printf("Faltas: %d\n", raiz->info.faltas);

        emOrdem(raiz->dir);
    }
}


/* =========================
   IMPRIMIR UM NIVEL
   ========================= */

void imprimirNivel(AVLNode *raiz, int nivel) {

    if (raiz == NULL) {
        return;
    }

    if (nivel == 1) {

        raiz->fatbal = fatorBalanceamento(raiz);

        printf("\nNome: %s\n", raiz->info.nome);
        printf("Matricula: %s\n", raiz->info.matr);
        printf("Media: %.2f\n", raiz->info.media);
        printf("Faltas: %d\n", raiz->info.faltas);
        printf("Fator de balanceamento: %d\n",
               raiz->fatbal);

    } else {

        imprimirNivel(raiz->esq, nivel - 1);
        imprimirNivel(raiz->dir, nivel - 1);
    }
}


/* =========================
   PERCURSO POR NIVEL
   ========================= */

void porNivel(AVLNode *raiz) {

    int h = altura(raiz);

    for (int nivel = 1; nivel <= h; nivel++) {
        imprimirNivel(raiz, nivel);
    }
}


/* =========================
   DESTROY
   ========================= */

void destroy(AVLNode *raiz) {

    if (raiz != NULL) {

        destroy(raiz->esq);
        destroy(raiz->dir);

        free(raiz);
    }
}


/* =========================
   MAIN
   ========================= */

int main() {

    AVLTree *arvore = criarArvore();

    if (arvore == NULL) {
        printf("Erro ao criar a arvore.\n");
        return 1;
    }

    int opcao;
    Aluno aluno;
    char matricula[20];
    AVLNode *resultado;

    do {

        printf("\n============================\n");
        printf("       MENU ARVORE AVL\n");
        printf("============================\n");
        printf("1 - Cadastrar aluno\n");
        printf("2 - Buscar aluno\n");
        printf("3 - Percorrer por nivel\n");
        printf("4 - Percorrer em ordem\n");
        printf("0 - Sair\n");
        printf("============================\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:

                printf("\nMatricula: ");
                scanf("%19s", aluno.matr);

                
                resultado = buscar(arvore->raiz, aluno.matr);

                if (resultado != NULL) {

                    printf("\nMatricula ja cadastrada!\n");

                } else {

                    printf("Nome: ");
                    scanf(" %99[^\n]", aluno.nome);

                    printf("Media: ");
                    scanf("%f", &aluno.media);

                    printf("Quantidade de faltas: ");
                    scanf("%d", &aluno.faltas);

                    arvore->raiz =
                        inserir(arvore->raiz, aluno);

                    arvore->status = 1;

                    printf("\nAluno cadastrado com sucesso!\n");
                }

                break;


            case 2:

                printf("\nDigite a matricula: ");
                scanf("%19s", matricula);

                resultado =
                    buscar(arvore->raiz, matricula);

                if (resultado != NULL) {

                    printf("\nAluno encontrado!\n");
                    printf("Nome: %s\n",
                           resultado->info.nome);

                    printf("Matricula: %s\n",
                           resultado->info.matr);

                    printf("Media: %.2f\n",
                           resultado->info.media);

                    printf("Faltas: %d\n",
                           resultado->info.faltas);

                } else {

                    printf("\nAluno nao encontrado.\n");
                }

                break;


            case 3:

                if (arvore->raiz == NULL) {

                    printf("\nArvore vazia.\n");

                } else {

                    printf("\nPercurso por nivel:\n");

                    porNivel(arvore->raiz);
                }

                break;


            case 4:

                if (arvore->raiz == NULL) {

                    printf("\nArvore vazia.\n");

                } else {

                    printf("\nAlunos em ordem crescente "
                           "de matricula:\n");

                    emOrdem(arvore->raiz);
                }

                break;


            case 0:

                printf("\nEncerrando programa...\n");

                break;


            default:

                printf("\nOpcao invalida.\n");
        }

    } while (opcao != 0);



    destroy(arvore->raiz);

    free(arvore);

    return 0;
}