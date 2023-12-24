# Trabalho de Estrutura de Dados III - README

Este repositório contém o código-fonte e a documentação do trabalho prático da disciplina Estrutura de Dados III (SCC0607), ministrada pela professora Profa. Dra. Cristina Dutra de Aguiar no Instituto de Ciências Matemáticas e de Computação (ICMC) da Universidade de São Paulo (USP).

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

## Arquivo de Dados e Registros

- Registro de Cabeçalho:
  - status: indica a consistência do arquivo de dados.
  - proxRRN: armazena o valor do próximo RRN (número relativo do registro) disponível.
  - nroTecnologias: indica a quantidade de tecnologias diferentes que estão armazenadas no arquivo de dados.
  - nroParesTecnologias: indica a quantidade de pares (nomeTecOrigem, nomeTecDestino) diferentes que estão armazenados no arquivo de dados.

- Registros de Dados:
  - grupo: grupo ao qual a tecnologia de origem pertence.
  - popularidade: total de milhões de acessos que existe no Stack Overflow para aquela tecnologia de origem.
  - peso: frequência com que as tags de tecnologia no Stack Overflow aparecem juntas em relação à frequência com que aparecem separadamente.
  - nomeTecnologiaOrigem: nome da tecnologia de origem.
  - nomeTecnologiaDestino: nome da tecnologia de destino.
  - removido: indica se o registro está logicamente removido.

## Programa

### Descrição Geral

Implementar um programa em C por meio do qual o usuário possa obter dados de um arquivo de entrada, gerar arquivos binários com esses dados e realizar operações de leitura e busca.

### Funcionalidades

O programa oferece as seguintes funcionalidades:

1. Leitura de registros de um arquivo CSV e gravação desses registros em um arquivo binário.
   - Entrada: arquivoEntrada.csv, arquivoSaida.bin
   - Saída: Exibição do arquivo binário usando a função binarioNaTela.

2. Recuperação dos dados de todos os registros armazenados em um arquivo de dados de entrada.
   - Entrada: arquivoEntrada.bin
   - Saída: Exibição organizada dos campos dos registros.

3. Recuperação dos dados de registros com base em critérios de busca definidos pelo usuário.
   - Entrada: arquivoEntrada.bin, n (quantidade de buscas), nomeCampo1 valorCampo1, nomeCampo2 valorCampo2, ...
   - Saída: Exibição dos registros que satisfazem os critérios de busca.

4. Recuperação dos dados de um registro com base no número relativo do registro (RRN).
   - Entrada: arquivoEntrada.bin, RRN
   - Saída: Exibição do registro correspondente ao RRN.
  
### Uso do programa

Para compilar o programa, execute o seguinte comando:
- make all

Para executar o programa, utilize o comando:
- make run

### Exemplos de uso das funcionalidades:

Inserção de Registros (Funcionalidade 1):
```
1 arquivoEntrada.csv arquivoSaida.bin
```

Listagem de Registros (Funcionalidade 2):
```
 2 arquivoEntrada.bin
```

Busca por Critérios (Funcionalidade 3):
```
3 arquivoEntrada.bin n
nomeCampo1 "valorCampo1"
nomeCampo2 "valorCampo2"
...
nomeCampon "valorCampon"
```

## Contato:

- Profa. Dra. Cristina Dutra de Aguiar: cdac@icmc.usp.br
- Felipe Aparecido da Silva: felipe.ap.silva@usp.br ou daf_felipe.ap.silva@outlook.br
- Vítor Augusto Paiva de Brito: 	vitor_brito@usp.br

Universidade de São Paulo - Instituto de Ciências Matemáticas e de Computação

Departamento de Ciências de Computação

Av. Trabalhador São-carlense, 400, Centro

São Carlos - SP, CEP 13566-590

Brasil

Website: www.icmc.usp.br

## Importante
Este repositório contém a documentação e código-fonte de um projeto acadêmico e não deve ser usado para fins comerciais ou de produção.
