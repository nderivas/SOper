/*
 * Trabajo previo - P4 SOper
 * Nicolás de Rivas Morillo 843740
 */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

#define MAL (int (*)())-1

void sig_hand(int n) {

    printf("Me ha llegado la senal %d", n);

}

int main(int argc, char* argv[]) {

    int id = getpid();

    if (signal(8, sig_hand) == MAL) exit(-1);

    kill(id, atoi(argv[1]));

    while(1) {

        printf("Sigo aquí\n");
        sleep(1);

    }

}
