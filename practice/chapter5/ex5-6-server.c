#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    int fd, n;
    char msg[] = "Hello, FIFO";

    printf("Server =====\n");

    // FIFO 파일 생성
    if (mkfifo("./HAN-FIFO", 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    // FIFO 파일 쓰기 모드로 열기
    if ((fd = open("./HAN-FIFO", O_WRONLY)) == -1) {
        perror("open");
        exit(1);
    }

    printf("To Client: %s\n", msg);

    // FIFO 파일에 문자열 출력
    n = write(fd, msg, strlen(msg)+1);
    if (n == -1) {
        perror("write");
        exit(1);
    }
    close(fd);

    return 0;
}