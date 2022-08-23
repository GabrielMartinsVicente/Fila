//Gabriel Martins Vicente

// Trabalho-3-Fila (circular)

/* Medir  o  tempo  para  inserção  de  1.000.000  milhão  de  inteiros  em  uma  estrutura  de  dados  e  o  tempo  para  percorrer  e  somar  1.000.000  
de  inteiros  em  uma  determinada  estrutura de dados, e o tempo para garantir que um determinado inteiro já está na fila. 
Finalmente  você deverá medir estes tempos percorrendo a fila em dois sentidos. De cima para baixo e de baixo  para cima. */
#include <stdio.h>
#include <time.h>    //clock_t
#include <stdlib.h>  //função malloc
#include<stdbool.h>  //função bool

struct fila{
               
int cap;        //Capacidade da minha fila (n° de elementos)
int topo;       //Índice do elemento do topo
int primeiro;   //Índice do primeiro elemento
int *ponteiro;  //Ponteiro que aponta para a locação de memória

};

void construtorFila(struct fila *f,int tamanho){

f->topo = -1;
f->primeiro = -1;
f->cap = tamanho;      //n° de elementos 
f->ponteiro = (int*)malloc(tamanho*(sizeof(int))); /*Memory Allocation, a função malloc recebe como parâmetro o número de bytes
                                                  que irá alocar na memória (por isso o: "sizeof(int)""), porém como esta função retorna o 
                                                  endereço do bloco de memória, é necessário fazer um cast: (int*) para que um ponteiro de mesmo tipo 
                                                  receba esse endereço. */
if(f->ponteiro == NULL){
    printf("A alocação na memoria não funcionou, nao exite espaço na memória");
}

for(int i = 0;i<tamanho;i++){
  f->ponteiro[i]=0;
}

}

bool cheiaFila(struct fila *f){

if(f->primeiro == (f->topo+1)){

  return true;   //true == esta cheia
                 //situação de cheia com remoção/movimentação     
}

if((f->primeiro == -1) && (f->topo+1 == f->cap)){
  return true;   //true == esta cheia
                 //situação de cheia sem remoção
}
  
else{return false;}    //false == não esta cheia

}

void inserirFila(struct fila *f,int valor){

if(cheiaFila(f) == false){    //Se a fila não esta cheia

  if(((f->topo+1) == f->cap) && ((f->primeiro) == 0)){

    f->topo = 0;                  //Situação onde a representação da fila é circular,
    f->ponteiro[f->topo] = valor; //no qual, o espaço vazio liberado pela remoção dos
                                  //primeiros pode ser reutilizado   
  }

  else{ 
    
    f->topo++;                     //Inserção nomal da fila sendo pelo topo
    f->ponteiro[f->topo] = valor;
    
    }
}

else{
  printf("\nA fila esta cheia, nao e´ possivel inserir o valor: %i\n",valor);
}

}

bool vaziaFila(struct fila *f){

if((f->topo == -1) && (f->primeiro == -1)){

  return true;  //true == esta vazia
                //1° Situação:
                //Não houve inserção de nenhum elemento, 
                //fila no seu estado de construção
}

else if((f->primeiro) == (f->topo+1)){
  if(((f->ponteiro[f->topo]) == 0) && ((f->ponteiro[f->primeiro]) == 0)){

    return true;  //true == esta vazia
                  //2° Situação:
                  //quando houve inserção/movimentação,
                  //fila não esta no seu estado de construção
  }

else{return false;} //false == não esta vazia
                    
}

else if((f->primeiro+1) == (f->cap)){
  if(((f->ponteiro[f->topo]) == 0) && ((f->ponteiro[f->primeiro]) == 0)){

    return true;  //true == esta vazia
                  //3° Situação: 
                  //Onde houve apenas inserção sem remoção.
                  //Quando o "topo" esta na última posição e o "primeiro"
                  //esta na posição [0] da memória
  }

else{return false;} //false == não esta vazia
  
}

else{return false;}  //false == não esta vazia

}

void remocao(struct fila *f){

if((f->primeiro) == -1){  //Foi preferível que no método construtor: "f->primeiro = -1"
  f->primeiro++;          //para não interferir na lógica da função vaziaFila 2° Situação.
                          //Portanto a movimentação de "f->primeiro++"" foi aplicada apenas na função remocao
}

if(vaziaFila(f) == false){ //Se a fila não esta vazia

  if((f->primeiro + 1) == (f->cap)){

    f->ponteiro[f->primeiro] = 0;
    f->primeiro = 0;

  }
    
  else{
    f->ponteiro[f->primeiro] = 0;
    f->primeiro++;
  }
}

else{

  printf("\nA fila esta vazia, nao e' possivel de remover elementos que nao foram inseridos\n");

}
}

int buscaValor(struct fila *f,int posicao){

  return f->ponteiro[posicao-1];

}


int main(){

struct fila minhaFila;
int tamanho, amostra;  //amostra é a variável de controle para a repetição das instruções
double populacao[50];  //populacao é apenas o total operações de cada tipo
clock_t tempo;
double soma = 0;

printf( "\nQual o tamanho de locacao da pilha? " );
scanf("%i",&tamanho);

construtorFila(&minhaFila,tamanho);

//------------------- 1°: Tempo de inserção ----------------------------

amostra = 0;
while(amostra<50){

  tempo = clock();

  for(int i = 1;i<=tamanho;i++){
    
    inserirFila(&minhaFila,i);
    
  }

  tempo = clock() - tempo;
  
  for(int i = 1;i<=tamanho;i++){

    remocao(&minhaFila);
    
  }

  populacao[amostra] = ((double)tempo)/CLOCKS_PER_SEC;
  
  amostra++;

  }

soma = 0;
for(int i = 0;i<50;i++){  //Somatório de todos os tempos para depois fazer a média
  soma += populacao[i];
}

printf("\nTempo para inserir: %fs\n\n",(double)((soma)/50));
  //------------------- 2°: Tempo para percorrer e somar ----------------------------

amostra = 0;
while(amostra<50){

  soma = 0;

  for(int i = 1;i<=tamanho;i++){
  
  inserirFila(&minhaFila,i);
  
  }

  tempo = clock();
  
  for(int i = 1;i<=tamanho;i++){
    
    soma += buscaValor(&minhaFila,i);
    
  }

  tempo = clock() - tempo;

  populacao[amostra] = ((double)tempo)/CLOCKS_PER_SEC;

  amostra++;

}

soma = 0;
for(int i = 0;i<50;i++){
  soma += populacao[i];
}

printf("\nTempo para percorrer e somar: %fs\n\n",(double)((soma)/50));

//------------------- 3°: Tempo de busca ----------------------------


amostra = 0;
while(amostra<50){

  tempo = clock();

  for(int i = 1;i<=tamanho;i++){
    
    if(buscaValor(&minhaFila,i) != i){
      printf("\nO inteiro: %i nao esta na pilha",i);
      }
  }

  for(int i = tamanho;i>0;i--){
    
    if(buscaValor(&minhaFila,i) != i){
      printf("\nO inteiro: %i nao esta na pilha",i);
      }
  }
  

  tempo = clock() - tempo;

  populacao[amostra] = ((double)tempo)/CLOCKS_PER_SEC;
  
  amostra++;

  }

soma = 0;
for(int i = 0;i<50;i++){
  soma += populacao[i];
}

printf("\nTempo para verificar: %fs\n\n",(double)((soma)/50));

return 0;
}