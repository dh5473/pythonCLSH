#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *fp;
    int fd;
    char str[BUFSIZ];

    fd = open("unix.txt", O_RDONLY);  // 저수준 파일 입출력 함수
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // fdopen -> 파일 기술자와 모드값을 받아 파일 포인터 생성
    fp = fdopen(fd, "r");

    fgets(str, BUFSIZ, fp);
    printf("Read: %s\n", str);  // 고수준 파일 읽기 함수

    fclose(fp);

    return 0;
}