#include <stdio.h>

// 명령행 인자
// argc(argument count): 커맨드 라인에서 전달된 인수의 개수
// argv(argument vector): 문자열 포인터 배열, 커맨드 라인에서 전달된 인수에 대한 문자열
int main(int argc, char *argv[]) {
    int n;

    printf("argc = %d\n", argc);
    for (n = 0; n < argc; n++)
        printf("argv[%d] = %s\n", n, argv[n]);
    
    return 0;
}