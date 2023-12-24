#include "ArquivosArvoreB.h"

//  Alunos - G17:
//  Felipe Aparecido da Silva - 11954502.
//  Vítor Augusto Paiva de Brito - 13732303.

//  Função que retorna valores unitários ou nulos na comparação de chaves.
int comparaChave(char *a, char *b);

//  Função que copia o conteúdo dos endereços dos atributos de uma chave para
//  outra estrutura de chave de registro.
void keycpy(chaveRegistro *destino, chaveRegistro *origem);

//  Função que retorna um registro do arquivo de dados em um RRN específico.
registro *buscaRegistroDados(FILE *arq, int RRN);

//  Função que retorna um registro do arquivo de índice em um RRN específico.
registroIndice *buscaRegistroIndice(FILE *arq, int RRN);

//  Função que insere um novo registro em um arquivo de índice a partir de um registro de dados,
//  lidando com a inexistência da raiz e com overflow na raiz.
void insereArquivoIndice(FILE *arq, cabecalhoIndice **cabIndice, registro *reg, int PR);

//  Função de busca de chave em um arquivo de índice.
int buscaChaveRecursivo(FILE *arq, int RRN, char *chave);

//  Função que performa a operação da funcionalidade seis de acordo com o campo e com o critério requeridos.
int imprimeListaIndice(FILE *arqIndice, FILE *arqDados, cabecalhoIndice *cab, node *raiz, char *campo, char *criterio);

//  Função que executa a troca dos conteúdos dos atributos de um para de chaves.
void trocaChave(chaveRegistro *chaveA, chaveRegistro *chaveB);

//  Função que insere uma chave em um registro de índice.
int insereChaveNo(registroIndice *reg, chaveRegistro *chave);

//  Função que remove uma chave de um registro de índice de acordo com a chave de busca.
int removeChaveNo(registroIndice *reg, char *chave);

//  Função que retorna a posição da chave que uma dada chave de busca ocupa ou ocuparia em um nó.
int encontraPosicaoNo(registroIndice *reg, char *chave);

//  Função que retorna o ponteiro para o nó descendente no qual uma dada chave deveria estar.
int encontraPonteiroNo(registroIndice *reg, char *chave);

//  Função que realiza o split em um registro de índice que apresentou uma sobrecarga de chaves.
void splitRegistro(FILE *arq, int *R_RRN, chaveRegistro **PROMO_KEY, registroIndice **paginaAtual, registroIndice **novaPagina);

//  Função que insere uma chave em um arquivo de índice.
int insereChave(FILE *arq, int RRN, int *R_RRN, chaveRegistro *PROMO_KEY);

//  Função que lê um registro de dados de acordo com a impressão.
registro *leRegistroDados();