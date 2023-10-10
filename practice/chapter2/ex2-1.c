#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fd;
    mode_t mode;

    // 접근 권한 644와 동일
    mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    // O_CREAT -> 파일이 없으면 파일 생성
    fd = open("unix.txt", O_CREAT, mode);
    if (fd == -1) {
        perror("Creat");
        exit(1);
    }
    close(fd);

    return 0;
}