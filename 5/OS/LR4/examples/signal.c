#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigusr1_handle(int signal) {
    printf("SIGUSR1 %d\n", signal);
}

void sigusr2_handle(int signal) {
    printf("SIGUSR2 %d\n", signal);
}

int main(int argc, char **argv)
{
    signal(SIGUSR1, sigusr1_handle);
    signal(SIGUSR2, sigusr2_handle);
    
    while(1) {
        sleep(2);
    }
    return 0;
}
