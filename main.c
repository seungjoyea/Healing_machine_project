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
#include <sys/msg.h>
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


////////////////////////////////////////
//////////   메세지 관련    ////////////
///////////////////////////////////////

//message structure
typedef struct
{
long int messageType;
char bulk_message[1000];
} structMyMsg;

static int cmp1, cmp2, cmp3,cmp4 ,cmp5, cmp6, cmp7, cmp8;  //두 문자열이 같으면 cmp = 0


pthread_t tid_led, tid_fnd, tid_textlcd, tid_colorled, tid_temperature, tid_acclMagGyro; //pthread 주소 return
static int err; //thread 생성 에러 검출
static int i; //에러확인용 변수



//1번 버
void* SLEEP_MODE(void *arg)
{
	//3초에 걸쳐 천천히 꺼짐
    slowly_DARK();
    
    sleep(1);
    buzzerPlaySong();
    ColorLED_OFF();
}


//2번 버튼
void* fix_posture(void *arg)
{
    int inclination;
    ledLibInit();
    ledAllBlink_4sec();
    while(1) {
        inclination = read_acclAccelerometer();
        usleep(500000);
        if(inclination > 4500)
            led_12();
        else if(3000<inclination && inclination<4500)
            led_23();
        else if(1500<inclination && inclination<3000)
            led_34();
        else if(-1500<inclination && inclination<1500)
            led_45();
        else if(-3000<inclination && inclination<-1500)
            led_56();
        else if(-4500<inclination && inclination<-3000)
            led_67();          
        else if(-6000<inclination && inclination<-4500)
            led_78();                     
    }
}

//3번 버튼 시작
void* thermal_mode(void *arg)
{
	pthread_t tid[4];
	double temper = 0;
    int ready = 0;

    pthread_mutex_t lock;
    
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

    
	int err0;
    int err1; 
    int err2;
    int err3;
	
	pwmLedInit();

    if(pthread_mutex_init(&lock, NULL) != 0) {
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
}


int main(int argc , char **argv)
{

	//버튼 관련
	structMyMsg messageRxData;
    int msgID = msgget((key_t)9999, IPC_CREAT|0666);
    if(msgID == -1){                               //우체통 생성 확인
        printf("Cannot get msgQueueID\n"); 
        return -1;
    }

    while (1) 
    {
    int returnValue = 0;
    returnValue = msgrcv(msgID, &messageRxData, sizeof(messageRxData.bulk_message
    ), 0, 0); //Wait here if no message

    cmp1 = strcmp(messageRxData.bulk_message, "1");
    cmp2 = strcmp(messageRxData.bulk_message, "2");
    cmp3 = strcmp(messageRxData.bulk_message, "3");
    cmp4 = strcmp(messageRxData.bulk_message, "4");
    cmp5 = strcmp(messageRxData.bulk_message, "5");
    cmp6 = strcmp(messageRxData.bulk_message, "6");
    cmp7 = strcmp(messageRxData.bulk_message, "7");
    cmp8 = strcmp(messageRxData.bulk_message, "8");

//버튼 1 누르면 SLEEP MODE
    if(cmp1==0) {
        printf("button1 ");
        err = pthread_create(&tid_led, NULL, &SLEEP_MODE, NULL);  //thread_led 생성
        if(err != 0) printf("Thread Create Error: [%d]\n", i);  //Thread 생성 확인 
	}
//버튼 2 누르면 자세교정 MODE
    else if (cmp2==0){
        printf("button2 ");
	    err = pthread_create(&tid_fnd, NULL, &fix_posture, NULL);  //thread_button 생성
       if(err != 0) printf("Thread Create Error: [%d]\n", i);  //Thread 생성 확인	
	}
    else if (cmp3==0){
        printf("button3 "); 
        err = pthread_create(&tid_textlcd, NULL, &thermal_mode, NULL);  //thread_button 생성
        if(err != 0) printf("Thread Create Error: [%d]\n", i);  //Thread 생성 확인  
    }
    else if (cmp4==0) {
        printf("button4 ");
 /*       err = pthread_create(&tid_colorled, NULL, &Buzzer_Func, NULL);  //thread_button 생성
        if(err != 0) printf("Thread Create Error: [%d]\n", i);  //Thread 생성 확인*/
	}
    else if (cmp5==0)
        printf("button5 ");
    else if (cmp6==0) {
        printf("button6 ");
        buzzerOFF();
	}
    else if (cmp7==0)
        printf("pressed\n");
    else if (cmp8==0)
        printf("released\n");
	}
   
/*
    err = pthread_create(&tid_colorled, NULL, &colorled_Func, NULL);  //thread_button 생성
    if(err != 0) printf("Thread Create Error: [%d]\n", i);  //Thread 생성 확인

    err = pthread_create(&tid_temperature, NULL, &temperature_Func, NULL);  //thread_button 생성
    if(err != 0) printf("Thread Create Error: [%d]\n", i);  //Thread 생성 확인
    
    err = pthread_create(&tid_acclMagGyro, NULL, &acclMagGyro_Func, NULL);  //thread_button 생성
    if(err != 0) printf("Thread Create Error: [%d]\n", i);  //Thread 생성 확인


    pthread_join(tid_led,NULL); //Thread 종료시까지 wait
    pthread_join(tid_fnd,NULL); //Thread 종료시까지 wait
    pthread_join(tid_textlcd,NULL); //Thread 종료시까지 wait
    pthread_join(tid_colorled,NULL); //Thread 종료시까지 wait    
    pthread_join(tid_temperature,NULL); //Thread 종료시까지 wait    
    pthread_join(tid_acclMagGyro,NULL); //Thread 종료시까지 wait    
	return 0;
	*/
}
