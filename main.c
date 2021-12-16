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


int main(){

//*****************buzzer program*************//
    buzzerInit();
    //buzzerTest();
    sleep(1);
    buzzerPlaySong();

//*****************textlcd program*************//
    int one = 1;
    int two = 2;
    char abc[10] = "Hello";
    char xyz[10] = "embeded";

    lcdtextInit();

    lcdtextWrite(one, abc);
    lcdtextWrite(two, xyz);
    sleep(5);
    
    lcdtextOff();

//*****************fnd program*************//
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

//*****************led program*************//
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

//*****************colorled program*************//
//---입력한 온도 값이라고 생각---//
    double a = 100;
    double b = 70;
    double c = 50;
    double d = 30;
    
    //---led 초기셋팅---//
    pwmLedInit();

    //---개별 조명 컨트롤---//
    ColorLED_White();
    sleep(1);
    ColorLED_Red();
    sleep(1);
    ColorLED_Green();
    sleep(1);
    ColorLED_Blue();
    sleep(1);
    
    //---온도값에 따른 색상 변화 함수---//
    pwmLed_thermalcheckmode(a);
    sleep(2);
    pwmLed_thermalcheckmode(b);
    sleep(2);
    pwmLed_thermalcheckmode(c);
    sleep(2);
    pwmLed_thermalcheckmode(d);
    sleep(2);
    
    //---led끄기 및 종료---//
    pwmLedOff();

//*****************temperature program*************//
    double t;
    t = read_temperature();
    
    printf("이것은 read_temperature 함수의 출력값(온도) : %lf \n", t);

//*****************accelMagGyro program*************//
    p_Accel();
    p_Magnet();
    p_Gyro();



    
    return 0;
}
