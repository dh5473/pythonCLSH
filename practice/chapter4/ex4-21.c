#include <stdlib.h>
#include <stdio.h>

void cleanup1(void) {
    printf("Cleanup 1 is called.\n");
}

void cleanup2(void) {
    printf("Cleanup 2 is called.\n");
}

int main(void) {
    // atexit -> 프로그램 종료 시 수행할 작업 예약
    atexit(cleanup1);
    atexit(cleanup2);  // 먼저 호출됨 (후입선출)

    exit(0);
}