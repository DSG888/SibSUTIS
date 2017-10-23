#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO "fifo.1"
#define MAXBUFF 80

int main(void)
{
    int  fd, n;
    char buff[MAXBUFF];

    if ((fd = open(FIFO, O_WRONLY)) < 0 ) {
        printf("Error open\n");
        exit(1);
    }

    while ((n = read(0, buff, MAXBUFF)) > 0) {
        if (!strncmp(buff, "exit\n", n))
            break;
        if (write(fd, buff, n) != n) {
            printf("Error write\n");
            exit(1);
        }
    }

    close(fd);

    return 0;
}
