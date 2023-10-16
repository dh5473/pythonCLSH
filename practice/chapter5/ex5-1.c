#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *fp;
    int a;

    // w 모드로 파이프 생성, 자식 프로세스는 wc -l 명령 실행
    fp = popen("wc -l", "w");
    if (fp == NULL) {
        fprintf(stderr, "popen failed\n");
        exit(1);
    }

    for (a = 0; a < 100; a++) {
        fprintf(fp, "test line\n");  // 자식 프로세스로 출력
    }

    pclose(fp);

    return 0;
}