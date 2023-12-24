#include "Fila.h"

//  Alunos - G17:
//  Felipe Aparecido da Silva - 11954502.
//  Vítor Augusto Paiva de Brito - 13732303.

#define INT_MAX 999999

// Tipo aresta do grafo
typedef struct aresta{
	struct VerticeGrafo *destino; 	// Vértice de destino da aresta
    int peso;    					// Peso da aresta
	struct aresta *prox;			// Ponteiro da próxima aresta da lista
} Aresta;

// Vértice para a lista de adjacêcia de cada vértice do grafo
typedef struct VerticeGrafo{
	char* nomeTecnologia;
	int grupo, grauEntrada, grauSaida, grau;
	struct aresta *aresta;	// Ponteiro para lista de arestas
} verticeGrafo;

// Estrutura do Grafo
typedef struct {
	int numMaxVertices;			// Número máximo de vértices
	int numVertices;			// Número efetivo de vértices
	verticeGrafo **lista_adj;	// Vetor para listas de adjacência

	int *distancia;				// Vetor de distâncias
	int *antecessor;			// Vetor de antecessores
	
	int *visitados;				// Vetor de vértices visitados
	int *tDescoberta;			// Vetor de tempo de descoberta de cada vértice
	int numComponentes;			// Número de componentes conexas
	int t;						// Tempo atual da busca

} Grafo;

// Função que inicializa e retorna um grafo de n vértices vazio
Grafo *iniciaGrafo(int n);

void ordenaVerticeDoGrafo(Grafo *G);

void binarioParaGrafo(FILE *arq, Grafo *G);

void printGrafo(Grafo *G);

void destroiGrafo(Grafo *G);

void transporGrafo(Grafo *G);

void printOrigem(Grafo *G, char *Destino);

void printConectividadeFortementeConexa(Grafo *G);

void printDistancia(Grafo *G, char *tecnologia1, char *tecnologia2);