
/*
 * Nicolás de Rivas Morillo - 843740
 * Problema voluntario - SOper
 * Fecha: 03/11/2022
 */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void imprimirCar(const char c, const int n) {

    for (int i = 0; i < n; i++)
        write(1, &c, 1);

}

int main(int argc, char *argv[]) {

    if (fork() == 0)
        imprimirCar('a', atoi(argv[1]));
    else if (fork() == 0)
        imprimirCar('b', atoi(argv[1]));
    else {
        imprimirCar('c', atoi(argv[1]));
        wait(0);
        wait(0);
    }

    exit(0);

}
