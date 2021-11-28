#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#define MAX_SCALE_STEP 8
#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"
#include "buzzer.h"


char gBuzzerBaseSysDir[128]; ///sys/bus/platform/devices/peribuzzer.XX 가 결정됨


const int musicScale[MAX_SCALE_STEP] =
{
262, /*do*/ 294,330,349,392,440,494, /* si */ 523
}; //musicScale[0] 도, [1] 레 ...



int findBuzzerSysPath(){
DIR* dir_info = opendir ("/sys/bus/platform/devices/");
int ifNotFound = 1;
if (dir_info != NULL){
while (1){
struct dirent *dir_entry;
dir_entry = readdir (dir_info);
if (dir_entry == NULL) break;
if (strncasecmp(BUZZER_FILENAME, dir_entry->d_name, strlen(BUZZER_FILENAME)) == 0){
ifNotFound = 0;
sprintf(gBuzzerBaseSysDir,"%s%s/", "/sys/bus/platform/devices/",dir_entry->d_name);
}
}
}
printf("find %s\n",gBuzzerBaseSysDir);
return ifNotFound;
}
//버저 경로 찾기: /sys/bus/platform/devices/peribuzzer.XX 의 XX를 결정하는 것

void doHelp(void)
{
printf("Usage:\n");
printf("buzzertest <buzzerNo> \n");
printf("buzzerNo: \n");
printf("do(1),re(2),mi(3),fa(4),sol(5),ra(6),si(7),do(8) \n");
printf("off(0)\n");
}

void buzzerEnable(int bEnable)
{
char path[200];
sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_ENABLE_NAME);
int fd=open(path,O_WRONLY);
if ( bEnable) write(fd, &"1", 1);
else write(fd, &"0", 1);
close(fd);
}

void setFrequency(int frequency)
{
char path[200];
sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_FREQUENCY_NAME);
int fd=open(path,O_WRONLY);
dprintf(fd, "%d", frequency);
close(fd);
}

int buzzerInit(void)
{
    findBuzzerSysPath();
}

int buzzerPlaySong(int time)
{   
    //time 노래 반복횟수
    //노래 나오게 음마다 딜레이하는법 생각 필요
    for(int t=0; t<time; t++){ 
        
        for(int a=0; a<9999; a++)
        { 
            setFrequency(1);
        buzzerEnable(1);
        }
        
        for(int b=0; b<9999; b++)
        {
        setFrequency(2);
        buzzerEnable(1);
        }
        
        for(int c=0; c<9999; c++)
        {
            setFrequency(3);
        buzzerEnable(1);
        }
       
        for(int d=0; d<9999; d++)
        {
            setFrequency(4);
        buzzerEnable(1);
        }
        
        for(int e=0; e<9999; e++)
        {
            setFrequency(5);
        buzzerEnable(1);
        }}
}
    


int buzzerStopSong(void)
{
    buzzerEnable(0);
}
