/*
? Crear 10 threads, cada uno usa un unico numero primo del array y lo imprime por pantalla
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

int primos[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* printPrimos(void* numero){
    int numero1 = *(int*)numero;
    printf("%d ", numero1);
    return NULL;
}

void crearThreads(pthread_t *th, int size_array, void* function){
    for (int i = 0 ; i < size_array; i++){
        if (pthread_create(&th[i], NULL, function, (void *)(primos + i)) != 0) {
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
    pthread_t t1[10];
    printf("[");
    crearThreads(t1, 10, printPrimos);
    esperarThreads(t1, 10);
    printf("]\n");


    return 0;
}
