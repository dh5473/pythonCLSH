#include <stdlib.h>
#include <stdio.h>

// 전역 변수, 환경 변수를 가리키는 문자열 포인터 배열의 포인터
extern char **environ;

int main(void) {
    char **env;
    
    env = environ;  // 복사본이 아닌, 동일한 환경 변수 배열을 가리키는 포인터
    while (*env) {  // 마지막 환경 변수는 NULL 포인터
        printf("%s\n", *env);
        env++;
    }

    return 0;
}