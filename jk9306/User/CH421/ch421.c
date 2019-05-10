#include "ch421.h"
#include "stdint.h"
#include "lpc177x_8x_gpio.h"
#include "Globalvalue/globalvalue.h"
union	UUU
{
	float	adx;
	uint8_t	bx[4];
};
union	UUU	div[9];
char tdat[48]={0};
uint8_t	test[5],range,sped,syn,disp[6],change;

void dly(uint8_t	a)
{
uint8_t	b;
	for(b=0;b<a;b++)
	{}
}
//初始化 CS，WR，RD，A0，引脚
void CH421_Init_CWRA1(void)
{
	LPC_IOCON->P2_0   = 0x30;//
	LPC_IOCON->P4_27  = 0x30;
//	LPC_IOCON->P5_3   = 0x30;
		LPC_IOCON->P1_15   = 0x30;
	LPC_IOCON->P1_4   = 0x30;
	GPIO_SetDir(2,(1<<0), GPIO_DIRECTION_OUTPUT);	//  XCS
	GPIO_SetDir(4,(1<<27), GPIO_DIRECTION_OUTPUT);	//  XWR
//	GPIO_SetDir(5, (1<<3),GPIO_DIRECTION_OUTPUT);   //  XRD
	GPIO_SetDir(1,(1<<15),GPIO_DIRECTION_OUTPUT);
	GPIO_SetDir(1,(1<<4),GPIO_DIRECTION_OUTPUT);   //  XA0
	GPIO_SetDir(2,(1<<26),GPIO_DIRECTION_OUTPUT);//D1
	GPIO_SetDir(1,(1),GPIO_DIRECTION_OUTPUT);//D2
//PLC io
		LPC_IOCON->P0_10   = 0x30;//
		LPC_IOCON->P2_11   = 0x30;//pas
		LPC_IOCON->P2_10   = 0x30;//hi
		LPC_IOCON->P0_11   = 0x30;//lo
		LPC_IOCON->P0_21   = 0x30;//
		LPC_IOCON->P0_20   = 0x30;//
	GPIO_SetDir(0,(1<<10),GPIO_DIRECTION_OUTPUT);
	GPIO_SetDir(2,(1<<11),GPIO_DIRECTION_OUTPUT);
	GPIO_SetDir(2,(1<<10),GPIO_DIRECTION_OUTPUT);
	GPIO_SetDir(0,(1<<11),GPIO_DIRECTION_OUTPUT);
	GPIO_SetDir(0,(1<<21),GPIO_DIRECTION_INPUT);
	GPIO_SetDir(0,(1<<20),GPIO_DIRECTION_INPUT);
	/*
	LPC_IOCON->P1_3   = 0x30;
	LPC_IOCON->P1_5   = 0x30;
	LPC_IOCON->P1_6   = 0x30;
	LPC_IOCON->P1_7   = 0x30;
	LPC_IOCON->P1_11   = 0x30;
	LPC_IOCON->P1_13   = 0x30;
	LPC_IOCON->P1_16   = 0x30;
	LPC_IOCON->P1_17   = 0x30;*/

//usb
	LPC_IOCON->P0_31   = 0x31;//usb D+  2
}

void CH421_Init_InPut(void)
{
	GPIO_SetDir(1, (1<<13), GPIO_DIRECTION_INPUT);//  XD7
	GPIO_SetDir(1, (1<<7), GPIO_DIRECTION_INPUT);	//  XD6
	GPIO_SetDir(1, (1<<5), GPIO_DIRECTION_INPUT);	//  XD5
	GPIO_SetDir(1, (1<<11), GPIO_DIRECTION_INPUT);//  XD4
	GPIO_SetDir(1, (1<<6), GPIO_DIRECTION_INPUT);	//  XD3
	GPIO_SetDir(1, (1<<3), GPIO_DIRECTION_INPUT);	//  XD2
	GPIO_SetDir(1, (1<<16), GPIO_DIRECTION_INPUT);//  XD1
	GPIO_SetDir(1, (1<<17), GPIO_DIRECTION_INPUT);//  XD0	
}

void CH421_Init_OutPut(void)
{
	GPIO_SetDir(1, (1<<13),GPIO_DIRECTION_OUTPUT);//  XD7
	GPIO_SetDir(1, (1<<7), GPIO_DIRECTION_OUTPUT);//  XD6
	GPIO_SetDir(1, (1<<5),GPIO_DIRECTION_OUTPUT);	//  XD5
	GPIO_SetDir(1, (1<<11),GPIO_DIRECTION_OUTPUT);//  XD4
	GPIO_SetDir(1, (1<<6),GPIO_DIRECTION_OUTPUT);	//  XD3
	GPIO_SetDir(1, (1<<3), GPIO_DIRECTION_OUTPUT);//  XD2
	GPIO_SetDir(1, (1<<16),GPIO_DIRECTION_OUTPUT);//  XD1
	GPIO_SetDir(1, (1<<17),GPIO_DIRECTION_OUTPUT);//  XD0
}

void LED421(void)
{
//D1_L
//	D2_H
	D2_L
}

void Write_Date(uint8_t dat)
{
//	uint8_t num=0,date=0;
	XCS_H
	XWR_H
	XRD_H
	if(dat&0x01)		GPIO_SetValue(1, 1<<17);			// XD0置为1
	else		GPIO_ClearValue(1, (1<<17));		//把1-17引脚置为0	GPIO_SetValue只能置1，GPIO_ClearValue只能置0
	
	if(dat&0x02)		GPIO_SetValue(1, (1<<16));		// XD1
	else		GPIO_ClearValue(1, (1<<16));
	
	if(dat&0x04)		GPIO_SetValue(1, (1<<3));			// XD2
	else		GPIO_ClearValue(1, (1<<3));
	
	if(dat&0x08)		GPIO_SetValue(1, (1<<6));			// XD3
	else		GPIO_ClearValue(1, (1<<6));
	
	if(dat&0x10)		GPIO_SetValue(1, (1<<11));		// XD4
	else		GPIO_ClearValue(1, (1<<11));
	
	if(dat&0x20)		GPIO_SetValue(1, (1<<5));			// XD5
	else		GPIO_ClearValue(1, (1<<5));
	
	if(dat&0x40)		GPIO_SetValue(1, (1<<7));			// XD6
	else		GPIO_ClearValue(1, (1<<7));
	
	if(dat&0x80)		GPIO_SetValue(1, (1<<13));		// XD7
	else		GPIO_ClearValue(1, (1<<13));
}

void WR_adr(uint8_t adr)
{
	CH421_Init_OutPut();
	Write_Date(adr);
	dly(3);
	XA0_L
	XCS_L
	XWR_L
	XWR_L

	dly(5);
	XCS_H
	XWR_H
	XRD_H
}
void WR_dat(uint8_t dat)
{
CH421_Init_OutPut();
Write_Date(dat);
	dly(3);
	XA0_H
	XCS_L
	XWR_L
	XWR_L

	dly(5);
	XCS_H
	XWR_H
	XRD_H
}

uint8_t read(void)
{
uint8_t dx=0;
	XA0_H
	XWR_H
	XCS_L
	XRD_L
	XRD_L
	dly(3);
	if(GPIO_ReadValue(1)&(1<<13))dx|=0x80;//D7

		if(GPIO_ReadValue(1)&(1<<7))dx|=0x40;//D6

			if(GPIO_ReadValue(1)&(1<<5))dx|=0x20;//D5

				if(GPIO_ReadValue(1)&(1<<11))dx|=0x10;//D4

					if(GPIO_ReadValue(1)&(1<<6))dx|=0x8;//D3

						if(GPIO_ReadValue(1)&(1<<3))dx|=0x4;//D2

							if(GPIO_ReadValue(1)&(1<<16))dx|=0x2;//D1

								if(GPIO_ReadValue(1)&(1<<17))dx|=1;//D0
	XRD_H
	XCS_H
	return dx;
}
uint8_t rd421(uint8_t adr)
{
uint8_t rx;

	WR_adr(adr);
	CH421_Init_InPut();
	rx=read();
	return rx;
}
void red421(uint8_t adr)
{
uint8_t i,x;
	x=adr;
for(i=0;i<0x4;i++)
	Test_Dat.RBuff[i]=rd421(x+i);
}
void Write421(uint8_t addr,uint8_t dat)//,uint8_t sum	
{
//	uint8_t i;
//	CH421_Init_CWRA();
	CH421_Init_OutPut();
	WR_adr(addr);
	WR_dat(dat);
}

//read 2 group data from ch421
void Read421(uint8_t addr,uint8_t sum)
{
	uint8_t i;
//	CH421_Init_CWRA();
	CH421_Init_OutPut();
//	WRITE_ADDE;
	XRD_H
	XWR_H
	XCS_H
	dly(3);
	Write_Date(addr);
	dly(3);
	XA0_L
	XCS_L
	XCS_L

	XWR_L
	XWR_L
dly(3);
	XWR_H
	XCS_H
		XCS_H
		XCS_H
	CH421_Init_InPut();//	READ_DATA;
XA0_H	
XWR_H
	XCS_H
		XCS_H
			
for(i=0;i<sum;i++)
		{
/*			XCS_L
			XCS_L
			XRD_L
			XRD_L
			dly(3);*/
			Test_Dat.RBuff[i]=read();//_Date
/*			XRD_H
			XRD_H
			XCS_H*/
		}
}

void init421_adj(void)
{Write421(0x42,0x11);
//wr 421 adj val
//0
//Write421(0,0);
//Write421(1,SaveData.div[0].bx[1]);//0x80;
//Write421(2,0);//SaveData.div[0].bx[2]
//Write421(3,0);//SaveData.div[0].bx[3]
//1
Write421(4,0);
Write421(5,SaveData.div[1].bx[1]);//0x01
Write421(6,SaveData.div[1].bx[2]);//0
Write421(7,SaveData.div[1].bx[3]);//0
//2
Write421(8,0);
Write421(9,SaveData.div[2].bx[1]);//0x01
Write421(10,SaveData.div[2].bx[2]);//
Write421(11,SaveData.div[2].bx[3]);//
//3
Write421(12,0);
Write421(13,SaveData.div[3].bx[1]);//0x01
Write421(14,SaveData.div[3].bx[2]);//
Write421(15,SaveData.div[3].bx[3]);//
//4
Write421(16,0);
Write421(17,SaveData.div[4].bx[1]);//0x01
Write421(18,SaveData.div[4].bx[2]);////
Write421(19,SaveData.div[4].bx[3]);//
//5
Write421(20,0);
Write421(21,SaveData.div[5].bx[1]);//0x01
Write421(22,SaveData.div[5].bx[2]);//
Write421(23,SaveData.div[5].bx[3]);//
//6
Write421(24,0);
Write421(25,SaveData.div[6].bx[1]);//0x01
Write421(26,SaveData.div[6].bx[2]);//
Write421(27,SaveData.div[6].bx[3]);//
//7
Write421(28,0);
Write421(29,SaveData.div[7].bx[1]);//0x01
Write421(30,SaveData.div[7].bx[2]);//
Write421(31,SaveData.div[7].bx[3]);//
//8
Write421(32,0);
Write421(33,SaveData.div[8].bx[1]);//0x01
Write421(34,SaveData.div[8].bx[2]);//
Write421(35,SaveData.div[8].bx[3]);//
//9
Write421(36,0);
Write421(37,SaveData.div[9].bx[1]);//0x01
Write421(38,SaveData.div[9].bx[2]);//
Write421(39,SaveData.div[9].bx[3]);//

Write421(0x2b,4);
Write421(0x2c,0);
Write421(0x2d,0);
Write421(0x2e,0);
Write421(0x2f,0);
}
//void init()
//{
//	char t;

//	tdat[0]=div[0].bx[0];
//	tdat[1]=div[0].bx[1];
//	tdat[2]=div[0].bx[2];
//	tdat[3]=div[0].bx[3];//2M

//	tdat[4]=div[1].bx[0];
//	tdat[5]=div[1].bx[1];
//	tdat[6]=div[1].bx[2];
//	tdat[7]=div[1].bx[3];//200k

//	tdat[8]=div[2].bx[0];
//	tdat[9]=div[2].bx[1];
//	tdat[10]=div[2].bx[2];
//	tdat[11]=div[2].bx[3];//20k

//	tdat[12]=div[3].bx[0];
//	tdat[13]=div[3].bx[1];
//	tdat[14]=div[3].bx[2];
//	tdat[15]=div[3].bx[3];//2k

//	tdat[16]=div[4].bx[0];
//	tdat[17]=div[4].bx[1];
//	tdat[18]=div[4].bx[2];
//	tdat[19]=div[4].bx[3];;//200

//	tdat[20]=div[5].bx[0];
//	tdat[21]=div[5].bx[1];
//	tdat[22]=div[5].bx[2];
//	tdat[23]=div[5].bx[3];//20

//	tdat[24]=div[6].bx[0];
//	tdat[25]=div[6].bx[1];
//	tdat[26]=div[6].bx[2];
//	tdat[27]=div[6].bx[3];//2

//	tdat[28]=div[7].bx[0];
//	tdat[29]=div[7].bx[1];
//	tdat[30]=div[7].bx[2];
//	tdat[31]=div[7].bx[3];//200m

//	tdat[32]=div[8].bx[0];
//	tdat[33]=div[8].bx[1];
//	tdat[34]=div[8].bx[2];
//	tdat[35]=div[8].bx[3];//20m

///*	tdat[36]=div[9].bx[0];
//	tdat[37]=div[9].bx[1];
//	tdat[38]=div[9].bx[2];
//	tdat[39]=div[9].bx[3];
//*/
//	tdat[40]=0xa;//atuo
//	tdat[41]=0;//fast
//	tdat[42]=T_FLG;
//	W421=0;
//	for(t=0;t<48;t++)
//		wr421(tdat[t]);

//	W421=SYNC_WADR;
//	syn=SYNC_CMD;
//	R421=syn;

//	W421=SYNC_RADR;
//	do{
//		   t=R421;
//	 }while(t!=(syn));

//	ES=1;
//}
