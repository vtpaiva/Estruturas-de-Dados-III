#include "Grafo.h"

//  Alunos - G17:
//  Felipe Aparecido da Silva - 11954502.
//  Vítor Augusto Paiva de Brito - 13732303.

// Função que inicializa e retorna um grafo de n vértices vazio
Grafo *iniciaGrafo(int n){
    Grafo *G = malloc(sizeof(Grafo));

    G -> numMaxVertices = n;
    G -> numVertices = 0;
    G -> lista_adj = malloc(sizeof(verticeGrafo*) * n);
    for(int i = 0; i < n; i++){G -> lista_adj[i] = NULL;}

    G -> distancia = malloc(sizeof(int) * n);
    G -> antecessor = malloc(sizeof(int) * n);

    G -> visitados = malloc(sizeof(int) * n);
    G -> tDescoberta = malloc(sizeof(int) * n);
    G -> numComponentes = 0;
    G -> t = 0;

    return G;
}

// Função que adiciona um vértice sem arestas na lista de adjacência do grafo em uma posição específica
verticeGrafo *criaVertice(char *tecnologia){
    verticeGrafo *novoVertice = malloc(sizeof(verticeGrafo));

    // Copia o nome da tecnologia no novo vértice
    novoVertice -> nomeTecnologia = malloc(sizeof(char) *(strlen(tecnologia) + 1));
    strcpy(novoVertice -> nomeTecnologia, tecnologia);
    
    // Termina de construir o novo vértice
    novoVertice -> aresta = NULL;
    novoVertice -> grupo = -1;
    novoVertice -> grau = novoVertice -> grauEntrada = novoVertice -> grauSaida = 0;
    
    // Insere o novo vértice no grafo na posição desejada
    return (novoVertice);
}

// Função que adiciona um vértice em uma posição específica da lista de adjacência
void adicionaVertice(Grafo *G, int pos, char *tecnologia, TabelaHash *h){
    if((G -> lista_adj[pos] == NULL) && (pos < G -> numMaxVertices)){
        G -> lista_adj[pos] = criaVertice(tecnologia);
        G -> numVertices++;
        inserirNaTabelaHash(h, tecnologia, pos);
    }else{
        printf("ERRO: numero de vertices excedido.\n");
    }
}

// Função que adiciona um vértice em uma posição específica da lista de adjacência
void adicionaGrupo(Grafo *G, int pos, int grupo){
    G->lista_adj[pos]->grupo = grupo;
}

// Função que cria e retorna uma nova aresta
Aresta *criaAresta(verticeGrafo *Destino, int peso){
    Aresta *novaAresta = malloc(sizeof(Aresta));
    novaAresta -> destino = Destino;
    novaAresta -> peso = peso;
    novaAresta -> prox = NULL;
    return (novaAresta);
}

// Função que adiciona uma aresta à lista de arestas de um dado vértice de origem
void adicionaAresta(verticeGrafo *Origem, verticeGrafo *Destino, int peso){
    // Cria nova aresta
    Aresta *novaAresta = criaAresta(Destino, peso);
    
    if (!Origem -> aresta) {
        // Se a lista de arestas estiver vazia, cria o primeiro vértice
        Origem -> aresta = novaAresta;
    } else {

        // Caso contrário, insere a nova aresta na posição correta
        Aresta *atual = Origem -> aresta;
        Aresta *anterior = NULL;

        // Encontra a posição correta na lista ordenada
        while (atual && strcmp((atual->destino)->nomeTecnologia, (Destino->nomeTecnologia)) <= 0) {
            anterior = atual;
            atual = atual -> prox;
        }

        // Insere a nova aresta na posição correta
        if (!anterior) {

            // Inserir no início da lista
            novaAresta -> prox = atual;
            Origem -> aresta = novaAresta;
        } else {

            // Inserir no meio ou final da lista
            anterior -> prox = novaAresta;
            novaAresta -> prox = atual;
        }
    }

    // Atualiza grau dos vertices
    Origem -> grauSaida++;
    Origem -> grau++;
    Destino -> grauEntrada++;
    Destino -> grau++;
}

//  Função que troca o valor de dois vértices de um grafo.
void troca(Grafo *G, int a, int b){
    verticeGrafo *aux = G->lista_adj[a];
    G->lista_adj[a] = G->lista_adj[b];
    G->lista_adj[b] = aux;
}

//  Função auxiliar que particiona o vetor de vértice no Quicksort.
int particiona(Grafo *G, int l, int h){
    char *x = (G->lista_adj[h]) -> nomeTecnologia;
    int i = (l - 1);
 
    for (int j = l; j <= h - 1; j++) {
        if (strcmp((G->lista_adj[j])->nomeTecnologia, x) < 0) {
            i++;
            troca(G, i, j);
        }
    }
    troca(G, (i + 1), h);
    return (i + 1);
}

//  Função que performa o Quicksort no vetor de vértice de um um grafo de acordo com a tecnologia de cada vértice.
void ordenaQuickSort(Grafo *G, int l, int h){
    // Cria uma pilha auxiliar
    int *pilha = malloc(sizeof(int) * (h - l + 1));
    int topo = -1;

    // Empilha os valores iniciais de l e h
    pilha[++topo] = l;
    pilha[++topo] = h;

    // Enquanto a pilha não estiver vazia
    while (topo >= 0) {
        // Desempilha h e l
        h = pilha[topo--];
        l = pilha[topo--];

        // Obtém o índice do pivo
        int pivo = particiona(G, l, h);

        // Se há elementos à esquerda do pivo, empilhe
        if (pivo - 1 > l) {
            pilha[++topo] = l;
            pilha[++topo] = pivo - 1;
        }

        // Se há elementos à direita do pivo, empilhe
        if (pivo + 1 < h) {
            pilha[++topo] = pivo + 1;
            pilha[++topo] = h;
        }
    }

    // Libera a memória da pilha auxiliar
    free(pilha);
}

//  Função que evoca o algoritmo do Quicksort na lista de adjacências de um grafo.
void ordenaVerticeDoGrafo(Grafo *G){
    ordenaQuickSort(G, 0, (G -> numVertices)-1);
}

//  Função que transforma um arquivo binário de registros de dados em um grafo.
void binarioParaGrafo(FILE *arq, Grafo *G){

    // Inicializa tabela hash auxiliar.
    TabelaHash *h = malloc(sizeof(TabelaHash));
    inicializarTabelaHash(h);
    
    // Iteração sobre os registros do arquivoe inserção no grafo.
    int pos = 0, posOrigem, posDestino;
    for(registro *obj; obj = lerRegistroBin(arq); destroiRegistro(obj)) {
        if (obj->removido == '0' && obj->tamanhoTecDestino > 0 && obj->tamanhoTecOrigem > 0){
            posOrigem = buscarNaTabelaHash(h, obj->tecOrigem);
            posDestino = buscarNaTabelaHash(h, obj->tecDestino);

            // Apenas Origem não está no grafo
            if(posOrigem == -1){
                adicionaVertice(G, pos, obj->tecOrigem, h);
                posOrigem = pos++;
            } 

            // Apenas Destino não está no grafo
            if(posDestino == -1){
                adicionaVertice(G, pos, obj->tecDestino, h);
                posDestino = pos++;
            }

            // Adicionar o grupo ao vértice origem, se necessário, e a aresta à lista de adjacência
            if((G->lista_adj[posOrigem]) -> grupo == -1 && obj->grupo != -1){adicionaGrupo(G, posOrigem, obj->grupo);}
            adicionaAresta(G->lista_adj[posOrigem], G->lista_adj[posDestino], obj->peso);
        }
    }

    // Ordena os vértices do grafo na lista de adjacência
    ordenaVerticeDoGrafo(G);

    liberarTabelaHash(h);
    free(h);
}

//  Função que imprime os vértices e arestas correspondentes de um grafo.
void printGrafo(Grafo *G){
    for (int i = 0; i < G -> numVertices; i++){
        verticeGrafo *v = G->lista_adj[i];

        for(Aresta *aux = (G -> lista_adj[i]) -> aresta; aux; aux = aux->prox){
            printf("%s %d %d %d %d %s %d\n",
                v->nomeTecnologia,
                v->grupo,
                v->grauEntrada,
                v->grauSaida,
                v->grau,
                aux->destino->nomeTecnologia,
                aux->peso
            );
        }
    }
}

//  Função que libera memória de uma lista de arestas.
void destroiListaAresta(Aresta *lista) {
    while(lista != NULL){
        Aresta *aux = lista;
        lista = lista-> prox;
        free(aux);
    }
}

//  Função que libera a memória de uma lista de adjacências.
void destroiListaAdj(verticeGrafo **lista, int tamanho){
    for (int i = 0; i < tamanho; i++){
        destroiListaAresta((lista[i]) -> aresta);
        free((lista[i]) -> nomeTecnologia);
        (lista[i]) = NULL;
    }
    free(*lista);
}

//  Função que libera memória de um grafo.
void destroiGrafo(Grafo *G){
    destroiListaAdj(G->lista_adj, G->numVertices);
    free(G);
}

//  Função que transforma um grafo no seu transposto.
void transporGrafo(Grafo *G){
    //  Inicializa a tabela hash.
    TabelaHash *h = malloc(sizeof(TabelaHash));
    inicializarTabelaHash(h);

    //  Insere todos os vértices do grafo original na lista de adjacências do grafo transposto.
    verticeGrafo **novaListaAdj = malloc(sizeof(verticeGrafo*) * G->numMaxVertices);
    for(int i = 0; i < G->numVertices; i++){
        novaListaAdj[i] = criaVertice(G->lista_adj[i]->nomeTecnologia);
        novaListaAdj[i] -> grupo = G->lista_adj[i] -> grupo;

        inserirNaTabelaHash(h, G->lista_adj[i]->nomeTecnologia, i);
    }

    //  Insere as arestas com direção inversa em cada vértice do grafo transposto.
    for (int i = 0; i < G -> numVertices; i++){
        for (Aresta *aux = (G->lista_adj[i]) -> aresta; aux != NULL; aux = aux -> prox){
            int pos = buscarNaTabelaHash(h, aux->destino->nomeTecnologia);
            adicionaAresta(novaListaAdj[pos], novaListaAdj[i], aux->peso);
        }
    }

    destroiListaAdj(G->lista_adj, G->numVertices);

    //  Atribui valor à lista de equivalências do grafo transposto.
    G->lista_adj = novaListaAdj;

    liberarTabelaHash(h);
    free(h);
}

//  Função que imprime as tecnologias de origem que geraram cliques.
void printOrigem(Grafo *G, char *nomeTecDestino){

    // Cria uma lista de strings
    char **lista = malloc(sizeof(char*) * G->numVertices);

    //  Inicializa variável de contagem de cliques.
    int cliques = 0;

    // Itera sobre os vértices do grafo.
    for (int i = 0; i < G -> numVertices; i++){

        // Busca a aresta desejada.
        Aresta *aux = (G->lista_adj[i]) -> aresta;
        while(aux && strcmp((aux->destino)->nomeTecnologia, nomeTecDestino) < 0){aux = aux -> prox;}

        // Se a aresta foi encontrada a lista guarda o endereço do nome da tecnologia.
        if (aux && !strcmp((aux->destino)->nomeTecnologia, nomeTecDestino)){
            lista[cliques++] = G->lista_adj[i]->nomeTecnologia;
        }
    }

    //  Caso não sejam encotradas tecnologias que geraram cliques, sinalize.
    if(!cliques) {
        printf("Registro inexistente.\n");
        free(lista);

        return;
    }

    // Imprime a lista.
    printf("%s: ", nomeTecDestino);
    for(int i = 0; i < cliques; i++){
        printf("%s", lista[i]);
        if(i < cliques - 1) {printf(", ");}
    }
    printf("\n");

    // Libera a memória da lista.
    free(lista);
}

// Função que performa a busca em profundidade adaptada (Função auxiliar do algoritmo Tarjan).
void tarjanDFS(Grafo *G, int v, int *pilha, int *posicaoPilha, int *low, int *conexos, int *naPilha, TabelaHash *h) {
	// Marca o vértice como visitado.
    G->visitados[v] = 1;
	
	// Armazena o tempo de descoberta do vértice, inicializa o valor 'low' do vértice e atualiza o tempo.
    G->tDescoberta[v] = G->t; 
    low[v] = G->t;
	G->t++; 

	// Empilha o vértice, o marca como presente e atualiza a posição da pilha.
    pilha[*posicaoPilha] = v;
    naPilha[v] = 1;
    (*posicaoPilha)++;

	// Percorre vértices adjacentes.
    for (Aresta *aresta = G->lista_adj[v]->aresta; aresta; aresta = aresta->prox) {
        int adj = buscarNaTabelaHash(h, aresta->destino->nomeTecnologia);

		 // Vértice adjacente não foi visitado.
        if (!G->visitados[adj]) {
            // Chamada recursiva para o vértice adjacente.
            tarjanDFS(G, adj, pilha, posicaoPilha, low, conexos, naPilha, h); 
			// Atualiza o valor 'low' do vértice se necessário.
            if (low[adj] < low[v]){low[v] = low[adj];}

        } 
		// Vértice adjacente foi visitado, o vértice adjacente está na pilha e possui um tempo de descoberta menor.
        else if (naPilha[adj] && G->tDescoberta[adj] < low[v]) {
			// Atualiza o valor 'low'.
            low[v] = G->tDescoberta[adj];
        }
    }

	// Valor 'low' é igual ao tempo de descoberta.
    if (low[v] == G->tDescoberta[v]) {
		
		// Retira os vértices da pilha até chegar ao vértice atual.
        int componente = -1;
        while (componente != v) {
			
			// Desempilha o vértice, marca como ausente na pilha e atribui o número da componente conexa ao vértice.
            componente = pilha[--(*posicaoPilha)];
            naPilha[componente] = 0;
            conexos[componente] = G->numComponentes;
        }

		// Incrementa o número de componentes conexas encontradas.
        G->numComponentes++;
    }
}

// Função que performa o algoritmo Tarjan usado para encontrar as componentes conexas do Grafo.
void tarjan(Grafo *G) {
    int *pilha = malloc(sizeof(int) * G->numVertices);	    // Pilha para armazenar os vértices.
    int *low = malloc(sizeof(int) * G->numVertices);		// Vetor 'low', armazena os menores tempos de descoberta alcançáveis pelos vértices.
    int *conexos = malloc(sizeof(int) * G->numVertices);	// Vetor para armazenar o número da componente conexa de cada vértice.
    int *naPilha = malloc(sizeof(int) * G->numVertices);	// Vetor para verificar se um vértice está presente na pilha.
    int posicaoPilha = 0;						            // Posição atual na pilha.
    TabelaHash *h = malloc(sizeof(TabelaHash));             // Tabela hash para facilitar a busca da posição dos vértices no Grafo.

    // Inicialização dos vetores auxiliares.
    for (int i = 0; i < G->numVertices; i++) {
        G->visitados[i] = 0;
        low[i] = -1;
        conexos[i] = -1;
        naPilha[i] = 0;
        inserirNaTabelaHash(h, G->lista_adj[i]->nomeTecnologia, i);
    }

	// Percorre o grafo.
    for (int i = 0; i < G->numVertices; i++) {

		// Vértice não visitado.
        if (!G->visitados[i]){

			// Faz a visita com a busca por profundidade adaptada.
            tarjanDFS(G, i, pilha, &posicaoPilha, low, conexos, naPilha, h);
        }
    }

    liberarTabelaHash(h);
    free(pilha), free(low), free(conexos), free(naPilha), free(h);
}

//  Função que sinaliza caso o grafo seja fortemente conexo e seu número de componentes.
void printConectividadeFortementeConexa(Grafo *G){
    tarjan(G);
    if (G->numComponentes == 1){
        printf("Sim, o grafo é fortemente conexo e possui %d componente.\n", G->numComponentes);
    }else{
        printf("Não, o grafo não é fortemente conexo e possui %d componentes.\n", G->numComponentes);
    }
}

// Relaxamento de aresta.
int relax(Grafo *G, int u, int v, int peso) {
	
    // Faz relaxamento, então, retorna 1.
    if (G->distancia[v] > G->distancia[u] + peso) {
        G->distancia[v] = G->distancia[u] + peso;
        G->antecessor[v] = u;
        return 1;
    }

    // Não faz relaxamento, então, retorna 0.
    return 0;
}

// Implementação do algoritmo de Dijkstra.
void Dijkstra(Grafo *G, TabelaHash *h, char *tecnologia) {
    int s = buscarNaTabelaHash(h, tecnologia);

	// Inicializa distância e antecessores.
	for (int i = 0; i < G->numVertices; i++) {
		G->distancia[i] = INT_MAX;		// Distância infinita.
		G->antecessor[i] = -1;			// Antecessor vazio.
	}
    // Distância do vértice inicial igual a 0
	G->distancia[s] = 0;				
	
	// Cria fila de prioridade com os vértices do grafo
	FilaPrioridade *F = criaFilaPrioridade(G->numVertices);
	for(int i = 0; i <  G->numVertices; i++){
		insereFilaPrioridade(F, i, G->distancia[i]);
        inserirNaTabelaHash(h,G->lista_adj[i]->nomeTecnologia, i);
	}

	// Fila não está vazia.
	while(F->tamanho) {
		// remove-se o primeiro vértice da fila de prioridade.
		NoFilaPrioridade raiz = removeFilaPrioridade(F);
		int u = raiz.indice;
		
		// Faz relaxamento dos vértices adjacentes, se necessário.
		for (Aresta *aux = G->lista_adj[u]->aresta; aux; aux = aux->prox) {
			int v = buscarNaTabelaHash(h, (aux->destino)->nomeTecnologia);
			int rel = relax(G, u, v, (aux->peso));

			// Relachamento foi feito.
			if (rel == 1) {
				
				// Atualiza fila de prioridade e adiciona novo antecessor.
				atualizaFilaPrioridade(F, v, G->distancia[v]);
				G->antecessor[v] = u;
			}
		}
	}

	destroiFilaPrioridade(F);
}

//  Função que imprime a distância mínima entre vértices.
void printDistancia(Grafo *G, char *tecnologia1, char *tecnologia2){
    //  Inicializa a tabela hash e insere os vértices.
    TabelaHash *h = malloc(sizeof(TabelaHash));
    inicializarTabelaHash(h);
    for(int i = 0; i < G->numVertices; i++){inserirNaTabelaHash(h, G->lista_adj[i]->nomeTecnologia, i);}

    //  Performa o algoritmo de Dijkstra no grafo.
    Dijkstra(G, h, tecnologia1);

    //  Retorna o valor da distância mínima.
    int distancia = G->distancia[buscarNaTabelaHash(h, tecnologia2)];

    //  Imprime o resultado.
    printf("%s %s: ", tecnologia1, tecnologia2);
    if(distancia < INT_MAX && distancia){
        printf("%d\n", distancia);
    } else{
        printf("CAMINHO INEXISTENTE.\n");
    }

    liberarTabelaHash(h);
    free(h);
}
