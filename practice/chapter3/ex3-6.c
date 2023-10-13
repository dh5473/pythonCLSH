#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    DIR *dp;
    struct dirent *dent;
    /*
    typedef struct dirent {
        ino_t           d_ino;
        off_t           d_off;
        unsigned short  d_reclen;
        char            d_name[1];
    } dirent_t;
    */

    // opendir -> 성공 시 DIR 포인터 리턴, 실패 시 NULL 리턴
    if ((dp = opendir("hanbit")) == NULL) {
        perror("opendir: hanbit");
        exit(1);
    }

    while ((dent = readdir(dp))) {
        printf("Name: %s    ", dent->d_name);
        printf("Inode: %d\n", (int)dent->d_ino);
    }

    closedir(dp);

    return 0;
}