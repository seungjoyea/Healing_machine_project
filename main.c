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
#include <pthread.h>
pthread_t tid_led, tid_fnd, tid_textlcd, tid_colorled, tid_temperature, tid_acclMagGyro; //pthread 주소 return
static int err; //thread 생성 에러 검출
static int i; //에러확인용 변수

void* led_Func(void *arg)
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
}

void* fnd_Func(void *arg)
{
	int mode ;
	int number,counter;
	

	counter_10();
    sleep(1);
	fndDisp(123456, 0);
	sleep(1);
	
	timeDis();
	sleep(1);
	fndDisp(123456, 0);
	sleep(1);
	fndDisp(234567, 0);
	sleep(1);	
	fndDisp(345678, 0);
	sleep(1);	
	fndOff();
}

void* textlcd_Func(void *arg)
{
	First_line_write();
	Second_line_write();
}

void* colorled_Func(void *arg)
{
pwmLedInit();

while(1){
 ColorLED_White();
 sleep(1);
 ColorLED_Red();
 sleep(1);
 ColorLED_Green();
 sleep(1);
 ColorLED_Blue();
 sleep(1);
}
}

void* temperature_Func(void *arg)
{
 read_temperature(); //모니터에 나옴
}

void* acclMagGyro_Func(void *arg)
{
 read_acclAccelerometer();
 read_Magnetometer();
 read_Gyroscope();
}

int main(int argc , char **argv)
{
	
	err = pthread_create(&tid_led, NULL, &led_Func, NULL);  //thread_led 생성
    if(err != 0) printf("Thread Create Error: [%d]\n", i);  //Thread 생성 확인
    
	err = pthread_create(&tid_fnd, NULL, &fnd_Func, NULL);  //thread_button 생성
    if(err != 0) printf("Thread Create Error: [%d]\n", i);  //Thread 생성 확인
    
    err = pthread_create(&tid_textlcd, NULL, &textlcd_Func, NULL);  //thread_button 생성
    if(err != 0) printf("Thread Create Error: [%d]\n", i);  //Thread 생성 확인

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
}
