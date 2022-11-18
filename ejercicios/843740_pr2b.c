#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void f(){
	signal(SIGUSR1,f);
	fprintf(stderr,"-");
}

int main(){

    int pidUno, pidDos;

    sigset_t miMasc, oldMasc;
    sigfillset(&miMasc);

    sigprocmask(SIG_BLOCK, &miMasc, &oldMasc);

	signal(SIGUSR1,f);

	if((pidUno = fork()) == 0) {
		
        pidUno = getppid();
		
        while(1) {
            fprintf(stderr,"h1");
			kill(pidUno,SIGUSR1);
		    sigsuspend(&oldMasc);
        }

	} else if ((pidDos = fork()) == 0) {

        sigsuspend(NULL);

        while(1) {
            fprintf(stderr, "h2");
            kill(pidUno, SIGUSR1);
            sigsuspend(&oldMasc);
        }

    } else {

		sigsuspend(NULL);
		
        while(1) {
            fprintf(stderr,"p");
			kill(pidDos,SIGUSR1);
		    sigsuspend(&oldMasc);
        }
	
    }
}
