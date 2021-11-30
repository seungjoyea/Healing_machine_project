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
static int num_4sec = 0;

int ledLibInit(void)
{
fd=open("/dev/periled", O_WRONLY);
ledValue = 0;
	if ( fd < 0 )
	{
		perror("driver (//dev//cnled) open error.\n");
		return 1;
	}
}

int ledOnOff (int ledNum, int onOff)
{
int i=1;
i = i<<ledNum;
ledValue = ledValue& (~i);
if (onOff !=0) ledValue |= i;
write (fd, &ledValue, 4);
}

int test(void)
{
	ledAllBlink_4sec();
}


int ledAllBlink_4sec(void)
{
for(num_4sec=0;num_4sec<2;num_4sec++){
ledValue = 0xFF;
write (fd, &ledValue, 4);
sleep(1);
ledValue = 0x00;
write (fd, &ledValue, 4);
sleep(1);
}
}

int AllLEDon_1s_twoLED_OFF_1s(void)
{
ledValue = 0xFF;
write (fd, &ledValue, 4);
sleep(1);
ledValue = 0b01111110;
write (fd, &ledValue, 4);
sleep(1);
ledValue = 0b00111100;
write (fd, &ledValue, 4);
sleep(1);
ledValue = 0b00011000;
write (fd, &ledValue, 4);
sleep(1);
ledValue = 0x00;
write (fd, &ledValue, 4);
sleep(1);
}

int ledLibExit(void)
{
ledValue = 0;
ledOnOff (0, 0);
close(fd);
}
