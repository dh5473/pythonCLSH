#include <stdlib.h>
#include <stdio.h>

int main(void) {
    char *val;

    val = getenv("SHELL");
    if (val == NULL)
        printf("SHELL not defined\n");
    else
        printf("1. SHELL = %s\n", val);
    
    // 설정하려는 환경변수를 "환경변수=값" 형태로 지정
    putenv("SHELL=/usr/bin/csh");

    val = getenv("SHELL");
    printf("2. SHELL = %s\n", val);
    
    return 0;
}