#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    char *argv[3];

    printf("--> Before exec function\n");

    argv[0] = "ls";  // 첫 인자는 관례적으로 실행파일명 지정
    argv[1] = "-a";
    argv[2] = NULL;  // 인자의 끝을 표시하는 NULL 포인터

    if (execv("/usr/bin/ls", argv) == -1) {  // 경로로 명령 지정
        perror("execv");
        exit(1);
    }

    printf("--> After exec function\n");  // 실행 안됨

    return 0;
}