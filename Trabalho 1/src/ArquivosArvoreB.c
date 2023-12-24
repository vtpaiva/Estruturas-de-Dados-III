#include "ArquivosArvoreB.h"

//  Função que concatena duas strings.
char *concatecaTec(char *tecA, char *tecB) {
    return strcat(strcpy(malloc(sizeof(char) * (strlen(tecA) + strlen(tecB) + 1)), tecA), tecB);
}

//  Função que preenche uma chave com '$' até os 55 bytes.
char *completaChave(char *chave) {
    return strcat(chave, memset(calloc(sizeof(char), (55 - strlen(chave))), '$', 55 - strlen(chave)));
}

//  Função que retorna a chave sem lixo no fim.
char *noChave(char *chave) {
    return strcmp(chave, NULL_KEY) ? strtok(strdup(chave), "$") : NULL_KEY;
}

//  Função que lê o cabeçalho de um arquivo de índice.
cabecalhoIndice *lerCabecalhoIndice(FILE *arq) {
    cabecalhoIndice *cab = malloc(sizeof(cabecalhoIndice));

    fread(&(cab -> status), sizeof(char), 1, arq);
    if(cab -> status == '0') {return NULL;}

    fread(&(cab -> noRaiz), sizeof(int), 1, arq);
    fread(&(cab -> RRNproxNo), sizeof(int), 1, arq);
    fseek(arq, sizeof(char) * 196, SEEK_CUR);

    return cab;
}

//  Função que lê um registro do arquivo de índice.
registroIndice *lerRegistroIndice(FILE *arq) {
    registroIndice *reg = malloc(sizeof(registroIndice));

    fread(&(reg -> nroChavesNo), sizeof(int), 1, arq);
    fread(&(reg -> alturaNo), sizeof(int), 1, arq);
    fread(&(reg -> RRNdoNo), sizeof(int), 1, arq);
    
    fread(&(reg -> P1), sizeof(int), 1, arq);
    fread(reg -> C1 = malloc(sizeof(char) * 56), sizeof(char), 55, arq);
    reg -> C1[55] = '\0';
    fread(&(reg -> PR1), sizeof(int), 1, arq);

    fread(&(reg -> P2), sizeof(int), 1, arq);
    fread(reg -> C2 = malloc(sizeof(char) * 56), sizeof(char), 55, arq);
    reg -> C2[55] = '\0';
    fread(&(reg -> PR2), sizeof(int), 1, arq);

    fread(&(reg -> P3), sizeof(int), 1, arq);
    fread(reg -> C3 = malloc(sizeof(char) * 56), sizeof(char), 55, arq);
    reg -> C3[55] = '\0';
    fread(&(reg -> PR3), sizeof(int), 1, arq);

    fread(&(reg -> P4), sizeof(int), 1, arq);
    strcpy(reg -> Ctmp = malloc(sizeof(char) * 56), NULL_KEY);
    reg -> Ptmp = reg -> PRtmp = -1;

    return reg;
}

//  Função que escre um registro no arquivo de índice em um dado RRN.
void escreveRegistroIndice(FILE *arq, int RRN, registroIndice *registro) {
    fseek(arq, TAM_CABECALHO_INDICE + RRN * TAM_REGISTRO_INDICE, SEEK_SET);

    fwrite(&(registro -> nroChavesNo), sizeof(int), 1, arq);
    fwrite(&(registro -> alturaNo), sizeof(int), 1, arq);
    fwrite(&(registro -> RRNdoNo), sizeof(int), 1, arq);
    fwrite(&(registro -> P1), sizeof(int), 1, arq);
    fwrite(completaChave(registro -> C1), sizeof(char), 55, arq);
    fwrite(&(registro -> PR1), sizeof(int), 1, arq);
    fwrite(&(registro -> P2), sizeof(int), 1, arq);
    fwrite(completaChave(registro -> C2), sizeof(char), 55, arq);
    fwrite(&(registro -> PR2), sizeof(int), 1, arq);
    fwrite(&(registro -> P3), sizeof(int), 1, arq);
    fwrite(completaChave(registro -> C3), sizeof(char), 55, arq);
    fwrite(&(registro -> PR3), sizeof(int), 1, arq);
    fwrite(&(registro -> P4), sizeof(int), 1, arq);
}

//  Função que escreve um cabeçalho no início de um arquivo de índice.
void escreveCabecalhoIndice(FILE *arq, cabecalhoIndice *cab) {
    fseek(arq, 0, SEEK_SET);

    if(cab) {
        fputc(cab -> status, arq);
        fwrite(&(cab -> noRaiz), sizeof(int), 1, arq);
        fwrite(&(cab -> RRNproxNo), sizeof(int), 1, arq);
    } else {
        int raizNULL = -1, rrnNULL = 0;

        fputc('0', arq);
        fwrite(&raizNULL, sizeof(int), 1, arq);
        fwrite(&rrnNULL, sizeof(int), 1, arq);
    }

    for(int i = 0; i++ < 196; fwrite("$", sizeof(char), 1, arq));
}

//  Função que retorna um cabeçalho genérico, com atributos nulos.
cabecalhoIndice *inicializaCabecalho() {
    cabecalhoIndice *cabe = malloc(sizeof(cabecalhoIndice));

    cabe -> noRaiz = -1;
    cabe -> RRNproxNo = 0;
    cabe -> status = '0';

    return cabe;
}

//  Função que inicializa uma chave de registro de acordo com uma chave de busca e uma referência ao arquivo de dados.
chaveRegistro *inicializaChave(char *chaveBusca, int PR) {
    chaveRegistro *chave = malloc(sizeof(chaveRegistro));

    chave -> ponteiroEsq = calloc(sizeof(int), 1);
    chave -> ponteiroDir = malloc(sizeof(int));
    chave -> ponteiroDados = malloc(sizeof(int));
    *chave -> ponteiroEsq = *chave -> ponteiroDir = -1;
    *chave -> ponteiroDados = PR;
    strcpy(chave -> chaveBusca = malloc(sizeof(char) * 56), chaveBusca);

    return chave;
}

//  Função que inicializa uma chave de regisstro com todos os atributos.
chaveRegistro *criaChave(char *chaveBusca, int *ponteiroEsquerda, int *ponteiroDireita, int *ponteiroDados) {
    chaveRegistro *chave = malloc(sizeof(chaveRegistro));

    chave -> ponteiroEsq = ponteiroEsquerda;
    chave -> ponteiroDir = ponteiroDireita;
    chave -> ponteiroDados = ponteiroDados;
    strcpy(chave -> chaveBusca = malloc(sizeof(char) * 56), chaveBusca);

    return chave;
}

//  Função que cria uma página de índice que contém os campos de um certo registro.
pagina *criaPagina(registroIndice **registro) {
    pagina *pag = malloc(sizeof(pagina));

    pag -> chaves = malloc(sizeof(char*) * 4);
    int NIL = -1;

    pag -> chaves[0] = criaChave((*registro) -> C1, &(*registro) -> P1, &(*registro) -> P2, &(*registro) -> PR1);
    (*registro) -> C1 = pag -> chaves[0] -> chaveBusca;
    pag -> chaves[1] = criaChave((*registro) -> C2, &(*registro) -> P2, &(*registro) -> P3, &(*registro) -> PR2);
    (*registro) -> C2 = pag -> chaves[1] -> chaveBusca;
    pag -> chaves[2] = criaChave((*registro) -> C3, &(*registro) -> P3, &(*registro) -> P4, &(*registro) -> PR3);
    (*registro) -> C3 = pag -> chaves[2] -> chaveBusca;
    pag -> chaves[3] = criaChave((*registro) -> Ctmp, &(*registro) -> P4, &(*registro) -> Ptmp, &(*registro) -> PRtmp);
    (*registro) -> Ctmp = pag -> chaves[3] -> chaveBusca;

    return pag;
}

//  Função que inicializa um registro, com campos e chaves nulos.
registroIndice *inicializaRegistro() {
    registroIndice *reg = malloc(sizeof(registroIndice));

    strcpy(reg -> C1 = malloc(sizeof(char) * 56), NULL_KEY);
    strcpy(reg -> C2 = malloc(sizeof(char) * 56), NULL_KEY);
    strcpy(reg -> C3 = malloc(sizeof(char) * 56), NULL_KEY);
    strcpy(reg -> Ctmp = malloc(sizeof(char) * 56), NULL_KEY);

    reg -> alturaNo = 1;
    reg -> nroChavesNo = reg -> RRNdoNo = 0;
    reg -> P1 = reg -> PR1 = -1;
    reg -> P2 = reg -> PR2 = -1;
    reg -> P3 = reg -> PR3 = -1;
    reg -> P4 = reg -> Ptmp = reg-> PRtmp = -1;

//  Retorna o regitro criado.
    return reg;
}

//  Função que libera a memória de uma chave.
void destroiChave(chaveRegistro *chave) {
    free(chave -> ponteiroEsq), free(chave -> ponteiroDir), free(chave -> ponteiroDados);

    free(chave);
}

//  Função que libera a memória de um registro de índice.
void destroiRegistroIndice(registroIndice *registro) {
    if(registro -> C1) {free(registro -> C1);} 
    if(registro -> C2) {free(registro -> C2);} 
    if(registro -> C3) {free(registro -> C3);} 
    if(registro -> Ctmp) {free(registro -> Ctmp);} 

    free(registro);
}

//  Função que inicializa um cabeçalho de dados com campos.
cabecalho *inicializaCabecalhoDados() {
    cabecalho *cabe = malloc(sizeof(cabecalho));

    cabe -> status = '0';
    cabe -> nroParesTecnologias = cabe -> nroTecnologias = cabe -> proxRRN = 0;

    return cabe;
}