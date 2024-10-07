# Sistema de Monitoramento de Incêndios em Floresta

## Autor
Renan Oliveira da Silva

## Descrição
Este projeto implementa um sistema de monitoramento de incêndios em uma floresta utilizando múltiplas threads. Cada thread simula um sensor de incêndio posicionado em uma matriz que representa a floresta. As threads são gerenciadas utilizando a biblioteca `pthread`, e a sincronização entre elas é feita através de um mutex. O sistema também conta com uma thread central que coordena as ações dos sensores e uma thread responsável por gerar incêndios aleatórios.

## Estrutura do Projeto

### Arquivo: `main.c`
Este é o ponto de entrada do programa. As principais responsabilidades deste arquivo são:
- **Inclusão de Bibliotecas:**
  - `stdio.h` e `stdlib.h`: Operações básicas de entrada/saída e alocação de memória.
  - `pthread.h`: Manipulação de threads.
  - `functions.h`: Declarações de funções auxiliares.
  
- **Função `main`:**
  1. Inicializa um mutex (`forest_mutex`) para sincronização entre threads.
  2. Chama a função `inicializar_floresta` para configurar o ambiente inicial da floresta.
  3. Cria um array de threads para os sensores de incêndio.
  4. Distribui os sensores pela matriz da floresta utilizando dois loops aninhados, com espaçamento definido pela constante `SENSOR_SPACING`.
  5. Para cada posição válida, aloca memória para os argumentos da thread (`ThreadArgs`), define os valores de `id`, `x`, e `y`, e cria a thread do sensor com `pthread_create`.
  6. Cria uma thread para a geração de incêndios (`thread_incendios`) e uma thread central (`thread_central`) para coordenar o sistema.

### Arquivo: `functions.c`
Este arquivo contém as implementações das funções declaradas em `functions.h`. Suas funções principais incluem:
- **`inicializar_floresta`:** Configura a matriz da floresta.
- **`sensor_thread`:** Define o comportamento de cada thread de sensor de incêndio.
- **`gerar_incendios`:** Gera incêndios aleatórios na floresta.
- **`central_thread`:** Coordena as ações dos sensores e responde aos incêndios detectados.

### Arquivo: `functions.h`
Este arquivo contém as declarações das funções e estruturas utilizadas em `functions.c` e `main.c`. As declarações incluem:
- **Estruturas:**
  - `ThreadArgs`: Utilizada para passar argumentos às threads.
  
- **Funções:**
  - `inicializar_floresta`
  - `sensor_thread`
  - `gerar_incendios`
  - `central_thread`
  
- **Variáveis Globais:**
  - `forest_mutex`: Mutex utilizado para sincronizar o acesso à floresta.
  - Constantes como `NUM_THREADS`, `MATRIX_SIZE`, e `SENSOR_SPACING`.
