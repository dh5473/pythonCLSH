#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *fp;
    char buf[256];

    // r 모드로 파이프 생성, 자식 프로세스는 date 명령 실행
    fp = popen("date", "r");
    if (fp == NULL) {
        fprintf(stderr, "popen failed\n");
        exit(1);
    }

    if (fgets(buf, sizeof(buf), fp) == NULL) {  // 파이프에서 데이터 읽기
        fprintf(stderr, "No data from pipe!\n");
        exit(1);
    }

    printf("line: %s\n", buf);
    pclose(fp);

    return 0;
}