#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int a;

    // system -> 새로운 프로그램을 실행하는 간단한 방법 (비효율적임)
    a = system("ps -ef | grep os > os.txt");
    printf("Return Value: %d\n", a);

    return 0;
}