#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *fname;
    char fntmp[BUFSIZ];
    char template[32];

    // tmpnam -> 임시 파일명을 시스템이 알아서 생성
    fname = tmpnam(NULL);
    printf("1. TMP File Name(tmpnam): %s\n", fname);

    tmpnam(fntmp);
    printf("2. TMP File Name(tmpnam): %s\n", fntmp);

    // tempnam -> 임시 파일명에 사용할 디렉토리와 접두어(5글자까지) 지정
    fname = tempnam("/tmp", "hanbit");
    printf("3. TMP File Name(tempnam): %s\n", fname);

    strcpy(template, "/tmp/hanbitXXXXXX");  // 템플릿은 'X' 6개로 마쳐야 함
    // mktemp -> 임시 파일의 템플릿을 받아 임시 파일명 생성
    // fname = mktemp(template);  // 오래된 방식이라 에러 발생
    // printf("4. TMP File Name(mktemp): %s\n", fname);

    return 0;
}