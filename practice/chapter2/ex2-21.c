#include <stdio.h>

int main(void) {
    FILE *fp;

    // tmpfile -> w+ 모드로 열린 파일 포인터 리턴
    fp = tmpfile();
    
    // 임시 파일에 출력
    fputs("unix system", fp);

    fclose(fp);

    return 0;
}