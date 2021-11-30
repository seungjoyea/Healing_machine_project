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
#include "textlcddrv.h"



#define TEXTLCD_DRIVER_NAME		"/dev/peritextlcd"

void doHelp(void)
{
	printf("usage: textlcdtest <linenum> <'string'>\n");
	printf("       linenum => 1 ~ 2\n");	
	printf("  ex) textlcdtest 2 'test hello'\n");
	
}


int main(int argc , char **argv)
{

	First_line_write();
	Second_line_write();
	
}
