/*
* La diferencia entre trylock y lock es que trylock() intentara bloquear el mutex pero no te asegura que lo haga
* En caso de que bloquee correctamente devolvera 0, sino un codigo de error
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/wait.h>

pthread_mutex_t mutex;

void * rutina (void * arg) {
    if (pthread_mutex_trylock(&mutex) == 0) {
        printf("Bloqueado\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
    } else {
        fprintf(stderr, "No me he bloqueado\nCodigo de error %d - %s\n\n", EBUSY, strerror(EBUSY));
    }
}

void crearThreads(pthread_t *th, int size_array, void* function, void *arg){
    for (int i = 0 ; i < size_array; i++){
        if (pthread_create(&th[i], NULL, function, arg) != 0) {
            perror("pthread_create: ");
            exit(-1);
        }
        // fprintf(stdout, "Thread %d creado\n", i);
    }
}

void esperarThreads(pthread_t *th, int size_array){
    for (int i = 0 ; i < size_array; i++){
        if (pthread_join(th[i], NULL) != 0) {
            perror("pthread_join: ");
            exit(-1);
        }
        // fprintf(stdout, "Thread %d termiando ejecucion\n", i);
    }
}

int main(int argc, char const *argv[]) {
    pthread_mutex_init(&mutex, NULL);
    pthread_t th[4];
    crearThreads(th, 4, rutina, NULL);
    esperarThreads(th, 4);
    pthread_mutex_destroy(&mutex);
    return 0;
}
