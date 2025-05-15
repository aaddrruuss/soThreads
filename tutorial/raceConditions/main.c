/*
* Simulacion de un sistema de correos electronicos
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/wait.h>

int mails = 0;
void* rutina1() {
    for (int i = 0 ; i < 1000000 ; i++) {
        mails++;
        // Lee el valor
        // Incrementa
        // Escribe el valor de nuevo
    }
}

int main(int argc, char const *argv[]) {
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

    fprintf(stdout, "Numero de mails enviados: %d\n", mails); //Se espera el valor 2.000.000 pero se recibe un valor inferior ¿porque?
    /*
    * A esto se le llama "race condition" 
    * El sistema operativo pausa al ejecucion de uno de los hilos mientras que el otro sigue ejecutando 
    * Cuando se reanuda el proceso que estaba en pause, en lugar de volver a leer la variable
    * Opera con el valor de la variable que estaba almacenado de forma local en la CPU, lo que
    * Ocasiona que se guarde en la variable un valor que no es el que corresponde
    * De tal forma que el thread 1 estuvo incrementando el valor de mails mientras thread 2 estaba en pausa
    * Hasta el valor 30 (por ejemplo) meintras que thread se quedo pausado en el valor 15, entonces
    * al volver a reanudarse la ejecucion del thread 2 este lo incrementara de 15 a 16 y sobreescribira el valor
    * de 30 por el valor de 16
    */
    return 0;
}
