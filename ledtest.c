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


#define LED_DRIVER_NAME		"/dev/periled"

void doHelp(void)
{
	printf("Usage:\n");
	printf("ledtest <hex byte>  :data bit0 operation 1=>on 0=>off\n");
	printf("ex) ledtest 0x04 ;3th led on\n");
	printf("    ledtest 0x05 ;4th and 1th led on\n");
	printf("    ledtest 0xff ;all led on\n");
	printf("    ledtest 0x00 ;all led off\n");
}



int main(int argc , char **argv)
{

	ledLibInit();
	test();
	
	
	AllLEDon_1s_twoLED_OFF_1s();
	
	ledAllBlink_4sec();
	
	while(1){
    ledOnOff (0x01,0x01);
    sleep(1);
    ledOnOff(0x02,0x02);
    sleep(1);
    ledOnOff(0x01,0x00);
    sleep(1);
    ledOnOff(0x02,0x00);
}




	ledLibExit();
	
	return 0;
}
