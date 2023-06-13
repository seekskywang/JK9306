/**********************************************************************
* $Id$		debug_frmwrk.c			2011-06-02
*//**
* @file		debug_frmwrk.c
* @brief	Contains some utilities that used for debugging through UART
* @version	1.0
* @date		02. June. 2011
* @author	NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
**********************************************************************/

#include "debug_frmwrk.h"
#include "lpc177x_8x_pinsel.h"
#include "stdarg.h"
//#include "ch421.h"
#include "modbus_slave.h"
#include "set_manu.h"
/* Debug framework */
//const uint8_t READDATA[7]={0xAB,0x01,0x06,0x03,0x08,0xbf,'\0'};
void (*_db_msg)(LPC_UART_TypeDef *UARTx, const void *s);
void (*_db_msg_)(LPC_UART_TypeDef *UARTx, const void *s);
void (*_db_char)(LPC_UART_TypeDef *UARTx, uint8_t ch);
void (*_db_dec)(LPC_UART_TypeDef *UARTx, uint8_t decn);
void (*_db_dec_16)(LPC_UART_TypeDef *UARTx, uint16_t decn);
void (*_db_dec_32)(LPC_UART_TypeDef *UARTx, uint32_t decn);
void (*_db_hex)(LPC_UART_TypeDef *UARTx, uint8_t hexn);
void (*_db_hex_16)(LPC_UART_TypeDef *UARTx, uint16_t hexn);
void (*_db_hex_32)(LPC_UART_TypeDef *UARTx, uint32_t hexn);
void (*_db_hex_)(LPC_UART_TypeDef *UARTx, uint8_t hexn);
void (*_db_hex_16_)(LPC_UART_TypeDef *UARTx, uint16_t hexn);
void (*_db_hex_32_)(LPC_UART_TypeDef *UARTx, uint32_t hexn);

uint8_t (*_db_get_char)(LPC_UART_TypeDef *UARTx);
uint8_t (*_db_get_val)(LPC_UART_TypeDef *UARTx, uint8_t option, uint8_t numCh, uint32_t * val);
Com_TypeDef ComBuf;//串口收发缓冲
Com_TypeDef ComBuf3;
#define MODBAS
/*********************************************************************
 * @brief		Puts a character to UART port
 * @param[in]	UARTx	Pointer to UART peripheral
 * @param[in]	ch		Character to put
 * @return		None
 **********************************************************************/
void UARTPutChar (LPC_UART_TypeDef *UARTx, uint8_t ch)
{
	UART_Send(UARTx, &ch, 1, BLOCKING);
}

/*********************************************************************//**
 * @brief		Get a character to UART port
 * @param[in]	UARTx	Pointer to UART peripheral
 * @return		character value that returned
 **********************************************************************/
uint8_t UARTGetChar (LPC_UART_TypeDef *UARTx)
{
	uint8_t tmp = 0;

	UART_Receive(UARTx, &tmp, 1, BLOCKING);

	return(tmp);
}

/*********************************************************************//**
 * @brief		Get a character to UART port
 * @param[in]	UARTx	Pointer to UART peripheral
 * @return		character value that returned
 **********************************************************************/
uint8_t UARTGetValue (LPC_UART_TypeDef *UARTx, uint8_t option,
												uint8_t numCh, uint32_t* val)
{
	uint8_t tmpCh = 0, cnt, factor, isValidCh = FALSE;
	uint32_t tmpVal, rVal, cntFailed, multiplier;
	//it does not get any value
	if(numCh <= 0)
	{
		*val = 0;
		return 0;
	}

	cntFailed = 0;
	// To store the multiplier of Decimal (10) or Heximal (16)
	factor = (option == DBG_GETVAL_IN_HEX) ? 16 : ((option == DBG_GETVAL_IN_DEC) ? 10 : 0);

	if (factor == 0)
	{
		*val = 0;
		return 0;
	}

	rVal = 0;

	while (numCh > 0)
	{
		isValidCh = TRUE;

		UART_Receive(UARTx, &tmpCh, 1, BLOCKING);

		if((tmpCh >= '0') && (tmpCh<= '9'))
		{
			tmpVal = (uint32_t) (tmpCh - '0');
		}
		else if (option == DBG_GETVAL_IN_HEX)
		{
			factor = 16;

			switch (tmpCh)
			{
				case 'a':
				case 'A':					tmpVal = 10;
					break;

				case 'b':
				case 'B':					tmpVal = 11;
					break;

				case 'c':
				case 'C':					tmpVal = 12;
					break;

				case 'd':
				case 'D':					tmpVal = 13;
					break;

				case 'e':
				case 'E':					tmpVal = 14;

					break;

				case 'f':
				case 'F':					tmpVal = 15;
					break;

				default:					isValidCh = FALSE;
					break;
			}
		}
		else
				isValidCh = FALSE;

		multiplier = 1;

		if(isValidCh == FALSE)
		{
			if(option == DBG_GETVAL_IN_DEC)
			
				UARTPuts(UARTx, "Please enter a char from '0' to '9'!!!\r\n");
			
			else if (option == DBG_GETVAL_IN_HEX)
			
				UARTPuts(UARTx, "Please enter a char from '0' to '9', and 'a/A', 'b/B', c/C', 'd/D', 'e/E' and 'f/F'!!!\r\n");
			

			cntFailed ++;

			if(cntFailed >= NUM_SKIPPED_ALLOWED)
			{
				UARTPuts(UARTx, "Reach limitation of re-tries. Return FAILED\r\n");

				//it's failed, should return
				return 0;
			}
		}
		else
		{
			//Echo the character to the terminal
			UARTPutChar(UARTx, tmpCh);

			if(numCh == 1)
			{
				factor = 1;
				multiplier = 1;
			}
			else
			{
				for(cnt = 1; cnt < numCh; cnt++)
				
					multiplier *= factor;
				
			}
			tmpVal *= multiplier;

			//Update the value return
			rVal += tmpVal;

			numCh --;
		}
	}
	*val = rVal;
	return(1);
}

/*********************************************************************//**
 * @brief		Puts a string to UART port
 * @param[in]	UARTx 	Pointer to UART peripheral
 * @param[in]	str 	string to put
 * @return		None
 **********************************************************************/
void UARTPuts(LPC_UART_TypeDef *UARTx, const void *str)
{
	uint8_t *s = (uint8_t *) str;

	while (*s!=0xa1)
	{
		UARTPutChar(UARTx, *s++);
	}
	//UARTPutChar(UARTx, 0xaf);
}

void uartSendChars(LPC_UART_TypeDef *UARTx,const void *str, uint16_t strlen)
{ 
	  uint16_t k= 0 ; 
	 uint8_t *s = (uint8_t *) str;
   do { 
				UARTPutChar(UARTx,*(s + k));
	      k++; 
	 }while (k < strlen); //循环发送,直到发送完毕  
} 

/*
extern uint8_t r421_rang;
extern void Savetoeeprom(void);
void txdp(uint8_t u)
{}
void to_pcdat(uint8_t comm,uint16_t dat,uint8_t dot,uint8_t dia)
{	uint8_t off[10]={0xab};
	uint16_t dt;
	dt=dat;
	off[1]=comm;
	off[2]=dt/10000;
	if(dot==4)
	{off[3]=0x2e;
	off[4]=dt%10000/1000;
	off[5]=dt%1000/100;
	off[6]=dt%100/10;
	off[7]=dt%10;
	}
	else if(dot==3)
	{
	off[3]=dt%10000/1000;
	off[4]=0x2e;
	off[5]=dt%1000/100;
	off[6]=dt%100/10;
	off[7]=dt%10;
	}
else if(dot==2)
	{
	off[3]=dt%10000/1000;
	off[4]=dt%1000/100;
	off[5]=0x2e;
	off[6]=dt%100/10;
	off[7]=dt%10;
	}
	else if(dot==1)
	{
	off[3]=dt%10000/1000;
	off[4]=dt%1000/100;
	off[5]=dt%100/10;
	off[6]=0x2e;
	off[7]=dt%10;
	}	
	else if(dot==0)
	{
	off[3]=dt%10000/1000;
	off[4]=dt%1000/100;
	off[5]=dt%100/10;
	off[6]=dt%10;
	off[7]=0x20;//0x2e;
	}
	if(dia==1)off[8]=0xa0;
	if(dia==2)off[8]=0xa1;
	if(dia==3)off[8]=0xa2;
	if(dia==4)off[8]=0xa3;
	off[9]=0xaf;
	UARTPuts(LPC_UART3,off);
	}
void to_pcper(uint8_t com,uint16_t dat)
{	uint8_t sbuf[9]={0xab};

	sbuf[1]=com;
sbuf[2]=dat%10000/1000;
sbuf[3]=dat%1000/100;
sbuf[4]=0x2e;
sbuf[5]=dat%100/10;
sbuf[6]=dat%10;
sbuf[7]=0x0;
sbuf[8]=0xaf;
UARTPuts(LPC_UART3,sbuf);
	}
uint16_t enter_chn()
{uint16_t ty;
	if(ComBuf3.rec.buf[8]==0xa0&&ComBuf3.rec.buf[4]==0x2e)
		r421_rang=1;
	else
		r421_rang=2;
		switch(ComBuf3.rec.buf[8])
		{
		case 0xa1:
		if(ComBuf3.rec.buf[3]==0x2e)
			SaveData.Main.range=3;
		else if(ComBuf3.rec.buf[4]==0x2e)
			SaveData.Main.range=4;
		else if(ComBuf3.rec.buf[5]==0x2e)
			SaveData.Main.range=5;
		break;
		case 0xa2:
		if(ComBuf3.rec.buf[3]==0x2e)
			SaveData.Main.range=6;
		else if(ComBuf3.rec.buf[4]==0x2e)
			SaveData.Main.range=7;
		else if(ComBuf3.rec.buf[5]==0x2e)
			SaveData.Main.range=8;
		break;
		case 0xa3:SaveData.Main.range=9;
		break;
		}
	ty=ComBuf3.rec.buf[2]*10000+10*ComBuf3.rec.buf[6]+ComBuf3.rec.buf[7];
		if(ComBuf3.rec.buf[3]==0x2e)
		ty=ty+ComBuf3.rec.buf[4]*1000+100*ComBuf3.rec.buf[5];
		if(ComBuf3.rec.buf[4]==0x2e)
		ty=ty+ComBuf3.rec.buf[3]*1000+100*ComBuf3.rec.buf[5];
		if(ComBuf3.rec.buf[5]==0x2e)
		ty=ty+ComBuf3.rec.buf[3]*1000+100*ComBuf3.rec.buf[4];
	return ty;
		}
void do232()
	{uint8_t buf[11];
//	ok232=0;
		switch(ComBuf3.rec.buf[1])
		{
//1接收是否单次标志
		case 0x9d://tstf=PEOM=PPS=PLO=PHI=1;
	//		HI_OFF
	//LO_OFF
	//PASS_OFF
	//D1_L
	//	auto_f=0;flgs.extt=1;
	break;
//2接收是否初始化标志
		case 0xAD:
//	if(clear)
		buf[2]=0x55;//1清开
//	else
	//	ComBuf3.rec.buf[2]=0x5a;
	if(SaveData.Main.mode)	buf[3]=0x55;//2分选
	else		buf[3]=0x5a;
	if(SaveData.Main.beep)	buf[4]=0x55;//3响
	else		buf[4]=0x5a;
	if(SaveData.Main.param)	buf[5]=0x5a;//4百分比
	else		buf[5]=0x55;
	if(SaveData.Main.speed)	buf[6]=0x55;
	else		buf[6]=0x5a;//5慢速
	if(SaveData.Main.range==0xa)	buf[7]=0x55;//6自动
	else		buf[7]=0x5a;
	if(SaveData.Main.trig)	buf[8]=0x55;//7内出发
	else		buf[8]=0x5a;
//状态6
	buf[0]=0xab;
		buf[1]=0xac;
		buf[9]=0x0;
		buf[10]=0xaf;
	UARTPuts(LPC_UART3, buf);	
//上限1
	to_pcdat(0xea,SaveData.Limit.Hi[0].Num,SaveData.Limit.Hi[0].Dot,SaveData.Limit.Hi[0].Unit);
//下限2
	to_pcdat(0xeb,SaveData.Limit.Low[0].Num,SaveData.Limit.Low[0].Dot,SaveData.Limit.Low[0].Unit);
//电阻3
	to_pcdat(0xec,SaveData.Limit.Hi[0].Num-30,SaveData.Limit.Hi[0].Dot,SaveData.Limit.Hi[0].Unit);
//上限%4
	to_pcper(0xed,110);
//下限%5
	to_pcper(0xef,80);
	break;
//3接收是否清零标志
		case 0xD9:
//		if(ComBuf3.rec.buf[2]==0x55)
//		SaveData.Main.clear=1;//开清零
//		if(ComBuf3.rec.buf[2]==0x5a)
//		SaveData.Main.clear=0;//关
	break;
//4接收是否分选标志
		case 0xDA:
		if(ComBuf3.rec.buf[2]==0x55)SaveData.Main.compar=1;//开
		if(ComBuf3.rec.buf[2]==0x5a)SaveData.Main.compar=0;//关
	break;
//5接收是否讯响标志
		case 0xDB:
		if(ComBuf3.rec.buf[2]==0x55)SaveData.Main.beep=1;//开
		if(ComBuf3.rec.buf[2]==0x5a)SaveData.Main.beep=0;//关
		//if(bep_f)
		///w_txt(0xb8,1,16,1,tab_bep);
	//else
		{//w_dat(0xb8,1,16,1,0);
	//	beepp=0;
		}
	break;
//6接收是否触发标志
		case  0xDC:
		if(ComBuf3.rec.buf[2]==0x55)
			;
	//	{xtrig=1;chn=compar_chn;}
	//	if(ComBuf3.rec.buf[2]==0x5a)xtrig=0;//?
	//	ch_new=1;
	break;
//7接收是否方式标志
		case  0xDd:
	//	if(ComBuf3.rec.buf[2]==0x55)SaveData.Main.range=5;
	//	if(ComBuf3.rec.buf[2]==0x5a)SaveData.Main.range=0xa;
	break;
//8接收是否速度标志
		case  0xDE:
	//	if(ComBuf3.rec.buf[2]==0x55)SaveData.Main.speed=0;//快
	//	if(ComBuf3.rec.buf[2]==0x5a)SaveData.Main.speed=2;//慢
	break;
//9接收是否自动标志
		case  0xDf:
//		if(ComBuf3.rec.buf[2]==0x55)SaveData.Main.param=0;//r
//		if(ComBuf3.rec.buf[2]==0x5a)SaveData.Main.param=1;//%
	break;
//10接收是否设置上限标志
		case  0xEA://high=enter_chn();
	break;
//11接收是否设置下限标志
		case  0xEB://low=enter_chn();
	break;
//12接收是否设置标称值
		case  0xEC://rxx=enter_chn();
	break;
//13接收%设置上限
		case  0xED://per_h=ComBuf3.rec.buf[2]*1000+ComBuf3.rec.buf[3]*100+ComBuf3.rec.buf[5]*10+ComBuf3.rec.buf[6];
	break;
//14接收%设置下限
		case  0xEF://per_w=ComBuf3.rec.buf[2]*1000+ComBuf3.rec.buf[3]*100+ComBuf3.rec.buf[5]*10+ComBuf3.rec.buf[6];
	break;
		}
	if(ComBuf3.rec.buf[1]>0xe9||(ComBuf3.rec.buf[1]>0xd8&&ComBuf3.rec.buf[1]<0xe0))
	{	//Delay(30000);
	//	sav_set();
		Savetoeeprom();
		}
}*/
/*********************************************************************//**
 * @brief		Puts a string to UART port and print new line
 * @param[in]	UARTx	Pointer to UART peripheral
 * @param[in]	str		String to put
 * @return		None
 **********************************************************************/
void UARTPuts_(LPC_UART_TypeDef *UARTx, const void *str)
{
	UARTPuts (UARTx, str);
	UARTPuts (UARTx, "\n\r");
}

/*********************************************************************//**
 * @brief		Puts a decimal number to UART port
 * @param[in]	UARTx	Pointer to UART peripheral
 * @param[in]	decnum	Decimal number (8-bit long)
 * @return		None
 **********************************************************************/
void UARTPutDec(LPC_UART_TypeDef *UARTx, uint8_t decnum)
{
	uint8_t c1=decnum%10;
	uint8_t c2=(decnum/10)%10;
	uint8_t c3=(decnum/100)%10;
	UARTPutChar(UARTx, '0'+c3);
	UARTPutChar(UARTx, '0'+c2);
	UARTPutChar(UARTx, '0'+c1);
}

/*********************************************************************//**
 * @brief		Puts a decimal number to UART port
 * @param[in]	UARTx	Pointer to UART peripheral
 * @param[in]	decnum	Decimal number (8-bit long)
 * @return		None
 **********************************************************************/
void UARTPutDec16(LPC_UART_TypeDef *UARTx, uint16_t decnum)
{
	uint8_t c1=decnum%10;
	uint8_t c2=(decnum/10)%10;
	uint8_t c3=(decnum/100)%10;
	uint8_t c4=(decnum/1000)%10;
	uint8_t c5=(decnum/10000)%10;
	UARTPutChar(UARTx, '0'+c5);
	UARTPutChar(UARTx, '0'+c4);
	UARTPutChar(UARTx, '0'+c3);
	UARTPutChar(UARTx, '0'+c2);
	UARTPutChar(UARTx, '0'+c1);
}

/*********************************************************************//**
 * @brief		Puts a decimal number to UART port
 * @param[in]	UARTx	Pointer to UART peripheral
 * @param[in]	decnum	Decimal number (8-bit long)
 * @return		None
 **********************************************************************/
void UARTPutDec32(LPC_UART_TypeDef *UARTx, uint32_t decnum)
{
	uint8_t c1=decnum%10;
	uint8_t c2=(decnum/10)%10;
	uint8_t c3=(decnum/100)%10;
	uint8_t c4=(decnum/1000)%10;
	uint8_t c5=(decnum/10000)%10;
	uint8_t c6=(decnum/100000)%10;
	uint8_t c7=(decnum/1000000)%10;
	uint8_t c8=(decnum/10000000)%10;
	uint8_t c9=(decnum/100000000)%10;
	uint8_t c10=(decnum/100000000)%10;
	UARTPutChar(UARTx, '0'+c10);
	UARTPutChar(UARTx, '0'+c9);
	UARTPutChar(UARTx, '0'+c8);
	UARTPutChar(UARTx, '0'+c7);
	UARTPutChar(UARTx, '0'+c6);
	UARTPutChar(UARTx, '0'+c5);
	UARTPutChar(UARTx, '0'+c4);
	UARTPutChar(UARTx, '0'+c3);
	UARTPutChar(UARTx, '0'+c2);
	UARTPutChar(UARTx, '0'+c1);
}

/*********************************************************************//**
 * @brief		Puts a hex number to UART port
 * @param[in]	UARTx	Pointer to UART peripheral
 * @param[in]	hexnum	Hex number (8-bit long)
 * @return		None
 **********************************************************************/
void UARTPutHex_ (LPC_UART_TypeDef *UARTx, uint8_t hexnum)
{
	uint8_t nibble, i;

	i = 1;
	do
	{
		nibble = (hexnum >> (4*i)) & 0x0F;

		UARTPutChar(UARTx, (nibble > 9) ? ('A' + nibble - 10) : ('0' + nibble));
	}
	while (i--);
}


/*********************************************************************//**
 * @brief		Puts a hex number to UART port
 * @param[in]	UARTx	Pointer to UART peripheral
 * @param[in]	hexnum	Hex number (8-bit long)
 * @return		None
 **********************************************************************/
void UARTPutHex (LPC_UART_TypeDef *UARTx, uint8_t hexnum)
{
	uint8_t nibble, i;

	UARTPuts(UARTx, "0x");

	i = 1;
	do {
		nibble = (hexnum >> (4*i)) & 0x0F;
		UARTPutChar(UARTx, (nibble > 9) ? ('A' + nibble - 10) : ('0' + nibble));
	} while (i--);
}


/*********************************************************************//**
 * @brief		Puts a hex number to UART port
 * @param[in]	UARTx	Pointer to UART peripheral
 * @param[in]	hexnum	Hex number (16-bit long)
 * @return		None
 **********************************************************************/
void UARTPutHex16_ (LPC_UART_TypeDef *UARTx, uint16_t hexnum)
{
	uint8_t nibble, i;

	i = 3;
	do
	{
		nibble = (hexnum >> (4*i)) & 0x0F;

		UARTPutChar(UARTx, (nibble > 9) ? ('A' + nibble - 10) : ('0' + nibble));
	}
	while (i--);
}

/*********************************************************************//**
 * @brief		Puts a hex number to UART port
 * @param[in]	UARTx	Pointer to UART peripheral
 * @param[in]	hexnum	Hex number (16-bit long)
 * @return		None
 **********************************************************************/
void UARTPutHex16 (LPC_UART_TypeDef *UARTx, uint16_t hexnum)
{
	uint8_t nibble, i;

	UARTPuts(UARTx, "0x");

	i = 3;
	do
	{
		nibble = (hexnum >> (4*i)) & 0x0F;

		UARTPutChar(UARTx, (nibble > 9) ? ('A' + nibble - 10) : ('0' + nibble));
	}
	while (i--);
}

/*********************************************************************//**
 * @brief		Puts a hex number to UART port
 * @param[in]	UARTx	Pointer to UART peripheral
 * @param[in]	hexnum	Hex number (32-bit long)
 * @return		None
 **********************************************************************/
void UARTPutHex32_ (LPC_UART_TypeDef *UARTx, uint32_t hexnum)
{
	uint8_t nibble, i;

	i = 7;
	do
	{
		nibble = (hexnum >> (4*i)) & 0x0F;

		UARTPutChar(UARTx, (nibble > 9) ? ('A' + nibble - 10) : ('0' + nibble));
	}
	while (i--);
}


/*********************************************************************//**
 * @brief		Puts a hex number to UART port
 * @param[in]	UARTx	Pointer to UART peripheral
 * @param[in]	hexnum	Hex number (32-bit long)
 * @return		None
 **********************************************************************/
void UARTPutHex32 (LPC_UART_TypeDef *UARTx, uint32_t hexnum)
{
	uint8_t nibble, i;

	UARTPuts(UARTx, "0x");

	i = 7;
	do
	{
		nibble = (hexnum >> (4*i)) & 0x0F;

		UARTPutChar(UARTx, (nibble > 9) ? ('A' + nibble - 10) : ('0' + nibble));
	}
	while (i--);
}

/*********************************************************************//**
 * @brief		print function that supports format as same as printf()
 * 				function of <stdio.h> library
 * @param[in]	None
 * @return		None
 **********************************************************************/
void  _printf (const  char *format, ...)
{
    static  char  buffer[512 + 1];
 //           va_list     vArgs;
  //          char	*tmp;
//    va_start(vArgs, format);
//    vsprintf((char *)buffer, (char const *)format, vArgs);
//    va_end(vArgs);

    _DBG(buffer);
}

/*********************************************************************//**
 * @brief		Initialize Debug frame work through initializing UART port
 * @param[in]	None
 * @return		None
 **********************************************************************/
void debug_frmwrk_init(void)
{
	UART_CFG_Type UARTConfigStruct;

#if (USED_UART_DEBUG_PORT == 0)
	/*
	 * Initialize UART0 pin connect
	 * P0.2: TXD
	 * P0.3: RXD
	 */
	PINSEL_ConfigPin (0, 2, 1);
	PINSEL_ConfigPin (0, 3, 1);
#elif (USED_UART_DEBUG_PORT == 1)
	/*
	 * Initialize UART1 pin connect
	 * P2.0: TXD
	 * P2.1: RXD
	 */
	//PINSEL_ConfigPin(2, 0, 2);
	//PINSEL_ConfigPin(2, 1, 2);
#elif (USED_UART_DEBUG_PORT == 2)
	/*
	 * Initialize UART2 pin connect
	 * P0.10: TXD
	 * P0.11: RXD
	 */
//	PINSEL_ConfigPin(0, 10, 1);
//	PINSEL_ConfigPin(0, 11, 1);
#elif (USED_UART_DEBUG_PORT == 3)
	/*
	 * Initialize UART3 pin connect
	 * P0.2: TXD
	 * P0.3: RXD
	 */
	PINSEL_ConfigPin(0, 2, 2);
	PINSEL_ConfigPin(0, 3, 2);
#elif (USED_UART_DEBUG_PORT == 4)
	/*
	 * Initialize UART4 pin connect
	 * P0.22: TXD
	 * P2.9: RXD
	 */
	PINSEL_ConfigPin(0, 22, 3);
	PINSEL_ConfigPin(2, 9, 3);

#endif

	/* Initialize UART Configuration parameter structure to default state:
	 * Baudrate = 9600bps
	 * 8 data bit
	 * 1 Stop bit
	 * None parity
	 */
	UART_ConfigStructInit(&UARTConfigStruct);
	// Re-configure baudrate to 115200bps
	UARTConfigStruct.Baud_rate = 115200;
//	UARTConfigStruct.Baud_rate = 9600;
	// Initialize DEBUG_UART_PORT peripheral with given to corresponding parameter
	UART_Init(DEBUG_UART_PORT, &UARTConfigStruct);//|UART_INTCFG_THRE
	UART_IntConfig(LPC_UART0,UART_INTCFG_RBR,ENABLE);
	//NVIC_SetPriority(UART0_IRQn, ((0x01<<3)|0x01));//??UART2?????
	 NVIC_EnableIRQ(UART0_IRQn);
	// Enable UART Transmit
	UART_TxCmd(DEBUG_UART_PORT, ENABLE);

	_db_msg	= UARTPuts;
	_db_msg_ = UARTPuts_;
	_db_char = UARTPutChar;
	_db_hex = UARTPutHex;
	_db_hex_16 = UARTPutHex16;
	_db_hex_32 = UARTPutHex32;
	_db_hex_ = UARTPutHex_;
	_db_hex_16_ = UARTPutHex16_;
	_db_hex_32_ = UARTPutHex32_;
	_db_dec = UARTPutDec;
	_db_dec_16 = UARTPutDec16;
	_db_dec_32 = UARTPutDec32;
	_db_get_char = UARTGetChar;
	_db_get_val = UARTGetValue;
}
//==========================================================
//函数名称：Uart0RecTimeOut
//函数功能：串口0接收超时判别
//入口参数：无
//出口参数：无
//创建日期：2014.04.07
//修改日期：2014.04.07
//备注说明：需要在系统时基10mS定时中调用
//==========================================================
void Uart0RecTimeOut(void)
{
	if (ComBuf.rec.TimeOut)//串口接收超时计时
	
		ComBuf.rec.TimeOut--;

	else//接收超时，结束当前帧
	{
		if (ComBuf.rec.ptr)//当前接收指针不为空
		{
			ComBuf.rec.end=TRUE;//数据接收结束
			ComBuf.rec.len=ComBuf.rec.ptr;//接收数据缓冲长度
			ComBuf.rec.ptr=0;
		}
	}
}
/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************//**
 * @brief		UART0 interrupt handler sub-routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/

uint8_t r_byte;
void UART0_IRQHandler(void)//UART0_IRQn
//void UART0_IRQn(void)
{
//	 USART_ClearFlag(DEBUG_UART_PORT,USART_FLAG_TC);
	 uint8_t dat;//Statu,
	 dat=UART_GetLineStatus(LPC_UART0);//DEBUG_UART_PORT

	dat=UART_ReceiveByte(LPC_UART0);

	if (!ComBuf.rec.end)//接收没结束
		{ComBuf.rec.ptr++;
	//		SetRecTimeOut(REC_TIME_OUT);//设置接收超时周期
			if(ComBuf.rec.ptr==1)//帧头=aa
			{//if(ComBuf.rec.ptr!=0) //首字节
				#ifdef MODBAS
				if(dat==0x01)
				#else
				if(dat==0xaa)//(uint8_t)(UART_REC_BEGIN))
				#endif
				ComBuf.rec.buf[0]=dat;
					else
					ComBuf.rec.ptr=0;//重新接收
			}
			else if (ComBuf.rec.ptr==2)//帧尾
			{
				#ifdef MODBAS
				if(dat==3)
				#else
				if(dat==1)
					#endif
					ComBuf.rec.buf[1]=dat;
				else
				{
					ComBuf.rec.end=0;//TRUE;//接收结束
					//ComBuf.rec.len=ComBuf.rec.ptr;//存接收数据长度
					ComBuf.rec.ptr=0;//指针清零重新开始新的一帧接收
				//	ComBuf.rec.TimeOut=0;//接收超时清零
				}	
			}
			else if(ComBuf.rec.ptr==3)
			{
//				#ifdef MODBAS
//				if(dat==4 || dat==16 || dat==0x2a)
//				#else
//				if(dat==17)
//				#endif
//				ComBuf.rec.buf[2]=dat;
//				
//			else		ComBuf.rec.ptr=0;//指针清零重新开始新的一帧接收
//				if(dat==4)r_byte=6;
//				else if(dat==16)r_byte=18;
//				else if(dat==0x2a)r_byte=0x2a+2;
				r_byte = dat + 2;
			}
			else if(ComBuf.rec.ptr>3)
			{
				#ifdef MODBAS
				r_byte--;
				ComBuf.rec.buf[ComBuf.rec.ptr-1]=dat;
				if(r_byte==0)
				{
					ComBuf.rec.ptr=0;//重新接收
					ComBuf.rec.end=TRUE;//接收结束
				}
				#else
				ComBuf.rec.buf[ComBuf.rec.ptr-1]=dat;
				if (ComBuf.rec.ptr>=24)//最大接收帧长度
					{//ComBuf.rec.buf[ComBuf.rec.ptr-1]=dat;//ComBuf.rec.ptr;
						ComBuf.rec.ptr=0;//重新接收
					ComBuf.rec.end=TRUE;//接收结束
					}
				//else// if(ComBuf.rec.ptr<24)
					//ComBuf.rec.ptr;//dat;//
				#endif
			}
		}
}

void  debug_uart0_init(uint32_t freq)
{
	UART_CFG_Type UARTConfigStruct;
//	uint32_t data;
	PINSEL_ConfigPin(0, 2, 1);
	PINSEL_ConfigPin(0, 3, 1);

	UART_ConfigStructInit(&UARTConfigStruct);
/*	switch(freq)
	{
		case 0:
			data=2400;
		break;
		case 1:
			data=4800;
		break;
		case 2:
			data=9600;
		break;
		case 3:
			data=14400;
			break;
		case 4:
			data=19200;
		break;
		default :
			data=9600;
		break;
	}*/
	//UARTConfigStruct.Baud_rate = freq;//data;

//	UART_ConfigStructInit(&UARTConfigStruct);
	//UART_InitStruct.Baud_rate =freq;
	UARTConfigStruct.Baud_rate = freq;//9600
	UARTConfigStruct.Databits = UART_DATABIT_8;
	UARTConfigStruct.Stopbits = UART_STOPBIT_1;
	UART_Init(LPC_UART0, &UARTConfigStruct);//|UART_INTCFG_THRE
	UART_IntConfig(LPC_UART0,UART_INTCFG_RBR,ENABLE);
	//NVIC_SetPriority(UART0_IRQn, ((0x01<<3)|0x01));//??UART2?????
	 NVIC_EnableIRQ(UART0_IRQn);
	// Enable UART Transmit
	UART_TxCmd(LPC_UART0, ENABLE);
}

void debug_uart3_init(uint32_t freq)
{
	UART_CFG_Type UARTConfigStruct;
	uint32_t data;

	/*
	 * Initialize UART3 pin connect
	 * P0.0: TXD
	 * P0.1: RXD
	 */
	PINSEL_ConfigPin(0, 0, 2);
	PINSEL_ConfigPin(0, 1, 2);



	/* Initialize UART Configuration parameter structure to default state:
	 * Baudrate = 9600bps
	 * 8 data bit
	 * 1 Stop bit
	 * None parity
	 */
	UART_ConfigStructInit(&UARTConfigStruct);
	// Re-configure baudrate to 115200bps
	switch(freq)
	{
		case 0:
			data=2400;
		break;
		case 1:
			data=4800;
		break;
		case 2:
			data=9600;
		break;
		case 3:
			data=14400;
		break;
		case 4:
			data=19200;
		break ;
		default:
			data=9600;
		break ;
	
	
	}
	UARTConfigStruct.Baud_rate = data;

	// Initialize DEBUG_UART_PORT peripheral with given to corresponding parameter
	UART_Init(LPC_UART3, &UARTConfigStruct);//|UART_INTCFG_THRE
	UART_IntConfig(LPC_UART3,UART_INTCFG_RBR,ENABLE);
//	NVIC_SetPriority(UART3_IRQn, ((0x01<<3)|0x02));//??UART2?????
	 NVIC_EnableIRQ(UART3_IRQn);
	// Enable UART Transmit
	UART_TxCmd(LPC_UART3, ENABLE);

	
}

void UART3_IRQHandler(void)
{
  uint8_t Statu,dat;
//    uint8_t *rxbuf;
  dat=UART_GetLineStatus(LPC_UART3);//DEBUG_UART_PORT
	dat=UART_ReceiveByte(LPC_UART3);
	if (!ComBuf3.rec.end)//接收没结束
	{
		ComBuf.rec.ptr++;
		if(ComBuf.rec.ptr == AddressVal)
		{
//			dat=Statu;
//			MODS_ReciveNew(dat);              // ModBus Recive function
		}
	}
}
//==========================================================
//函数名称：SendDataToCom
//函数功能：发送串口数据
//入口参数：无
//出口参数：True(发送)/False
//创建日期：2014.04.08 
//修改日期：2014.04.08 12:50
//备注说明：按串口发送结构表处理
//==========================================================
//bool SendDataToCom(void)
//{
//	if ((!ComBuf.send.begin)&&ComBuf.send.len)//有数据且发送没开始
//		{
//			ComBuf.send.begin=TRUE;//置发送忙标志
//			ComBuf.send.ptr=0;//当前指针清零
//			SBUF=ComBuf.send.buf[ComBuf.send.ptr++];//启动发送
//			return (1);
//		}
//	return (0);
//}

