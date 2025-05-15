/*
* Importante incluir el argumento [-lpthread] al compilar (gcc main.c -lpthread -o main)

* Al crear un hilo se ejecuta una funcion 

* Threads usados para la ejecucion de diferentes funciones en paralelo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h> //Libreria para trabajar con threads


void* threadTest(){
    fprintf(stdout, "Test threads\n");    
    sleep(2);
    fprintf(stdout, "End of thread\n");
}

int main(int argc, char const *argv[]) {
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &threadTest, NULL) != 0) {
        fprintf(stderr, "Error al crear el primer thread\n");
        return -1;
    }
    if (pthread_create(&t2, NULL, &threadTest, NULL) != 0) {
        fprintf(stderr, "Error al crear el segundo thread\n");
        return -1;
    }
    if (pthread_join(t1, NULL) != 0){ // Parecido al wait() con los procesos
        fprintf(stderr, "Error al esperar al primer thread\n"); 
        return -1;
    }
    if (pthread_join(t2, NULL) != 0) {
        fprintf(stderr, "Error al crear el segundo thread\n");
        return -1;
    } 
    
    return 0;
}
