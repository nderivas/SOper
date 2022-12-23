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

// Modo 1: Pantalla
// Modo 2: Fichero
// Modo 3: Los dos

int salidaNormal = 1;
int salidaError = 1;

struct descriptores {

    int fdLectura, fdEscritura, salida;
    int* modo;

};

// Actua como un interruptor para la salida normal
void cambiarSalidaNormal() {

    salidaNormal = (salidaNormal % 3) + 1;

}

// Actua como un interruptor para la salida de error
void cambiarSalidaError() {

    salidaError = (salidaError % 3) + 1;

}

// Función del hilo
void funcionHilo(void* fds) {

    char buffer[SIZE];

    // Leemos hasta que no haya nada más en el pipe
    int leido = read(((struct descriptores*)fds)->fdLectura, buffer, SIZE);
    while (leido != 0) {

        // Escribimos en diferentes salidas dependiendo de la variable global
        if ((*((struct descriptores*)fds)->modo % 2) == 1)
            write(((struct descriptores*)fds)->salida, buffer, leido);
        if (*((struct descriptores*)fds)->modo > 1)
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

    struct sigaction accionNormal, accionError;
    accionNormal.sa_handler = cambiarSalidaNormal;
    accionError.sa_handler = cambiarSalidaError;

    sigaction(SIGUSR1, &accionNormal, NULL);
    sigaction(SIGUSR2, &accionError, NULL);

    // Cerramos extremos de escritura
    close(pipeNormal[1]);
    close(pipeError[1]);

    // Abrimos ficheros
    int fdNormal = creat(argv[1], 0700);
    int fdError = creat(argv[2], 0700);
    if (fdNormal == -1 || fdError == -1)
        exit(1);

    // Lanzamos un hilo que se encarga de la salida de error
    // y otro de la salida normal
    pthread_t hiloNormal, hiloError;
    struct descriptores fdsError = {pipeError[0], fdError, 2, &salidaError};
    struct descriptores fdsNormal = {pipeNormal[0], fdNormal, 1, &salidaNormal};
    pthread_create(&hiloError, NULL, funcionHilo, &fdsError);
    pthread_create(&hiloNormal, NULL, funcionHilo, &fdsNormal);

    // Join de hilos
    pthread_join(hiloNormal, NULL);
    pthread_join(hiloError, NULL);

    // Cerramos
    close(pipeNormal[0]);
    close(pipeError[0]);
    close(fdError);
    close(fdNormal);

    // Esperamos al hijo
    wait(NULL);

    exit(0);

}
