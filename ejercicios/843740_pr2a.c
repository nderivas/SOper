#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define MAL (int (*)())-1

void sig_han() {

    if (signal(SIGALRM, sig_han) == MAL) {

        printf("Error signal.\n");
        exit(1);

    }

}

void salir() {

    exit(0);

}

int main() {

    signal(SIGINT, salir);

    if (signal(SIGALRM, sig_han) == MAL) {

        printf("Error signal.\n");
        exit(1);

    }

    if (fork() == 0) { // P1
        
        int s = 1;
        alarm(1);
        pause();
        printf("P1: %ds\n", s);
        while (1) {

            s += 3;
            alarm(3);
            pause();
            printf("P1: %ds\n", s);
            
        }

    } else if (fork() == 0) { // P2

        int s = 2;
        alarm(2);
        pause();
        printf("P2: %ds\n", s);
        while (1) {

            s += 3;
            alarm(3);
            pause();
            printf("P2: %ds\n", s);
            
        }

    } else { // P3
        
        int s = 3;
        alarm(3);
        pause();
        printf("P3: %ds\n", s);
        while (1) {

            s += 3;
            alarm(3);
            pause();
            printf("P3: %ds\n", s);
            
        }

    }

}
