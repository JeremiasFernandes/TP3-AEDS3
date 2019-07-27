#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
#include "header.h"






int Ler(char * entrada){
  FILE * arq1;
	arq1=fopen(entrada, "r");
	int NumVertices;
  if(arq1 == NULL){
    printf("ERRO na CRIACAO do arquivo: inicial\n");
    exit(1);
  }
  fscanf (arq1,"%d", &NumVertices); // Lê o número de vértice //
  return NumVertices;
}

int **PreencherMatriz(int ** matriz, int NumVertices, char * entrada, Vertices * vertices){
  FILE * arq2;
  int Vertice, Arestas, i, j, lixo;
  matriz= (int**)malloc(NumVertices * sizeof(int*));
  for (i=0; i < NumVertices; i++){
    matriz[i]= (int*)malloc(NumVertices * sizeof(int));
    for (j=0; j < NumVertices; j++){
      matriz[i][j]=0; // Preenche a matriz com 0, para evitar lixo de memória //
    }
  }
  arq2=fopen(entrada, "r");
  fscanf (arq2,"%d", &lixo); // Lê o número de vértice, que ja foi lido em outra função, por isso não há importancia //
  while( (fscanf(arq2,"%d %d",&Vertice , &Arestas))!=EOF ){
      matriz[Vertice][Arestas] = 1; // Preenche a matriz de adjacência
      matriz[Arestas][Vertice] = 1;                                    // 
      vertices[Vertice].indice= Vertice; // Guarda o índice de cada vértice
      vertices[Arestas].indice= Arestas;                                   //
      vertices[Vertice].grau++; // Conta o grau de cada vértice
      vertices[Arestas].grau++;                                //
  }
  return matriz;
}