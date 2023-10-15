#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int status;
    pid_t pid;

    switch (pid = fork()) {
        case -1:  /* fork failed */
            perror("fork");
            exit(1);
            break;
        case 0:  /* child process */
            printf("--> Child Process\n");
            exit(2);
            break;
        default:  /* parent process */
            // wait -> 자식 프로세스 PID 리턴, 자식 프로레스가 없는 경우 -1 리턴
            while (wait(&status) != pid)  // 자식 프로세스 종료 기다림
                continue;
            printf("--> Parent process\n");
            printf("Status: %d, %x\n", status, status);
            printf("Child Process Exit Status: %d\n", status >> 8);  // 종료 상태값을 위해 오른쪽으로 8비트 이동
            break;
    }

    return 0;
}