#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SIZE 1024

int salidaNormal = 1;
int salidaError = 1;

struct descriptores {

    int fdLectura, fdEscritura;

};

// Actua como un interruptor para la salida normal
void cambiarSalidaNormal() {

    signal(SIGUSR1, cambiarSalidaNormal);
    if (salidaNormal)
        salidaNormal = 0;
    else
        salidaNormal = 1;

}

// Actua como un interruptor para la salida de error
void cambiarSalidaError() {

    signal(SIGUSR2, cambiarSalidaError);
    if (salidaError)
        salidaError = 0;
    else
        salidaError = 1;

}

// Función del hilo
void funcionHilo(void* fds) {

    char buffer[SIZE];

    // Leemos hasta que no haya nada más en el pipe
    int leido = read(((struct descriptores*)fds)->fdLectura, buffer, SIZE);
    while (leido != 0) {

        // Escribimos en diferentes salidas dependiendo de la variable global
        if (salidaError)
            fprintf(stderr, "%s", buffer);
        else
            write(((struct descriptores*)fds)->fdEscritura, buffer, leido);
        leido = read(((struct descriptores*)fds)->fdLectura, buffer, SIZE);

    }

}

// Función principal
int main(int argc, char* argv[]) {

    // Comprobación de error
    if (argc < 4) {

        fprintf(stderr, "Faltan argumentos.\n");
        exit(1);

    }

    // Inicialización de pipes
    int pipeNormal[2];
    int pipeError[2];
    pipe(pipeNormal);
    pipe(pipeError);

    if (fork() == 0) { // Hijo va a ejecutar el comando

        close(pipeNormal[0]); // Cierro extremo no usado
        close(1); // Cierro salida estándar
        dup(pipeNormal[1]); // Duplico la pipe en 1
        close(pipeNormal[1]); // Cierro el pipe duplicado
        
        close(pipeError[0]); // Cierro extremo no usado
        close(2); // Cierro salida error
        dup(pipeError[1]); // duplico la pipe en 2
        close(pipeError[1]); // Cierro el pipe duplicado
        
        execvp(argv[3], argv + 3);
        exit(1);

    }
    
    // Padre va a controlar la salida
    printf("PID del padre: %d\n", getpid()); // pid monitor para poder mandar las señales
    char buffer[SIZE];
    signal(SIGUSR1, cambiarSalidaNormal);
    signal(SIGUSR2, cambiarSalidaError);

    // Cerramos extremos de escritura
    close(pipeNormal[1]);
    close(pipeError[1]);

    // Abrimos ficheros
    int fdNormal = creat(argv[1], 0700);
    int fdError = creat(argv[2], 0700);
    if (fdNormal == -1 || fdError == -1)
        exit(1);

    // Lanzamos un hilo que se encarga de la salida de error
    pthread_t hilo;
    struct descriptores fds = {pipeError[0], fdError};
    pthread_create(&hilo, NULL, funcionHilo, &fds);

    // Leemos hasta que no haya nada más en el pipe
    // Este hilo se encarga de la salida estándar
    int leido = read(pipeNormal[0], buffer, SIZE);
    while (leido != 0) {

        // Escribimos en diferentes salidas dependiendo de la variable global
        if (salidaNormal)
            fprintf(stdout, "%s", buffer);
        else
            write(fdNormal, buffer, leido);
        leido = read(pipeNormal[0], buffer, SIZE);

    }

    // Join de hilos
    pthread_join(hilo, NULL);

    // Cerramos
    close(pipeNormal[0]);
    close(pipeError[0]);
    close(fdError);
    close(fdNormal);

    // Esperamos al hijo
    wait(NULL);

    exit(0);

}