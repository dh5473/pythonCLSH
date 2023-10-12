#include <stdlib.h>
#include <stdio.h>

// "문자" 기반 입출력
int main(void) {
    FILE *rfp, *wfp;  // 파일 구조체 포인터
    int c;

    // 고수준 파일 열기
    if ((rfp = fopen("unix.txt", "r")) == NULL) {
        perror("fopen: unix.txt");
        exit(1);
    }

    if ((wfp = fopen("unix.out", "w")) == NULL) {
        perror("fopen: unix.out");
        exit(1);
    }

    // fgetc -> 문자 한 개를 unsigned char 형태로 읽기
    while ((c = fgetc(rfp)) != EOF) {  // EOF를 만날 떄까지 한 문자씩 읽기
        fputc(c, wfp);  // 파일로 출력
    }

    // 고수준 파일 닫기
    fclose(rfp);
    fclose(wfp);

    return 0;
}