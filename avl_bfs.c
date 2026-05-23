#include <stdio.h>
#include <stdlib.h>
//IMPLEMENTAÇÃO ÁRVORE AVL + PERCURSO BFS (EM LARGURA) COM FILA ENCADEADA

typedef struct No{
    int valor,altura;
    struct No *esq,*dir;
}No;

No* criaNo(int valor){
    No* n=malloc(sizeof(No));
    n->valor=valor;
    n->altura=0;
    n->esq=n->dir=NULL;
    return n;
}

int altura(No* n){ //retorna altura do nó
    return (n == NULL) ? -1 : n->altura;
}

int fatorBalanceamento(No* n){//retorna fator balanceamento do nó
    return (n==NULL) ? 0 : altura(n->dir)-altura(n->esq);
}

int maior(int a,int b){ //função auxiliar para atualizar altura de cada nó
    return a>b ? a : b;
}

No* rotacaoEsq(No* no){
    No* x=no->dir;
    No* y=x->esq;

    x->esq=no; //rotaciona a raiz para a esquerda
    no->dir=y;
  
    no->altura = 1 + maior(altura(no->esq),altura(no->dir));
    //como 'no' vai virar filho de x, precisamos calcular a altura dele primeiro, pois a altura de x depende da altura de no
    x->altura = 1 + maior(altura(x->esq),altura(x->dir));

    return x;
}

No* rotacaoDir(No* no){
    No* x=no->esq;
    No* y=x->dir;
    
    x->dir=no; //rotaciona a raiz para a direita
    no->esq=y;

    no->altura = 1 + maior(altura(no->esq),altura(no->dir)); 
    x->altura = 1 + maior(altura(x->dir),altura(x->esq));
    
    return x;
}

No* balancear(No* raiz){
     int fb=fatorBalanceamento(raiz); //desbalanceado= fator balanceamento >1 ou <-1
    
     if(fb>1){ //nó está desbalanceado para a direita;

        if(fatorBalanceamento(raiz->dir)<0){ //se for verdadeiro = caso RL       
            raiz->dir=rotacaoDir(raiz->dir);
        }
            raiz=rotacaoEsq(raiz);
     }

     if(fb<-1){ //nó está desbalanceado para a esquerda
        if(fatorBalanceamento(raiz->esq)>0){ //caso LR
            raiz->esq=rotacaoEsq(raiz->esq);
        }
            raiz=rotacaoDir(raiz);
     }
    
     return raiz;
}

No* inserir(No* raiz,int valor){ //chama a função balancear no final
    if(raiz==NULL){
        return criaNo(valor);
    }

    if(valor>raiz->valor){
        raiz->dir=inserir(raiz->dir,valor);

    }else if(valor<raiz->valor){

        raiz->esq=inserir(raiz->esq,valor);
    }else{
        
        return raiz; //quando valor==raiz->valor só retorna o nó normalmente, não adiciona repetidos ---> não vai chamar a função balancear
    }
    
    raiz->altura = 1 + maior(altura(raiz->esq), altura(raiz->dir)); //atualiza altura 

    return balancear(raiz); //vai balancear quando inserir um elemento;
}

No* remover(No* raiz,int valor){
    if(raiz==NULL)return NULL;

    if(valor>raiz->valor){
        raiz->dir=remover(raiz->dir,valor);
    }else if(valor<raiz->valor){
        raiz->esq=remover(raiz->esq,valor);
    }else{
        //primeiro caso: nó é uma folha;
        if(raiz->esq==NULL && raiz->dir==NULL){
                free(raiz);
                return NULL;

        //segundo caso: apenas 1 filho
        }else if(raiz->esq==NULL){ //só tem o filho direito
                No* temp=raiz->dir;
                free(raiz);

                return temp; //temp já era a raiz de uma subárvore avl válida

        }else if(raiz->dir==NULL){ //só tem o filho esquerdo
                No* temp=raiz->esq;
                free(raiz);

                return temp;

        }else{ //tem os dois filhos, nesse caso vamos pegar o menor filho da direita
            No* escolhido=raiz->dir;
            while(escolhido->esq!=NULL){
                escolhido=escolhido->esq;
            }
            raiz->valor=escolhido->valor; //troca o valor da raiz a ser removida;
            
            raiz->dir=remover(raiz->dir,escolhido->valor);//remove o valor repetido
        }
    }
    
    raiz->altura= 1 + maior(altura(raiz->esq),altura(raiz->dir));

    return balancear(raiz);
}

void infixo(No* raiz){ //percurso em ordem
    if(raiz!=NULL){
        infixo(raiz->esq);
        printf("%d ",raiz->valor);
        infixo(raiz->dir);
    }
}

No* buscar(No* raiz,int valor){ //busca na árvore
    if(raiz==NULL)return NULL;
    
    if(valor>raiz->valor){
        return buscar(raiz->dir,valor);

    }else if(valor<raiz->valor){
        return buscar(raiz->esq,valor);
    }
    
    return raiz;
}

void liberarArvore(No* raiz){ //faz a liberação pós-ordem
    if(raiz!=NULL){
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

//FILA ENCADEADA + BFS

typedef struct Celula{ //guarda um nó e um ponteiro para o próximo da fila
    No* no;
    struct Celula *prox; 
}Celula;

Celula* criaCelula(No* n){
    Celula* c=malloc(sizeof(Celula));
    c->no=n;
    c->prox=NULL;
    return c;
}

typedef struct Fila{
    Celula* primeiro;
    Celula* ultimo;
}Fila;

Fila* criaFila(){
    Fila* f=malloc(sizeof(Fila));
    f->primeiro=NULL;
    f->ultimo=NULL;
    return f;
}

void enqueue(Fila* f,No* n){ //inserção na fila 
    Celula* nova=criaCelula(n);

    if(f->primeiro==NULL){ //fila vazia
        f->primeiro=nova;
        f->ultimo=nova;
        return;
    }

    f->ultimo->prox=nova;
    f->ultimo=nova; //atualiza o último da fila
}

No* dequeue(Fila* f){
    Celula* tmp=f->primeiro; //primeiro elemento

    f->primeiro=tmp->prox; //atualiza o primeiro da fila
    if(f->primeiro==NULL){
        f->ultimo=NULL;
    }

    No* x=tmp->no;
    free(tmp); //remove o primeiro elemento

    return x; //retorna o nó
}

void bfs(No* raiz){ //imprime o percurso em largura da árvore
    if(raiz==NULL)return;

    Fila* f=criaFila();
    enqueue(f,raiz); //insere a raiz da árvore

    while(f->primeiro!=NULL){ //enquanto a fila não estiver vazia

        No* atual=dequeue(f); //retira o primeiro da fila

        printf("%d ",atual->valor);
        
        //adiciona os outros filhos do nó atual
        if(atual->esq!=NULL)enqueue(f,atual->esq);
        if(atual->dir!=NULL)enqueue(f,atual->dir);
    }

    free(f);
}

int main(){
    No* raiz = NULL;

    raiz=inserir(raiz,30);
    raiz=inserir(raiz,20);
    raiz=inserir(raiz,10);
    raiz=inserir(raiz,40);
    raiz=inserir(raiz,50);

    printf("AVL em ordem:\n");
    infixo(raiz);

    printf("\n\nPercurso em largura (BFS):\n");
    bfs(raiz);

    printf("\n\nRemovendo 40\n");

    raiz=remover(raiz,40);

    printf("AVL apos remocao:\n");
    infixo(raiz);
    
    printf("\n\nPercurso em largura apos remocao:\n");
    bfs(raiz);

    printf("\n");
   
    liberarArvore(raiz);

  	return 0;
}