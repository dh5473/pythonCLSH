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

    // 명령행 인자로 매핑할 파일명 입력
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }

    // 파일 메타데이터 가져오기
    if (stat(argv[1], &statbuf) == -1) {
        perror("stat");
        exit(1);
    }

    // 읽고 쓰기 가능한 모드로 파일 열기
    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror("open");
        exit(1);
    }

    /* prot: 보호 모드
    PROT_READ: 매핑된 파일 읽기용
    PROT_WRITE: 매핑된 파일에 쓰기 허용
    */

    /* flags
    MAP_SHARED: 데이터의 변경 내용 공유
    MAP_PRIVATE: 데이터의 변경 내용 공유 안함
    */

    // mmap -> fd가 가리키는 파일에서 offset으로부터 len 크기만큼 데이터를 읽어 addr이 가리키는 메모리 공간에 매핑
    addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t)0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    close(fd);
    
    // 매핑한 파일 내용 출력
    printf("%s", addr);

    return 0;
}