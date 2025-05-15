#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    int x = 2;
    int pid = fork();

    if (pid == -1) {
        fprintf(stderr, "Error al crear un procesos nuevo\n");
        return -1;
    }

    if (pid == 0) {
        x++;
        fprintf(stdout, "Valor de x: %d\n", x);
    }
    else {
        fprintf(stdout, "Valor de x: %d\n", x);
        wait(NULL);
    }

    return 0;
}
