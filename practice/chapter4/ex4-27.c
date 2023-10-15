#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int status;
    pid_t pid;

    if ((pid = fork()) < 0) {  /* fork failed */
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        printf("--> Child process\n");
        sleep(3);
        exit(3);
    }

    printf("--> Parent process\n");

    /* waitpid 리턴 조건
    WCONTINUED: 수행 중인 자식 프로세스 상태값 리턴
    WNOHANG: pid로 지정한 자식 프로세스의 상태값을 즉시 리턴받을 수 없어도 호출한 프로세스의 실행을 블록하지 않고 다른 작업 수행
    WNOWAIT: 상태값을 리턴한 프로세스가 대기 상태에 머물 수 있도록 함
    WUNTRACED: 실행을 중단한 자식 프로세스의 상태값 리턴
    */
    while (waitpid(pid, &status, WNOHANG) == 0) {
        printf("Parent still wait...\n");
        sleep(1);
    }

    printf("Child Exit Status: %d\n", status >> 8);

    return 0;
}