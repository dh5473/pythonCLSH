#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *fp;
    int n;
    fpos_t cur;
    char buf[BUFSIZ];

    if ((fp = fopen("unix.txt", "r")) == NULL) {
        perror("fopen: unix.txt");
        exit(1);
    }

    // ftell -> 현재 offset 리턴
    cur = ftell(fp);
    printf("Offset cur=%d\n", (int)cur);

    n = fread(buf, sizeof(char), 4, fp);
    buf[n] = '\0';
    printf("-- Read Str=%s\n", buf);

    // fseek -> 성공하면 0, 실패하면 EOF 리턴
    fseek(fp, 1, SEEK_CUR);

    cur = ftell(fp);
    printf("Offset cur=%d\n", (int)cur);

    n = fread(buf, sizeof(char), 6, fp);
    buf[n] = '\0';
    printf("-- Read Str=%s\n", buf);

    // fsetpos -> pos가 가리키는 위치로 파일 offset 이동
    cur = 12;
    fsetpos(fp, &cur);

    // fgetpos -> 파일의 현재 offset을 pos가 가리키는 영역에 저장
    fgetpos(fp, &cur);
    printf("Offset cur=%d\n", (int)cur);

    n = fread(buf, sizeof(char), 13, fp);
    buf[n] = '\0';
    printf("-- Read Str=%s\n", buf);

    fclose(fp);

    return 0;
}