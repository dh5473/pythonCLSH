#include <sys/mmap.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int fd;
    caddr_t addr;
    struct stat statbuf;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }

    if (stat(argv[1], &statbuf) == -1) {
        perror("stat");
        exit(1);
    }

    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror("open");
        exit(1);
    }

    addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t)0);

    if (addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    close(fd);

    printf("%s", addr);

    // munmap -> addr이 가리키는 영역에 len 크기만큼 할당해 매핑한 메모리 해제
    if (munmap(addr, statbuf.st_size) == -1) {
        perror("munmap");
        exit(1);
    }

    // 매핑이 해제된 메모리에 접근 -> segmentation fault (코어 덤프)
    // 코어 덤프: 비정상적인 종료가 발생하는 경우 커널에서 해당 프로세스와 관련된 메모리 상태를 기록한 파일
    printf("%s", addr);

    return 0;
}