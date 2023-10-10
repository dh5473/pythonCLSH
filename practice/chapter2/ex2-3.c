#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fd;

    close(0);

    // 읽기, 쓰기가 가능하도록 파일 열기
    fd = open("unix.txt", O_RDWR);
    if (fd == -1) {
        perror("Excl");
        exit(1);
    }

    // 11행에서 0번을 닫음 -> 새로 파일 생성 시 0번 할당
    printf("unix.txt: fd = %d\n", fd);
    close(fd);

    return 0;
}