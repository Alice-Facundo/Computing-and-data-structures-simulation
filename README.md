
# Simulação de Escalonamento de Processos

Este projeto, desenvolvido para a disciplina de Estruturas de Dados, realiza a simulação de algoritmos de escalonamento de processos, especificamente o FCFS (First-Come, First-Served) e o SJF (Shortest Job First). O programa lê uma lista de processos de um arquivo de entrada, os distribui entre múltiplos computadores simulados e calcula métricas de desempenho como tempo de execução e tempo de espera.

## Estruturas de Dados Utilizadas

As políticas de escalonamento foram implementadas utilizando as seguintes estruturas de dados:

  * **FCFS (First-Come, First-Served):** Implementado com uma estrutura de fila (FIFO - First-In, First-Out), onde o primeiro processo a chegar é o primeiro a ser executado. A fila foi construída usando uma lista encadeada simples.
  * **SJF (Shortest Job First):** Implementado com uma lista encadeada que é ordenada de forma crescente com base no tempo de duração da CPU de cada processo.

## Funcionalidades

  * **Simulação de Múltiplos Computadores:** O usuário pode especificar quantos computadores serão utilizados na simulação.
  * **Leitura de Processos:** Os processos são lidos a partir de um arquivo de entrada `.txt`, contendo informações sobre o instante de chegada e os tempos de execução para CPU, disco e rede.
  * **Distribuição de Carga:** Os processos e suas tarefas de disco são aleatoriamente distribuídos entre os computadores e seus discos disponíveis.
  * **Cálculo de Métricas de Desempenho:** Ao final da simulação, o programa exibe:
      * Tempo de Execução Total e Médio.
      * Tempo de Espera Total e Médio.
      * Taxa de Processamento (throughput).

## Estrutura do Projeto

O projeto está organizado nos seguintes arquivos principais:

  * `main.cpp`: Contém a lógica principal da simulação, leitura de arquivos e interação com o usuário.
  * `FCFS.h` / `FCFS.cpp`: Implementação da estrutura de dados de Fila (FIFO).
  * `SJF.h` / `SJF.cpp`: Implementação da estrutura de dados de Lista Encadeada, com função de ordenação para a política SJF.
  * `NeoLook.h` / `NeoLook.cpp`: Contém as classes que modelam os componentes da simulação, como `Processo`, `CPU`, `Disk` e `Computador`.
  * `Node.h`: Estrutura de nó utilizada como base para as listas encadeadas.

## Como Compilar e Executar

Para compilar e executar o projeto, siga os passos abaixo.

### Pré-requisitos

  * Um compilador C++ (como o g++).

### Compilação

1.  Abra um terminal na pasta raiz do projeto.

2.  Execute o seguinte comando para compilar todos os arquivos `.cpp` e gerar um executável chamado `main.exe`:

    ```bash
    g++ -std=c++11 *.cpp -o main.exe
    ```

### Execução

1.  Após a compilação, execute o programa utilizando o seguinte comando:

    ```bash
    ./main.exe <estrutura> <arquivo_de_entrada.txt>
    ```

    **Argumentos:**

      * `<estrutura>`: O algoritmo de escalonamento a ser utilizado. Pode ser `FCFS` ou `SJF`.
      * `<arquivo_de_entrada.txt>`: O nome do arquivo de texto contendo a lista de processos.

    **Exemplo de uso:**

    ```bash
    ./main.exe SJF arquivo_de_entrada_1.txt
    ```

2.  O programa solicitará que você informe o número de computadores a serem utilizados na simulação. Digite o número desejado e pressione Enter.

## Autoras

  * **Maria Alice Angelim Facundo**
  * **Yasmin Lima Costa**