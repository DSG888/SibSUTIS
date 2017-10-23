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

    if (mknod(FIFO, S_IFIFO | 0666, 0) < 0) {
        printf("Error mknod FIFO\n");
        exit(1);
    }

    if ((fd = open(FIFO, O_RDONLY)) < 0 ) {
        printf("Error open\n");
        exit(1);
    }

    while ((n = read(fd, buff, MAXBUFF)) > 0) {
        if (write(1, buff, n) != n) {
            printf("Error write\n");
            exit(1);
        }
    }

    close(fd);
    if (unlink(FIFO) < 0) {
        printf("Error unlink(FIFO)\n");
        exit(1);
    }

    return 0;
}
