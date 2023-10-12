#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *rfp, *wfp;
    char buf[BUFSIZ];
    int n;

    if ((rfp = fopen("unix.txt", "r")) == NULL) {
        perror("fopen: unix.txt");
        exit(1);
    }

    if ((wfp = fopen("unix.out", "a")) == NULL) {
        perror("fopen: unix.out");
        exit(1);
    }

    // 항목 크기가 char크기 * 2 이고 3개이므로 6바이트씩 읽어서 출력
    while ((n = fread(buf, sizeof(char)*2, 3, rfp)) > 0) {
        fwrite(buf, sizeof(char)*2, n, wfp);  // fwrite -> 오류 발생 시 EOF 리턴
    }

    fclose(rfp);
    fclose(wfp);

    return 0;
}