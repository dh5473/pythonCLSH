#include <unistd.h>
#include <stdio.h>

int main(void) {
    printf("PID: %d\n", (int)getpid());
    printf("PPID: %d\n", (int)getppid());  // PPID: 부모 프로세스ID

    return 0;
}