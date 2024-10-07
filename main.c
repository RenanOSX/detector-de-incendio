#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "functions.h"

int main() {
    pthread_mutex_init(&forest_mutex, NULL);

    inicializar_floresta();

    pthread_t sensores[NUM_THREADS];
    int sensor_count = 0;
    for (int i = 0; i < MATRIX_SIZE; i += SENSOR_SPACING) {
        for (int j = 0; j < MATRIX_SIZE; j += SENSOR_SPACING) {
            if (sensor_count < NUM_THREADS) {
                ThreadArgs* args = malloc(sizeof(ThreadArgs));
                args->id = sensor_count;
                args->x = i;
                args->y = j;
                if (pthread_create(&sensores[sensor_count], NULL, sensor_thread, args) != 0) {
                    perror("Failed to create sensor thread");
                    return 1;
                }
                printf("Sensor thread %d created at (%d, %d)\n", sensor_count, i, j);
                sensor_count++;
            }
        }
    }

    pthread_t thread_incendios;
    if (pthread_create(&thread_incendios, NULL, gerar_incendios, NULL) != 0) {
        perror("Failed to create fire generation thread");
        return 1;
    }
    printf("Fire generation thread created\n");

    pthread_t thread_central;
    if (pthread_create(&thread_central, NULL, central_thread, NULL) != 0) {
        perror("Failed to create central thread");
        return 1;
    }
    printf("Central thread created\n");

    pthread_t thread_imprimir;
    if (pthread_create(&thread_imprimir, NULL, imprimir_floresta, NULL) != 0) {
        perror("Failed to create print thread");
        return 1;
    }
    printf("Print thread created\n");

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(sensores[i], NULL);
    }
    pthread_join(thread_incendios, NULL);
    pthread_join(thread_central, NULL);
    pthread_join(thread_imprimir, NULL);

    pthread_mutex_destroy(&forest_mutex);

    return 0;
}