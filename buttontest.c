#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl

int main(int argc, char *argv[])
{
int fp;
char inputDevPath[200]={0,};

fp = Initialize_Button();   //file open해서 fp 받음

close(fp);
}
