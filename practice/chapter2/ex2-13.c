#include <stdlib.h>
#include <stdio.h>

int main(void) {
    FILE *rfp;
    char buf[BUFSIZ];
    int n;

    if ((rfp = fopen("unix.txt", "r")) == NULL) {
        perror("fopen: unix.txt");
        exit(1);
    }

    // fread -> 읽어온 항목 수 return, 읽을 항목 없으면 0 return
    while ((n = fread(buf, sizeof(char)*2, 3, rfp)) > 0) {
        buf[6] = '\0';
        printf("n=%d, buf=%s\n", n, buf);
    }

    fclose(rfp);

    return 0;
}