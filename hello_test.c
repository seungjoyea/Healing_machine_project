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

#define HELLO_DRIVER_NAME "/dev/hello1"

int main(int argc , char **argv)
{ 

    char data[2000];
    int fd;
    unsigned int inputCmd;
    int value = 0;
    unsigned long returnValue;

    printf("enter test\n");

    while (1) {
    printf("1 to write\n");
    printf("2 to read\n");
    printf("3 to ioctl\n");
    printf("please enter :");
    scanf("%d", &value);

    switch(value){
    case 1 : 
    printf("write option selected\n");
    /* file open */
    fd = open(HELLO_DRIVER_NAME,O_RDWR); // file open
    if ( fd < 0 ) //open 잘 됬나 확인
    { printf(" open fail\n");
    perror("driver (/dev/hello1) open error.\n");
    return 1;
    }
    printf("open success\n"); //open 잘 됨
    /* write  */
    printf("please enter the data to write into device\n"); //Data를 써주세요
    gets(data); //한줄의 문자열 입력을 받음
    write(fd, &data, 2000);
    close(fd);
    break;
    
    
    case 2 : 
    printf("read option selected\n");
    /* file open */
    fd = open(HELLO_DRIVER_NAME,O_RDWR);
    if ( fd < 0 ) //open 잘 됬나 확인
    { printf(" open fail\n");
    perror("driver (/dev/hello1) open error.\n");
    return 1;
    }
    printf("open success\n"); //open 잘 됨
    /* read */
    read(fd,data,2000);        
    printf("data is %c %c %c %c\n",data[0], data[1],data[2],data[3]);
    close(fd);
    break;

    
    case 3 :
    printf("ioctl option selected\n");
    /* file open */
    fd = open(HELLO_DRIVER_NAME,O_RDWR);
    if ( fd < 0 ) //open 잘 됬나 확인
    { printf(" open fail\n");
    perror("driver (/dev/hello1) open error.\n");
    return 1;
    }
    printf("open success\n"); //open 잘 됨
    
    printf("'how much byte do you want to read?' please enter  :");
    scanf("%d", &value);  //사용자가 원하는 byte를 입력
   //value는 몇 byte 읽을지 정한 숫자 (ppt 65p, 66p 참고)
    inputCmd = _IOW(0x55, 98, int); //cmd만들 때 그 size만큼 읽도록 만듬   현재는 8byte
    returnValue = ioctl(fd, inputCmd, &value);
    close(fd);
    
    
    default :     printf("select 1 or 2 or 3 \n");
    }



    }

  //  close(fd);
    return 0;
}

//write -> read 순으로 test 진행하기