#ifndef __test_h
#define __test_h
//#include "stdint.h"
#include  "Globalvalue/globalvalue.h"

void Power_Process(void);
//测试程序
//void Test_Process(void);
void Use_SysSetProcess(void);
void  Resist_Test(uint8_t key);	   //,uint8_t t电阻测试显示界面
void	Disp_R(uint8_t p);
void Use_MainProcess(void);
//void  Compare_Process(uint8_t key);   //比较显示界面
#define	CS_L		GPIO_ClearValue(1, 1<<16);
#define CLK_L		GPIO_ClearValue(1, 1<<6);//A0
#define	DIN_L		GPIO_ClearValue(1, 1<<11);
#define	CS_H		GPIO_SetValue(1, 1<<16);
#define CLK_H		GPIO_SetValue(1, 1<<6);
#define	DIN_H		GPIO_SetValue(1, 1<<11);

#define	RST_H		GPIO_SetValue(1, 1<<5);
#define	RST_L		GPIO_ClearValue(1, 1<<5);

#define	D2_H		GPIO_SetValue(2, (1<<26));
#define	D1_H		GPIO_SetValue(1, (1));
#define	D2_L		GPIO_ClearValue(2, (1<<26));
#define	D1_L		GPIO_ClearValue(1, (1));

#define	DO_L		!GPIO_ReadValue(1)&(1<<17)
#define	DO_H		GPIO_ReadValue(1)&(1<<17)
#define	INT_L		!GPIO_ReadValue(1)&(1<<3)


#define READ_MASK	0x3e
#define REG_CONFR	0x40
#define	REG_CYCCONT 0x4A
#define REG_VRMSR   0x18
#define REG_IRMSR	0x16
#define REG_Pactive	0x14

#define REG_STATUSR 0x5E 	//??
#define REG_MODER	0x64

#define REG_MASKR   0x74
#define REG_CTRLR   0x78
#define CMD_STARTC  0XE8  	//????????
#define CMD_SYNC0	0xfe
#define CMD_SYNC1	0xff

#define CS5463_VScale	0x1ff
#define CS5463_IScale	0x1ff

#define  ModePnt				    0
#define  URangPnt				    1
#define  IRangPnt					  2

#define  VAPnt  				    3
#define  PFPnt				      4

#define  VARPnt  				    5
#define  FPnt  				      6
#define  VHzPnt  				    7
#define  IHzPnt  				    8
#define  VrmsPnt  				  9
#define  IrmsPnt  				  10
#define  PPnt  				      11
#define  EPnt  				      12
/*
struct RDispPara_main	
{
  int row;                    //???
  int col;                   //???
	int len;
	char flag;
	unsigned int max;
	unsigned int val;
  char En[16];    //??
  char Ch[16];    //??
	char Item[10][16];    //?? 
};
*/
void Setvalue_Reduction(void);//
void Setvalue_Add(void);
extern unsigned char KPULCursorP ;			
extern unsigned char KPILCursorP ;			
extern unsigned char KPADDCursorP;	
#endif
