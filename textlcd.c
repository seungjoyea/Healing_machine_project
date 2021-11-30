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


int First_line_write(void)
{
	stTextLCD  stlcd; 
	int fd;
	int len; 
	char *data =("What do you want") ;
	memset(&stlcd,0,sizeof(stTextLCD));

	stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
	
	len = strlen(data);
	if ( len > COLUMN_NUM)
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],data,COLUMN_NUM);
	}
	else
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],data,len);
	}
		
	stlcd.cmd = CMD_WRITE_STRING;
	
	fd = open(TEXTLCD_DRIVER_NAME,O_RDWR);
	if ( fd < 0 )
	{
		perror("driver (//dev//peritextlcd) open error.\n");
		return 1;
	}
	write(fd,&stlcd,sizeof(stTextLCD));
	
    close(fd);
		
	return 0;
}

int Second_line_write(void)
{

	stTextLCD  stlcd; 
	int fd;
	int len; 
	char *data =("Second line s") ;
	memset(&stlcd,0,sizeof(stTextLCD));

	stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
	
	len = strlen(data);
	if ( len > COLUMN_NUM)
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],data,COLUMN_NUM);
	}
	else
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],data,len);
	}
		
	stlcd.cmd = CMD_WRITE_STRING;
	
	fd = open(TEXTLCD_DRIVER_NAME,O_RDWR);
	if ( fd < 0 )
	{
		perror("driver (//dev//peritextlcd) open error.\n");
		return 1;
	}
	write(fd,&stlcd,sizeof(stTextLCD));
	
    close(fd);
		
	return 0;
}
