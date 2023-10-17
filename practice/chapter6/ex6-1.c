#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

struct mymsgbuf {
    long mtype;
    char mtext[80];  // 메시지 버퍼 정의
};

int main(void) {
    key_t key;
    int msgid;
    struct mymsgbuf mesg;

    key = ftok("keyfile", 1);  // 키 값 생성
    msgid = msgget(key, IPC_CREAT|0644);  // 메시지 큐 생성
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    mesg.mtype = 1;
    strcpy(mesg.mtext, "Message Q Test\n");  // 보낼 메시지

    if (msgsnd(msgid, (void *)&mesg, 80, IPC_NOWAIT) == -1) {  // 메시지 전송
        perror("msgsnd");
        exit(1);
    }

    return 0;
}