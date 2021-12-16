#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <getopt.h>
#include <errno.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
/////////////////////////////////////////////////////////////
#include <pthread.h>
#define MUTEX_ENABLE 0
////////////////////////////////////////////////////////////

//사용자 헤더 파일 전처리
#include "buzzer.h"
#include "textlcddrv.h"
#include "fnddrv.h"
#include "led.h"
#include "colorled.h"
#include "temperature.h"
#include "accelMagGyro.h"

//buzzer define
#define MAX_SCALE_STEP 8
#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"

//testled define
#define TEXTLCD_DRIVER_NAME		"/dev/peritextlcd"

//fnd define
#define FND_DRIVER_NAME		"/dev/perifnd"

//led define
#define LED_DRIVER_NAME		"/dev/periled"

//colorled define
#define COLOR_LED_DEV_R_ "/sys/class/pwm/pwmchip0/"
#define COLOR_LED_DEV_G_ "/sys/class/pwm/pwmchip1/"
#define COLOR_LED_DEV_B_ "/sys/class/pwm/pwmchip2/"
#define PWM_EXPORT "export"
#define PWM_UNEXPORT "unexport"
#define PWM_DUTY "pwm0/duty_cycle"
#define PWM_PERIOD "pwm0/period"
#define PWM_ENABLE "pwm0/enable"
#define PWM_COLOR_R 0
#define PWM_COLOR_G 1
#define PWM_COLOR_B 2
#define PWM_PERIOD_NS 1000000 //ns. = 1ms = 1khz 


///////////////////////쓰레드를 위한 전역 변수 파트 //////////////////
pthread_t tid[4];
double temper = 0;
int ready = 0;

pthread_mutex_t lock;
///////////////////////////////////////////////////////////////////


void* temperature(void *arg){
    while(1){
        //pthread_mutex_lock(&lock);
        temper=read_temperature();
        //pthread_mutex_unlock(&lock);
        sleep(1);
    }
}

void* thermalcheckmode(void *arg){
    while(1){
    //pwmLed_thermalcheckmode(temper);
    pwmLed_thermalcheckmode(temper);
    sleep(1);
    }
}

void* fndtherview(void *arg){
    while(1){
   
    if(temper>=35) fnd_static_dis(35);
    else if(temper>=34) fnd_static_dis(34);
    else if(temper>=33) fnd_static_dis(33);
    else if(temper>=32) fnd_static_dis(32);
    else if(temper>=31) fnd_static_dis(31);
    else if(temper>=30) fnd_static_dis(30);
    else if(temper>=29) fnd_static_dis(29);
    else if(temper>=28) fnd_static_dis(28);
    else if(temper>=27) fnd_static_dis(27);
    else if(temper>=26) fnd_static_dis(26);
    else if(temper>=25) fnd_static_dis(25);
    else if(temper>=24) fnd_static_dis(24);
    else if(temper>=23) fnd_static_dis(23);
    else fnd_static_dis(22);
    sleep(1);
    }
}

void* thermode_txtlcd(void *arg){
    char abc[10] = "Hello";
    char xyz[10] = "embeded";
    lcdtextInit();
    lcdtextWrite(1, abc);
    lcdtextWrite(2, xyz);
    sleep(1000);
    
}


int main(){

int err0;
int err1;
int err2;
int err3;


pwmLedInit();

if(pthread_mutex_init(&lock, NULL) != 0)
{
    printf("\n Mutext Init Failed!!\n");
    return 1;
}

err0 = pthread_create(&(tid[0]), NULL, &temperature, NULL);
if(err0 !=0) printf("Thread Create Error: [%d]\n",err0);

err1 = pthread_create(&(tid[1]), NULL, &thermalcheckmode, NULL);
if(err1 !=0) printf("Thread Create Error: [%d]\n",err1);

err2 = pthread_create(&(tid[2]), NULL, &fndtherview, NULL);
if(err2 !=0) printf("Thread Create Error: [%d]\n",err2);

err3 = pthread_create(&(tid[3]), NULL, &thermode_txtlcd, NULL);
if(err3 !=0)
printf("Thread Create Error: [%d]\n",err3);


pthread_join (tid[0], NULL);
pthread_join (tid[1], NULL);
pthread_join (tid[2], NULL);
pthread_join (tid[3], NULL);


    
    return 0;
}
