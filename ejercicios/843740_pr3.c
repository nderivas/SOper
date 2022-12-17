/*
 * Ejercicio voluntario 3 - SOper
 * Autor: Nicolás de Rivas Morillo (843740)
 * Fecha: 01-12-2022
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define buffsize 1024

// Lee de fd y lo guarda en buff hasta que encuentra el carácter c
int migets(int fd, char buff[], char c) {

    char aux;
    int i = 0;
    
    do {

        ssize_t bytesLeidos = read(fd, &aux, 1); // Lee byte a byte
        
        if (bytesLeidos == -1) { // Caso error
            
            fprintf(stderr, "Error en la lectura.\n");
            exit(1);
        
        } else if (bytesLeidos == 0) { // Caso EOF
    
            buff[i] = '\0';
            return 0; // Devuelve 0 -> falso
    
        } if (aux != c) { // Añadir al buffer
            
            buff[i] = aux;
            i++;
        
        }

    } while (aux != c);

    buff[i] = '\0';
    return 1; // Devuelve 1 -> verdadero

}

// Separa un string por los espacios en un vector de strings
void vectorizador(char* v[], char s[]) {

    int i = 1;
    
    v[0] = strtok(s, " ");
    while ((v[i] = strtok(NULL, " ")) != NULL)
        i++;

}

int main(int argc, char* argv[]) {

    // Variables
    char buno[buffsize];
    char bdos[buffsize];
    char* argvectUno[buffsize];
    char* argvectDos[buffsize];
    int pipefds[2];

    if (argc < 2) {
        fprintf(stderr, "Falta nombre del archivo.\n");
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY); // Abrir el archivo
    if (fd == -1) {
        fprintf(stderr, "Error al abrir el archivo.\n");
        exit(1);
    }
    
    // Asumo la sintáxis estricta del archivo
    while(migets(fd, buno, '|')) { // Mientras lea del archivo + cogemos comando 1
        
        migets(fd, bdos, '\n'); // Cogemos el segundo comando

        vectorizador(argvectUno, buno); // Creamos los vectores
        vectorizador(argvectDos, bdos);

        pipe(pipefds); // Creamos el pipe

        if (fork() == 0) { // Hijo 1: Tiene que escribir en pipefds[1]

            close(pipefds[0]); // Cierro extremo no usado
            close(1); // Cierro salida estándar
            // Duplico el extremo necesario del pipe en la salida estándar
            dup(pipefds[1]);
            close(pipefds[1]); // Cierro el pipe duplicado
            execvp(argvectUno[0], argvectUno); // Ejecuto el comando 1

        } else if (fork() == 0) { // Hijo 2: Tiene que leer en pipefds[0]

            close(pipefds[1]);
            close(0); // Cierro entrada estándar
            dup(pipefds[0]);
            close(pipefds[0]);
            execvp(argvectDos[0], argvectDos);

        } else {

            close(pipefds[0]);
            close(pipefds[1]);
            wait(NULL);
            wait(NULL);

        }

    }

    close(fd);

    exit(0);

}