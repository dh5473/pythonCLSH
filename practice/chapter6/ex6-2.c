#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

struct mymsgbuf {
    long mtype;
    char mtext[80];  // 메시지 버퍼 정의
};

int main(void) {
    struct mymsgbuf inmsg;
    key_t key;
    int msgid, len;

    key = ftok("keyfile", 1);  // 송신 측과 같은 키 값 생성
    if ((msgid = msgget(key, 0)) < 0) {
        perror("msgget");
        exit(1);
    }

    len = msgrcv(msgid, &inmsg, 80, 0, 0);  // 메시지 수신
    printf("Received Msg = %s, Len = %d\n", inmsg.mtext, len);

    return 0;
}