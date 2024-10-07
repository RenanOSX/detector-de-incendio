# Renan Oliveira da Silva

## Relatório sobre o Código

O arquivo main.c é o ponto de entrada do programa que simula um sistema de
monitoramento de incêndios em uma floresta. Ele utiliza a biblioteca pthread para
criar e gerenciar múltiplas threads.
1. Inclusão de Bibliotecas:
- stdio.h e stdlib.h para operações básicas de entrada/saída e alocação
de memória.
- pthread.h para manipulação de threads.
- functions.h para funções auxiliares definidas em outro arquivo.
2. Função main:
- Inicializa um mutex (forest_mutex) para sincronização entre threads.
- Chama a função inicializar_floresta para configurar o ambiente inicial
da floresta.
- Cria um array de threads (sensores) para os sensores de incêndio.
- Utiliza dois loops aninhados para distribuir os sensores pela matriz da
floresta, com espaçamento definido por SENSOR_SPACING.
- Para cada posição válida, aloca memória para os argumentos da
thread (ThreadArgs), define os valores de id, x e y, e cria a thread do
sensor com pthread_create.
- Cria uma thread para geração de incêndios (thread_incendios) e uma
thread central (thread_central) para coordenação.
Arquivo: functions.c
O arquivo functions.c contém as implementações das funções declaradas em
functions.h. Estas funções são utilizadas para inicializar a floresta, gerar incêndios e
definir o comportamento das threads dos sensores e da central.
1. Funções Esperadas:
- inicializar_floresta: Configura a matriz da floresta.
- sensor_thread: Define o comportamento de cada thread de sensor.
- gerar_incendios: Gera incêndios aleatórios na floresta.
- central_thread: Coordena as ações dos sensores e responde aos
incêndios.
Arquivo: functions.h
O arquivo functions.h contém as declarações das funções e estruturas utilizadas em
functions.c e main.c.
1. Declarações Esperadas:
- Estruturas como ThreadArgs para passar argumentos às threads.
- Funções como inicializar_floresta, sensor_thread, gerar_incendios e
central_thread.
- Variáveis globais como forest_mutex e constantes como
NUM_THREADS, MATRIX_SIZE, e SENSOR_SPACING.

## Conclusão
O código implementa um sistema de monitoramento de incêndios utilizando threads
para simular sensores distribuídos em uma matriz que representa a floresta. A
sincronização é feita através de um mutex, e a coordenação das ações é gerida por
uma thread central. As funções auxiliares são definidas em functions.c e declaradas
em functions.h.
