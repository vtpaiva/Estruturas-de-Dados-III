#include "Funcionalidades.h"

//  Alunos - G17:
//  Felipe Aparecido da Silva - 11954502.
//  Vítor Augusto Paiva de Brito - 13732303.

//  Função que performa o procedimento da funcionalidade um, obtendo, a partir de um arquivo
//  "arqEntrada", um arquivo de saída "arqSaida" e evoca a função "binarioNaTela".
void Fucionalidade1(char *arqEntrada, char *arqSaida){
    FILE *arq = fopen(arqEntrada, "r"), *novo = fopen(arqSaida, "wb");

//  Declara a variável de árvore, "tecRaiz", para armazenamento de tecnologias e as
//  variáveis de cabeçalho e de registro.
    tecnologia *tecRaiz = NULL;
    registro *obj;
    cabecalho *cabe;

//  Retorna falha se o arquivo apresentar defeitos.
    if(!arq || !(cabe = lerCabecalhoCsv(novo))) {
        printf("Falha no processamento do arquivo.\n");
        fclose(arq), fclose(novo);
        return;
    }

//  Ignora a primeira linha do arquivo CSV.
    fscanf(arq, "%*s");

//  Iteração que inicializa os registros em uma variável, escreve no binário e realiza as operações
//  com o número de tecnologias no cabçalho.
    for(char *st = malloc(TAM_REGISTRO + 1), *tmp; fscanf(arq, "%s", st) != EOF; st = malloc(TAM_REGISTRO + 1)){

//  Lê um registro.
        obj = lerRegistroCsv(st);

//  Escreve os campos do registro no arquivo binário.
        escreveRegistro(novo, obj);

//  Escreve os caracteres lixo no final do registro.
        escreveLixo(novo, obj);

//  Verifica se a tecnologia e o par já estão presentes no arquivo.
        if(!isNullString(obj -> tecOrigem)) {
            buscaTec(&tecRaiz, obj -> tecOrigem, obj -> tecDestino, cabe);
        }
        if(!isNullString(obj -> tecDestino)) {
            buscaTec(&tecRaiz, obj -> tecDestino, NULL_STRING, cabe);
        }

//  Atualiza o próximo RRN do cabeçalho.
        cabe -> proxRRN++;

        destroiRegistro(obj);
    }

//  Atualiza o status do cabeçalho e o reescreve no início do arquivo.
    cabe -> status = '1';
    fseek(novo, 0, SEEK_SET);
    escreveCabecalho(novo, cabe);

    free(cabe), destroiArvore(tecRaiz);
    fclose(novo), fclose(arq);

//  Evoca o binário na tela.
    binarioNaTela(arqSaida);
}

//  Função que performa o processo da funcionalidade dois, imprimindo os
//  registros de um arquivo de entrada, "arqEntrada".
void Funcionalidade2(char *arqEntrada){
    FILE *arq = fopen(arqEntrada, "rb");

//  Declara uma variável de cabeçalho.
    cabecalho *cabe;

//  Variável de contagem de registros.
    int contagem = 0;

//  Retorna uma falha se o arquivo apresentar erros ou estiver inconsistente.
    if(!arq || !(cabe = lerCabecalhoBin(arq))) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

//  Iteração sobre os registros do arquivo e evocação da função que imprime os registros.
    for(registro *obj; obj = lerRegistroBin(arq); destroiRegistro(obj)) {
        contagem += imprimeRegistro(obj);
    }

//  Verifica de o arquivo continha algum registro válido.
    if(!contagem) {printf("Registro inexistente.\n");}

    free(cabe);

    fclose(arq);
}

//  Função que performa o processo da funcionalidade três, imprimindo os registros
//  de tamanhos compatíveis um número "n" de chamadas.
void Funcionalidade3(char *arqEntrada, int n){
    FILE *arq = fopen(arqEntrada, "rb");

//  Declara variável de cabeçalho.
    cabecalho *cabe;

    if(!arq || !(cabe = lerCabecalhoBin(arq))) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

//  Inicialização das variáveis que armazenarão as strings de campo e critério.
    char *campo = malloc(sizeof(char) * 21), *criterio = malloc(sizeof(char) * 55);

//  Declara variável de início da lista encadeada de registros.
    node *raiz = NULL;

//  Intera sobre o arquivo, inserindo na lista.
    for(registro *tmp; tmp = lerRegistroBin(arq); insereNode(&raiz, tmp));

//  Imprime os registros com campos compatíveis o número "n" de vezes.
    for(int i = 0; i < n; i++){
        scanf("%s %s", campo, criterio);

        if(!imprimeLista(raiz, campo, criterio)) {
            printf("Registro inexistente.\n");
        }
    }

    free(campo), free(criterio);
    free(cabe);

    destroiLista(raiz);

    fclose(arq);
}

//  Função que performa a funcionalidade quatro, imprimindo um registro na
//  posição "RRN" do arquivo "arqEntrada".
void Funcionalidade4(char *arqEntrada, int RRN){
    FILE *arq = fopen(arqEntrada, "rb");

    cabecalho *cabe; 
    registro *obj;

    if(!arq || !(cabe = lerCabecalhoBin(arq))) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

//  Retorna um erro referente ao registro se o fseek retornar uma falha ou se
//  o registro apresentar falhas.
    if(fseek(arq, TAM_CABECALHO + RRN * TAM_REGISTRO, SEEK_SET) || !(obj = lerRegistroBin(arq))){
        printf("Registro inexistente.\n");
        free(cabe);
        return;
    }

//  Imprime o registro buscado.
    if(!imprimeRegistro(obj)) {
        printf("Registro inexistente.\n");
    }

    destroiRegistro(obj), free(cabe);

    fclose(arq);
}

//  Função que evoca a funcionalidade requisitada a partir do input.
void defineOperacao(int op){
//  Inicializa ponteiro que armazena o nome do arquivo de entrada.
    char *arq = malloc(sizeof(char) * 15), *alt;

    scanf("%s", arq);

//  Definição da operação.
    switch (op) {
        case 1:
            alt = malloc(sizeof(char) * 15);
            scanf("%s", alt);
            Fucionalidade1(arq, alt);
            break;
        case 2:
            Funcionalidade2(arq);
            break;
        case 3:
            scanf("%d", &op);
            Funcionalidade3(arq, op);
            break;
        case 4:
            scanf("%d", &op);
            Funcionalidade4(arq, op);
            break;
        default:
            break;
    }
}
