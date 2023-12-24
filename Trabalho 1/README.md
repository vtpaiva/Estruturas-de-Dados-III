# Trabalho I de Estrutura de Dados III.

  

Este repositório contém o código-fonte e a documentação do trabalho prático I da disciplina Estrutura de Dados III (SCC0607), ministrada pela professora Profa. Dra. Cristina Dutra de Aguiar no Instituto de Ciências Matemáticas e de Computação (ICMC) da Universidade de São Paulo (USP) em 2023.2.

  

## Dados da Disciplina

  

- Universidade de São Paulo

- Instituto de Ciências Matemáticas e de Computação

- Disciplina: SCC0607 - Estrutura de Dados III

- Professora: Dra. Cristina Dutra de Aguiar

- Monitores:

- Eduardo Souza Rocha (eduardos.rocha17@usp.br ou telegram: @edwolt)

- Beatriz Aimee Teixeira Furtado Braga (beatriztfb@usp.br ou telegram: @bia_aimee)

- Heitor Tanoue de Mello (heitortanoue@usp.br ou telegram: @heitortanoue)

  

## Integrantes do Grupo

  

- Felipe Aparecido da Silva nºUSP: 11954502

- Vítor Augusto Paiva de Brito nºUSP: 13732303

  

## Arquivos de índice

  

- ### Registro de cabeçalho de índice:

- ***status***: indica a consistência do arquivo de índice, devido à queda de energia, travamento do programa, etc. Pode assumir os valores 0, para indicar que o arquivo de dados está inconsistente, ou 1, para indicar que o arquivo de dados está consistente. Ao se abrir um arquivo para escrita, seu status deve ser 0 e, ao finalizar o uso desse arquivo, seu status deve ser 1.

- ***noRaiz***: armazena o *RRN* do nó (página) raiz do índice árvore-B. Quando a árvore-B está vazia, noRaiz = -1.

- ***RRNproxNo***: armazena o *RRN* do próximo nó (página) do índice árvore-B a ser inserido. Assume inicialmente o valor 0, sendo esse valor incrementado a cada criação de um novo nó.

  

- ### Registros de dados de índice:

- ***nroChavesNo***: armazena o número de chaves de busca indexadas no nó.

- ***alturaNo***: armazena a altura do nó na árvore. Quando o nó é um nó-folha, alturaNo deve ser igual a 1. Quando o nó é pai de um nó-folha, então alturaNo deve ser igual a 2. E assim sucessivamente.

- ***RRNdoNo***: armazena o número do *RRN* referente ao nó (ou seja, à página de disco).
- ***Chave*** **(C<sub>i</sub>)**: Chave de busca correspondente a um registro de dados na página de disco.
- ***Ponteiro*** **(P<sub>i</sub>)**: Ponteiro de referência para uma página de disco descendente na árvore B.
- ***Ponteiro de referência*** **(PR<sub>i</sub>)**: Ponteiro de referência para o registro de dados em um arquivo de dados correspondente a uma chave na página de disco.

  

## Programa

  

### Descrição Geral

  

Implementação um programa em *C* por meio do qual seja possível realizar a pesquisa e a inserção de dados em arquivos de dados com o auxílio de um índice árvore-B.

  

### Funcionalidades

  

O programa oferece as seguintes funcionalidades:

  

5. Crie um arquivo de índice árvore-B que indexa a chave de busca definida sobre um arquivo de dados de entrada já existente.

- **Entrada**: ***arquivoBinariodeDados.bin***  ***arquivoBinariodeIndice.bin***

- **Saída**: Listar o arquivo binário ***arquivoIndice.bin*** usando a função *binarioNaTela*.

  

6. Permita a recuperação dos dados de todos os registros de um arquivo de dados de entrada, de forma que esses registros satisfaçam um critério de busca determinado pelo usuário. Quando o campo usado na busca for a chave de busca, que é a concatenação dos campos *nomeTecnologiaOrigem* e *nomeTecnologiaDestino*, então a busca deve ser feita usando o índice árvore-B criado na funcionalidade ***5***.

- **Entrada**: arquivoEntrada.bin, n (quantidade de buscas)
nomeCampo<sub>1</sub> valorCampo<sub>1</sub>
 nomeCampo<sub>2</sub> valorCampo<sub>2</sub>...

- **Saída**: Exibição dos registros que satisfazem os critérios de busca.

  

7. Permita a inserção de novos registros em um arquivo de dados de entrada, a qual deve ser realizada no final do arquivo.

- **Entrada**: ***arquivoDados.bin arquivoIndice.bin*** *n*
nomeTecnologiaOrigem<sub>1</sub> grupo<sub>1</sub> popularidade<sub>1</sub> nomeTecnologiaDestino<sub>1</sub> peso<sub>1</sub>
nomeTecnologiaOrigem<sub>2</sub> grupo<sub>2</sub> popularidade<sub>2</sub> nomeTecnologiaDestino<sub>2</sub> peso<sub>2</sub>...

- **Saída**: Listar os arquivos ***arquivoDados.bin*** e ***arquivoIndice.bin*** usando a função fornecida *binarioNaTela*.
### Uso do programa

  

Para compilar o programa, execute o seguinte comando:

- ``make all``

Para executar o programa, utilize o comando:

- ``make run``

  

### Exemplos de uso das funcionalidades:

  

Criação de arquivo de índice (Funcionalidade 5):

```

5 arquivoDados.bin arquivoIndice.bin
```
  

Listagem de Registros (Funcionalidade 6):

```

6 arquivoDados.bin arquivoIndice.bin n
nomeCampo1 valorCampo1
nomeCampo2 valorCampo2
...
nomeCampon valorCampon
```

  

Inserção em arquivo de índice (Funcionalidade 7):

```

7 arquivoDados.bin arquivoIndice.bin n
nomeTecnologiaOrigem1 grupo1 popularidade1 nomeTecnologiaDestino1 peso1
nomeTecnologiaOrigem2 grupo2 popularidade2 nomeTecnologiaDestino2 peso2
...
nomeTecnologiaOrigemn grupon popularidaden nomeTecnologiaDestinon peson
```

  

## Contato:

  

- Profa. Dra. Cristina Dutra de Aguiar: cdac@icmc.usp.br

- Felipe Aparecido da Silva: felipe.ap.silva@usp.br ou daf_felipe.ap.silva@outlook.br

- Vítor Augusto Paiva de Brito: vitor_brito@usp.br

  

Universidade de São Paulo - Instituto de Ciências Matemáticas e de Computação

  

Departamento de Ciências de Computação

  

Av. Trabalhador São-carlense, 400, Centro

  

São Carlos - SP, CEP 13566-590

  

Brasil

  

Website: www.icmc.usp.br

  

## Importante

Este repositório contém a documentação e código-fonte de um projeto acadêmico e não deve ser usado para fins comerciais ou de produção.