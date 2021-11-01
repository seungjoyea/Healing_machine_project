#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string.h>

//메세지 structure 선언
typedef struct structMyMsg {
    long int messageType;
    char bulk_message[1000];
} structMyMsg;

//공유메모리 읽을 변수 선언
typedef struct data {
    char bank[1000];
    } data;

int main(void)
{
    data command;               //공유메모리에서 데이터를 읽을 변수
    structMyMsg messageRxData; //message 구조체 생성
    int returnValue = 0; //msgrcv 성공,실패여부 확인
    char *shmemAddr; //공유메모리 주소 저장
    int count = 1;

    int msgQueue = msgget((key_t)9999, IPC_CREAT|0666);  //우체통 생성
    if(msgQueue == -1){                               //우체통 생성 확인
        printf("Cannot get msgQueueID\n"); 
        return -1;
    }

    int shmID = shmget((key_t)1234, 1024, IPC_CREAT|0666);  //공유메모리 할당
    if(shmID == -1) { //공유메모리 할당 에러
        printf("shmget Error\n");
        return 1;
    }

    shmemAddr = shmat(shmID, (void*)NULL, 0); //공유메모리 접근권한부여
    if( ((int)shmemAddr)==-1) {               //공유메모리 접근권한부여 g확인
        printf("Shmat Error\n");
        return -2;
    }
    
    while(1) {
        returnValue = msgrcv(msgQueue, &messageRxData, sizeof(messageRxData.bulk_message),0,0); //메시지 왔나 확인, 안왔으면 올때까지 wait
        printf("%d message comes : %s\n", count, messageRxData.bulk_message); //message Queue의 값을 읽어서 출력
        count++;

        command = *((data*)shmemAddr);  //공유메모리의 값을 읽음
        printf("받은 메시지 : %s\n", command.bank ); //공유메모리 값 출력
        //다시 처음으로가서 메시지 올 때 까지 기다렸다가 오면 출력
    }








}