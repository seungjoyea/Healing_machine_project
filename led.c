#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "led.h"

static unsigned int ledValue = 0;
static int fd = 0;

int ledOnOff (int ledNum, int onOff)
{
    int i=1;
    i = i<<ledNum;
    ledValue = ledValue& (~i);
    if (onOff !=0) ledValue |= i;
    write (fd, &ledValue, 4);
}


int ledLibInit(void)
{
    fd = open("/dev/periled", O_WRONLY);
    ledValue = 0;
}

int ledLibExit(void)
{
    ledValue = 0;
    ledOnOff (0, 0);
    close(fd);
}

/*
//추가할 때 쓰기 헤더파일에도 추가
int ledBlink(void)
{
    while(1){
        write(fd, 0xFF,4);
        delay(1000); //1초 대기
        write(fd, 0x00,4);
    }
 //카운터나 타임관련 전처리기 include하기
}

//이거 아니면
int ledBlink(void)
{
    while(1){
    ledOnOff (0xFF, 1);
    delay(5000) ;
    ledOnOff (0xFF, 0);   
    }
}
*/