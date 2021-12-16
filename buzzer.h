#ifndef _BUZZER_H_
#define _BUZZER_H_
int buzzerInit(void);
void buzzerON(void);
void buzzerOFF(void);
void F_DO(void);
void F_RE(void);
void F_MI(void);
void F_PA(void);
void F_SOL(void);
void F_RA(void);
void F_SI(void);
void F_DO_High(void);
void F_RE_High(void);
void F_MI_High(void);
void F_PA_High(void);
void F_SOL_High(void);
void F_RA_High(void);

//매크로//
void buzzerTest(void);
void buzzerSiren(void);
void buzzerPlaySong(void);
void buzzer_Last_Christmas_Song(void); //징글벨
#endif
