#ifndef __CH_H_
#define __CH_H_
#include "stdint.h"
#include  "Globalvalue/globalvalue.h"

#define XA0_L		GPIO_ClearValue(1, (1<<4));
#define	XWR_L		GPIO_ClearValue(4, (1<<27));
//#define	XRD_L		GPIO_ClearValue(5, (1<<3));
#define	XRD_L		GPIO_ClearValue(1, (1<<15));
#define	XCS_L		GPIO_ClearValue(2, (1));
#define XA0_H		GPIO_SetValue(1, (1<<4));
#define	XWR_H		GPIO_SetValue(4, (1<<27));
#define	XRD_H		GPIO_SetValue(1, (1<<15));
//#define	XRD_H		GPIO_SetValue(5, (1<<3));
#define	XCS_H		GPIO_SetValue(2, (1));

#define	D2_H		GPIO_SetValue(2, (1<<26));
#define	D1_H		GPIO_SetValue(1, (1));
#define	D2_L		GPIO_ClearValue(2, (1<<26));
#define	D1_L		GPIO_ClearValue(1, (1));

//#define	BEEP_ON		GPIO_SetValue(0, (1<<12));
//#define	BEEP_OFF		GPIO_ClearValue(0, (1<<12));

//PLC
//#define	PASS_ON		GPIO_ClearValue(2, (1<<11));
//#define	PASS_OFF	GPIO_SetValue(2, (1<<11));
//#define	HI_ON			GPIO_ClearValue(0, (1<<11));
//#define	HI_OFF		GPIO_SetValue(0, (1<<11));
////#define	HI_ON			GPIO_ClearValue(2, (1<<10));
////#define	HI_OFF		GPIO_SetValue(2, (1<<10));
//#define	LO_ON			GPIO_ClearValue(0, (1<<11));
//#define	LO_OFF		GPIO_SetValue(0, (1<<11));
//#define	TST_ON		!GPIO_ReadValue(0)&(1<<20)
//#define	TST_OFF		GPIO_ReadValue(0)&(1<<20)

//#define RANG		0x28
//#define SPEED		0x29
//#define T_adr		0x2a
//#define D_RDY		0x34
//#define DOT			0xa
//#define RDY			0
//#define FAST		0
//#define MIDD		1
//#define SLOW		2
//#define SYNC_RADR	0x40
//#define SYNC_WADR	0x42
//#define SYNC_CMD	0x11

//#define RANG2M		0
//#define RANG200K	1
//#define RANG20K		2
//#define RANG2K		3
//#define RANG200		4
//#define RANG20		5
//#define RANG2		6
//#define RANG200m	7
//#define RANG20m		8

#define ATUO	0xa
#define T_FLG	0x80


void Write421(uint8_t addr,uint8_t dat);//	,uint8_t sum
void Read421(uint8_t addr,uint8_t sum);
//void Power_On_Reset_Date(void);

#endif



