#include "header.h"

//  Função que verifica se uma string é nula ou armazena o valor da exceção determinada. (Auxiliares.c:8:1)
int isNullString(char *string);

//  Função que transforma um inteiro em uma string e a retorna. (Auxiliares.c:13:1)
char *toString(int x);

//  Função que retorna o conteúdo de uma string entre aspas. (Auxiliares.c:20:1)
char *quotesString(char **string);

//  Função que retorna o maior inteiro de um par. (Auxiliares.c:25:1)
int greatInt(int a, int b);

//  Função que retorna a altura de um nó na árvore binária, retornando zero se o nó é nulo. (Auxiliares.c:30:1)
int nodeHeight(tecnologia *node);

//  Função que corrige a altura de um nó na árvore. (Auxiliares.c:35:1)
void fixHeight(tecnologia *node);

//  Função que retorna o fator de balanceamento de um nó na árvore. (Auxiliares.c:40:1)
int balanceFactor(tecnologia *node);

//  Função de rotação na árvore. (Auxiliares.c:45:1)
void LLrotate(tecnologia **node);

//  Função de rotação na árvore. (Auxiliares.c:59:1)
void RRrotate(tecnologia **node);

//  Função que retorna uma nova tecnologia que armazena uma string na árvore. (Funcionalidade 1)
//  (Auxiliares.c:73:1)
node *newNode(registro *obj);

//  Função que retorna um novo nó que armazena um registro da lista. (Funcionalidade 3)
//  (Auxiliares.c:83:1)
tecnologia *newTec(char *Tecnologia);

//  Função que insere um nó de registro em uma lista. (Auxiliares.c:92:1)
void insereNode(node **no, registro *data);

//  Função que verifica se um certo campo "field" requisitado pelo input consiz
//  com o critério imposto, "criterion". (Auxiliares.c:101:1)
int verificaCampo(registro *obj, char *field, char *criterion);

//  Função que imprime os campos de registro, imprimindo "NULO" em campos nulos. (Auxiliares.c:124:1)
int imprimeRegistro(registro *obj);

//  Função recursiva que imprime os campos de todos os registros compatíveis com o critério imposto
//  em uma lista. (Auxiliares.c:140:1)
int imprimeLista(node *head, char *field, char *criterion);

//  Função que libera a memória de uma lista de registros. (Auxiliares.c:149:1)
void destroiLista(node *head);

//  Função que busca uma tecnologia em uma árvore binária. (Auxiliares.c:156:1)
void buscaPar(tecnologia **root, char *s_tecPar, cabecalho *cabe);

//  Função que busca, em uma lista de pares de um nó na árvore, se o pair inserido já existe. (Auxiliares.c:193:1)
void buscaTec(tecnologia **root, char *s_Tecnologia, char *s_tecPar, cabecalho *cabe);

void binarioNaTela(char *nomeArquivoBinario);