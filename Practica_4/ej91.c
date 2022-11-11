/*
 * Práctica 4 - SOper
 * Nicolás de Rivas Morillo 843740
 */

#include <stdlib.h>
#include "duerme.h"

int main(int argc, char* argv[]) {

    if (argc < 3) {

        printf("USO: %s X Y\n", argv[0]);
        exit(0);

    }

    int id, X = atoi(argv[1]), Y = atoi(argv[2]);

    switch (id = fork()) {

        case -1:
            printf("fork() error.\n");
            exit(0);

        case 0:
            while (1) {

                duerme(X);
                printf("Soy el hijo\n");

            }
        

        default:
            duerme(Y);
            printf("Paro al hijo durante %ds\n", Y);
            kill(id, SIGTSTP);
            duerme(Y);
            printf("Reinicio el hijo\n");
            kill(id, SIGCONT);
            duerme(Y);
            printf("Mato a mi hijo y acabo\n");
            kill(id, 9);
            exit(0);

    }

}
