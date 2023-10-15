#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    char *argv[3];
    char *envp[2];

    printf("--> Before exec function\n");

    argv[0] = "arg.out";  // 실행파일명 지정
    argv[1] = "100";
    argv[2] = NULL;  // 인자의 끝을 표시하는 NULL 포인터

    envp[0] = "MYENV=hanbit";  // 환경변수 설정
    envp[1] = NULL;

    if (execve("./arg.out", argv, envp) == -1) {  // arg.c 컴파일하여 생성해 두어야 함
        perror("execve");
        exit(1);
    }

    printf("After exec function\n");  // 실행 안됨

    return 0;
}