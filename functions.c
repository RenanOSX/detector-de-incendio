#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char forest[MATRIX_SIZE][MATRIX_SIZE];
pthread_mutex_t forest_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t fire_detected_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t fire_detected_mutex = PTHREAD_MUTEX_INITIALIZER;
int fire_detected = 0;

void inicializar_floresta(void) {
    pthread_mutex_lock(&forest_mutex);
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            forest[i][j] = '-';
        }
    }
    for (int i = 0; i < MATRIX_SIZE; i += SENSOR_SPACING) {
        for (int j = 0; j < MATRIX_SIZE; j += SENSOR_SPACING) {
            forest[i][j] = 'T';
        }
    }
    pthread_mutex_unlock(&forest_mutex);
}

void* imprimir_floresta(void* arg) {
    while (1) {
        pthread_mutex_lock(&forest_mutex);
        system("clear");
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                printf("%c ", forest[i][j]);
            }
            printf("\n");
        }
        pthread_mutex_unlock(&forest_mutex);
        usleep(500000);
    }
    return NULL;
}

void apagar_fogo(int x, int y) {
    if (x < 0 || x >= MATRIX_SIZE || y < 0 || y >= MATRIX_SIZE) {
        return;
    }
    if (forest[x][y] == '@') {
        forest[x][y] = '/';
        printf("Fire extinguished at (%d, %d)\n", x, y);
        apagar_fogo(x - 1, y);
        apagar_fogo(x + 1, y);
        apagar_fogo(x, y - 1);
        apagar_fogo(x, y + 1);
    }
}

void* sensor_thread(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    int x = args->x;
    int y = args->y;

    while (1) {
        pthread_mutex_lock(&forest_mutex);
        int fire_nearby = 0;

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int nx = x + i;
                int ny = y + j;
                if (nx >= 0 && nx < MATRIX_SIZE && ny >= 0 && ny < MATRIX_SIZE) {
                    if (forest[nx][ny] == '@') {
                        fire_nearby = 1;
                        apagar_fogo(nx, ny);
                    }
                }
            }
        }

        if (fire_nearby) {
            pthread_mutex_lock(&fire_detected_mutex);
            fire_detected = 1;
            pthread_cond_signal(&fire_detected_cond);
            pthread_mutex_unlock(&fire_detected_mutex);
        }

        pthread_mutex_unlock(&forest_mutex);
        sleep(1);
    }
    free(args);
    return NULL;
}

void* gerar_incendios(void* arg) {
    while (1) {
        pthread_mutex_lock(&forest_mutex);
        int x = rand() % MATRIX_SIZE;
        int y = rand() % MATRIX_SIZE;
        if (forest[x][y] == '-') {
            forest[x][y] = '@';
            printf("Fire generated at (%d, %d)\n", x, y);
        }
        pthread_mutex_unlock(&forest_mutex);
        sleep(5);
    }
    return NULL;
}

void* central_thread(void* arg) {
    while (1) {
        pthread_mutex_lock(&fire_detected_mutex);
        while (!fire_detected) {
            pthread_cond_wait(&fire_detected_cond, &fire_detected_mutex);
        }
        fire_detected = 0;
        pthread_mutex_unlock(&fire_detected_mutex);

        pthread_mutex_lock(&forest_mutex);
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                if (forest[i][j] == '@') {
                    apagar_fogo(i, j);
                }
            }
        }
        pthread_mutex_unlock(&forest_mutex);
        sleep(10);
    }
    return NULL;
}