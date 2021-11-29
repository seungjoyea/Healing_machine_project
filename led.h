#ifndef _LED_H_

#define _LED_H_

int ledLibInit(void);

int ledOnOff (int ledNum, int onOff);

int test(void);

int ledAllBlink_4sec(void);

int AllLEDon_1s_twoLED_OFF_1s(void);

int ledStatus (void);

int ledLibExit(void);

#define LED_DRIVER_NAME

"/dev/periled”

#endif _LED_H_
