#include <stdlib.h>
#include <stdio.h>

int main(void) {
    char *val;

    val = getenv("SHELL");
    if (val == NULL)
        printf("SHELL not defined\n");
    else
        printf("1. SHELL = %s\n", val);

    // int setenv(const char *envname, const char *envval, int overwrite);
    // overwrite: 0이 아니면 덮어쓰고, 0이면 덮어쓰지 않음
    setenv("SHELL", "/usr/bin/csh", 0);  // 덮어쓰기 X
    val = getenv("SHELL");
    printf("2. SHELL = %s\n", val);

    setenv("SHELL", "/usr/bin/csh", 1); // 덮어쓰기 O
    val = getenv("SHELL");
    printf("3. SHELL = %s\n", val);

    return 0;
}