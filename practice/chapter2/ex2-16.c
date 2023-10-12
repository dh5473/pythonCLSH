#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *rfp, *wfp;
    int id, s1, s2, s3, s4, n;

    if ((rfp = fopen("unix.dat", "r")) == NULL) {
        perror("fopen: unix.dat");
        exit(1);
    }

    if ((wfp = fopen("unix.scr", "w")) == NULL) {
        perror("fopen: unix.scr");
        exit(1);
    }

    // fprintf -> 지정한 파일로 형식 지정 방법을 사용하여 출력
    fprintf(wfp, "학번    평균\n");
    while ((n = fscanf(rfp, "%d %d %d %d %d", &id, &s1, &s2, &s3, &s4)) != EOF)
        fprintf(wfp, "%d: %d\n", id, (s1 + s2 + s3 + s4)/4);
    
    fclose(rfp);
    fclose(wfp);

    return 0;
}