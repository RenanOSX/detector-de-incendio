#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <pthread.h>

#define NUM_THREADS 10
#define MATRIX_SIZE 30
#define SENSOR_SPACING 3

typedef struct {
    int id;
    int x;
    int y;
} ThreadArgs;

extern char forest[MATRIX_SIZE][MATRIX_SIZE];
extern pthread_mutex_t forest_mutex;
extern pthread_cond_t fire_detected_cond;
extern pthread_mutex_t fire_detected_mutex;
extern int fire_detected;

void inicializar_floresta(void);
void* imprimir_floresta(void* arg);
void* sensor_thread(void* arg);
void* gerar_incendios(void* arg);
void* central_thread(void* arg);
void apagar_fogo(int x, int y);

#endif // FUNCTIONS_H