/*
* Podemos ejecutar 3 operaciones con los condition variables
? pthread_cond_wait() -> esperar
? pthread_cond_signal() -> enviar una señal
? pthread_cond_broadcast() -> "despierta" aquellos hilos que estaban durmiendo
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <pthread.h>

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
int fuel = 0; 

void* repostando(void* arg) {
    for (int i = 0 ; i < 5 ; i++){
        pthread_mutex_lock(&mutexFuel);
        fuel += 15;
        fprintf(stdout, "Repostando: %d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        pthread_cond_signal(&condFuel);
        sleep(1);
    }   
}

void* coche_esperando(void *arg) {
    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40) {
        fprintf(stdout, "No hay conbustible. Waiting...\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
        // Equivalente a:
        // pthread_mutex_unlock(&mutexFuel);
        // wait for signal condFuel;
        // pthread_mutex_lock(&mutexFuel);
    }
    fuel -= 40;
    fprintf(stdout, "Combustible restante: %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);
}

int main(int argc, char const *argv[]) {
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);
    pthread_t th[2];
    for (int i = 0 ; i < 2 ; i++) {
        if (i == 1) {
            if (pthread_create(&th[i], NULL, repostando, NULL) != 0) {
                perror("pthread_create: ");
            }
        }
        else {
            if (pthread_create(&th[i], NULL, coche_esperando, NULL) != 0) {
                perror("pthread_create: ");
            }
        }
    }

    for (int i = 0 ; i < 2 ; i++) {
        if (pthread_join(th[i], NULL) != 0){
            perror("pthread_join ");
        }
    }

    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return 0;
}
