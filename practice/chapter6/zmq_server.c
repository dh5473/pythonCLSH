#include <zmq.h>  // apt install libzmq3-dev
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

/* compile
gcc zmq_server.c -lzmq -o svr
*/

int main(void) {
    // socket to talk to clients
    void *context = zmq_ctx_new();  // 새로운 zeroMQ 컨텍스트 생성 (스레드 safe)
    void *responder = zmq_socket(context, ZMQ_REP);  // context로부터 socket 생성
    /* socket type
    ZMQ_REQ/ZMQ_REP
    ZMQ_PUB/ZMQ_SUB
    ZMQ_PULL/ZMQ_PUSH
    */
    int rc = zmq_bind(responder, "ipc://./data.zmq");  // 들어오는 socket 연결 수립
    /* endpoint: 연결 문자열
    ipc://{파일 경로}: IPC
    inproc://{name}: 프로세스 내
    Tcp://{IP}:
    */
    assert(rc == 0);

    while (1) {
        char buffer[10];
        zmq_recv(responder, buffer, 10, 0);  // 읽은 bytes 수 반환, 실패시 -1
        printf("Received Hello\n");
        sleep(1);
        zmq_send(responder, "World", 5, 0);  // 전송한 bytes 수 반환, 실패시 -1
    }
    
    return 0;
}