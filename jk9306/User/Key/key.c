#include "Key/key.h"
#include "lpc177x_8x_gpio.h"
#include "LCD/lpc177x_8x_lcd.h"
//#include "Globalvalue/GlobalValue.h"
#include "EX_SDRAM/EX_SDRAM.H"
#include "use_disp.h"
void GPIO_Key_Configuration(void)
{
	GPIO_SetDir(1, (1<<10), GPIO_DIRECTION_OUTPUT);//74LS164的数据端		//1--10
	GPIO_SetDir(1, (1<<1), GPIO_DIRECTION_OUTPUT);//74LS164的cp			//1--1

	GPIO_SetDir(0, (1<<24), GPIO_DIRECTION_INPUT);//24
//	GPIO_SetDir(2, (1<<27), GPIO_DIRECTION_INPUT);
	GPIO_SetDir(0, (1<<25), GPIO_DIRECTION_INPUT);
	
	GPIO_SetDir(2,(1<<26),GPIO_DIRECTION_OUTPUT);//D1
	GPIO_SetDir(1,(1),GPIO_DIRECTION_OUTPUT);//D2
}

void k_164Delaay(void)
{
	uint8_t i;
	for(i=0;i<6;i--)
	;
}
void HW_Sendvalueto164(u8 value)
{
	uint8_t i,v;
	Hc164CpL;
	v=value;
	for(i=0;i<8;i++)
	{
		if((v&0x80)==0x80)		Hc164DH;
		else			Hc164DL;
		Hc164CpH;
		k_164Delaay();
		Hc164CpL;
		k_164Delaay();
		v<<=1;
	}
}
void HW_keyInt(void)
{
	GPIO_Key_Configuration();
	HW_Sendvalueto164(0xff);
}
void dyk()
{
uint8_t k;
	for(k=0;k<50;k++)
	;
}
const uint8_t  Scan_Value[]={0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
u8 HW_KeyScsn(void)//0x7f,0xbf,
{
		uint8_t  row,i;//,sw[4]={0};
	uint8_t key_value=0xff;
	uint8_t value=0xff;

	HW_Sendvalueto164(0);

row=2;
	dyk();//p0.25
		if(!(GPIO_ReadValue(0) & (1<<25)))
		row=0;
		if(!(GPIO_ReadValue(0) & (1<<24)))
		row=1;

	if(row<2)
	{//BUZZER();
		for(i=0;i<6;i++)
		{GPIO_ClearValue(1, (1<<9));
			HW_Sendvalueto164(Scan_Value[i]);
			GPIO_SetValue(1, (1<<9));
			dyk();

			switch(row)
			{//p0.25
				case 0:
				if(!(GPIO_ReadValue(0) & (1<<25)))		
				value=i;
					break;
				case 1://p0.24
					if(!(GPIO_ReadValue(0)&(1<<24)))
							value=i;
					break;
			}
		if(value!=0xff)
			break;
		}
		key_value=row*8+value;
	}
	return key_value;
}
void Delay_Key(void)
{
	uint8_t key;
	do{		key=HW_KeyScsn();
	}while(key!=0xff);
	do{		key=HW_KeyScsn();
	}while(key!=0xff);
}

void BUZZER(void)
{
	GPIO_SetDir(0, (1<<12), GPIO_DIRECTION_OUTPUT);	
//	Delay(0xf);
	GPIO_SetValue(0, (1<<12));
	Delay(0x8);
	GPIO_ClearValue(0, (1<<12));
}

#define DIS_TEST	0
#define COMP_SYS	1
#define TOOL_TEST	2
#define FILE_TEST	3
#define PAR_TEST	4
#define RANG_TEST	5
#define SPED_TEST	6
#define TRIG_TEST	7

#define ADJ0_CAL	18
#define ADJ0_KEY	28

Button_Page_Typedef Button_Page;
extern void Page_Polygon_Box(void);
extern void Disp_Box(uint16_t x1,uint16_t y1,uint16_t x2, uint16_t y2, uint8_t bevel_edge, uint32_t color);
//extern void Disp_Comp(void);
extern void Disp_Test(void);
extern void Input_Bar(void);

extern const uint8_t Disp_Unit[][3];
/*
void key_enter_pro()
{
switch(Button_Page.index)
{
	case DIS_TEST://显示上1
	if(Button_Page.row)
	Button_Page.test=Button_Page.row-1;//COMP_TEST;
	lcd_Clear(LCD_COLOR_TURQUOISE);
	if(Button_Page.row==1)
	SaveData.Main.mode=0;//Button_Page.test&&

	if(Button_Page.row==2)
	SaveData.Main.mode=1;//Button_Page.test&&

	if(Button_Page.row==3)
	SaveData.Main.beep=!SaveData.Main.beep;
	Disp_Test();
	Button_Page.row=0;
	Saveeeprom.Save_Main.mode=SaveData.Main.mode;
	Savetoeeprom();
		break;
	case COMP_SYS://显示上2
		Button_Page.page=2;//TOOL_TEST;
	if(SaveData.Main.mode)
	{
	if(Button_Page.row==1)//挍准
	{Button_Page.index=ADJ0_CAL;
	Button_Page.page=ADJ0_CAL;
		Button_Page.third=1;
		Button_Page.test=1;
		lcd_Clear(LCD_COLOR_TURQUOISE);
//		R_ADJ_Pro();
	}
	}
		break;
	case ADJ0_CAL:
	if(Button_Page.third==6)	//key=92518
	{
	if(Button_Page.key==92518)//key ok
		{	Button_Page.third=10;
		lcd_Clear(LCD_COLOR_TURQUOISE);
	//		R_ADJ_Pro();
		Button_Page.test=2;//input val
	}
//	if(Button_Page.key==92000)//float ok
//	{	Button_Page.third=10;
//		lcd_Clear(LCD_COLOR_TURQUOISE);
//			R_flot();
//		Button_Page.test=38;//input val
//	}
	}
if(Button_Page.third==17)//endDIS_TEST
{Button_Page.page=0;Button_Page.index=DIS_TEST;
	Saveeeprom.div[0].ax=SaveData.div[0].ax;
	Saveeeprom.div[1].ax=SaveData.div[1].ax;
	Saveeeprom.div[2].ax=SaveData.div[2].ax;
	Saveeeprom.div[3].ax=SaveData.div[3].ax;
	Saveeeprom.div[4].ax=SaveData.div[4].ax;
	Saveeeprom.div[5].ax=SaveData.div[5].ax;
	Saveeeprom.div[6].ax=SaveData.div[6].ax;
	Saveeeprom.div[7].ax=SaveData.div[7].ax;
	Saveeeprom.div[8].ax=SaveData.div[8].ax;
	Saveeeprom.div[9].ax=SaveData.div[9].ax;
	Savetoeeprom();
	lcd_Clear(LCD_COLOR_TURQUOISE);
}
	break;
	case TOOL_TEST:
		Button_Page.page=FILE_TEST;
		break;
	case FILE_TEST:
		Button_Page.page=DIS_TEST;
		break;
	case PAR_TEST:
		if(SaveData.Main.mode)
		{
			if(Button_Page.row==1)			SaveData.Main.compar=0;
			if(Button_Page.row==2)			SaveData.Main.compar=1;
		Savetoeeprom();}
		break;
	case RANG_TEST:
		if(!SaveData.Main.mode)
		{
		if(Button_Page.row==1)
		{SaveData.Main.range=10;
		SaveData.Main.lock=0;
		}
		if(Button_Page.row==2)
		{if(SaveData.Main.range<10)
			{SaveData.Main.lock=1;
			SaveData.Main.lockrang=SaveData.Main.range;
			}
		}
		if(Button_Page.row==3)
		{SaveData.Main.range++;
			if(SaveData.Main.range==9)
				SaveData.Main.range=10;
		if(SaveData.Main.range>10)
			SaveData.Main.range=2;//2
		}
		
		if(Button_Page.row==4)
		{SaveData.Main.range--;
			if(SaveData.Main.range==9)
				SaveData.Main.range=8;
		if(SaveData.Main.range<2)//<2
			SaveData.Main.range=10;
		}
		Saveeeprom.Save_Main.lockrang=SaveData.Main.lockrang;
		Saveeeprom.Save_Main.lock=SaveData.Main.lock;
		Saveeeprom.Save_Main.range=SaveData.Main.range;
		Savetoeeprom();
		}
		break;
	case SPED_TEST://hi
	if(SaveData.Main.mode)
	{
if(Button_Page.sumkey==19||Button_Page.sumkey==4)//enter key/\Esc
			{
				Button_Page.index=Button_Page.page=DIS_TEST;
			if(Button_Page.sumkey==19)//Enter
			{ SaveData.Limit.Hi[0].Num=Set_CompareMenu.Toplimt.Num;
				if(Set_CompareMenu.Toplimt.Dot)
				SaveData.Limit.Hi[0].Dot=Set_CompareMenu.Toplimt.Wei-Set_CompareMenu.Toplimt.Dot;
				else
					SaveData.Limit.Hi[0].Dot=0;
				SaveData.Limit.Hi[0].Unit=Set_CompareMenu.Toplimt.Unit;
			
				Savetoeeprom();
			}
			}
if(Button_Page.sumkey==18&&Set_CompareMenu.Toplimt.Dotp)//.
{Set_CompareMenu.Toplimt.Dotp=0;
	Set_CompareMenu.Toplimt.Wei++;
Set_CompareMenu.Toplimt.Dot=Set_CompareMenu.Toplimt.Wei;
	DispBuf[0]='.';
}
if(Button_Page.sumkey==17)//"0"
{DispBuf[0]='0'+0;
Set_CompareMenu.Toplimt.Num*=10;
Set_CompareMenu.Toplimt.Wei++;
}
if(Button_Page.sumkey==4)//Esc
		{
		lcd_Clear(LCD_COLOR_TURQUOISE);
				Button_Page.page=DIS_TEST;
				Button_Page.index=0;
		}
if(Button_Page.sumkey==9)//BackSpace
		{
			if(Set_CompareMenu.Toplimt.Wei)
			Set_CompareMenu.Toplimt.Wei--;
			if(Set_CompareMenu.Toplimt.Wei)
			{
		Set_CompareMenu.Toplimt.Num/=10;
				if(Set_CompareMenu.Toplimt.Dot)Set_CompareMenu.Toplimt.Dot--;
				if(Set_CompareMenu.Toplimt.Dot==0)Set_CompareMenu.Toplimt.Dotp=1;
			}
				else
		{
		Set_CompareMenu.Toplimt.Num=1;
		Set_CompareMenu.Toplimt.Wei=0;
//		Set_CompareMenu.Lowlimt.Unit=2;
		Set_CompareMenu.Toplimt.Dot=0;
		Set_CompareMenu.Toplimt.Dotp=1;
			Input_Bar();
		}
		}
if(Button_Page.sumkey==5)Set_CompareMenu.Toplimt.Unit=1;
if(Button_Page.sumkey==10)Set_CompareMenu.Toplimt.Unit=2;
if(Button_Page.sumkey==15)Set_CompareMenu.Toplimt.Unit=3;
if(Button_Page.sumkey==20)Set_CompareMenu.Toplimt.Unit=4;

if(Button_Page.sumkey==14)//Clear
{Set_CompareMenu.Toplimt.Num=0;
Set_CompareMenu.Toplimt.Wei=0;
	Set_CompareMenu.Toplimt.Unit=2;//ou
	Set_CompareMenu.Toplimt.Dot=0;
	Set_CompareMenu.Toplimt.Dotp=1;
	Input_Bar();
}
		if(Button_Page.sumkey==0)
		{Button_Page.page=SPED_TEST;
		Button_Page.index=SPED_TEST;
		Button_Page.sumkey=1;
			Set_CompareMenu.Toplimt.Wei=0;
			Set_CompareMenu.Toplimt.Num=0;
			Set_CompareMenu.Toplimt.Unit=2;//ou
	Set_CompareMenu.Toplimt.Dot=0;
			Set_CompareMenu.Toplimt.Dotp=1;
		Num_Keyboard();//&Button_Page
		}
		else if(Set_CompareMenu.Toplimt.Wei<6)
		{
			if(Button_Page.sumkey<4)
			{Set_CompareMenu.Toplimt.Num*=10;
				Set_CompareMenu.Toplimt.Wei++;
				Set_CompareMenu.Toplimt.Num+=Button_Page.sumkey;
				DispBuf[0]='0'+Button_Page.sumkey;
			}
			if(Button_Page.sumkey>5&&Button_Page.sumkey<9)
			{Set_CompareMenu.Toplimt.Num*=10;Set_CompareMenu.Toplimt.Wei++;
				Set_CompareMenu.Toplimt.Num+=Button_Page.sumkey-2;
			DispBuf[0]='0'+Button_Page.sumkey-2;
			}
			if(Button_Page.sumkey>10&&Button_Page.sumkey<14)
			{Set_CompareMenu.Toplimt.Num*=10;Set_CompareMenu.Toplimt.Wei++;
				Set_CompareMenu.Toplimt.Num+=Button_Page.sumkey-4;
			DispBuf[0]='0'+Button_Page.sumkey-4;
			}

//if(Set_CompareMenu.Toplimt.Num)
	{
//		Hex_Format(Set_CompareMenu.Toplimt.Num,Set_CompareMenu.Toplimt.Dot,6,0);//加单位LCD_COLOR_BABYGREY
	//	WriteString_16_Shade(136,27,DispBuf,0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,5);//COLORFLAG
DispBuf[1]=0;//end flg

		if(Button_Page.sumkey==9)//Backspace
		{DispBuf[0]=' ';
			if(Set_CompareMenu.Toplimt.Wei)
				WriteString21(140+10*Set_CompareMenu.Toplimt.Wei,25,DispBuf,0,\
							 POLYGON_WORD1,POLYGON_WORD1,POLYGON_WORD1,POLYGON_CHANG,COLORFLAG);
			else
				WriteString21(130,25,DispBuf,0,\
							 POLYGON_WORD1,POLYGON_WORD1,POLYGON_WORD1,POLYGON_CHANG,COLORFLAG);
			}
		else
			WriteString21(130+10*Set_CompareMenu.Toplimt.Wei,25,DispBuf,0,\
							 POLYGON_WORD1,POLYGON_WORD1,POLYGON_WORD1,POLYGON_CHANG,COLORFLAG);
	WriteString_16_Shade(236,25,Disp_Unit[Set_CompareMenu.Toplimt.Unit],0,\
							 POLYGON_WORD1,POLYGON_WORD1,POLYGON_WORD1,POLYGON_CHANG,6);//COLORFLAG
	}
		}
		Disp_Num_Keyboard_Box();
if(Button_Page.sumkey==19)///enter
			lcd_Clear(LCD_COLOR_TURQUOISE);
	}
	else
	{
	if(Button_Page.row==1)
		{SaveData.Main.speed=0;}
		if(Button_Page.row==2)
		{SaveData.Main.speed=1;}
		if(Button_Page.row==3)
		{SaveData.Main.speed=2;}
		Saveeeprom.Save_Main.speed=SaveData.Main.speed;
	Savetoeeprom();
	}
		break;
	case TRIG_TEST:
		if(SaveData.Main.mode)//lo
		{
			if(Button_Page.sumkey==19||Button_Page.sumkey==4)//Enter key/\ESC
			{
				//Button_Page.page=DIS_TEST;Button_Page.index=0;
				Button_Page.page=Button_Page.index=DIS_TEST;
				if(Button_Page.sumkey==19)//Enter
				{	SaveData.Limit.Low[0].Num=Set_CompareMenu.Lowlimt.Num;
					if(Set_CompareMenu.Lowlimt.Dot)
				SaveData.Limit.Low[0].Dot=Set_CompareMenu.Lowlimt.Wei-Set_CompareMenu.Lowlimt.Dot;
					else
						SaveData.Limit.Low[0].Dot=0;
				SaveData.Limit.Low[0].Unit=Set_CompareMenu.Lowlimt.Unit;

				Savetoeeprom();
				}
			}
if(Button_Page.sumkey==18&&Set_CompareMenu.Lowlimt.Dotp)//.
{Set_CompareMenu.Lowlimt.Dotp=0;
	Set_CompareMenu.Lowlimt.Wei++;	//Set_CompareMenu.Lowlimt.Dot=Set_CompareMenu.Lowlimt.Wei;
	//SaveData.Limit.Low[0].Dot=Set_CompareMenu.Lowlimt.Wei;
	Set_CompareMenu.Lowlimt.Dot=Set_CompareMenu.Lowlimt.Wei;
	DispBuf[0]='.';
}
if(Button_Page.sumkey==17)//"0"
{DispBuf[0]='0'+0;
Set_CompareMenu.Lowlimt.Num*=10;
Set_CompareMenu.Lowlimt.Wei++;
}
if(Button_Page.sumkey==4)//Esc
		{
		lcd_Clear(LCD_COLOR_TURQUOISE);
				Button_Page.page=DIS_TEST;
				Button_Page.index=0;
		}
if(Button_Page.sumkey==9)//BackSpace
		{
			if(Set_CompareMenu.Lowlimt.Wei)
				Set_CompareMenu.Lowlimt.Wei--;
			if(Set_CompareMenu.Lowlimt.Wei)
		{
		Set_CompareMenu.Lowlimt.Num/=10;
			if(Set_CompareMenu.Lowlimt.Dot)Set_CompareMenu.Lowlimt.Dot--;
			if(Set_CompareMenu.Lowlimt.Dot==0)Set_CompareMenu.Lowlimt.Dotp=1;
				}
		else
		{
		Set_CompareMenu.Lowlimt.Num=1;
		Set_CompareMenu.Lowlimt.Wei=0;
//		Set_CompareMenu.Lowlimt.Unit=2;
		Set_CompareMenu.Lowlimt.Dot=0;
		Set_CompareMenu.Lowlimt.Dotp=1;
			Input_Bar();
		}
		}
if(Button_Page.sumkey==5)Set_CompareMenu.Lowlimt.Unit=1;
if(Button_Page.sumkey==10)Set_CompareMenu.Lowlimt.Unit=2;
if(Button_Page.sumkey==15)Set_CompareMenu.Lowlimt.Unit=3;
if(Button_Page.sumkey==20)Set_CompareMenu.Lowlimt.Unit=4;

if(Button_Page.sumkey==14)//Clear
		{Set_CompareMenu.Lowlimt.Num=0;
		Set_CompareMenu.Lowlimt.Wei=0;
		Set_CompareMenu.Lowlimt.Unit=2;
		Set_CompareMenu.Lowlimt.Dot=0;
		Set_CompareMenu.Lowlimt.Dotp=1;
			Input_Bar();
		}
			if(Button_Page.sumkey==0)
			{Button_Page.page=TRIG_TEST;
			Button_Page.index=TRIG_TEST;
		Button_Page.sumkey=1;
				Set_CompareMenu.Lowlimt.Wei=0;
				Set_CompareMenu.Lowlimt.Num=0;
				Set_CompareMenu.Lowlimt.Unit=2;
		Set_CompareMenu.Lowlimt.Dot=0;
				Set_CompareMenu.Lowlimt.Dotp=1;
			Num_Keyboard();//&Button_Page
			}
			else if(Set_CompareMenu.Lowlimt.Wei<6)
			{
			if(Button_Page.sumkey<4)
			{Set_CompareMenu.Lowlimt.Num*=10;
				Set_CompareMenu.Lowlimt.Wei++;
				Set_CompareMenu.Lowlimt.Num+=Button_Page.sumkey;
				DispBuf[0]='0'+Button_Page.sumkey;
			}
			if(Button_Page.sumkey>5&&Button_Page.sumkey<9)
			{Set_CompareMenu.Lowlimt.Num*=10;Set_CompareMenu.Lowlimt.Wei++;
			Set_CompareMenu.Lowlimt.Num+=(Button_Page.sumkey-2);
			DispBuf[0]='0'+Button_Page.sumkey-2;
			}
			if(Button_Page.sumkey>10&&Button_Page.sumkey<14)
			{Set_CompareMenu.Lowlimt.Num*=10;Set_CompareMenu.Lowlimt.Wei++;
				Set_CompareMenu.Lowlimt.Num+=Button_Page.sumkey-4;
			DispBuf[0]='0'+Button_Page.sumkey-4;
			}

//if(Set_CompareMenu.Lowlimt.Num)
	{
		//Hex_Format(Set_CompareMenu.Lowlimt.Num,Set_CompareMenu.Lowlimt.Dot,6,0);//加单位
		DispBuf[1]=0;
		if(Button_Page.sumkey==9)
		{DispBuf[0]=' ';
			if(Set_CompareMenu.Lowlimt.Wei)
			WriteString21(140+10*Set_CompareMenu.Lowlimt.Wei,25,DispBuf,0,\
							 POLYGON_WORD1,POLYGON_WORD1,POLYGON_WORD1,POLYGON_CHANG,COLORFLAG);
			else
				WriteString21(130,25,DispBuf,0,\
							 POLYGON_WORD1,POLYGON_WORD1,POLYGON_WORD1,POLYGON_CHANG,COLORFLAG);
		}
			else
		WriteString21(130+10*Set_CompareMenu.Lowlimt.Wei,25,DispBuf,0,\
							 POLYGON_WORD1,POLYGON_WORD1,POLYGON_WORD1,POLYGON_CHANG,COLORFLAG);
	WriteString_16_Shade(236,25,Disp_Unit[Set_CompareMenu.Lowlimt.Unit],0,\
							 POLYGON_WORD1,POLYGON_WORD1,POLYGON_WORD1,POLYGON_CHANG,6);
	}
			}
		Disp_Num_Keyboard_Box();
		if(Button_Page.sumkey==19)
			lcd_Clear(LCD_COLOR_TURQUOISE);
		}
		else
		{
		if(Button_Page.row==1)
		{SaveData.Main.trig=0;}
		if(Button_Page.row==2)
		{SaveData.Main.trig=1;}
		Saveeeprom.Save_Main.trig=SaveData.Main.trig;
		Savetoeeprom();
		}
		break;
	}
}
void key_setup_pro()
{
	uint16_t x0,x1;
	if(SaveData.Main.mode)
	{if(Button_Page.index<6)
	{	if(Button_Page.row)
	{x0=(Button_Page.row-1)*45+2;
	x1=(Button_Page.row-1)*45+45;
	Disp_Box(387,x0,476,x1,4,LCD_COLOR_TURQUOISE);
	}
}}
	else
	{
	if(Button_Page.row)
	{x0=(Button_Page.row-1)*45+2;
	x1=(Button_Page.row-1)*45+45;
	Disp_Box(387,x0,476,x1,4,LCD_COLOR_TURQUOISE);
	}
	}
switch(Button_Page.index)
{
	case DIS_TEST:		if(Button_Page.row==0)	Button_Page.row=1;
			break;
	case COMP_SYS:		if(Button_Page.row==0)	Button_Page.row=1;
			break;
	case TOOL_TEST:		if(Button_Page.row==0)	Button_Page.row=1;
		break;
	case FILE_TEST:		if(Button_Page.row==0)	Button_Page.row=1;
			break;
	case PAR_TEST:		if(Button_Page.row==0)	Button_Page.row=1;
			break;
	case RANG_TEST:		if(Button_Page.row==0)	Button_Page.row=1;
			break;
	case SPED_TEST:
	if(!SaveData.Main.mode)	
	{	if(Button_Page.row==0)	Button_Page.row=1;}
			break;
	case TRIG_TEST:
		if(!SaveData.Main.mode)
	{if(Button_Page.row==0)	Button_Page.row=1;}
			break;
}
if(Button_Page.row==1)
	Disp_Box(387,2,476,45,4,LCD_COLOR_CYAN);
}
/////
void Key_Up_Pro()
{uint8_t m9;
	if(Button_Page.index<6)		{Button_Page.sumkey=0;
	Button_Page.third=Button_Page.test=0;
	}
	if(Button_Page.index<8)
	{		if(Button_Page.row)//&&Button_Page.index6<
	{
	if(Button_Page.row&&Button_Page.row<7)//row sel
					{
			Disp_Box(387,(Button_Page.row-1)*45+2,476,(Button_Page.row-1)*45+45,4,LCD_COLOR_TURQUOISE);
			Button_Page.row--;
					if(Button_Page.row==0)Button_Page.row=6;
					}
	}

if(Button_Page.sumkey==0)
{	if(Button_Page.row)
Disp_Box(387,(Button_Page.row-1)*45+2,476,(Button_Page.row-1)*45+45,4,LCD_COLOR_CYAN);
else{//par sel
					if(Button_Page.index>3)						Button_Page.index-=4;
					else						Button_Page.index+=4;
					}
				}
	if(Button_Page.index>5)
		{	if(SaveData.Main.mode&&Button_Page.sumkey)
	{
	{if(Button_Page.sumkey>5)
		Button_Page.sumkey-=5;
		Disp_Num_Keyboard_Box();
		}
	}
	}
	}
	else
	{	

//////////R_adj
	if(Button_Page.index==ADJ0_CAL)
	{
	if(Button_Page.third<6)	Button_Page.key%=100000;
	if(Button_Page.third==1)	Button_Page.key+=10000;
	if(Button_Page.third==2)	Button_Page.key+=1000;
	if(Button_Page.third==3)	Button_Page.key+=100;
	if(Button_Page.third==4)	Button_Page.key+=10;
	if(Button_Page.third==5)	Button_Page.key+=1;
	if(Button_Page.third<6)	Button_Page.key%=100000;

	if(Button_Page.third==10)//档
	{
	Button_Page.force++;
		if(Button_Page.force>9)Button_Page.force=0;
//	Button_Page.key=(SaveData.div[Button_Page.force].ax);
	}
//if(Button_Page.third>10)	Button_Page.key%=100000;

	if(Button_Page.third==11)//Button_Page.key+=10000;
		{m9=SaveData.div[Button_Page.force].bx[1]&0xf;

		m9++;if(m9>9)m9=0;
		SaveData.div[Button_Page.force].bx[1]&=0xf0;
		SaveData.div[Button_Page.force].bx[1]=m9;
	}
	
	if(Button_Page.third==12)
	{
	m9=SaveData.div[Button_Page.force].bx[2]>>4;

		m9&=0xf;
		m9++;if(m9>9)m9=0;
		SaveData.div[Button_Page.force].bx[2]&=0xf;
		m9<<=4;
	SaveData.div[Button_Page.force].bx[2]+=m9;
	}
	if(Button_Page.third==13)
		{
		m9=SaveData.div[Button_Page.force].bx[2]&0xf;

		m9++;if(m9>9)m9=0;
		SaveData.div[Button_Page.force].bx[2]&=0xf0;
	SaveData.div[Button_Page.force].bx[2]+=m9;
	}
	if(Button_Page.third==14)
		{
		m9=SaveData.div[Button_Page.force].bx[3]>>4;

		m9&=0xf;
		m9++;if(m9>9)m9=0;
		SaveData.div[Button_Page.force].bx[3]&=0xf;
		m9<<=4;
	SaveData.div[Button_Page.force].bx[3]+=m9;
	}
	if(Button_Page.third==15)
		{
	m9=SaveData.div[Button_Page.force].bx[3]&0xf;

		m9++;if(m9>9)m9=0;
		SaveData.div[Button_Page.force].bx[3]&=0xf0;
	SaveData.div[Button_Page.force].bx[3]+=m9;
	}
//R_ADJ_Pro();
	}
//////
	}
}
void Key_Dw_Pro()
{uint8_t m9;
if(Button_Page.index<6)	{	Button_Page.sumkey=0;
Button_Page.third=Button_Page.test=0;
}
if(Button_Page.index<8)
{	if(Button_Page.row)//&&Button_Page.index<6
	{
if(Button_Page.row&&Button_Page.row<7)//row sel
		{
			Disp_Box(387,(Button_Page.row-1)*45+2,476,(Button_Page.row-1)*45+45,4,LCD_COLOR_TURQUOISE);
			Button_Page.row++;
			if(Button_Page.row>6)Button_Page.row=1;
		}
	}
	if(Button_Page.sumkey==0)
{if(Button_Page.row)
Disp_Box(387,(Button_Page.row-1)*45+2,476,(Button_Page.row-1)*45+45,4,LCD_COLOR_CYAN);
else{//par sel
		if(Button_Page.index>3)		Button_Page.index-=4;
		else						Button_Page.index+=4;
		}
	}
if(Button_Page.index>5)
{ if(SaveData.Main.mode&&Button_Page.sumkey)//
	{
		{if(Button_Page.sumkey<16)
		Button_Page.sumkey+=5;
		Disp_Num_Keyboard_Box();
		}
	}
}
}
else
{

//////////R_adj
	if(Button_Page.index==ADJ0_CAL)
	{
	if(Button_Page.third<6)	Button_Page.key%=100000;
	if(Button_Page.third==1)	Button_Page.key-=10000;
	if(Button_Page.third==2)	Button_Page.key-=1000;
	if(Button_Page.third==3)	Button_Page.key-=100;
	if(Button_Page.third==4)	Button_Page.key-=10;
	if(Button_Page.third==5)	Button_Page.key-=1;

	if(Button_Page.third<6)	Button_Page.key%=100000;

	if(Button_Page.third==10)//档
	{
	Button_Page.force--;
		if(Button_Page.force>9)Button_Page.force=9;
	//Button_Page.key=(uint32_t) (SaveData.div[Button_Page.force].adx);
	}
	if(Button_Page.third==11)
		{
	m9=(SaveData.div[Button_Page.force].bx[1])&0xf;
		m9--;if(m9>9)m9=9;
			SaveData.div[Button_Page.force].bx[1]&=0xf0;
	SaveData.div[Button_Page.force].bx[1]=m9;
	}
	if(Button_Page.third==12)
		{
	m9=(SaveData.div[Button_Page.force].bx[2]>>4)&0xf;
		m9--;if(m9>9)m9=9;
			SaveData.div[Button_Page.force].bx[2]&=0x0f;
	SaveData.div[Button_Page.force].bx[2]+=m9<<4;
	}
	if(Button_Page.third==13)
		{
	m9=(SaveData.div[Button_Page.force].bx[2])&0xf;
		m9--;if(m9>9)m9=9;
			SaveData.div[Button_Page.force].bx[2]&=0xf0;
	SaveData.div[Button_Page.force].bx[2]+=m9;
	}
	if(Button_Page.third==14)
		{
	m9=(SaveData.div[Button_Page.force].bx[3]>>4)&0xf;
		m9--;if(m9>9)m9=9;
			SaveData.div[Button_Page.force].bx[3]&=0x0f;
	SaveData.div[Button_Page.force].bx[3]+=m9<<4;
	}
	if(Button_Page.third==15)
		{
	m9=(SaveData.div[Button_Page.force].bx[3])&0xf;
		m9--;if(m9>9)m9=9;
			SaveData.div[Button_Page.force].bx[3]&=0xf0;
	SaveData.div[Button_Page.force].bx[3]+=m9;
	}

//R_ADJ_Pro();
	}
//////
}
}
void Key_Right_Pro()
{
	if(Button_Page.index<6)	{Button_Page.sumkey=0;
	Button_Page.third=0;Button_Page.test=0;
	}
if(Button_Page.index==6||Button_Page.index==7)//set Hi or Lo
{ if(SaveData.Main.mode&&Button_Page.sumkey)
	{
		{if(Button_Page.sumkey<20)
		Button_Page.sumkey++;
	Disp_Num_Keyboard_Box();
		}
	}
}
	if(Button_Page.sumkey==0&&Button_Page.index<8)
{if(Button_Page.row)
	{
	Disp_Box(387,(Button_Page.row-1)*45+2,476,(Button_Page.row-1)*45+45,4,LCD_COLOR_TURQUOISE);
	Button_Page.row=0;
	}//clr row

else//select index
{if(Button_Page.index<4)//H1
				{Button_Page.index++;
					if(Button_Page.index>3)					Button_Page.index=0;	
				}
				else//H2
				{	Button_Page.index++;
				if(Button_Page.index>7)					Button_Page.index=4;
				}
			}
}
if(Button_Page.index==ADJ0_CAL)
{
if(Button_Page.third<8)//key crush
{Button_Page.third++;
	if(Button_Page.third>6)		Button_Page.third=1;
}
else if(Button_Page.third<18)//zero val crush
{Button_Page.third++;
	if(Button_Page.third>17)	Button_Page.third=10;
}
//R_ADJ_Pro();
}
}
////////////////////
void Key_Left_Pro()
{
	if(Button_Page.index<6)
		{Button_Page.sumkey=0;
	Button_Page.third=0;Button_Page.test=0;
	}
if(Button_Page.index==6||Button_Page.index==7)//set Hi or Lo
{	 if(SaveData.Main.mode&&Button_Page.sumkey)
	{
		{if(Button_Page.sumkey>1)
		Button_Page.sumkey--;
	Disp_Num_Keyboard_Box();
			}
	}
}
		if(Button_Page.sumkey==0&&Button_Page.index<8)
	{if(Button_Page.row)
	{Disp_Box(387,(Button_Page.row-1)*45+2,476,(Button_Page.row-1)*45+45,4,LCD_COLOR_TURQUOISE);
	Button_Page.row=0;//clr row
	}
else
{				if(Button_Page.index<4)//H1	
				{Button_Page.index--;
				if(Button_Page.index>4)					Button_Page.index=3;
				}
				else//H2
				{		Button_Page.index--;
					if(Button_Page.index<4)				Button_Page.index=7;
				}
			}
		}
			if(Button_Page.index==ADJ0_CAL)
{
if(Button_Page.third<8)//key crush
{
Button_Page.third--;
	if(Button_Page.third==0)	Button_Page.third=6;
}
else if(Button_Page.third<18)//zero val crush
{Button_Page.third--;
	if(Button_Page.third<10)	Button_Page.third=17;
}
//R_ADJ_Pro();
}
}
//////
void Key_Pro(uint8_t key)
{uint16_t x,x0,x1;

			switch(key)
			{
				case KEY_Disp:
lcd_Clear(LCD_COLOR_TURQUOISE);
for(x=0;x<4;x++)
				{Disp_Box(BOX_0_SITE+x*96,BOX_0_SITE,96+x*96,45,4,LCD_COLOR_TURQUOISE);
				Disp_Box(BOX_0_SITE+x*96,47,96+x*96,90,4,LCD_COLOR_TURQUOISE);
				}
				Disp_Box(BOX_0_SITE,BOX_0_SITE,96,45,4,LCD_COLOR_ORANGE);
if(Button_Page.row)
	{x0=(Button_Page.row-1)*45+2;
	x1=(Button_Page.row-1)*45+45;
	Disp_Box(387,x0,476,x1,4,LCD_COLOR_TURQUOISE);
	Button_Page.row=0;
	}
Button_Page.page=0;Button_Page.index=0;
	break;

			case KEY_Right:		Key_Right_Pro();
				break;

			case KEY_Left:		Key_Left_Pro();
				break;

			case KEY_UP:			Key_Up_Pro();
				break;

			case KEY_Down:		Key_Dw_Pro();
				break;

			case KEY_Setup:		key_setup_pro();
				break;

			case KEY_Enter:		key_enter_pro();
		break;
	case KEY_Trig:
					SaveData.Main.trig=!SaveData.Main.trig;
			//	if(SaveData.Main_Func.trig>1)
			//		=0;
				Saveeeprom.Save_Main.trig=SaveData.Main.trig;//=Disp_Set_Resist.Trigger;
				Savetoeeprom();
					break;
			case 	KEY_Mid:
				SaveData.Main.speed++;
			if(SaveData.Main.speed>2)
				SaveData.Main.speed=0;
			Saveeeprom.Save_Main.speed=SaveData.Main.speed;//=Disp_Set_Resist.Trigger;
				Savetoeeprom();
				break;
			case KEY_0ADJ:
				Button_Page.page=ADJ0_KEY;
			
			Button_Page.sumkey=SaveData.Main.mode;
				break;
			}
}
*/

