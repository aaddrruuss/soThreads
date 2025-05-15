/*
* Como crear multiples threads con bucles en lugar de tener codigo duplicado
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/wait.h>

int mails = 0;
pthread_mutex_t mutex;

void* rutina1() {
    for (int i = 0 ; i < 100000000 ; i++) {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex); 
    }
}

void crearThreads(pthread_t *th, int size_array, void* function){
    for (int i = 0 ; i < size_array; i++){
        if (pthread_create(&th[i], NULL, function, NULL) != 0) {
            perror("pthread_create: ");
            exit(-1);
        }
        fprintf(stdout, "Thread %d creado\n", i);
    }
}
void esperarThreads(pthread_t *th, int size_array){
    for (int i = 0 ; i < size_array; i++){
        if (pthread_join(th[i], NULL) != 0) {
            perror("pthread_join: ");
            exit(-1);
        }
        fprintf(stdout, "Thread %d termiando ejecucion\n", i);
    }
}

int main(int argc, char const *argv[]) {
    pthread_t th[12];
    pthread_mutex_init(&mutex, NULL);
    crearThreads(th, 12, rutina1);
    esperarThreads(th, 12);
    pthread_mutex_destroy(&mutex);
    fprintf(stdout, "Numero de mails enviados: %d\n", mails); 
    return 0;
}
