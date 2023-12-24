#include "Arquivos.h"

//  Alunos - G17:
//  Felipe Aparecido da Silva - 11954502.
//  Vítor Augusto Paiva de Brito - 13732303.

//  Função que retorna o próximo campo de uma string retirada de um arquivo CSV
//  separada por vírgulas, retornando uma exceção, "exception", caso o campo seja nulo.
char *proximoCampo(char **st, char *exception){

//  Se a string não existir ou for vazia, retorne a exceção.
    if(!*st || !strlen(*st)) {return exception;}

//  Cria uma cópia da string.
    char *tmp = strdup(*st);

//  Retorna, caso o primeiro caractere seja uma vírgula, ou seja, o campo é nulo, a exceção e,
//  caso contrário, retorne a parcela da string até a vírgula.
    if(*st[0] != ',') {
        if(*st = strchr(*st, ',')) {++*st;}
        return strtok(tmp, ",");
    }

    return ++*st, exception;
}

//  Função que lê o cabeçalho de um arquivo binário.
cabecalho *lerCabecalhoBin(FILE *arq){
//  Inicializa uma variável de cabeçalho;
    cabecalho *obj = malloc(sizeof(cabecalho));

//  Lê o status do cabeçalho.
    fread(&(obj -> status), 1, 1, arq);

//  Retorna uma falha caso o status esteja inconsistente.
    if(obj -> status == '0') {return NULL;}

//  Lê o restante dos campos do cabeçalho.
    fread(&(obj -> proxRRN), sizeof(int), 1, arq);
    fread(&(obj -> nroTecnologias), sizeof(int), 1, arq);
    fread(&(obj -> nroParesTecnologias), sizeof(int), 1, arq);

//  Retorna o endereço da variável cabeçalho.
    return obj;                  
}

//  Função que lê um registro de um arquivo binário.
registro *lerRegistroBin(FILE *arq){
//  Inicializa uma variável de registro.
    registro *obj = malloc(sizeof(registro));

    if(!fread(&(obj -> removido), sizeof(char), 1, arq)) {return NULL;}

    fread(&(obj -> grupo), sizeof(int), 1, arq);
    fread(&(obj -> popularidade), sizeof(int), 1, arq);
    fread(&(obj -> peso), sizeof(int), 1, arq);

//  Lê o tamanho da tecnologia de origem e lê a string posteriormente.
    fread(&(obj -> tamanhoTecOrigem), sizeof(int), 1, arq);
    obj -> tecOrigem = malloc(sizeof(char) * obj -> tamanhoTecOrigem + 1);
    fread(obj -> tecOrigem, sizeof(char) * obj -> tamanhoTecOrigem, 1, arq);
    obj -> tecOrigem[obj -> tamanhoTecOrigem] = '\0';

//  Lê o tamanho da tecnologia de origem e lê a string posteriormente.
    fread(&(obj -> tamanhoTecDestino), sizeof(int), 1, arq);
    obj -> tecDestino = malloc(sizeof(char) * obj -> tamanhoTecDestino + 1);
    fread(obj -> tecDestino, sizeof(char) * obj -> tamanhoTecDestino, 1, arq);
    obj -> tecDestino[obj -> tamanhoTecDestino] = '\0';

//  Ignora os lixos no final do registro.
    fseek(arq, 55 - (obj -> tamanhoTecOrigem + obj -> tamanhoTecDestino), SEEK_CUR);

//  Retorna um endereço de objeto.
    return obj;
}

//  Função que inicializa um cabeçalho de um arquivo e o escreve no novo binário.
cabecalho *lerCabecalhoCsv(FILE *new){
    cabecalho *cabe = malloc(sizeof(cabecalho));

//  Inicializa os campos do cabeçalho como nulos, inicialmente.
    cabe -> status = '0';
    cabe -> proxRRN = 0;
    cabe -> nroTecnologias = 0;
    cabe -> nroParesTecnologias = 0;

//  Escreve o novo cabeçalho no arquivo binário.
    escreveCabecalho(new, cabe);

//  Retorna um endereço de cabeçalho.
    return cabe;
}

//  Função que lê um registro de um arquivo CSV.
registro *lerRegistroCsv(char *st){
//  Inicialização de uma variável registro.
    registro *obj = malloc(sizeof(registro));

//  Leitura dos campos e preenchimento da variável registro.
    obj -> removido = '0';
    obj -> tecOrigem = proximoCampo(&st, NULL_STRING);
    obj -> tamanhoTecOrigem = (!isNullString(obj -> tecOrigem)) ? strlen(obj -> tecOrigem) : 0;
    obj -> grupo = atoi(proximoCampo(&st, NULL_INT));
    obj -> popularidade = atoi(proximoCampo(&st, NULL_INT));
    obj -> tecDestino = proximoCampo(&st, NULL_STRING);
    obj -> tamanhoTecDestino = (!isNullString(obj -> tecDestino)) ? strlen(obj -> tecDestino) : 0;
    obj -> peso = atoi(proximoCampo(&st, NULL_INT));

//  Retorna um endereço de registro.
    return obj;
}

//  Função que escreve um cabeçalho em um arquivo binário.
void escreveCabecalho(FILE *new, cabecalho *obj){
//  Escreve os campos.
    fputc(obj -> status, new);
    fwrite(&(obj -> proxRRN), sizeof(int), 1, new);
    fwrite(&(obj -> nroTecnologias), sizeof(int), 1, new);
    fwrite(&(obj -> nroParesTecnologias), sizeof(int), 1, new);
}

//  Função que escreve um registro em um arquivo binário.
void escreveRegistro(FILE *new, registro *obj) {
    fputc(obj -> removido, new);
    fwrite(&(obj -> grupo), sizeof(int), 1, new);
    fwrite(&(obj -> popularidade), sizeof(int), 1, new);
    fwrite(&(obj -> peso), sizeof(int), 1, new);
    fwrite(&(obj -> tamanhoTecOrigem), sizeof(int), 1, new);
    fwrite(obj -> tecOrigem, strlen(obj -> tecOrigem), 1, new);
    fwrite(&(obj -> tamanhoTecDestino), sizeof(int), 1, new);
    fwrite(obj -> tecDestino, strlen(obj -> tecDestino), 1, new);
}

//  Função que escreve os caracteres residuais em um registro.
void escreveLixo(FILE *new, registro *obj) {
    for(int i = 0; i++ < 55 - (obj -> tamanhoTecDestino + obj -> tamanhoTecOrigem); fwrite("$", sizeof(char), 1, new));
}

//  Função que libera a memória de um registro.
void destroiRegistro(registro *obj){
    if(!isNullString(obj -> tecOrigem)) {free(obj -> tecOrigem);}
    if(!isNullString(obj -> tecDestino)) {free(obj -> tecDestino);}

    free(obj);
}

//  Função que libera a memória dos nós de tecnologia par na árvore binária a partir do primeiro nó.
void destroiPares(tecnologia *node){
    if(node -> pair) {destroiPares(node -> pair);}

    free(node -> tec), free(node);
}

//  Função que libera a memória dos nós de uma árvore binária, incluindo a lista de nós das tecnologias
//  pares.
void destroiArvore(tecnologia *root){
    if(root -> left) {destroiArvore(root -> left);}
    if(root -> right) {destroiArvore(root -> right);}

    destroiPares(root);
}