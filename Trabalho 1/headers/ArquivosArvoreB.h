#include "Arquivos.h"

//  Estrutura que representa o cabeçalho de um arquivo de índice,
//  apresentando o status, o RRN do nó raíz e o próximo nço a ser inserido.
typedef struct CabecalhoIndice {
    char status;
    int noRaiz, RRNproxNo;
} cabecalhoIndice;

//  Estrutura que representa um registro de um arquivo de índice,
//  apresentando um inteiro de referência a seus descendentes, chaves de busca
//  e os ponteiros de referência para o RRN do registro de dados correspondente,
//  além dos indicadores de número de chaves, de altura e o RRN do registro.
typedef struct RegistroIndice {
    int nroChavesNo, alturaNo, RRNdoNo;
    int P1, PR1, P2, PR2, P3, PR3, P4, Ptmp, PRtmp;
    char *C1, *C2, *C3, *Ctmp;
} registroIndice;

//  Estrutura que representa uma chave de um registro de índice correspondente
//  a um registro de dados.
typedef struct Chave {
    int *ponteiroEsq, *ponteiroDir, *ponteiroDados;
    char *chaveBusca;
} chaveRegistro;

//  Estrutura que representa uma página no arquivo de índice, no qual os endereços dos 
//  campos das chaves têm o mesmo endereço que os campos correspondentes em uma
//  estrutura de registro de índice, fazendo com que as chaves no registro sejam iteráveis.
typedef struct PaginaIndice {
    chaveRegistro **chaves;
} pagina;

#define TAM_CABECALHO_INDICE 205
#define TAM_REGISTRO_INDICE 205
#define NULL_KEY "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\0"
#define ERRO -1
#define PROMOCAO 11
#define SEM_PROMOCAO 12

//  Função que concatena duas strings.
char *concatecaTec(char *tecA, char *tecB);

//  Função que preenche uma chave com '$' até os 55 bytes.
char *completaChave(char *chave);

//  Função que retorna a chave sem lixo no fim.
char *noChave(char *chave);

//  Função que lê o cabeçalho de um arquivo de índice.
cabecalhoIndice *lerCabecalhoIndice(FILE *arq);

//  Função que lê um registro do arquivo de índice.
registroIndice *lerRegistroIndice(FILE *arq);

//  Função que escre um registro no arquivo de índice em um dado RRN.
void escreveRegistroIndice(FILE *arq, int RRN, registroIndice *registro);

//  Função que escreve um cabeçalho no início de um arquivo de índice.
void escreveCabecalhoIndice(FILE *arq, cabecalhoIndice *cab);

//  Função que inicializa uma chave de registro de acordo com uma chave de busca e uma referência ao arquivo de dados.
chaveRegistro *inicializaChave(char *chaveBusca, int PR);

//  Função que inicializa um registro, com campos e chaves nulos.
registroIndice *inicializaRegistro();

//  Função que retorna um cabeçalho genérico, com atributos nulos.
cabecalhoIndice *inicializaCabecalho();

//  Função que inicializa uma chave de registro com todos os atributos.
chaveRegistro *criaChave(char *chaveBusca, int *ponteiroEsquerda, int *ponteiroDireita, int *ponteiroDados);

//  Função que cria uma página de índice que contém os campos de um certo registro.
pagina *criaPagina(registroIndice **registro);

//  Função que libera a memória de uma chave.
void destroiChave(chaveRegistro *chave);

//  Função que libera a memória de um registro de índice.
void destroiRegistroIndice(registroIndice *registro);

//  Função que inicializa um cabeçalho de dados com campos.
cabecalho *inicializaCabecalhoDados();