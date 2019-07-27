#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
#include "header.h"




// Função de tempo
double timeofday(){
  struct timeval tv;
  gettimeofday(&tv,0);
  return tv.tv_sec + tv.tv_usec/1e6;
}
//
void freeMatriz (int ** matriz, int NumVertices){
int i;
for (i=0; i < NumVertices; i++){
free(matriz[i]);
}
free (matriz);
}

int Colorir (int ** matriz, Vertices * vertice, int NumVertices, int VerticeColorir, int * cores){
  int numMinimo=0, i, j, condicao=0, k=0;

  for (i=0; i < NumVertices; i++){ // "Zera" as cores dos vértices, para serem coloridos novamente //
    vertice[i].cor=1;
  }
    
    
  for (i=VerticeColorir; i < NumVertices; i++){
    condicao++;
    if (condicao == NumVertices+1){ // Evita de colorir grafos, que já foram coloridos anteriormente.//
      break;
    }
     
    for(j=0; j < NumVertices; j++){
      if (matriz[i][j]==1){   // Verifica adjacência entre os vértices //
        if (vertice[i].cor == vertice[j].cor){
          for (k=0; k < NumVertices; k++){  // Caminha no vetor de cores //
            if (vertice[i].cor == cores[k]){ // Colore o vértice adjacente //
              vertice[j].cor = cores[k+1];
              k=NumVertices;  // Quebra o laço //
            }
          }
        }
      }
    }
    if (i==NumVertices-1){ // Garante que colora todos os vértices //
      i=-1;
    }
  }

  
  for (i=0; i < NumVertices; i++){
    if (vertice[i].cor >= numMinimo){ // Acha o número mínimo de cores, para colorir o grafo //
      numMinimo=vertice[i].cor;
    }
  }
  
  return numMinimo;
}



int Algoritmo1(int ** matriz, Vertices * vertice, int NumVertices){
  int i=0, MenorColoracao=0, Vertice;
  int *  numMinimo, * cores;
  cores= (int*)malloc(NumVertices * sizeof(int));
  for(i=0; i < NumVertices; i++){
    cores[i]= cores[i-1] + 1; // Preenche o vetor de cores com N cores, onde N é o número de vértices. //
  }

  numMinimo= (int*)malloc(NumVertices * sizeof(int));
  for (i=0; i < NumVertices; i++){ 
    Vertice=vertice[i].indice;
    numMinimo[i]=Colorir(matriz, vertice, NumVertices, Vertice, cores); // Salva no vetor, o número mínimo de cor. //
  }
  MenorColoracao=numMinimo[0];
  for (i=0; i < NumVertices; i++){
    if (numMinimo[i] <= MenorColoracao){ // Compara no vetor de números mínimos possíveis para colorir um grafo, o menor número possível para coloração. //
      MenorColoracao=numMinimo[i];
    }
  }
  free(cores);
  free(numMinimo);
  return MenorColoracao;
}



int particiona_struct(Vertices * vetor, int inicio, int fim)
{
    int esq, dir;
    Vertices pivo, aux;
    esq = inicio;
    dir = fim;
    pivo = vetor[inicio];
    while(esq < dir)
    {
            while(vetor[esq].grau >= pivo.grau && esq < fim)
                    esq++;

            while(pivo.grau > vetor[dir].grau)
                    dir--;

            if(dir < inicio || esq > fim) printf("\nERRO\n\n");
            if(esq < dir)
            {
             
                    aux = vetor[esq]; // troca vetor[esq] com vetor[dir]
                    vetor[esq] = vetor[dir];
                    vetor[dir] = aux;
            }
    }
    vetor[inicio] = vetor[dir];
    vetor[dir] = pivo;

    //retorna dir, que é o novo pivô
    return dir;
}

void QuickSort(Vertices *vetor, int inicio, int fim)
{
  
    int pivo;
    if(inicio < fim)
    {
        pivo = particiona_struct(vetor,inicio,fim); // encontra um pivo que "divide" o vetor em dois
        QuickSort(vetor, inicio, pivo-1); // realiza a partição para a parte da esquerda
        QuickSort(vetor, pivo+1, fim); // e realiza a partição para a parte de direita
    }
}



int Heuristica2(int ** matriz, Vertices * vertice, int NumVertices){
  int i, j, k, numMinimo=0;
  int * cores;
  
  cores= (int*)malloc(NumVertices * sizeof(int));
  for(i=0; i < NumVertices; i++){
    cores[i]= cores[i-1] + 1;    // Preenche o vetor de cores com N cores, onde N é o número de vértices //
  }

  for (i=0; i < NumVertices; i++){
    for(j=0; j < NumVertices; j++){
      if (matriz[vertice[i].indice][j]==1){ // Verifica de acordo com o vetor ordenado, o índice de cada vértice, para fazer comparação na matriz //
        if (vertice[vertice[i].indice].cor == vertice[j].cor){
          for (k=0; k < NumVertices; k++){ // Percorre o vetor de cores //
            if (vertice[vertice[i].indice].cor == cores[k]){
            vertice[j].cor = cores[k+1]; // Faz a troca com o adjacente //
            k=NumVertices; // Quebra o laço //
            }
         
          }
        }
      }
    }
  }
  
  for (i=0; i < NumVertices; i++){
    if (vertice[i].cor >= numMinimo){
      numMinimo=vertice[i].cor; // Acha o número mínimo de cores, para colorir o grafo //
      
    }
  }
  free(cores);
  return numMinimo;
}



int Heuristica1(int ** matriz, Vertices * vertice, int NumVertices){
  int i, j, k, numMinimo=0;
  int * cores;
  
  cores= (int*)malloc(NumVertices * sizeof(int));
  for(i=0; i < NumVertices; i++){
    cores[i]= cores[i-1] + 1; // Preenche o vetor de cores com N cores, onde N é o número de vértices //
  }

  for (i=0; i < NumVertices; i++){
    for(j=0; j < NumVertices; j++){
      if (matriz[i][j]==1){ // Verifica adjacência entre os vértices //
        if (vertice[i].cor == vertice[j].cor){
          for (k=0; k < NumVertices; k++){ // Caminha no vetor de cores //
            if (vertice[i].cor == cores[k]){ 
              vertice[j].cor = cores[k+1]; // Colore o vértice adjacente //
              k=NumVertices; // Quebra o laço //
            }
          }
        }
      }
    }
  }

  for (i=0; i < NumVertices; i++){
    if (vertice[i].cor >= numMinimo){ // Acha o número mínimo de cores, para colorir o grafo //
      numMinimo=vertice[i].cor;
    }
  }
  free(cores);
  return numMinimo; 
}
