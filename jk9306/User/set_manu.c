#include "set_manu.h"
#include "lpc177x_8x_gpio.h"
#include "LCD/lpc177x_8x_lcd.h"
#include "use_disp.h"
#include "EX_SDRAM/EX_SDRAM.H"
#include "string.h"
#include "key.h"
#include "Test/test.h"
extern unsigned char KInputF;
char DisULInputNum[10];
char DisILInputNum[10];
char DisADDInputNum[3]={0};

unsigned char CursorP = Clearcur;
struct RDispPara Para_Set[ParaNUM]={
	{20, 30, 6, 0,7,0, "BaudRate:","波特率:"},
	{20, 58, 3, 0,3,0, "Check: ","校验方式:"},
	{20, 86, 3, 0,MAX_ADD,1,"Address:","地址:"},
	{20, 114, 4, 0,1,0, "Filter:","滤波器:"},
	{20, 142, 5, 0,1,0, "IOMode:","接口模式:"},
	{20, 170, 4, 0,1,0, "AutoZero:","归零:"},
  {20, 198, 10, 0,1,0, "Language:","语言:"},
  {20, 226, 10, 0,1,0, "WH:","电能累计:"},
	{250, 30, 4,  0,1,0, "Signal:","测量源:"},
	{250, 58, 10, 0,1,0, "USBMode:","闪存模式:"},
	{250, 86, 4,  0,1,0, "HotKey:","快捷键:"},
	{250, 114, 4, 0,1,0, "Beeper:","按键声:"},
	{250, 142, 6, 0,MAX_PW,0,"PLimit:","功率上限:"},
	{250, 170, 6, 0,MAX_CUR,0,"ILimit:","电流上限:"},
	{250, 198, 6, 0,1,0,"BeepAlm:","报警声:"}
	
};
static char BaudRate[8][7]=
{
	"1200\0",
	"2400\0",
	"4800\0",
	"9600\0",
	"19200\0",
	"38400\0",
	"57600\0",
	"115200\0"
};
static char Check[4][4]=
{
	"8n1\0",
	"8e1\0",
	"8o1\0",
	"8n0\0",
};

static char OFForON_En[2][4]=
{
	"ON\0",
	"OFF\0"
};
static char OFForON_Ch[2][5]=
{
	"开\0",
	"关\0"
};

static char IOMode_En[2][7]=
{
	"RS232\0",
	"USB\0"
};

char USBMode_En[2][7]=
{
	"Host\0",
	"Device\0"
};
static char USBMode_Ch[2][8]=
{
	"主机\0",
	"设备\0"
};
static char Language_En[2][8]=
{
	"CHINESE\0",
	"ENGLISH\0"
};
static char Language_Ch[2][8]=
{
	"中文\0",
	"英文\0"
};
//uint8_t
char SetFDSP= NULLsetMu;//
uint8_t BlankP = BaudRatePnt;//

static void SlectPara( uint8_t ip,uint8_t blank)
{
	char str[10]={0};
	int len = 0;
	switch(ip)
	{
		case BaudRatePnt:
			WriteString_16(Para_Set[0].row+98,Para_Set[0].col,(char *)BaudRate[Para_Set[0].val],0);
		  len = strlen(BaudRate[Para_Set[0].val]);
		  strncpy(str,BaudRate[Para_Set[0].val],len);
			break;
		case CheckPnt:
			WriteString_16(Para_Set[1].row+98,Para_Set[1].col,(char *)Check[Para_Set[1].val],0);
			len = strlen(Check[Para_Set[1].val]);
		  strncpy(str,Check[Para_Set[1].val],len);
			break;
		case AddressPnt:
	  	DisADDInputNum[0] =  ((AddressVal /100));
			DisADDInputNum[1] =  ((AddressVal %100)/10);
			DisADDInputNum[2] =  ((AddressVal %10));
			PutNum(Para_Set[2].row+98,Para_Set[2].col, DisADDInputNum[0], Colour.Fword, Colour.black);
			PutNum(Para_Set[2].row+110,Para_Set[2].col, DisADDInputNum[1], Colour.Fword, Colour.black); 
			PutNum(Para_Set[2].row+122,Para_Set[2].col, DisADDInputNum[2], Colour.Fword, Colour.black); 
		  strncpy(str,DisADDInputNum,3);
			len = 3;
			break;
		case FilterPnt:
			if(flag_SetLang==0)
			{
				WriteString_16(Para_Set[3].row+98, Para_Set[3].col, (char *)OFForON_Ch[Para_Set[3].val],1);
				len = strlen(OFForON_Ch[Para_Set[ip].val]);
				strncpy(str,OFForON_Ch[Para_Set[ip].val],len);
			}
				else
				{
				WriteString_16(Para_Set[3].row+98, Para_Set[3].col, (char *)OFForON_En[Para_Set[3].val],0);
					len = strlen(OFForON_En[Para_Set[ip].val]);
				strncpy(str,OFForON_En[Para_Set[ip].val],len);
				}
			break;

		case IOModePnt:
				WriteString_16(Para_Set[4].row+98, Para_Set[4].col, (char *)IOMode_En[Para_Set[4].val],0);
				len = strlen(IOMode_En[Para_Set[ip].val]);
				strncpy(str,IOMode_En[Para_Set[ip].val],len);
			break;
		case AutoZeroPnt:
		case Wh:
		case PowerPnt:
		case HotKeyPnt:
		case BeeperPnt:
		case BeepPnt:
			if(flag_SetLang==0)
			{WriteString_16(Para_Set[ip].row+98, Para_Set[ip].col, (char *)OFForON_Ch[Para_Set[ip].val],1);
			len = strlen(OFForON_Ch[Para_Set[ip].val]);
				strncpy(str,OFForON_Ch[Para_Set[ip].val],len);
			}
				else
			{WriteString_16(Para_Set[ip].row+98, Para_Set[ip].col, (char *)OFForON_En[Para_Set[ip].val],0);
				len = strlen(OFForON_En[Para_Set[ip].val]);
				strncpy(str,OFForON_En[Para_Set[ip].val],len);
			}
			break;
		case PLimitPnt:
			DisULInputNum[0] =  Para_Set[12].val /10000;
			DisULInputNum[1] =  Para_Set[12].val %10000/1000;
			DisULInputNum[2] =  Para_Set[12].val %1000/100;
			DisULInputNum[3] =  Para_Set[12].val %100/10;
		DisULInputNum[4] =  '.';
			DisULInputNum[5] =  Para_Set[12].val %10;

			PutNum(Para_Set[12].row+98, Para_Set[12].col, DisULInputNum[0], Colour.Fword, Colour.black);
			PutNum(Para_Set[12].row+110, Para_Set[12].col,  DisULInputNum[1], Colour.Fword, Colour.black); 
      PutNum(Para_Set[12].row+122, Para_Set[12].col , DisULInputNum[2], Colour.Fword, Colour.black);
			PutNum(Para_Set[12].row+134, Para_Set[12].col,  DisULInputNum[3], Colour.Fword, Colour.black);
			PutChar(Para_Set[12].row+146, Para_Set[12].col,  DisULInputNum[4], Colour.Fword, Colour.black);

		PutNum(Para_Set[12].row+158, Para_Set[12].col,  DisULInputNum[5], Colour.Fword, Colour.black);
		PutChar(Para_Set[12].row+173, Para_Set[12].col,'W',Colour.Fword, Colour.black);
		len = 6;
			break;
	  case ILimitPnt:
			DisILInputNum[0] =  Para_Set[13].val /10000;
			DisILInputNum[1] =  Para_Set[13].val %10000/1000;
		DisILInputNum[2] =  '.';
			DisILInputNum[3] =  Para_Set[13].val %1000/100;
			DisILInputNum[4] =  Para_Set[13].val %100/10;
			DisILInputNum[5] =  Para_Set[13].val %10;
			PutNum(Para_Set[13].row+98, Para_Set[13].col,DisILInputNum[0],Colour.Fword,Colour.black);
		  PutNum(Para_Set[13].row+110, Para_Set[13].col,DisILInputNum[1],Colour.Fword,Colour.black);
			PutChar(Para_Set[13].row+122, Para_Set[13].col,DisILInputNum[2],Colour.Fword,Colour.black); 
			PutNum(Para_Set[13].row+134, Para_Set[13].col,DisILInputNum[3],Colour.Fword,Colour.black);
			PutNum(Para_Set[13].row+146, Para_Set[13].col,DisILInputNum[4],Colour.Fword,Colour.black);
			PutNum(Para_Set[13].row+158, Para_Set[13].col,DisILInputNum[5],Colour.Fword,Colour.black);
      PutChar(Para_Set[13].row+173, Para_Set[13].col,'A',Colour.Fword,Colour.black);
			len = 6;
			break;

		case USBModePnt:
			if(flag_SetLang==0)
			{
				WriteString_16(Para_Set[ip].row+98, Para_Set[ip].col,(char *)USBMode_Ch[Para_Set[ip].val],1);
				len = strlen(USBMode_Ch[Para_Set[ip].val]);
				strncpy(str,USBMode_Ch[Para_Set[ip].val],len);
			}
			else
			{
				WriteString_16(Para_Set[ip].row+98, Para_Set[ip].col,(char *)USBMode_En[Para_Set[ip].val],0);
				len = strlen(USBMode_En[Para_Set[ip].val]);
				strncpy(str,USBMode_En[Para_Set[ip].val],len);
			}
			break;
		case LanguagePnt:
			if(flag_SetLang==0)
			{
				WriteString_16(Para_Set[6].row+98, Para_Set[6].col,(char *)Language_Ch[Para_Set[6].val],1);
				len = strlen(Language_Ch[Para_Set[6].val]);
				strncpy(str,Language_Ch[Para_Set[6].val],len);
			}
			else
			{
				WriteString_16(Para_Set[6].row+98, Para_Set[6].col,(char *)Language_En[Para_Set[6].val],0);
				len = strlen(Language_En[Para_Set[6].val]);
				strncpy(str,Language_En[Para_Set[6].val],len);
			}
			break;
		default: ip=0;
			break;
	}

	if(len>0&&ip==blank)
	{
		LCD_DrawRect(Para_Set[ip].row+98,Para_Set[ip].col,Para_Set[ip].row+98+Para_Set[ip].len*10,Para_Set[ip].col+16,Colour.black );
		Colour.Fword=Red;
		Colour.black=Blue;//LCD_COLOR_TEST_BACK;
			if(blank==AddressPnt)
			{
					PutNum(Para_Set[2].row+98, Para_Set[2].col, DisADDInputNum[0], Colour.Fword, Colour.black );
					PutNum(Para_Set[2].row+110, Para_Set[2].col,  DisADDInputNum[1], Colour.Fword, Colour.black ); 
					PutNum(Para_Set[2].row+122, Para_Set[2].col,  DisADDInputNum[2], Colour.Fword, Colour.black ); 

				if(TSetInput ==SET)//反显
				 	PutNum(Para_Set[2].row+98+12*(KInputF),Para_Set[2].col,DisADDInputNum[KInputF],Colour.black,Colour.Fword); 
			}
			else if(blank==PLimitPnt)
			{
				PutNum(Para_Set[12].row+98, Para_Set[12].col, DisULInputNum[0], Colour.Fword, Colour.black );
				PutNum(Para_Set[12].row+110, Para_Set[12].col,  DisULInputNum[1], Colour.Fword, Colour.black );
				PutNum( Para_Set[12].row+122, Para_Set[12].col , DisULInputNum[2], Colour.Fword, Colour.black );
				PutNum(Para_Set[12].row+134, Para_Set[12].col,  DisULInputNum[3], Colour.Fword, Colour.black );
				PutChar(Para_Set[12].row+146, Para_Set[12].col,  DisULInputNum[4], Colour.Fword, Colour.black );
				PutNum(Para_Set[12].row+158, Para_Set[12].col,  DisULInputNum[5], Colour.Fword, Colour.black );
		    if(TSetInput ==SET)//反显
					PutNum(Para_Set[12].row+98+12*(KInputF), Para_Set[12].col,DisULInputNum[KInputF],Colour.black,Colour.Fword); 
			}
			else if(blank==ILimitPnt)
			{
				PutNum(Para_Set[13].row+98, Para_Set[13].col, DisILInputNum[0], Colour.Fword, Colour.black );
				PutNum(Para_Set[13].row+110, Para_Set[13].col,  DisILInputNum[1], Colour.Fword, Colour.black );
			  PutChar(Para_Set[13].row+122, Para_Set[13].col , DisILInputNum[2], Colour.Fword, Colour.black );
			  PutNum(Para_Set[13].row+134, Para_Set[13].col,  DisILInputNum[3], Colour.Fword, Colour.black );
				PutNum(Para_Set[13].row+146, Para_Set[13].col,  DisILInputNum[4], Colour.Fword, Colour.black );
				PutNum(Para_Set[13].row+158, Para_Set[13].col,  DisILInputNum[5], Colour.Fword, Colour.black );
				if(TSetInput ==SET)//反显
					PutNum(Para_Set[13].row+98+12*(KInputF),Para_Set[13].col,DisILInputNum[KInputF],Colour.black,Colour.Fword); 
			}
			else if(blank==BaudRatePnt)
				WriteString_16(Para_Set[0].row+98,Para_Set[0].col,(char *)BaudRate[Para_Set[0].val],0);

			else if(blank==CheckPnt)
				WriteString_16(Para_Set[1].row+98,Para_Set[1].col,(char *)Check[Para_Set[1].val],0);

			else if(blank==IOModePnt)
				WriteString_16(Para_Set[4].row+98,Para_Set[4].col,(char *)IOMode_En[Para_Set[4].val],0);		

			else if(blank==USBModePnt)
			{
				if(flag_SetLang==0)  //中文
					WriteString_16(Para_Set[9].row+98,Para_Set[9].col,(char *)USBMode_Ch[Para_Set[8].val],1);

				else
					WriteString_16(Para_Set[9].row+98,Para_Set[9].col,(char *)USBMode_En[Para_Set[8].val],0);
			}
			else if(blank==LanguagePnt)
			{
				if(flag_SetLang==0)  //中文
					WriteString_16(Para_Set[6].row+98,Para_Set[6].col,(char *)Language_Ch[Para_Set[6].val],1);

				else
					WriteString_16(Para_Set[6].row+98,Para_Set[6].col,(char *)Language_En[Para_Set[6].val],0);
			}
			else
			{
				if(flag_SetLang==0)  //中文
		    	WriteString_16(Para_Set[ip].row+98,Para_Set[ip].col,(char *)OFForON_Ch[Para_Set[ip].val],1);

				else
					WriteString_16(Para_Set[ip].row+98,Para_Set[ip].col,(char *)OFForON_En[Para_Set[ip].val],0);
			}
	}
  Colour.Fword=White;
	Colour.black=LCD_COLOR_TEST_BACK;//Black;
}

//mode   0 中间 KEY_Left左移 KEY_Right右移
void DisBlank_set(unsigned char bank,uint8_t mode)
{
		LCD_DrawRect(Para_Set[bank].row+98,Para_Set[bank].col,Para_Set[bank].row+98+Para_Set[bank].len*10,Para_Set[bank].col+16,Colour.black);
		Colour.Fword=Red;
		Colour.black=Blue;//LCD_COLOR_TEST_BACK;//
			if(bank==AddressPnt)
			{
				DisADDInputNum[0] =  AddressVal /100;  
		   	DisADDInputNum[1] =  AddressVal %100/10; 
		   	DisADDInputNum[2] =  AddressVal%10; 
				PutNum(Para_Set[bank].row+98, Para_Set[bank].col, DisADDInputNum[0], Colour.Fword, Colour.black );
				PutNum(Para_Set[bank].row+110, Para_Set[bank].col,  DisADDInputNum[1], Colour.Fword, Colour.black ); 
				PutNum(Para_Set[bank].row+122, Para_Set[bank].col,  DisADDInputNum[2], Colour.Fword, Colour.black ); 
				if(TSetInput ==SET)
				{
					PutNum(Para_Set[bank].row+98+12*(KInputF),Para_Set[bank].col,DisADDInputNum[KInputF],Colour.black,Colour.Fword); 
				  KPADDCursorP =CursorP;
				}
			}
			else if(bank==PLimitPnt)
			{
				  DisULInputNum[0] =  Para_Set[bank].val /10000;
					DisULInputNum[1] =  Para_Set[bank].val %10000 /1000;
					DisULInputNum[2] =  Para_Set[bank].val %1000 /100;
					DisULInputNum[3] =  Para_Set[bank].val %100 /10;
				DisULInputNum[4] =  '.';
					DisULInputNum[5] =  Para_Set[bank].val %10;
					PutNum(Para_Set[bank].row+98, Para_Set[bank].col,DisULInputNum[0], Colour.Fword, Colour.black);
					PutNum(Para_Set[bank].row+110, Para_Set[bank].col,DisULInputNum[1], Colour.Fword, Colour.black); 
          PutNum(Para_Set[bank].row+122, Para_Set[bank].col,DisULInputNum[2], Colour.Fword, Colour.black);
					PutNum(Para_Set[bank].row+134, Para_Set[bank].col,DisULInputNum[3], Colour.Fword, Colour.black);
					PutChar(Para_Set[bank].row+146, Para_Set[bank].col,DisULInputNum[4], Colour.Fword, Colour.black);
					PutNum(Para_Set[bank].row+158, Para_Set[bank].col,DisULInputNum[5], Colour.Fword, Colour.black);
				if(TSetInput ==SET)
				{
					PutNum(Para_Set[bank].row+98+12*(KInputF),Para_Set[bank].col,DisULInputNum[KInputF],Colour.black,Colour.Fword); 
					KPULCursorP =CursorP;
				}
			}
			else if(bank==ILimitPnt)
			{
				DisILInputNum[0] =  Para_Set[bank].val /10000;
				DisILInputNum[1] =  Para_Set[bank].val %10000/1000;
				DisILInputNum[2] =  '.';
				DisILInputNum[3] =  Para_Set[bank].val %1000/100;
				DisILInputNum[4] =  Para_Set[bank].val %100/10;
				DisILInputNum[5] =  Para_Set[bank].val %10;
				PutNum(Para_Set[bank].row+98, Para_Set[bank].col, DisILInputNum[0], Colour.Fword, Colour.black);
		    PutNum(Para_Set[bank].row+110, Para_Set[bank].col, DisILInputNum[1], Colour.Fword, Colour.black);
				PutChar(Para_Set[bank].row+122, Para_Set[bank].col,  DisILInputNum[2], Colour.Fword, Colour.black); 
				PutNum(Para_Set[bank].row+134, Para_Set[bank].col,  DisILInputNum[3], Colour.Fword, Colour.black);
				PutNum(Para_Set[bank].row+146, Para_Set[bank].col,  DisILInputNum[4], Colour.Fword, Colour.black);
				PutNum(Para_Set[bank].row+158, Para_Set[bank].col,  DisILInputNum[5], Colour.Fword, Colour.black);
			  if(TSetInput ==SET)
				{
					PutNum(Para_Set[bank].row+98+12*(KInputF),Para_Set[bank].col,DisILInputNum[KInputF],Colour.black,Colour.Fword); 
					KPILCursorP=CursorP;
				}
			}
			else if(bank==BaudRatePnt){
				Colour.Fword=Blue;
				Colour.black=Red;
				WriteString_16(Para_Set[0].row+98,Para_Set[0].col,(char *)BaudRate[Para_Set[0].val],0);

			}else if(bank==CheckPnt){
				Colour.Fword=Blue;
				Colour.black=Red;
				WriteString_16(Para_Set[1].row+98,Para_Set[1].col,(char *)Check[Para_Set[1].val],0);

			}else if(bank==IOModePnt){
				Colour.Fword=Blue;
				Colour.black=Red;
				WriteString_16(Para_Set[4].row+98,Para_Set[4].col,(char *)IOMode_En[Para_Set[4].val],0);

			}else if(bank==USBModePnt)
			{
				Colour.Fword=Blue;
				Colour.black=Red;
				if(flag_SetLang==0)  //中文
					WriteString_16(Para_Set[9].row+98,Para_Set[9].col,(char *)USBMode_Ch[Para_Set[8].val],1);

				else
					WriteString_16(Para_Set[9].row+98,Para_Set[9].col,(char *)USBMode_En[Para_Set[8].val],0);
			}
			else if(bank==LanguagePnt)
			{
				Colour.Fword=Blue;
				Colour.black=Red;
		/*	if(flag_SetLang==0)  //中文
		    {
					WriteString_16(Para_Set[blank].row+98, Para_Set[blank].col, (uint8_t *)Language_Ch[Para_Set[blank].val],1);
				}
				else
		    {
					WriteString_16(Para_Set[blank].row+98, Para_Set[blank].col, (uint8_t *)Language_En[Para_Set[blank].val],0);
				}
				*/
				Disp_Sys_set();
			}
			else
			{
				Colour.Fword=Blue;
				Colour.black=Red;
				if(flag_SetLang==0)  //中文
					WriteString_16(Para_Set[bank].row+98, Para_Set[bank].col, (char *)OFForON_Ch[Para_Set[bank].val],1);

				else
					WriteString_16(Para_Set[bank].row+98, Para_Set[bank].col, (char *)OFForON_En[Para_Set[bank].val],0);
			}
   Colour.Fword=White;
	 Colour.black=LCD_COLOR_TEST_BACK;//Black;
}
extern void Disp_Box(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint8_t bevel_edge,uint32_t color);
void Disp_Sys_set(void)
{
   uint32_t i;
//	lcd_Clear(LCD_COLOR_TEST_BACK);
  Disp_Box(3,25,478,250,3,Yellow);
  Colour.Fword=White;
		Colour.black=LCD_COLOR_TEST_BACK;//Black;
	if(flag_SetLang==0)
	{
		WriteString_16(0,4,All_TopName[8],1);//中文
		Colour.Fword=White;
		Colour.black=LCD_COLOR_TEST_BACK;//Black;
		Para_Set[0].row =20;
		for(i=0;i<ParaNUM;i++)
			 WriteString_16(Para_Set[i].row, Para_Set[i].col,(char *)Para_Set[i].Ch,1);
	}
	else
	{
		WriteString_16(0,4,All_TopName_E[8],0);//英文
		Colour.Fword=White;
		Colour.black=LCD_COLOR_TEST_BACK;//Black;
		Para_Set[0].row =20;
		for(i=0;i<ParaNUM;i++)
			 WriteString_16(Para_Set[i].row, Para_Set[i].col,(char *)Para_Set[i].En,0);
	}
		for(i=0;i<ParaNUM;i++)
					SlectPara(i,BlankP);
		 
}

