#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    int id = fork();
    int pid = getpid();
    int ppid = getppid();

    switch (id) {

        case 0:
            printf("Soy el hijo - pid: %d - ppid: %d\n", pid, ppid);
            break;

        case -1:
            printf("Error al crear el hijo");
            break;
        
        default:
            printf("\nSoy el padre - pid: %d - ppid: %d\n", pid, ppid);
            wait(0);

    }

    exit(0);

}

/* 
 * execl(directorio, arg0, ..., argn)
 * execv(directorio, vargs)
 * execlp(archivo, arg0, ..., argn)
 * execvp(archivo, vargs)
 */
