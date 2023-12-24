#include "Fila.h"

//  Alunos - G17:
//  Felipe Aparecido da Silva - 11954502.
//  Vítor Augusto Paiva de Brito - 13732303.

// Funções de criação, destruição, inserção, remoção e atualização da FilaPrioridade de prioridade (Heap Binária).
FilaPrioridade *criaFilaPrioridade(int MAX) {
    FilaPrioridade *f = malloc(sizeof(FilaPrioridade));
    f->p = malloc(sizeof(NoFilaPrioridade) * MAX);
    f->tamanhoMAX = MAX;
    f->tamanho = 0;
    return(f);
}

// Destruição da Fila de prioridade (Heap Binária).
void destroiFilaPrioridade(FilaPrioridade *f) {
    free(f->p);
    f->tamanhoMAX = 0;
    f->tamanho = 0;
}

// Faz a troca de dois nós da fila.
void trocaNos (FilaPrioridade *f, int a, int b){
    // Cópia dos valores da posição 'a'.
    int vaux, prioriaux;
    vaux = f->p[a].indice;
    prioriaux = f->p[a].prioridade;
    
    // Cópia dos valores da posição 'b' na posição 'a'.
    f->p[a].indice = f->p[b].indice;
    f->p[a].prioridade = f->p[b].prioridade;
    
    // Cópia dos antigos valores de 'a' em 'b'.
    f->p[b].indice = vaux;
    f->p[b].prioridade = prioriaux;
}

// Inserção de novo elemento na fila de prioridade (Heap binária).
void insereFilaPrioridade(FilaPrioridade *f, int indice, int prioridade) {
    // Erro: a fila de prioridade está cheia.
    if (f->tamanho == f->tamanhoMAX)
        return;
    
    // Coloca no fim da fila
    int i = f->tamanho;
    f->p[i].indice = indice;
    f->p[i].prioridade = prioridade;
    f->tamanho++;

    // Reorganiza fila usando a prioridade (subindo na árvore).
    while (i > 0 && f->p[i].prioridade < f->p[(i - 1) / 2].prioridade) {
        trocaNos(f, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}


// Remoção do primeiro elemento, a raíz, da fila de prioridade (Heap Binária).
NoFilaPrioridade removeFilaPrioridade(FilaPrioridade *f) {
    // Fila vazia.
    if (f->tamanho == 0) {
        NoFilaPrioridade emptyNode;
        emptyNode.indice = -1;
        emptyNode.prioridade = -1;
        return emptyNode;
    }

    // Cópia do nó raíz.
    NoFilaPrioridade root = f -> p[0];
    
    // Último da fila é colocado na raíz.
    f->p[0] = f->p[f->tamanho - 1];
    f->tamanho--;

	// Reorganiza fila.
    int i = 0;
    int menorFilho;
    while (2 * i + 1 < f->tamanho) {
        
        // Nó atual tem filhos.
        if (2 * i + 2 == f->tamanho) {
            menorFilho = 2 * i + 1;
        } 
        // Nó atual não tem filhos.
        else {
            
            // Escolhe o menor filho.
            if (f->p[2 * i + 1].prioridade < f->p[2 * i + 2].prioridade)
                menorFilho = 2 * i + 1;
             else
                menorFilho = 2 * i + 2;
        }
        
        // Nó atual é maior que o menor filho.
        if (f->p[i].prioridade > f->p[menorFilho].prioridade) {
            trocaNos(f, i, menorFilho);
            i = menorFilho;
        } 
        // O nó atual é menor ou igual ao menor filho.
        else {break;}
    }
    return root;
}

// Atualização da fila de Prioridade.
void atualizaFilaPrioridade(FilaPrioridade *f, int indice, int novaPrioridade) {
    // Percorre a fila de prioridade.
    for (int i = 0; i < f->tamanho; i++) {

		// Encontrou o vértice desejado.
        if (f->p[i].indice == indice) {
			
            // Atualiza a prioridade do vértice.
            f->p[i].prioridade = novaPrioridade;

            // Reorganiza a fila usando a nova prioridade.
            while (i > 0 && f -> p[i].prioridade < f -> p[(i - 1) / 2].prioridade) {
                trocaNos(f, i, (i - 1) / 2);
                i = (i - 1) / 2;
            }

            break;
        }
    }
}

// Verificação da presença do vértice na fila.
int estaNaFila(FilaPrioridade *H, int indice) {
	// Percorre fila.
	for (int i = 0; i < H->tamanho; i ++)
		// Está na fila.
		if (H->p[i].indice == indice)
			return 1;
	
	// Não está na fila.
	return 0;
}