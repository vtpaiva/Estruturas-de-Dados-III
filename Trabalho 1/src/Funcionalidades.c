#include "Funcionalidades.h"

//  Alunos - G17:
//  Felipe Aparecido da Silva - 11954502.
//  Vítor Augusto Paiva de Brito - 13732303.

//  Função que performa o procedimento da funcionalidade um, obtendo, a partir de um arquivo
//  "arqEntrada", um arquivo de saída "arqSaida" e evoca a função "binarioNaTela".
void Funcionalidade1(char *arqEntrada, char *arqSaida){
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

//      Lê um registro.
        obj = lerRegistroCsv(st);

//      Escreve os campos do registro no arquivo binário.
        escreveRegistro(novo, obj);

//      Escreve os caracteres lixo no final do registro.
        escreveLixo(novo, obj);

//      Verifica se a tecnologia e o par já estão presentes no arquivo.
        if(!isNullString(obj -> tecOrigem)) {
            buscaTec(&tecRaiz, obj -> tecOrigem, obj -> tecDestino, cabe);
        }
        if(!isNullString(obj -> tecDestino)) {
            buscaTec(&tecRaiz, obj -> tecDestino, NULL_STRING, cabe);
        }

//      Atualiza o próximo RRN do cabeçalho.
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

//  Funcionalidade que cria um arquivo de índice de acordo com os registros de um
//  arquivo de dados.
void Funcionalidade5(char *arqDados, char *arqIndice) {
    FILE *binario = fopen(arqDados, "rb"), *indice = fopen(arqIndice, "w+b");

    cabecalho *cabDados;

//  Caso o arquivo apresente problemas, retorne uma falha no processamento.
    if(!binario || !(cabDados = lerCabecalhoBin(binario))) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

//  Inicializa um cabeçalho de índice com campos iniciais nulos.
    cabecalhoIndice *cabIndice = inicializaCabecalho();

    escreveCabecalhoIndice(indice, cabIndice);

    registro *regDados;

//  Itera sobre os registros no arquivo de dados, inserindo-os no arquivo de índice.
    for(int i = 0; regDados = lerRegistroBin(binario); i++, destroiRegistro(regDados)) {
        if(regDados -> removido == '0' && regDados -> tamanhoTecDestino && regDados -> tamanhoTecOrigem) {
            insereArquivoIndice(indice, &cabIndice, regDados, i);
        }
    }

//  Altera a consistência do cabeçalho de índice.
    cabIndice -> status = '1';

//  Escreve o cabeçalho final no arquivo de índice.
    escreveCabecalhoIndice(indice, cabIndice);

    fclose(binario), fclose(indice);
    free(cabDados), free(cabIndice);

    binarioNaTela(arqIndice);
}

void Funcionalidade6(char *arqDados, char *arqIndice, int n){
    FILE *dados = fopen(arqDados, "rb"), *indice = fopen(arqIndice, "rb");

    cabecalho *cabe;

//  Caso o arquivo de dados apresente algum problema, retorne falha no processamento.
    if(!dados || !(cabe = lerCabecalhoBin(dados))) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    cabecalhoIndice *cabeIndice;

//  Caso o arquivo de índice apresente algum problema, retorne falha no processamento.
    if(!arqIndice || !(cabeIndice = lerCabecalhoIndice(indice))) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

//  Inicializa as strings para armazenar o campo e o critério de busca.
    char *campo = malloc(sizeof(char) * 55), *criterio = malloc(sizeof(char) * 55);

//  Inicializa a lista.
    node *raiz = NULL;

//  Estrutura a lista a lista de acordo com os registro no arquivo de dados.
    for(registro *tmp; tmp = lerRegistroBin(dados); insereNode(&raiz, tmp));

//  Iteração que analisa o campo e o critério de busca e imprime a saída.
    for(int i = 0; i < n; i++){
        scanf("%s %s", campo, criterio);

        if(!imprimeListaIndice(indice, dados, cabeIndice, raiz, campo, criterio)) {
            printf("Registro inexistente.\n");
        }
    }

    free(campo), free(criterio);
    free(cabe), free(cabeIndice);

    destroiLista(raiz);

    fclose(dados), fclose(indice);
}

void Funcionalidade7(char *arqDados, char *arqIndice, int n) {
    FILE *binario = fopen(arqDados, "rb+"), *indice = fopen(arqIndice, "rb+");

//  Lê o cabeçalho do arquivo de índice;
    cabecalhoIndice *cabIndice;

    if(!indice || !(cabIndice = lerCabecalhoIndice(indice)) || !binario) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

//  Inicializa uma cópia do cabeçalho do arquivo de dados para iterar sobre o
//  arquivo e ter uma noção sobre o RRN, as tecnologias e os pares existentes.
    cabecalho *cabDados = inicializaCabecalhoDados();

//  Inicializa a árvore de tecnologias.
    tecnologia *tecRaiz = NULL;

    fseek(binario, TAM_CABECALHO, SEEK_SET);

    registro *reg;

//  Itera sobre o arquivo de dados inserindo as tecnologias a fim de se desenvolver a cópia
//  do cabeçalho.
    for(; reg = lerRegistroBin(binario); destroiRegistro(reg)) {
//      Caso o arquivo não esteja removido, adicione na árvore.
        if(reg -> removido == '0') {
            if(!isNullString(reg -> tecOrigem)) {
                buscaTec(&tecRaiz, reg -> tecOrigem, reg -> tecDestino, cabDados);
            }
            if(!isNullString(reg -> tecDestino)) {
                buscaTec(&tecRaiz, reg -> tecDestino, NULL_STRING, cabDados);
            }
        }

        cabDados -> proxRRN++;
    }

//  Lê o registro de dados a ser inserido, o escreve no arquivo de dados, atualiza o cabeçalho e
//  insere a chave correspondente noa arquivo de índice.
    for(int i = 0; i < n; i++, cabDados -> proxRRN++) {
        reg = leRegistroDados();
        escreveRegistro(binario, reg);
        escreveLixo(binario, reg);

        if(!isNullString(reg -> tecOrigem)) {
            buscaTec(&tecRaiz, reg -> tecOrigem, reg -> tecDestino, cabDados);
        }
        if(!isNullString(reg -> tecDestino)) {
            buscaTec(&tecRaiz, reg -> tecDestino, NULL_STRING, cabDados);
        }

        if(reg -> removido == '0' && reg -> tamanhoTecOrigem && reg -> tamanhoTecDestino) {
            insereArquivoIndice(indice, &cabIndice, reg, cabDados -> proxRRN);
        }
    }

//  Atualiza a consistência do cabeçalho de dados.
    cabDados -> status = '1';

//  Escreve o novo cabeçalho de dados.
    fseek(binario, 0, SEEK_SET);
    escreveCabecalho(binario, cabDados);

//  Escreve o cabeçalho de índice atualizado.
    escreveCabecalhoIndice(indice, cabIndice);

    fclose(binario), fclose(indice);
    free(cabDados), free(cabIndice);

    destroiArvore(tecRaiz);

    binarioNaTela(arqDados);
    binarioNaTela(arqIndice);
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
            Funcionalidade1(arq, alt);

            free(alt);
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
        case 5:
            alt = malloc(sizeof(char) * 15);
            scanf("%s", alt);
            Funcionalidade5(arq, alt);

            free(alt);
            break;
        case 6:
            alt = malloc(sizeof(char) * 15);
            scanf("%s", alt);
            scanf("%d", &op);
            Funcionalidade6(arq, alt, op);

            free(alt);
            break;
        case 7:
            alt = malloc(sizeof(char) * 15);
            scanf("%s", alt);
            scanf("%d", &op);
            Funcionalidade7(arq, alt, op);

            free(alt);
            break;
        default:
            break;
    }
}