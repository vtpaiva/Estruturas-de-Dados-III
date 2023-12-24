# Trabalho II de Estrutura de Dados III.

  

Este repositório contém o código-fonte e a documentação do trabalho prático II da disciplina Estrutura de Dados III (SCC0607), ministrada pela professora Profa. Dra. Cristina Dutra de Aguiar no Instituto de Ciências Matemáticas e de Computação (ICMC) da Universidade de São Paulo (USP) em 2023.2.

  

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

## Programa

### Descrição Geral  

Implementação um programa por meio do qual o usuário possa obter dados de um arquivo binário de entrada, gerar um grafo direcionado ponderado a partir deste e realizar investigações interessantes dentro do contexto de ecossistemas tecnológicos e como as tecnologias estão relacionadas entre si.

### Funcionalidades

  

O programa oferece as seguintes funcionalidades:

  

#### 8. Permita a recuperação dos dados, de todos os registros, armazenados em um arquivo de dados no formato binário e a geração de um grafo contendo esses dados na forma de um conjunto de vértices *V* e um conjunto de arestas *A*, sendo que cada elemento do vetor representa o nome de uma tecnologia. O grafo é um grafo direcionado ponderado e representa como as tecnologias estão relacionadas entre si, ou seja, a frequência que as pessoas que estão vendo uma tecnologia origem clicam para ver uma tecnologia destino a partir desta, o peso. 

- **Entrada**: ***arquivoDados.bin***

- **Saída**: Para cada elemento *i* do vetor e para cada elemento *j* da lista linear correspondente, deve ser exibido em uma linha diferente: nomeTecnologia do elemento *i*, grupo do elemento *i*, grau de entrada do elemento *i*, grau de saída do elemento *i*, grau do elemento *i*, nomeTecnologia do elemento *j* e peso do elemento *j*.

  

#### 9. Gere o grafo transposto do grafo gerado na funcionalidade ***8***.

- **Entrada**: ***arquivoDados.bin***

- **Saída**: Impressão dos elementos que compõem o grafo análoga à funcionalidade ***8***.

  

#### 10. Dado o nome de uma tecnologia destino, liste o nome de todas as tecnologias que originaram o clique para essa tecnologia destino.

- **Entrada**: ***arquivoDados.bin*** *n*
nomeTecnologia<sub>1</sub>
nomeTecnologia<sub>2</sub>...

- **Saída**: Primeiro, deve ser escrito o nome da tecnologia passada como parâmetro, depois deve ser colocado o caractere ":". Depois, escreva cada nome de cada tecnologia que originou a tecnologia passada como parâmetro em ordem crescente, separando cada nome por vírgula e deixando um espaço em branco.

#### 11. Dado um grafo direcionado como entrada, determine se ele é fortemente conexo e quantos componentes fortemente conexos ele possui. 

- **Entrada**: ***arquivoDados.bin***

- **Saída**: Caso o grafo seja fortemente conexo, deve ser escrita a saída **"Sim, o grafo e fortemente conexo e possui 1 componente."** Caso o grafo não seja fortemente conexo, deve ser escrita a saída **"Nao, o grafo nao e fortemente conexo e possui *x* componentes."**, sendo que *x* é o número de componentes fortemente conexos que o grafo possui. 

#### 12. Dado o nome de uma tecnologia origem e uma tecnologia destino, determine o caminho mais curto entre essas duas tecnologias.

- **Entrada**: ***arquivoDados.bin*** *n*
nomeTecnologiaOrigem<sub>1</sub> nomeTecnologiaDestino<sub>1</sub>
nomeTecnologiaOrigem<sub>2</sub> nomeTecnologiaDestino<sub>2</sub>

- **Saída**: Escreva o valor de *nomeTecnologiaOrigem*, seguido do valor de *nomeTecnologiaDestino*, seguido do caractere ":", seguido pelo peso do caminho mais curto, conforme ilustrado no exemplo de execução. Quando não existir caminho entre a tecnologia origem e a tecnologia destino, a saída deve ser da seguinte forma: escreva o valor de *nomeTecnologiaOrigem*, seguido do valor de *nomeTecnologiaDestino*, seguido do caractere ":", seguido de **CAMINHO INEXISTENTE**.

### Uso do programa  

Para compilar o programa, execute o seguinte comando:

- ``make all``

Para executar o programa, utilize o comando:

- ``make run``

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