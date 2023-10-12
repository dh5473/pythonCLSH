#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *fp;
    int fd, n;
    char str[BUFSIZ];

    fp = fopen("unix.txt", "r");  // 고수준 파일 입출력 함수
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }

    // fileno -> 파일 포인터를 인자로 받아 파일 기술자 리턴
    fd = fileno(fp);
    printf("fd: %d\n", fd);

    n = read(fd, str, BUFSIZ);  // 저수준 파일 읽기 함수
    str[n] = '\0';
    printf("Read: %s\n", str);

    close(fd);

    return 0;   
}