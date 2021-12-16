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


#define FND_DRIVER_NAME		"/dev/perifnd"


int main(int argc , char **argv)
{
long x =5;
long y =3;
long z = 12345;
fnd_static_dis(z);
sleep(3);
fnd_time_dis();
sleep(3);
fnd_count_dis(x);
sleep(3);
fnd_rev_count_dis(y);
sleep(3);
fndOff();
	return 0;
}
