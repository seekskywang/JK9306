#ifndef __Key_H_
#define __Key_H_
typedef unsigned char u8;
typedef unsigned  int u32;

#define		Key_Disp 	(27)
#define		Key_SETUP	(19)
#define		Key_FAST	(2)
#define		Key_LEFT	(3)
#define		Key_RIGHT  	(11)
#define		Key_UP		(26)
#define		Key_DOWN	(10)

#define		Key_BACK	(12)
#define		Key_LOCK	(255)
#define		Key_BIAS	(31)
#define		Key_REST	(7)
#define		Key_TRIG	(15)

#define		KEY_Disp	4
#define   KEY_Setup	5
#define   KEY_UP		9
#define   KEY_Down  10
#define   KEY_Left  2
#define		KEY_Right	1
#define   KEY_File  12
#define   KEY_0ADJ  3
#define   KEY_Enter 11
#define   KEY_Trig  00
#define   KEY_Mid   8

#define 	Hc164CpL GPIO_ClearValue(1, (1<<1))
#define 	Hc164CpH GPIO_SetValue(1, (1<<1))
#define 	Hc164DL GPIO_ClearValue(1, (1<<10))
#define 	Hc164DH GPIO_SetValue(1, (1<<10))

extern void Delay (unsigned long tick);
void HW_Sendvalueto164(u8 value);
void HW_keyInt(void);
u8 HW_KeyScsn(void);
void Delay_Key(void);
void BUZZER(void);
void Key_Pro(u8 key);
#endif


