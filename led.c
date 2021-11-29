//#include “led.h”
#include <fcntl.h>

static unsigned int ledValue = 0;
static int fd = 0;
static int num_4sec = 0;

int ledLibInit(void)
{
fd=open("/dev/periled", O_WRONLY);
ledValue = 0;
}

int ledOnOff (int ledNum, int onOff)
{
int i=1;
i = i<<ledNum;
ledValue = ledValue& (~i);
if (onOff !=0) ledValue |= i;
write (fd, &ledValue, 4);
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

int ledLibExit(void)
{
ledValue = 0;
ledOnOff (0, 0);
close(fd);
}
