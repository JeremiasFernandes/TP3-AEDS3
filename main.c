
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
#include "header.h"




int main (int argc, char ** argv){
  int NumVertices, numMinimo, opt, maiorVert;
  int ** matriz;
  int i, j=0;
  double t1, t2; // Variáveis do tempo //
  char * entrada=NULL, * saida=NULL, * codigo=NULL;
  while( (opt = getopt(argc, argv, "i:o:c:")) > 0 ) { // Lê o arquivo de entrada, e o método de coloração
              switch ( opt ) {
                case 'i':
                entrada= optarg;
                break;
                case 'c':
                codigo = optarg;
                break;
                default:
                exit(1);

              }
    }
  t1= timeofday(); // Começa a contagem do tempo //
  NumVertices= Ler(entrada);
  Vertices * vertices;
  vertices= (Vertices*)malloc(NumVertices * sizeof(Vertices));
  for (i=0; i < NumVertices; i++){ // Inicia cada vértice do grafo, com a cor 1 e o grau 0
    vertices[i].cor=1;
    vertices[i].grau=0;
  }
  matriz=PreencherMatriz(matriz, NumVertices, entrada, vertices);

  switch (codigo[0]){ // Escolhe qual método colorir o grafo
          case '1':
            numMinimo=Algoritmo1(matriz, vertices, NumVertices);
            freeMatriz(matriz, NumVertices);
            break;
          case '2':
            numMinimo=Heuristica1(matriz, vertices, NumVertices);
            freeMatriz(matriz, NumVertices);
            break;
          case '3':
            QuickSort(vertices, 0, NumVertices -1);
            numMinimo = Heuristica2(matriz, vertices, NumVertices);
            freeMatriz(matriz, NumVertices);
            break;
            default:
            printf ("Entrada inválida, escolha um número válido.\n");
            exit(1);
  }
  free(vertices);

  printf ("\n O número cromático mínimo é: %d \n", numMinimo);
  t2= timeofday(); // Termina a contagem do tempo //
  printf (" Tempo: %lf\n", t2-t1); // Printa a diferença //
  return 0;
}
