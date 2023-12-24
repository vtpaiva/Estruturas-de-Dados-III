#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Alunos - G17:
//  Felipe Aparecido da Silva - 11954502.
//  Vítor Augusto Paiva de Brito - 13732303.

//  Estrutura que armazena os dados de um cabeçalho de um arquivo.
typedef struct {
    int proxRRN, nroTecnologias, nroParesTecnologias;
    char status;
} cabecalho;

//  Estrutura que armazena os dados de um registro em um arquivo.
typedef struct{
    int grupo, popularidade, peso;
    int tamanhoTecOrigem, tamanhoTecDestino;
    char removido, *tecOrigem, *tecDestino;
} registro;

//  Estrutura que representa um nó de uma árvore binária AVL, armazenando a altura 
//  em que o nó se encontra, uma tecnologia, "tec", dois nós filhos, "left" e "right", e
//  um elemento "pair" que representa um nó inicial de uma lista embutida que armazena
//  os pares existentes correspondentes à tecnologia "tec" caracterizada em específico.
//  Estrutura implementada na funcionalidade um.
typedef struct Tecnologia{
    struct Tecnologia *left, *right, *pair;
    char *tec;
    int height;
} tecnologia;

//  Estrutura que representa um nó de uma lista encadeada, em que cada nó armazena um registro 
//  a fim de que sejam armazenados os dados dos registros de um arquivo.
typedef struct Node{
    registro *data;
    struct Node *next;
} node;

//  Constantes referentes ao projeto.
#define NULL_INT "-1"
#define NULL_STRING ""
#define TAM_REGISTRO 76
#define TAM_CABECALHO 13
#define NULL_PRINT "NULO"