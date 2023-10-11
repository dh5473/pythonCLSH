#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fd, n;
    off_t start, cur;  // offset
    char buf[256];

    fd = open("unix.txt", O_RDONLY);
    if (fd == -1) {
        perror("Open unix.txt");
        exit(1);
    }

    start = lseek(fd, 0, SEEK_CUR);  // 현재 위치 기준에서 0번째 위치로 이동
    n = read(fd, buf, 255);
    buf[n] = '\0';  // 문자열 끝 표시
    printf("Offset start=%d, Read Str=%s, n=%d\n", (int)start, buf, n);
    
    cur = lseek(fd, 0, SEEK_CUR);
    printf("Offset cur=%d\n", (int)cur);

    start = lseek(fd, 5, SEEK_SET);  // 파일 시작 위치 기준에서 5번째 위치로 이동
    n = read(fd, buf, 255);
    buf[n] = '\0';
    printf("Offset start=%d, Read Str=%s", (int)start, buf);

    close(fd);

    return 0;
}

// lseek(fd, 5, SEEK_SET); -> 파일의 시작 기준에서 5번째 위치로 이동
// lseek(fd, 0, SEEK_END); -> 파일의 끝 기준에서 0번째 위치로 이동 (끝으로 이동)