#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int x = 2;

void* rutina2() {
    x++;
    sleep(2);
    fprintf(stdout, "Valor de x: %d\n", x);
}
void* rutina1() {
    sleep(2);
    fprintf(stdout, "Valor de x: %d\n", x);
}

int main(int argc, char const *argv[]) {
    pthread_t t1,t2;
    pthread_create(&t1, NULL, rutina1, NULL);
    pthread_create(&t2, NULL, rutina2, NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}