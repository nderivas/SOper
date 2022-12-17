#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    for (int i = 0; i < atoi(argv[1]); i++) {

        sleep(1);

        //char buff[10];
        //sprintf(buff, "%d - nor\n", i);

        if (i % 2 == 0)
            fprintf(stdout, "%d - nor\n", i);
            //write(1, buff, 9);
        else
            fprintf(stderr, "%d - err\n", i);

    }

    return 0;

}