#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fd1[2], fd2[2];
    pid_t pid;
    char buf[257];
    int len, status;

    // pipe 2개 생성
    if (pipe(fd1) == -1) {
        perror("pipe");
        exit(1);
    }

    if (pipe(fd2) == -1) {
        perror("pipe");
        exit(1);
    }

    switch (pid = fork()) {
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:  /* child process */
            close(fd1[1]);
            close(fd2[0]);
            write(1, "Child Process: ", 15);
            len = read(fd1[0], buf, 256);  // fd1[0]으로 읽기
            write(1, buf, len);

            strcpy(buf, "Good\n");
            write(fd2[1], buf, strlen(buf));  // fd2[1]로 쓰기
            break;
        default:
            close(fd1[0]);
            close(fd2[1]);
            buf[0] = '\0';
            write(fd1[1], "Hello\n", 6);  // fd1[1]로 쓰기

            write(1, "Parent Process: ", 15);
            len = read(fd2[0], buf, 256);  // fd2[0]으로 읽기
            write(1, buf, len);
            waitpid(pid, &status, 0);
            break;
    }

    return 0;
}