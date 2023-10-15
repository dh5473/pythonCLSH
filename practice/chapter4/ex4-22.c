#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    printf("--> Before exec function\n");

    if (execlp("ls", "ls", "-a", (char *)NULL) == -1) {
        perror("execlp");
        exit(1);
    }

    printf("--> After exec function\n");  // 실행 안됨 (메모리 이미지가 'ls' 명령으로 바뀌어서)
    
    return 0;
}