#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

typedef struct
{
long int messageType;
char bulk_message[1000];
} structMyMsg;

static int count = 0;


int main (void)
{
structMyMsg messageRxData;
int msgID = msgget((key_t)9999, IPC_CREAT|0666);
    if(msgID == -1){                               //우체통 생성 확인
        printf("Cannot get msgQueueID\n"); 
        return -1;
    }

   while (1)
{
int returnValue = 0;
returnValue = msgrcv(msgID, &messageRxData, sizeof(messageRxData.bulk_message), 0, IPC_NOWAIT);
if (returnValue == -1) break; //There is no message at all
count++;
printf ("%d message Comes: [%s]\r\n",count, messageRxData.bulk_message);
}
printf ("\tI got %d messages in the queue\r\n",count);
while (1)
{
int returnValue = 0;
returnValue = msgrcv(msgID, &messageRxData, sizeof(messageRxData.bulk_message
), 0, 0); //Wait here if no message
count++;
printf ("%d message Comes: [%s]\r\n",count, messageRxData.bulk_message);
}
}
