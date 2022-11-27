/*
 * Práctica 5 - SOper (Universidad de Zaragoza)
 * Nicolás de Rivas Morillo (843740)
 * Noviembre de 2022
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#define buffsize 1024

int main(int argc, char* argv[]) {

    char buff[buffsize];
    ssize_t len = read(0, &buff, buffsize);

    if (len == -1) {
        fprintf(stderr, "Error al leer la entrada.\n");
        exit(1);
    }

    int fd = 1;
    if (argc > 1) {
        fd = open(argv[1], O_WRONLY, 0700);
        if (fd == -1)
            fd = creat(argv[1], 0700); // equiv a O_WRONLY | O_CREAT | O_TRUNC
        else {
            int seekerr = lseek(fd, 0, SEEK_END); // no O_APPEND en open?
            if (seekerr == -1) {
                fprintf(stderr, "Error al ir al final del archivo.\n");
                exit(1);

            }
        }
    }

    if (fd == -1) {
        fprintf(stderr, "Error al abrir el archivo de salida.\n");
        exit(1);
    }

    ssize_t wr = write(fd, &buff, len);

    if (wr == -1) {
        fprintf(stderr, "Error al escribir a la salida.\n");
        exit(1);
    }

    exit(0);

}
