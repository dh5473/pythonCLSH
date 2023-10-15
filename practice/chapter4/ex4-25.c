#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    pid_t pid;

    switch (pid = fork()) {
        case -1:  /* fork failed */
            perror("fork");
            exit(1);
            break;
        case 0:  /* child process */
            printf("--> Child Process\n");
            // 자식 프로세스에서 execlp 함수 실행
            if (execlp("ls", "ls", "-a", (char *)NULL) == -1) {
                perror("execlp");
                exit(1);
            }
            exit(0);
            break;
        default:  /* parent process */
            printf("--> Parent Process - My PID: %d\n", (int)getpid());
            break;
    }

    return 0;
}