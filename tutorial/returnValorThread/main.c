#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/wait.h>


void* tirarDado() {
    int value = (rand() % 6) + 1 ;
    int *result = (int*)malloc(sizeof(int) * 1);
    *result = value;
    printf("%p\n", result);
    return result;
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
void esperarThreads(pthread_t *th, int size_array, int **res){
    for (int i = 0 ; i < size_array; i++){
        if (pthread_join(th[i], (void **) &res[i]) != 0) {
            perror("pthread_join: ");
            exit(-1);
        }
        fprintf(stdout, "Thread %d termiando ejecucion\n", i);
    }
}

int main(int argc, char **argv) {
    int *res[6];
    srand(time(NULL));
    pthread_t t1[6];
    crearThreads(t1, 6, tirarDado);
    esperarThreads(t1, 6, res);
    for (int i = 0 ; i < 6 ; i++) {
        printf("Main res variable: %p\n", (res[i]));
        printf("Resultado en main %d\n", *(res[i]));
    }
    for(int i = 0 ; i < 6 ; i++) {
        free(res[i]);
    }
    return 0;
}