#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fd;

    fd = open("tmp.bbb", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Create tmp.bbb");
        exit(1);
    }

    // 표준 출력 1로 지정하여 복사
    dup2(fd, 1);

    // 표준 출력을 출력한 내용이 파일로 저장됨
    printf("DUP2: Standard Output Redirection\n");
    close(fd);

    return 0;
}