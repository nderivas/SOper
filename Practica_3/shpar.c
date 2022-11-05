#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
   
    int n;

    for (int i = 1; i < argc; i++) {
    
        if (strcmp(argv[i], "+") == 0) {
        
            argv[i] = NULL;
            n = i + 1;
        
        }
    
    }
    
    switch (fork()) {
        
        case 0:
            execvp(argv[1], argv + 1);
            break;
        
        case -1:
            printf("Error!");
            break;
    
        default:
            execvp(argv[n], argv + n);
            wait(NULL);

    }

    exit(0);

}
