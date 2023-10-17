#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/* compile
gcc zmq_client.c -lzmq -o cli
*/

int main(void) {
    printf("Connecting to hello world server...\n");
    void *context = zmq_ctx_new();  // 새로운 zeroMQ 컨텍스트 생성 (스레드 safe)
    void *requester = zmq_socket(context, ZMQ_REQ);  // context로부터 socket 생성
    zmq_connect(requester, "ipc://./data.zmq");  // 대기중(bind)인 위치로 연결, 0이면 성공 -1이면 실패

    int request_nbr;
    for (request_nbr = 0; request_nbr != 10; request_nbr++) {
        char buffer[10];
        printf("Sending Hello %d...\n", request_nbr);
        zmq_send(requester, "Hello", 5, 0);
        zmq_recv(requester, buffer, 10, 0);
        printf("Received World %d\n", request_nbr);
    }
    zmq_close(requester);
    zmq_ctx_destroy(context);
    
    return 0;
}