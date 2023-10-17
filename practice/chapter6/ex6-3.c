#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    key_t key;
    int msgid;

    key = ftok("keyfile", 1);  // 키 값 생성
    msgid = msgget(key, IPC_CREAT|0644);  // 메시지 큐 생성
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Before IPC_RMID\n");
    system("ipcs -q");
    msgctl(msgid, IPC_RMID, (struct msqid_ds *)NULL);  // 메시지 큐 삭제
    printf("After IPC_RMID\n");
    system("ipcs -q");

    return 0;
}