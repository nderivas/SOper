
/*
 * Práctica 3 - SOper
 * Nicolás de Rivas Morillo (843740)
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    char *args1[argc];
    char *args2[argc];

    int turno = 1, j = 0;

    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "+") == 0) {

            turno = 2;
            args1[i - 1] = NULL;

        } else if (turno == 1) {

            args1[i - 1] = argv[i];

        } else {

            args2[j] = argv[i];
            j++;

        }

    }

    args2[j] = NULL;

    switch (fork()) {

        case 0:
            execvp(args1[0], args1);
            break;

        case -1:
            fprintf("El fork ha fallado", error);
            break;

        default:
            execvp(args2[0], args2);
            wait(0);

    }

    exit(0);

}
