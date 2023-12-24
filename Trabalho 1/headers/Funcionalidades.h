#include "ArvoreB.h"

//  Função que performa o procedimento da funcionalidade um, obtendo, a partir de um arquivo
//  "arqEntrada", um arquivo de saída "arqSaida" e evoca a função "binarioNaTela". (Funcionalidades.c:9:1)
void Funcionalidade1(char *arqEntrada, char *arqSaida);

//  Função que performa o processo da funcionalidade dois, imprimindo os
//  registros de um arquivo de entrada, "arqEntrada". (Funcionalidades.c:68:1)
void Funcionalidade2(char *arqEntrada);

//  Função que performa o processo da funcionalidade três, imprimindo os registros
//  de tamanhos compatíveis um número "n" de chamadas. (Funcionalidades.c:90:1)
void Funcionalidade3(char *arqEntrada, int n);

//  Função que performa a funcionalidade quatro, imprimindo um registro na
//  posição "RRN" do arquivo "arqEntrada". (Funcionalidades:127:1)
void Funcionalidade4(char *arqEntrada, int RRN);

void Funcionalidade5(char *arqDados, char *arqIndice);

void Funcionalidade6(char *arqDados, char *arqIndice, int n);

void Funcionalidade7(char *arqDados, char *arqIndice, int n);

//  Função que evoca a funcionalidade requisitada a partir do input. (Auxiliares.c:203:1)
void defineOperacao(int op);