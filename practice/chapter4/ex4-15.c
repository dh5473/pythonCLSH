#include <stdio.h>

// 명령행 인자, 환경 변수
int main(int argc, char **argv, char **envp) {
    char **env;

    env = envp;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}