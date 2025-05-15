/*
? Crear 10 threads, cada uno usa un unico numero primo del array y lo imprime por pantalla
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

int primos[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int size_primos = sizeof(primos)/sizeof(int);


void* printPrimos(void* numero){
    int idx = *(int*)numero;
    int suma = 0;

    for (int i = 0 ; i < 5 ; i++) {
        suma += primos[idx + i];
    }
    *(int *)numero = suma;
    return numero;
}

void crearThreads(pthread_t *th, int size_array, void* function, void* args){
    for (int i = 0 ; i < size_array; i++){
        *(int *)args = i * 5;
        if (pthread_create(&th[i], NULL, function, args) != 0) {
            perror("pthread_create: ");
            exit(-1);
        }
        // fprintf(stdout, "Thread %d creado\n", i);
    }
}

void esperarThreads(pthread_t *th, int size_array, void* save_here){
    for (int i = 0 ; i < size_array; i++){
        if (pthread_join(th[i], save_here) != 0) {
            perror("pthread_join: ");
            exit(-1);
        }
        // fprintf(stdout, "Thread %d termiando ejecucion\n", i);
    }
}

int main(int argc, char const *argv[]) {
    pthread_t t1[2];
    void* suma = malloc(sizeof(int)) ;
    printf("Suma de todos los valores del array [");
    crearThreads(t1, 2, printPrimos, suma);
    esperarThreads(t1, 2, suma);
    for(int i = 0 ; i < size_primos ; i++) {
        if (i != size_primos -1 ) {
            printf("%d ", primos[i]);
        }else {
            printf("%d", primos[i]);
        }
    }
    printf("]\nEs: %d", *(int *)suma);

    free(suma);
    return 0;
}
