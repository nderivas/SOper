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
    if (argc > 1)
        fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0700); 

    if (fd == -1) {
        fprintf(stderr, "Error al abrir el archivo de salida.\n");
        exit(1);
    }

    ssize_t wr = write(fd, &buff, len);

    if (wr == -1) {
        fprintf(stderr, "Error al escribir a la salida.\n");
        exit(1);
    }

    int error = close(fd);
    if (error == -1) {
        fprintf(stderr, "Error al cerrar el archivo.\n");
        exit(0);
    }

    exit(0);

}
