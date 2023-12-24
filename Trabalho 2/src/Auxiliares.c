#include "Auxiliares.h"

//  Alunos - G17:
//  Felipe Aparecido da Silva - 11954502.
//  Vítor Augusto Paiva de Brito - 13732303.

//  Função que verifica se uma string é nula ou armazena o valor da exceção determinada.
int isNullString(char *string){
    return (string && strcmp(string, NULL_STRING)) ? 0 : 1;
}

//  Função que transforma um inteiro em uma string e a retorna.
char *toString(int x){
    char *tmp = malloc(sizeof(int));

    return sprintf(tmp, "%d", x), tmp;
}

//  Função que retorna o conteúdo de uma string entre aspas.
char *quotesString(char **string){
    return strtok(++*string, "\"");
}

//  Função que retorna o maior inteiro de um par.
int greatInt(int a, int b) {
    return (a > b) ? a : b;
}

//  Função que retorna a altura de um nó na árvore binária, retornando zero se o nó é nulo.
int nodeHeight(tecnologia *node) {
    return (node) ? node -> height : 0;
}

//  Função que corrige a altura de um nó na árvore.
void fixHeight(tecnologia *node){
    node -> height = greatInt(nodeHeight(node -> left), nodeHeight(node -> right)) + 1;
}

//  Função que retorna o fator de balanceamento de um nó na árvore.
int balanceFactor(tecnologia *node){
    return labs(nodeHeight(node -> left) - nodeHeight(node -> right));
}

//  Função de rotação na árvore.
void RRrotate(tecnologia **node){
//  Rotaciona o nó com o seu filho à esquerda.
    tecnologia *tmp = (*node) -> right;

    (*node) -> right = tmp -> left;
    tmp -> left = *node;

//  Conserta a altura do nó rotacionado.
    fixHeight(*node);

    *node = tmp;
}

//  Função de rotação na árvore.
void LLrotate(tecnologia **node){
//  Rotaciona o nó com o seu filho à direita.
    tecnologia *tmp = (*node) -> left;

    (*node) -> left = tmp -> right;
    tmp -> right = *node;

//  Conserta a altura do nó rotacionado.
    fixHeight(*node);

    *node = tmp;
}

//  Função que retorna uma nova tecnologia que armazena uma string na árvore. (Funcionalidade 1)
tecnologia *newTec(char *Tecnologia){
    tecnologia *Tec = malloc(sizeof(tecnologia));

    Tec -> tec = strdup(Tecnologia), Tec -> height = 1;
    Tec -> left = Tec -> right = Tec -> pair = NULL;

    return Tec;
}

//  Função que retorna um novo nó que armazena um registro da lista. (Funcionalidade 3)
node *newNode(registro *obj){
    node *No = malloc(sizeof(node));

    No -> data = obj, No -> next = NULL;

    return No;
}

//  Função que insere um nó de registro em uma lista.
void insereNode(node **no, registro *data){
    node *tmp = newNode(data);

//  Insere no começo da lista.
    (*no != NULL) ? (tmp -> next = *no, *no = tmp) : (*no = tmp);
}

//  Função que verifica se um certo campo "field" requisitado pelo input condiz
//  com o critério imposto, "criterion".
int verificaCampo(registro *obj, char *field, char *criterion){
//  Retorna 1 se o campo for condizente.
    if(!strcmp(field, "grupo")){
        if(atoi(criterion) == obj -> grupo) {return imprimeRegistro(obj);}
    }
    else if(!strcmp(field, "popularidade")){
        if(atoi(criterion) == obj -> popularidade) {return imprimeRegistro(obj);}
    }
    else if(!strcmp(field, "peso")){
        if(atoi(criterion) == obj -> peso) {return imprimeRegistro(obj);}
    }
    else if(!strcmp(field, "nomeTecnologiaOrigem")){
        if(!strcmp(obj -> tecOrigem, quotesString(&criterion))) {return imprimeRegistro(obj);}
    }
    else if(!strcmp(field, "nomeTecnologiaDestino")){
        if(!strcmp(obj -> tecDestino, quotesString(&criterion))) {return imprimeRegistro(obj);}
    }

//  Retorna 0 se não haver compatibilidade.
    return 0;
}

//  Função que imprime os campos de registro, imprimindo "NULO" em campos nulos.
int imprimeRegistro(registro *obj){
//  Se o registro for inconsistente, retorne uma falha.
    if(!obj || obj -> removido == '1') {return 0;}

    printf("%s, %s, %s, %s, %s\n", (!isNullString(obj -> tecOrigem)) ? obj -> tecOrigem : NULL_PRINT,
                                   (obj -> grupo != -1) ? toString(obj -> grupo) : NULL_PRINT, 
                                   (obj -> popularidade != -1) ? toString(obj -> popularidade) : NULL_PRINT, 
                                   (!isNullString(obj -> tecDestino)) ? obj -> tecDestino : NULL_PRINT,
                                   (obj -> peso != -1) ? toString(obj -> peso) : NULL_PRINT);

    return 1;
}

//  Função recursiva que imprime os campos de todos os registros compatíveis com o critério imposto
//  em uma lista.
int imprimeLista(node *head, char *field, char *criterion){
    if(!head) {return 0;}

    return imprimeLista(head -> next, field, criterion) + verificaCampo(head -> data, field, criterion);
}

//  Função que libera a memória de uma lista de registros.
void destroiLista(node *head){
    if(head -> next) {destroiLista(head -> next);}

    free(head);
}

//  Função que busca uma tecnologia em uma árvore binária.
void buscaTec(tecnologia **root, char *s_Tecnologia, char *s_tecPar, cabecalho *cabe){
//  Se o nó atual for nulo, contabilize uma nova tecnologia e um novo par, além de inserir a tecnologia e seu
//  par na árvore.
    if(!*root){
        cabe -> nroTecnologias++, *root = newTec(s_Tecnologia);
        if(!isNullString(s_tecPar)) {buscaPar(root, s_tecPar, cabe);}
        return;
    }

//  Caso o nó atual exista e não possuir a tecnologia requisitada, performe a recursão à direita até o fim do processo.
    if(strcmp(s_Tecnologia, (*root) -> tec) < 0){
        buscaTec(&((*root) -> right), s_Tecnologia, s_tecPar, cabe);
//      Se o fator de balanceamento for maior que um, performe as rotações.
        if(balanceFactor(*root) > 1){
            if(strcmp(s_Tecnologia, (*root) -> right -> tec) < 0) {
                RRrotate(root);
            }
            else {
                LLrotate(&((*root) -> right));
                RRrotate(root);
            }
        }
    }
    
//  Caso o nó atual exista e não possuir a tecnologia requisitada, performe a recursão à esquerda até o fim do processo.
    else if(strcmp(s_Tecnologia, (*root) -> tec) > 0){
        buscaTec(&((*root) -> left), s_Tecnologia, s_tecPar, cabe);
//      Se o fator de balanceamento for maior que um, performe as rotações.
        if(balanceFactor(*root) > 1){
            if(strcmp(s_Tecnologia, (*root) -> left -> tec) > 0) {
                LLrotate(root);
            }
            else {
                RRrotate(&((*root) -> left));
                LLrotate(root);
            }
        }
    }
//  Se o nó atual possuir a tecnologia requisitada, verifique se o par é único e relação a essa tecnologia.
    else{
        if(!isNullString(s_tecPar)) {buscaPar(root, s_tecPar, cabe);}
        return;
    }

//  Corrija a altura do nó em cada recursão.
    fixHeight(*root);
}

//  Função que busca, em uma lista de pares de um nó na árvore, se o pair inserido já existe.
void buscaPar(tecnologia **root, char *s_tecPar, cabecalho *cabe){
//  Se o par existir, não performe nenhuma ação.
    if(!strcmp((*root) -> tec, s_tecPar)) {return;}

//  Performa uma recursão sobre a lista embutida até atingir o final ou encontrar o par requisitado, se
//  chegar ao fim da estrutura, adiciona o par à lista embutida no nó da tecnologia.
    if((*root) -> pair) {
        buscaPar(&((*root) -> pair), s_tecPar, cabe);
    }
    else {
        (*root) -> pair = newTec(s_tecPar);
        cabe -> nroParesTecnologias++;
    }
}

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}
