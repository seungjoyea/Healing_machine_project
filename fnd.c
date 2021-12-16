#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "fnddrv.h"
#define FND_DRIVER_NAME "/dev/perifnd"

//-------------1. fnd 디스플레이------------------//
int fndDisp(int num , int dotflag) //0-999999 숫자, 비트로 인코딩된 dot on/off
{
int fd;
int temp,i;
stFndWriteForm stWriteData;
for (i = 0; i < MAX_FND_NUM ; i++ )
{
stWriteData.DataDot[i] = (dotflag & (0x1 << i)) ? 1 : 0;
stWriteData.DataValid[i] = 1;
}
// if 6 fnd
temp = num % 1000000; stWriteData.DataNumeric[0]= temp /100000;
temp = num % 100000; stWriteData.DataNumeric[1]= temp /10000;
temp = num % 10000; stWriteData.DataNumeric[2] = temp /1000;
temp = num %1000; stWriteData.DataNumeric[3] = temp /100;
temp = num %100; stWriteData.DataNumeric[4] = temp /10;
stWriteData.DataNumeric[5] = num %10;

fd = open(FND_DRIVER_NAME,O_RDWR);
if ( fd < 0 )
{
perror("driver open error.\n");
return 0;
}
write(fd, &stWriteData, sizeof(stFndWriteForm));
close(fd);
return 1;
}

//-------------2. fnd static number display------------------//
void fnd_static_dis(long a)
{
fndDisp(a , 0);
}

//-------------3. fnd time display------------//
void fnd_time_dis(void)
{
    int number;
    struct tm *ptmcur;
    time_t tTime;
    if ( -1 == time(&tTime) )
    return -1;
    ptmcur = localtime(&tTime);
    number = ptmcur->tm_hour * 10000;
    number += ptmcur->tm_min *100;
    number += ptmcur->tm_sec;
    fndDisp(number , 0b1010);
}

//-------------4. fnd count display------------//
void fnd_count_dis(long a)
{
int counter = 0;
while(1)
{
if (!fndDisp(counter , 0))
break;
counter++;
sleep(1);
if (counter > a )
break;
}
}

//-------------5. fnd reverse count display------------//
void fnd_rev_count_dis(long a)
{
int counter = a;
while(1)
{
if (!fndDisp(counter , 0))
break;
counter--;
sleep(1);
if (counter == 0 )
break;
}
}

//-----------6. fnd off -----------------------//


int fndOff()
{
	int fd,i;
	stFndWriteForm stWriteData;
	
	for (i = 0; i < MAX_FND_NUM ; i++ )
	{
		stWriteData.DataDot[i] =  0;  
		stWriteData.DataNumeric[i] = 0;
		stWriteData.DataValid[i] = 0;
	}
	fd = open(FND_DRIVER_NAME,O_RDWR);
	if ( fd < 0 )
	{
		perror("driver open error.\n");
		return 0;
	}	
	write(fd,&stWriteData,sizeof(stFndWriteForm));
	close(fd);
	return 1;
}
