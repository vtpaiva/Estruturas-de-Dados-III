#include "Arquivos.h"

#define TAMANHO_TABELA 9999

//  TAD componente da tabela hash.
typedef struct {
    char* chave;
    int valor;
} Entrada;

//  Estrutura que representa uma tabela hash, com valores de chaves e inteiros.
typedef struct {
    Entrada* entradas[TAMANHO_TABELA];
} TabelaHash;

// Função de hash simples para strings.
unsigned int hash(const char* chave);

// Inicializar a tabela Hash.
void inicializarTabelaHash(TabelaHash* h);

// Inserir um par chave-valor na tabela Hash.
void inserirNaTabelaHash(TabelaHash* h, const char* chave, int valor);

// Procurar um valor por chave na tabela Hash.
int buscarNaTabelaHash(const TabelaHash* h, const char* chave);

// Liberar a memória alocada pela tabela Hash.
void liberarTabelaHash(TabelaHash* h);