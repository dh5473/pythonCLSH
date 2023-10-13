#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) 
{
    int fd, n ;
    char buf[256];

    fd = open("data.txt", O_RDONLY);
    if (fd == -1) {
        perror("Open data.txt");
        exit(1);
    }
    
    while(1) {
        n = read(fd, buf, 255);  // 데이터 수신
        buf[n] = '\0';

        if (n == -1) {
            perror("Read error");
        } else if (n == 0) continue;  // 읽은 내용 없으면 대기

        write(1, "Recv>> ", 7);
        write(1, buf, n);  // 화면에 출력

        if(n == 1 && buf[0] == 'q') {  // q 입력 시 종료
            write(1, "Terminate\n", 10);
            break;
        }
    }

    close(fd);

    return 0;
}