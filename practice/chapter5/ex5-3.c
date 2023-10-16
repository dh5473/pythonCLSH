#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    pid_t pid;
    char buf[257];
    int len, status;

    if (pipe(fd) == -1) {  // pipe 생성
        perror("pipe");
        exit(1);
    }

    switch (pid = fork()) {  // 자식 프로세스 생성
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:  /* child process */
            close(fd[1]);  // 쓰기용 파일 기술자 닫기
            len = read(fd[0], buf, 256);  // 파이프에서 읽기
            write(1, buf, len);
            close(fd[0]);
            break;
        default:
            close(fd[0]);  // 읽기용 파일 기술자 닫기
            buf[0] = '\0';
            write(fd[1], "Test Message\n", 14);  // 파이프에 텍스트 출력
            close(fd[1]);
            waitpid(pid, &status, 0);
            break;
    }

    return 0;
}