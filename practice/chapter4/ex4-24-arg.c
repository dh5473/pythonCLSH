#include <stdio.h>

int main(int argc, char **argv, char **envp) {
    int n;
    char **env;

    printf("\n--> In ex4_24_arg.c Main\n");
    printf("argc %d\n", argc);
    for (n = 0; n < argc; n++)
        printf("argv[%d] %s\n", n, argv[n]);  // 인자값 출력

    env = envp;
    while (*env) {
        printf("%s\n", *env);  // 환경변수 출력
        env++;
    }

    return 0;
}