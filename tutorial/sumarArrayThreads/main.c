#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

int primos[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int size_primos = sizeof(primos)/sizeof(int);

void* printPrimos(void* numero){
    int idx = *(int*)numero;
    int* resultado = malloc(sizeof(int));
    *resultado = 0;

    for (int i = 0; i < 5; i++) {
        *resultado += primos[idx + i];
    }
    
    free(numero); 
    return resultado;
}

void crearThreads(pthread_t *th, int size_array, void* function){
    for (int i = 0; i < size_array; i++){
        int *a = malloc(sizeof(int));
        *a = i * 5;
        if (pthread_create(&th[i], NULL, function, a) != 0) {
            perror("pthread_create: ");
            exit(-1);
        }
        // fprintf(stdout, "Thread %d creado\n", i);
    }
}

int esperarThreads(pthread_t *th, int size_array, void** save_here){
    int res = 0;
    for (int i = 0; i < size_array; i++){
        void* resultado;
        if (pthread_join(th[i], &resultado) != 0) {
            perror("pthread_join: ");
            exit(-1);
        }
        res += *(int*)resultado;
        if (save_here != NULL) {
            save_here[i] = resultado;
            printf("Resultado %d es %d\n", i , *(int*)save_here[i]);
        }
    }
}

int main(int argc, char const *argv[]) {
    pthread_t t1[2];
    void* resultados[2] = {0};
    int suma_total = 0;
    
    printf("Valores del array [");
    for(int i = 0; i < size_primos; i++) {
        if (i != size_primos - 1) {
            printf("%d, ", primos[i]);
        } else {
            printf("%d", primos[i]);
        }
    }
    printf("]\n");
    
    crearThreads(t1, 2, printPrimos);
    esperarThreads(t1, 2, resultados);
    int res = 0;
    for (int i = 0 ; i < 2 ; i++) {
        res += *(int *)resultados[i];
    }
    
    printf("La suma calculada por los hilos es: %d\n", res);
    
    return 0;
}