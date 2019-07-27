
// Estrutura para os vértices
typedef struct V{
  int cor, indice, grau;
}Vertices;
//

double timeofday();
int Colorir (int ** matriz, Vertices * vertice, int NumVertices, int VerticeColorir, int * cores);
void freeMatriz (int ** matriz, int NumVertices);
int Algoritmo1(int ** matriz, Vertices * vertice, int NumVertices);
int particiona_struct(Vertices * vetor, int inicio, int fim);
void QuickSort(Vertices *vetor, int inicio, int fim);
int Heuristica2(int ** matriz, Vertices * vertice, int NumVertices);
int Heuristica1(int ** matriz, Vertices * vertice, int NumVertices);
int Ler(char * entrada);
int **PreencherMatriz(int ** matriz, int NumVertices, char * entrada, Vertices * vertices);
