#include "Hash.h"

//  Alunos - G17:
//  Felipe Aparecido da Silva - 11954502.
//  Vítor Augusto Paiva de Brito - 13732303.

// Função de hash simples para strings.
unsigned int hash(const char* chave) {
    unsigned int hash = 0;
    while (*chave) {
        hash = (hash * 31) + (*chave++);
    }
    return hash % TAMANHO_TABELA;
}

// Inicializar a tabela Hash.
void inicializarTabelaHash(TabelaHash* h) {
    for (int i = 0; i < TAMANHO_TABELA; ++i) {
        h->entradas[i] = NULL;
    }
}

// Inserir um par chave-valor na tabela Hash.
void inserirNaTabelaHash(TabelaHash* h, const char* chave, int valor) {
    Entrada* novaEntrada = malloc(sizeof(Entrada));
    novaEntrada->chave = malloc(sizeof(char) * (strlen(chave) + 1));
    strcpy(novaEntrada->chave, chave);
    novaEntrada->valor = valor;

    unsigned int indice = hash(chave);

    // Lidar com colisões usando sondagem linear.
    while (h->entradas[indice]) {
        indice = (indice + 1) % TAMANHO_TABELA;
    }

    h->entradas[indice] = novaEntrada;
}

// Procurar um valor por chave na tabela Hash.
int buscarNaTabelaHash(const TabelaHash* h, const char* chave) {
    // Procurar na tabela usando sondagem linear.
    for (unsigned int indice = hash(chave); h->entradas[indice]; indice = (indice + 1) % TAMANHO_TABELA) {
        if (!strcmp(h->entradas[indice]->chave, chave)) {
            return h->entradas[indice]->valor;
        }
    }

    // Chave não encontrada.
    return -1;
}

// Liberar a memória alocada pela tabela Hash.
void liberarTabelaHash(TabelaHash* h) {
    for (int i = 0; i < TAMANHO_TABELA; ++i) {
        if (h->entradas[i]) {
            free(h->entradas[i]->chave);
            free(h->entradas[i]);
        }
    }
}