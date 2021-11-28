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

#define HELLO_DRIVER_NAME "/dev/hello2"

int main(int argc , char **argv)
{ char data[2000]={0,};
  char data_W[7] = {'9','8','7','6','5','1','3'};
int fd;
int value;
int count;
printf("enter test\n");
// open driver
fd = open(HELLO_DRIVER_NAME,O_RDWR);
if ( fd < 0 )
{ printf(" open fail\n");
perror("driver (/dev/hello2) open error.\n");
return 1;
}
printf("open success\n");

//while(1){
printf("1번 wirte, 2번 read, 3번 ioctl, 다른숫자 종료: ");
scanf("%d", &value);

if(value==1){
//data_W 마저도 쓸 수 있게 하면됨 이때, 7대신 입력한 바이트 수 계산필요
write(fd, &data_W, 7);
}
else if(value ==2){
read(fd,data,2000);
printf("read value:%c%c%c%c\n",data[0],data[1],data[2],data[3]);
}
else if(value ==3){
printf("몇바이트 출력해줄지 숫자써라 :");
scanf("%d", &count);
unsigned int inputCmd = _IOW(0x55, 99, int);
unsigned long returnValue = ioctl (fd, inputCmd, &count);
}

close(fd);
return 0;

}
