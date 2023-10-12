#include <stdlib.h>
#include <stdio.h>

// "문자열" 기반 입출력
int main(void) {
    FILE *rfp, *wfp;
    char buf[BUFSIZ];

    if ((rfp = fopen("unix.txt", "r")) == NULL) {
        perror("fopen: unix.txt");
        exit(1);
    }

    // a mode -> 추가용으로 텍스트 파일 열기
    if ((wfp = fopen("unix.out", "a")) == NULL) {
        perror("fopen: unix.out");
        exit(1);
    }

    // fgets -> stream(파일)에서 n보다 하나 적게 문자열을 읽어 buf에 저장
    while (fgets(buf, BUFSIZ, rfp) != NULL) {  // 한 행씩 buf로 읽기
        fputs(buf, wfp);  // 파일로 출력
    }

    fclose(rfp);
    fclose(wfp);

    return 0;
}