#include "ArvoreB.h"

//  Alunos - G17:
//  Felipe Aparecido da Silva - 11954502.
//  Vítor Augusto Paiva de Brito - 13732303.

//  Função que retorna valores unitários ou nulos na comparação de chaves.
int comparaChave(char *a, char *b) {
    int cmp;

    return (!(cmp = strcmp(a, b))) ? 0 : ((cmp > 0) ? 1 : -1);
}

//  Função que copia o conteúdo dos endereços dos atributos de uma chave para
//  outra estrutura de chave de registro.
void keycpy(chaveRegistro *destino, chaveRegistro *origem) {
    *(destino -> ponteiroDir) = *(origem -> ponteiroDir);
    *(destino -> ponteiroDados) = *(origem-> ponteiroDados);
    strcpy(destino -> chaveBusca, origem -> chaveBusca);
}

//  Função que retorna um registro do arquivo de dados em um RRN específico.
registro *buscaRegistroDados(FILE *arq, int RRN) {
    fseek(arq, TAM_CABECALHO + TAM_REGISTRO * RRN, SEEK_SET);

    return lerRegistroBin(arq);
}

//  Função que retorna um registro do arquivo de índice em um RRN específico.
registroIndice *buscaRegistroIndice(FILE *arq, int RRN) {
    fseek(arq, TAM_CABECALHO_INDICE + TAM_REGISTRO_INDICE * RRN, SEEK_SET);

    return lerRegistroIndice(arq);
}

//  Função que retorna a posição da chave que uma dada chave de busca ocupa ou ocuparia em um nó.
int encontraPosicaoNo(registroIndice *reg, char *chave) {
    pagina *pag = criaPagina(&reg);

    int i = reg -> nroChavesNo/2, j = 0;

//  Performa a busca binária no registro de índice.
    for(; i > 0 && i < 3 && comparaChave(pag -> chaves[i] -> chaveBusca, NULL_KEY) && 
    j != -comparaChave(chave, pag -> chaves[i] -> chaveBusca); j = comparaChave(chave, pag -> chaves[i] -> chaveBusca), i += j);

    j = (comparaChave(chave, pag -> chaves[i] -> chaveBusca) > 0 && comparaChave(pag -> chaves[i] -> chaveBusca, NULL_KEY));

    free(pag);

    return i + j;
}

//  Função que retorna o ponteiro para o nó descendente no qual uma dada chave deveria estar.
int encontraPonteiroNo(registroIndice *reg, char *chave) {
    switch(encontraPosicaoNo(reg, chave)) {
        case 0: return reg -> P1;
        case 1: return reg -> P2;
        case 2: return reg -> P3;
        case 3: return reg -> P4;
    }
}

//  Função que executa a troca dos conteúdos dos atributos de um para de chaves.
void trocaChave(chaveRegistro *chaveA, chaveRegistro *chaveB) {
    chaveRegistro *tmp = inicializaChave(NULL_KEY, -1);

//  Executa a troca de valores das chaves de registro.
    keycpy(tmp, chaveA);
    keycpy(chaveA, chaveB);
    keycpy(chaveB, tmp);

    destroiChave(tmp);
}


//  Função que insere uma chave em um registro de índice.
int insereChaveNo(registroIndice *reg, chaveRegistro *chave) {
//  Encontra a posição em que a chave deveria estar.
    int p = encontraPosicaoNo(reg, chave -> chaveBusca);

//  Cria uma página referente ao registro de índice.
    pagina *pag = criaPagina(&reg);

    chaveRegistro *cmp = chave;

//  Itera sobre as chaves do registro, inserindo a nova chave em sua posição e realocando o restante.
    for(int i = p; i < 4 && strcmp(cmp -> chaveBusca, NULL_KEY); i++) {
        if(!strcmp(pag -> chaves[i] -> chaveBusca, NULL_KEY) || strcmp(pag -> chaves[i] -> chaveBusca, cmp -> chaveBusca) > 0) {
            if(i == 0) {*pag -> chaves[i] -> ponteiroEsq = *cmp -> ponteiroEsq;}
            trocaChave(pag -> chaves[i], cmp);
        }
    }

    free(pag);

    reg -> nroChavesNo++;

//  Retorna PROMOCAO caso o registro tenha apresentado overflow.
    return strcmp(reg -> Ctmp, NULL_KEY) ? PROMOCAO : SEM_PROMOCAO;
}

//  Função que remove uma chave de um registro de índice de acordo com a chave de busca.
int removeChaveNo(registroIndice *reg, char *chave) {
//  Caso a chave não exista no registro, retorne um erro.
    if(strcmp(reg -> C1, chave) && strcmp(reg -> C2, chave) && strcmp(reg -> C3, chave) && strcmp(reg -> Ctmp, chave)) {return ERRO;}

    int p = encontraPosicaoNo(reg, chave);

    pagina *pag = criaPagina(&reg);

//  Itera sobre as chaves do registro de índice, removendo a chave requerida e realocando o restante.
    for(int i = p; i < 4 && strcmp(pag -> chaves[i] -> chaveBusca, NULL_KEY); i++) {
//  Caso a chave não for a última do registro, remova-a e copie a chave seguinte.
        if(i != 3) {
            if(i == 0) {*pag -> chaves[i] -> ponteiroEsq = *pag -> chaves[i + 1] -> ponteiroEsq;}
            strcpy(pag -> chaves[i] -> chaveBusca, pag -> chaves[i + 1] -> chaveBusca);
            *pag -> chaves[i] -> ponteiroDir = *pag -> chaves[i + 1] -> ponteiroDir;
            *pag -> chaves[i] -> ponteiroDados = *pag -> chaves[i + 1] -> ponteiroDados;
        }
//      Caso a chave requerida estiver na última posição, apenas remova a chave.
        else {
            strcpy(pag -> chaves[i] -> chaveBusca, NULL_KEY);
            *pag -> chaves[i] -> ponteiroDir = *pag -> chaves[i] -> ponteiroDados = -1;
        }
    }

    free(pag);

//  Retorna sucesso.
    return 1;
}

//  Função que realiza o split em um registro de índice que apresentou uma sobrecarga de chaves.
void splitRegistro(FILE *arq, int *R_RRN, chaveRegistro **PROMO_KEY, registroIndice **paginaAtual, registroIndice **novaPagina) {
//  Cria uma página referente ao registro de índice que apresentou overflow.
    pagina *pag = criaPagina(paginaAtual);

//  Copia os atributos da chave a ser promovida para a variável "PROMO_KEY".
    strcpy((*PROMO_KEY) -> chaveBusca, pag -> chaves[2] -> chaveBusca);
    *(*PROMO_KEY) -> ponteiroDados = *pag -> chaves[2] -> ponteiroDados;
    *(*PROMO_KEY) -> ponteiroDir = *R_RRN;
    *(*PROMO_KEY) -> ponteiroEsq = (*paginaAtual) -> RRNdoNo;

//  Caso a chave tenha apresentado sobrecarga, cria um novo registro de índice à direita.
    if((*paginaAtual) -> Ctmp && strcmp((*paginaAtual) -> Ctmp, NULL_KEY)) {

//      Inicializa o registro e atribui valor aos seus campos.
        *novaPagina = inicializaRegistro();
        insereChaveNo(*novaPagina, pag -> chaves[3]);
        (*novaPagina) -> nroChavesNo = 1;
        (*novaPagina) -> RRNdoNo = (*R_RRN)++;
        (*novaPagina) -> alturaNo = (*paginaAtual) -> alturaNo;

//      Escreve o novo registro de índice no fim do arquivo.
        escreveRegistroIndice(arq, (*novaPagina) -> RRNdoNo, *novaPagina);

        destroiRegistroIndice(*novaPagina);
    }

//  Exclui a chave a ser promovida do registro inicial.
    removeChaveNo(*paginaAtual, (*paginaAtual) -> C3);
    (*paginaAtual) -> nroChavesNo = 2;

//  Reescreve o registro com a nova disposição de chaves.
    escreveRegistroIndice(arq, (*paginaAtual) -> RRNdoNo, *paginaAtual);

    destroiRegistroIndice(*paginaAtual);
}

//  Função que insere uma chave em um arquivo de índice.
int insereChave(FILE *arq, int RRN, int *R_RRN, chaveRegistro *PROMO_KEY) {
//  Caso a recursão tenha alcançado um nó folha, sinalize.
    if(RRN == -1) {return PROMOCAO;}

//  Cria uma representação dos registro do arquivo de índice em memória primária.
    registroIndice *paginaAtual = buscaRegistroIndice(arq, RRN), *novaPagina;

//  Analisa o ponteiro no qual a chave a ser inserida deveria ocupar.
    int POS = encontraPonteiroNo(paginaAtual, PROMO_KEY -> chaveBusca), RETORNO;

//  Performa a recursão sobre a árvore no descendente "POS".
    switch(RETORNO = insereChave(arq, POS, R_RRN, PROMO_KEY)) {
//      Caso a recursão e a inserção não tenham ocasionado uma promoção, sinalize.
        case (SEM_PROMOCAO || ERRO):
            return RETORNO;
//      Caso a recursão tenha sinalizado uma promoção, inicie o processo de inserção.
        case PROMOCAO:
//          Insere no registro e analise a ocorrência de um overflow.
            if(insereChaveNo(paginaAtual, PROMO_KEY) == PROMOCAO) {
//              Caso a promoção tenha ocasionado um overflow, faça o processo de split do nó.
                splitRegistro(arq, R_RRN, &PROMO_KEY, &paginaAtual, &novaPagina);

//              Sinalize a promoção da chave.
                return PROMOCAO;
            }
//          Escreve o registro no arquivo de índice.
            escreveRegistroIndice(arq, paginaAtual -> RRNdoNo, paginaAtual);

            destroiRegistroIndice(paginaAtual);

            return SEM_PROMOCAO;
//      Caso o retorno seja diferente, retorne um erro.
        default:
            return ERRO;
    }
}

//  Função que insere um novo registro em um arquivo de índice a partir de um registro de dados,
//  lidando com a inexistência da raiz e com overflow na raiz.
void insereArquivoIndice(FILE *arq, cabecalhoIndice **cabIndice, registro *reg, int PR) {
//  Inicializa a chave a ser inserida de acordo com as tecnologias do registro de dados.
    chaveRegistro *INSERCAO = inicializaChave(concatecaTec(reg -> tecOrigem, reg -> tecDestino), PR);

//  Caso a raiz ainda não exista, crie uma e atualize o cabeçalho.
    if((*cabIndice) -> noRaiz == -1) {
//      Inicialize a raiz e a escreva no arquivo.
        registroIndice *novaRaiz = inicializaRegistro();

        insereChaveNo(novaRaiz, INSERCAO);

        novaRaiz -> RRNdoNo = 0;

        escreveRegistroIndice(arq, novaRaiz -> RRNdoNo, novaRaiz);

        (*cabIndice) -> noRaiz = 0;
        (*cabIndice) -> RRNproxNo = 1;
        
        destroiRegistroIndice(novaRaiz);
    } else {
//      Caso a raiz exista, inicia o processo de inserção a partir da raíz;
        if(insereChave(arq, (*cabIndice) -> noRaiz, &(*cabIndice) -> RRNproxNo, INSERCAO) ==  PROMOCAO) {
//          Caso a inserção tenha causado um overflow na raíz, cria uma nova raíz, manipula seus ponteiros e atualiza o cabeçalho.
            registroIndice *novaRaiz = inicializaRegistro();

            insereChaveNo(novaRaiz, INSERCAO);

            novaRaiz -> P1 = (*cabIndice) -> noRaiz;
            novaRaiz -> P2 = (*cabIndice) -> RRNproxNo - 1;
            novaRaiz -> RRNdoNo = (*cabIndice) -> RRNproxNo++;
            novaRaiz -> alturaNo = buscaRegistroIndice(arq, (*cabIndice) -> noRaiz) -> alturaNo + 1;

            (*cabIndice) -> noRaiz = novaRaiz -> RRNdoNo;

//          Escreve a nova raíz.
            escreveRegistroIndice(arq, novaRaiz -> RRNdoNo, novaRaiz);

            destroiRegistroIndice(novaRaiz);
        }
    }

    destroiChave(INSERCAO);
}

//  Função de busca de chave em um arquivo de índice.
int buscaChaveRecursivo(FILE *arq, int RRN, char *chave) {
    registroIndice *reg;

//  Caso o RRN procurado não exista ou for atingido um nó folha, retorne erro na procura.
    if(RRN == -1 || !(reg = buscaRegistroIndice(arq, RRN))) {return ERRO;}
    
    int cmp;

//  Inicia a busca binária comparando a chave intermediária à chaved requerida.
    if(!(cmp = strcmp(chave, noChave(reg -> C2)))) {return reg -> PR2;}
    else {
//      Caso a chave intermediária for menor que a chave procurada ou a chave intermediária for nula,
//      verifique na chave inicial.
        if(cmp < 0 || !strcmp(NULL_KEY, reg -> C2)) {
            if(!(cmp = strcmp(chave, noChave(reg -> C1)))) {return reg -> PR1;}

//          Caso não encontre a chave, performe a recursão de acordo com a relação entre as chaves.
            return (cmp < 0) ? buscaChaveRecursivo(arq, reg -> P1, chave) :
                               buscaChaveRecursivo(arq, reg -> P2, chave);
        } else {
//          Caso a chave intermediária for maior que a chave procurada, verifique na chave final.
            if(!(cmp = strcmp(chave, noChave(reg -> C3)))) {return reg -> PR3;}

//          Caso não encontre a chave, performe a recursão de acordo com a relação entre as chaves.
            return (cmp < 0 || !strcmp(NULL_KEY, reg -> C3)) ? buscaChaveRecursivo(arq, reg -> P3, chave) :
                                                               buscaChaveRecursivo(arq, reg -> P4, chave);
        }
    }
}

//  Função que performa a operação da funcionalidade seis de acordo com o campo e com o critério requeridos.
int imprimeListaIndice(FILE *arqIndice, FILE *arqDados, cabecalhoIndice *cab, node *raiz, char *campo, char *criterio) {
//  Caso a entrada sinalize uma busca no arquivo de índice, performe a busca.
    if(!strcmp(campo, "nomeTecnologiaOrigemDestino")) {
        int chave;

        return ((chave = buscaChaveRecursivo(arqIndice, cab -> noRaiz, quotesString(&criterio))) != -1) ? 
                 imprimeRegistro(buscaRegistroDados(arqDados, chave)) : 0;
    } else {
//      Caso o campo seja um valor ordinário do arquivo de dados, performe operação análoga à funcionalidade três.
        return imprimeLista(raiz, campo, criterio);
    }
}

//  Função que lê um registro de dados de acordo com a impressão.
registro *leRegistroDados() {
//  Inicializa e atribui valor ao registro de dados.
    registro *reg = malloc(sizeof(registro));

    char *tecOrigem = malloc(sizeof(char) * 56), *tecDestino = malloc(sizeof(char) * 56);
    char *gru = malloc(sizeof(char) * 11), *pop = malloc(sizeof(char) * 11), *pes = malloc(sizeof(char) * 11);

   scanf(" %55[^,], %10[^,], %10[^,], %55[^,], %10s", tecOrigem, gru, pop, tecDestino, pes);

    if(strcmp(tecOrigem, "NULO")) {
        reg -> tecOrigem = tecOrigem;
        reg -> tamanhoTecOrigem = strlen(tecOrigem);
    }
    else {
        reg -> tecOrigem = NULL_STRING;
        reg -> tamanhoTecOrigem = 0;
        free(tecOrigem);
    }
    if(strcmp(tecDestino, "NULO")) {
        reg -> tecDestino = tecDestino;
        reg -> tamanhoTecDestino = strlen(tecDestino);
    }
    else {
        reg -> tecDestino = NULL_STRING;
        reg -> tamanhoTecDestino = 0;
        free(tecDestino);
    }
    reg -> grupo = strcmp(gru, "NULO") ? atoi(gru) : -1;
    reg -> popularidade = strcmp(pop, "NULO") ? atoi(pop) : -1;
    reg -> peso = strcmp(pes, "NULO") ? atoi(pes) : -1;

    reg -> removido = '0';

    free(gru), free(pop), free(pes);

//  Retorne o registro resultante.
    return reg;
}