#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int fd, pagesize, length;
    caddr_t addr;

    // 메모리의 페이지 크기 정보 검색
    pagesize = sysconf(_SC_PAGESIZE);
    length = 1 * pagesize;

    if ((fd = open("m.dat", O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1) {
        perror("open");
        exit(1);
    }

    // ftruncate -> 파일 기술자를 활용한 파일 크기 확장
    if (ftruncate(fd, (off_t)length) == -1) {
        perror("ftruncate");
        exit(1);
    }

    addr = mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t)0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    close(fd);

    // 매핑한 메모리에 데이터 쓰기
    strcpy(addr, "Ftruncate Test\n");

    return 0;
}