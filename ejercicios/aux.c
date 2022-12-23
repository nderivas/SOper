#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    for (int i = 0; i < atoi(argv[1]); i++) {

        sleep(1);

        char buff[10];
        sprintf(buff, "%d - nor\n", i);

        char b[10];
        sprintf(b, "%d - err\n", i);

        if (i % 2 == 0)
            write(1, buff, 9);
        else
            write(2, b, 9);

    }

    return 0;

}
