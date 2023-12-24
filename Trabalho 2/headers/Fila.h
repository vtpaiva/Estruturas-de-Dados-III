#include "Hash.h"

// Estrutura do nó da FilaPrioridade de prioridade (Heap Binária)
typedef struct {
    int indice;      // Vértice
    int prioridade; // Prioridade
} NoFilaPrioridade;

// Estrutura da FilaPrioridade de prioridade (Heap Binária)
typedef struct {
    int tamanhoMAX, tamanho;// Tamanho máximo e tamanho atual da FilaPrioridade
    NoFilaPrioridade *p;              // Ponteiro para os nós da FilaPrioridade
} FilaPrioridade;

// Funções de criação, destruição, inserção, remoção e atualização da FilaPrioridade de prioridade (Heap Binária).
FilaPrioridade *criaFilaPrioridade(int MAX);

// Destruição da Fila de prioridade (Heap Binária).
void destroiFilaPrioridade(FilaPrioridade *f);

// Faz a troca de dois nós da fila.
void trocaNos (FilaPrioridade *f, int a, int b);

// Inserção de novo elemento na fila de prioridade (Heap binária).
void insereFilaPrioridade(FilaPrioridade *f, int indice, int prioridade);

// Remoção do primeiro elemento, a raíz, da fila de prioridade (Heap Binária).
NoFilaPrioridade removeFilaPrioridade(FilaPrioridade *f);

// Atualização da fila de Prioridade.
void atualizaFilaPrioridade(FilaPrioridade *f, int indice, int novaPrioridade);

// Verificação da presença do vértice na fila.
int estaNaFila(FilaPrioridade *H, int indice);