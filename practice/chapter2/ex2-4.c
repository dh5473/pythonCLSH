#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int rfd, wfd, n;  // 2개의 파일 기술자 선언
    char buf[10];

    // 파일을 읽기 전용으로 열기
    rfd = open("unix.txt", O_RDONLY);
    if (rfd == -1) {
        perror("Open unix.txt");
        exit(1);
    }

    // 파일이 있는 경우 -> 쓰기 권한 확인 후 O_TRUNC로 내용 지우고 열기
    // 파일이 없는 경우 -> O_CREAT로 생성 후 열기
    wfd = open("unix.bak", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (wfd == -1) {
        perror("Open unix.bak");
        exit(1);
    }

    // 6바이트씩 읽고 buf에 저장
    while ((n = read(rfd, buf, 6)) > 0)  // 파일에서 읽어 buf에 저장 (읽어온 바이트 개수 반환)
        if (write(wfd, buf, n) != n)  // buf가 가리키는 메모리로부터 파일에 기록
            perror("Write");
    
    if (n == -1)
        perror("Read");
    
    close(rfd);
    close(wfd);

    return 0;
}