#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {  // pipe 생성
        perror("pipe");
        exit(1);
    }

    switch (pid = fork()) {
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:
            close(fd[1]);
            if (fd[0] != 0) {  // fd[0]에 0번(표준입력) 복사
                dup2(fd[0], 0);  // 자식 프로세스는 입력으로 0번 사용
                close(fd[0]);
            }
            execlp("grep", "grep", "telnet", (char *)NULL);
            exit(1);
            break;
        default:
            close(fd[0]);
            if (fd[1] != 1) {  // fd[1]에 1번(표준출력) 복사
                dup2(fd[1], 1);  // 부모 프로세스는 출력으로 1번 사용
                close(fd[1]);
            }
            execlp("ps", "ps", "-ef", (char *)NULL);
            wait(NULL);
            break;
    }

    return 0;
}