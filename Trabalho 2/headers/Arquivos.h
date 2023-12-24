#include "Auxiliares.h"

//  Alunos - G17:
//  Felipe Aparecido da Silva - 11954502.
//  Vítor Augusto Paiva de Brito - 13732303.

//  Função que retorna o próximo campo de uma string retirada de um arquivo CSV
//  separada por vírgulas, retornando uma exceção, "exception", caso o campo seja nulo.
//  (Arquivos.c:9:1)
char *proximoCampo(char **st, char *exception);

//  Função que lê o cabeçalho de um arquivo binário. (Arquivos.c:23:1)
cabecalho *lerCabecalhoBin(FILE *arq);

//  Função que lê um registro de um arquivo binário. (Arquivos:43:1)
registro *lerRegistroBin(FILE *arq);

//  Função que inicializa um cabeçalho de um arquivo e o escreve no novo binário.
//  (Arquivos.c:73:1)
cabecalho *lerCabecalhoCsv(FILE *new);

//  Função que lê um registro de um arquivo CSV. (Arquivos.c:90:1)
registro *lerRegistroCsv(char *st);

//  Função que escreve um cabeçalho em um arquivo binário. (Arquivos.c:109:1)
void escreveCabecalho(FILE *new, cabecalho *obj);

//  Função que escreve um registro em um arquivo binário.(Arquivos.c:118:1)
void escreveRegistro(FILE *new, registro *obj);

//  Função que escreve os caracteres residuais em um registro. (Arquivos.c:131:1)
void escreveLixo(FILE *new, registro *obj);

//  Função que libera a memória de um registro. (Arquivos.c:136:1)
void destroiRegistro(registro *obj);

//  Função que libera a memória dos nós de tecnologia par na árvore binária a partir do primeiro nó.
//  (Arquivos.c:144:1)
void destroiPares(tecnologia *node);

//  Função que libera a memória dos nós de uma árvore binária, incluindo a lista de nós das tecnologias
//  pares. (Arquivos.c:152:1)
void destroiArvore(tecnologia *root);
