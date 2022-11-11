/* 
 * Practica 4 - SOper
 * Función duerme mediante señales
 * Nicolás de Rivas Morillo 843740
 */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

#define MAL (int (*)())-1

void sig_han() {

    if (signal(SIGALRM, sig_han) == MAL) {

        printf("Error - signal.\n");
        exit(1);

    }

}

void duerme(const unsigned s) {

    if (signal(SIGALRM, sig_han) == MAL) {

        printf("Error - signal.\n");
        exit(1);

    }


    alarm(s);
    pause();

}
