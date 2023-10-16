#include <stdio.h>

/* 명령행 인자
argc, argv: main 함수에서 받은 것 그대로 지정
optstring: 사용할 수 있는 옵션 문자
optarg: 옵션의 인자 저장
optind: 다음에 처리할 argv의 주소
optopt: 오류를 발생시킨 문자
opterr: 오류 메시지를 출력하지 않으려면 0으로 지정
*/

int main(int argc, char *argv[]) {
    int n;
    extern char *optarg;
    extern int optind;

    printf("Current Optind: %d\n", optind);
    while ((n = getopt(argc, argv, "abc: ")) != -1) {
        switch (n) {
            case 'a':
                printf("Option: a\n");
                break;
            case 'b':
                printf("Option: b\n");
                break;
            case 'c':
                printf("Option: c, Argument=%s\n", optarg);
                break;
        }
        printf("Next Optind: %d\n", optind);
    }

    return 0;
}