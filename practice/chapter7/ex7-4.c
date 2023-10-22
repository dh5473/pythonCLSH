#include <sys/mman.h>
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

    printf("%s", addr);  // 매핑된 내용 출력

    printf("----------\n");
    addr[0] = 'D';  // 매핑된 내용 수정
    printf("%s", addr);

    // msync -> 매핑된 메모리의 내용과 백업 내용 일치하도록 동기화
    /* flags
    MS_ASYNC: 비동기 쓰기 작업
    MS_SYNC: 쓰기 작업 완료시까지 msync 리턴 안함
    MS_INVALIDATE: 메모리에 복사되어 있는 내용 무효화
    */
    msync(addr, statbuf.st_size, MS_SYNC);  // 수정된 내용 동기화

    return 0;
}