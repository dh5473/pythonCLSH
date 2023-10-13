#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    DIR *dp;
    struct dirent *dent;

    if ((dp = opendir("hanbit")) == NULL) {
        perror("opendir");
        exit(1);
    }

    // telldir -> dir offset의 현재 위치 리턴 (ftell과 유사)
    printf("** Directory content **\n");
    printf("Start Offset: %ld\n", telldir(dp));
    while ((dent = readdir(dp))) {
        printf("Read: %s\n", dent->d_name);
        printf("Cur Offset: %ld\n", telldir(dp));
    }
    
    // rewinder -> dir offset을 시작 위치로 이동 (rewind와 유사)
    printf("** Directory Pointer Rewind **\n");
    rewinddir(dp);
    printf("Cur Offset: %ld\n", telldir(dp));
    
    // seekdir -> dir offset을 loc 위치로 이동 (fseek과 유사)
    printf("** Move Directory Pointer **\n");
    seekdir(dp, 24);
    printf("Cur Offset: %ld\n", telldir(dp));

    dent = readdir(dp);
    printf("Read %s  ", dent->d_name);
    printf("Next Offset %ld\n", telldir(dp));

    closedir(dp);

    return 0;
}