#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fd, n;
    char inmsg[80];

    // 서버 측에서 생성한 FIFO 파일 열기
    if ((fd = open("./HAN-FIFO", O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }

    printf("Client =====\n");
    write(1, "From Server: ", 13);

    // 서버가 보낸 데이터 읽기
    while ((n = read(fd, inmsg, 80)) > 0)
        write(1, inmsg, n);
    
    if (n == -1) {
        perror("read");
        exit(1);
    }

    write(1, "\n", 1);
    close(fd);

    return 0;
}