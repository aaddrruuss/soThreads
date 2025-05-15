/*
? Como solucionar el error que estabamos teniamos con los hilos en ../raceConditions
* Usando mutex -> es como una especie de "bloqueo" en una parte del codigo
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/wait.h>

int mails = 0;
pthread_mutex_t mutex;
// int lock = 0; // lock = 1 cuando hagamos algo, y lock = 0 cuando no se haga nada

void* rutina1() {
    for (int i = 0 ; i < 3000000 ; i++) {
        pthread_mutex_lock(&mutex);
        //if (lock == 1){
            // Esperar hasta que lock sea 0
        // }
        // lock = 1;
        mails++;
        pthread_mutex_unlock(&mutex); // ? Gracias a usar estas funciones ahora si que vamos a recibir el resultado esperado (2000000)
        // lock = 0;
    }
}

int main(int argc, char const *argv[]) {
    pthread_mutex_init(&mutex, NULL);
    pthread_t t1,t2;
    if (pthread_create(&t1, NULL, rutina1, NULL) != 0){
        fprintf(stderr, "Error al crear un nuevo thread\n");
        return -1;
    }
    if (pthread_create(&t2, NULL, rutina1, NULL) != 0){
        fprintf(stderr, "Error al crear un nuevo thread\n");
        return -1;
    }

    if (pthread_join(t1, NULL) != 0) {
        fprintf(stderr, "Error al esperar a que termine de ejecutarse el thread / hilo\n");
        return -1;
    }
    if (pthread_join(t2, NULL) != 0) {
        fprintf(stderr, "Error al esperar a que termine de ejecutarse el thread / hilo\n");
        return -1;
    }
    pthread_mutex_destroy(&mutex);
    fprintf(stdout, "Numero de mails enviados: %d\n", mails); 
    return 0;
}
