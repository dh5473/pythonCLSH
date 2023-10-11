#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int fd, fd1;

    fd = open("tmp.aaa", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Create tmp.aaa");
        exit(1);
    }

    // 표준 출력 1 닫기
    close(1);

    // fd 복사 시 가장 작은 값인 1로 복사
    fd1 = dup(fd);

    // 표준 출력을 출력한 내용이 파일로 저장됨
    printf("DUP FD=%d\n", fd1);
    printf("Standard Output Redirection\n");
    close(fd);

    return 0;
}