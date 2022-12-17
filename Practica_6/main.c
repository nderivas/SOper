#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define MAX 100

int fdEscritura;

void lanzar() {

    int pelota = 0;
    int error = write(fdEscritura, &pelota, sizeof(int));
    if (error != 0)
        exit(1);

}

void reiniciar() {



}

int main() {

    int pipeunodos[2];
    int pipedosuno[2];
    pipe(pipeunodos);
    pipe(pipedosuno);

    struct sigaction actionLanzar, actionReiniciar, basura;
    actionLanzar.sa_handler = lanzar;
    actionReiniciar.sa_handler = reiniciar;

    sigaction(SIGUSR1, &actionLanzar, &basura);
    sigaction(SIGUSR2, &actionReiniciar, &basura);

    if (fork() == 0) { // Hijo 1

        int pelota = 0;
        pid_t pid = getpid();
        fdEscritura = pipeunodos[1];

        while (1) {           

            ssize_t error = write(pipeunodos[1], &pelota, sizeof(int));
            if (error == -1)
                exit(1);

            if (pelota >= MAX)
                exit(0);

            error = read(pipedosuno[0], &pelota, sizeof(int));
            if (error == -1)
                exit(1);
            
            printf("%d recibe %d\n", pid, pelota);

            pelota++;
            sleep(1);

        }

    } else {

        int pelota;
        pid_t pid = getpid();
        fdEscritura = pipedosuno[1];

        while(1) {

            ssize_t error = read(pipeunodos[0], &pelota, sizeof(int));
            if (error == -1)
                exit(1);

            printf("%d recibe %d\n", pid, pelota);

            pelota++;

            sleep(1);

            error = write(pipedosuno[1], &pelota, sizeof(int));
            if (error == -1)
                exit(1);
       
            if (pelota >= MAX) {

                wait(NULL);
                exit(0);

            }

        }
    }

    return 0;

}