#include "LCD/lpc177x_8x_lcd.h"
#include "EX_SDRAM/EX_SDRAM.H"
#include "LCD/AsciiLib.h"
#include "use_disp.h"
#include  "stdint.h"
#include  "stdio.h"
#include "Key/key.h"
#include "test/Test.h"
#include  "Globalvalue/globalvalue.h"
#include "lpc177x_8x_eeprom.h"
#include "timer.h"
#include <math.h>
#include "debug_frmwrk.h"
#include "set_manu.h"
uint8_t CorrectionflagC=0,CorrectionflagR=0,Correc_successflag=0;

const uint8_t User_Comp[][4]=
{  "OFF",	"ON"};

const uint8_t Switch_Value[][5]=
{	"OFF",	"ON"};

const uint8_t SetupRefa_Button_Tip[][8]=  //频率选择时候的下面的提示符号
{    "MEASURE"};

const char User_LimitList_Value[][4]=
{	"ABS",	"%"};
const uint8_t Sys_Buard_Value[][7]=
{	"关闭",	"4800",	"9600",	"19200",	"38400",
//	{"56000"},
};
const uint8_t Set_Unit[][6]=
{	"p"};
const uint8_t Disp_Unit[][3]=
{"n","m","#","k","M"};//"p""u",
const uint8_t Disp_Range_Main_Disp[][3]=
{	"F",	"Ω"};//F,H,Ω，S r °空格
/*
const uint8_t T_Right[][9]=			//测试设置
{	"测量显示",	"分选显示",	"讯响(on)",	"清零(ON)"};
const uint8_t T2_Right[][9]=			//测试设置
{	"测量显示",	"分选显示",	"讯响off",	"清零(ON)"};
const uint8_t Comp_Set_Right[][9]=			//比较设置
{	"校准",	"232速率",	"讯响模式",	"讯响"};
const uint8_t Disp_Test_Menu[][9]=
{	"测量显示",	"系统",	"工具",	"文件",	"参数",	"量程",	"速度",	"触发"};
const uint8_t Comp_Set[][9]=
{	"测量显示",	"分选显示",	"工具",	"文件",	"参数",	"量程",	"速度",	"触发"};
const uint8_t Disp_Set_Menu[][9]=
{	"测量显示",	"系统",	"工具",	"文件",	"比较","分选模式",	"上限",	"下限"};
const uint8_t Disp_Com_Menu[][9]=
{	"分选显示",	"系统",	"工具",	"文件",	"分选",	"模式",	"上限",	"下限"};
const uint8_t Disp_Chek_Menu[][5]=
{	"校验",	"通讯",	"速度",	"触发"};
const char Comp_Parameter[][4]=
{	"ON",	"OFF"};
const char T_Parameter[][4]=	//测试参数
{	" R ",	"LPR"};
const char T_Mode[][4]=
{"ABS"};
const char Mi_Key[][9]={
	"密码:",	"Enetr",	"档位:",	"校准数:",	"写入",	"退出校准",	"R:"};
const char T_Rang[][6]=	//测试量程
{	" 2 M#",//0Ω
	"200K#",//1Ω
	"20 K#",//2Ω
	" 2 K#",//3Ω
	"200 #",//4Ω
	"20  #",//5Ω
	" 2  #",//6Ω
	"200m#",//7Ω
	"20 m#",//8
	"10 m#",//9
"AUTO ",//10
};
const char T_Speed[][6]=
{	" FAST",	" MED ",	" SLOW"
//	{"SLOW2"},
};
const char T_Trigger[][4]=
{	"INT",	"EXT"};
const  char Rang_Button_Tip[][5]=
{	"AUTO",	"HOLD",	"↑",	"↓"};
const uint8_t Key_Num_UpOrLow[][3]=	//数字键盘上的上限线选择参数
{	"n",	"毫",	"欧",	"卡",	"兆"};
const char Button_Key_Num_UpOrLowM[][2]=	//数字键盘上的上限线选择参数
{	"n",	"m",	"#",	"k",	"M"};

const uint8_t Test_File[][9]=
{	"文件管理",	"全屏复制",	"保存数据"};
const char Test_Tool[][4]=
{	"OFF",	"ON"};
const char Test_File_Save[][4]=
{	"OFF",	"ON"};
const uint8_t Disp_Compare_Menu[][9]=
{	"测量显示",	"分选页面",	"文件页面",	"工具页面",	"比较",	"比较模式",	"上限",	"下限",	"标称",	"%"};
const uint8_t Compare_File_Save[][4]=
{	"OFF",	"ON"};
const uint8_t Compare_Fool_Disp[][4]=	//比较显示中的工具显示
{	"OFF",	"ON"};
const uint8_t Compare_Fool_Ring[][4]=//比较显示中的比较讯响
{	"OFF",	"NG",	"GD"};
const uint8_t Compare_Fool_Count[][4]=//比较显示中的计数
{	"OFF",	"ON"};
const uint8_t Compare_Compa[][4]=		//比较显示中的比较
{	"OFF",	"ON"};
const uint8_t Compare_Comp_Mode[][4]=	//比较显示中的比较模式
{	"ABS",	" %"};
const char Compare_Uplimt[][8]=
{   "0.0000",   "0.0000"};
const uint8_t Disp_ShiftSet_Menu[][4]=
{	"%"};
const uint8_t SysSet_Baud[][7+1]=
{	" 9600 ",	"19200 ",	"28800 ",	"38400 "};
const uint8_t Keyboard[][6]=
{	"上限:",	"下限:",	"值:"};
const uint8_t Disp_Up_Menu[][6]=
{	"上限:",	"下限:",	"值:"};
const uint8_t Button_Num[][9+1]=
{	"1",	"2",	"3",	"4",	"5",	"6",	"7",	"8",	"9",
	"+/-",	"0",	".",	"Esc",	"Backspace",	"Clear",	"Enter",
};
static 	void KEY_COLORBLOCK(void)	//按键色块条
{
	 uint8_t i,j;
	 for(i=0;i<6;i++)		//按键颜色渐变
	 {
		  LCD_DrawRectShade(KEY_XLEFTP,i*KEY_HIGH+4*(i+1)-1,KEY_XRIGHT,(i+1)*(KEY_HIGH+4),KEY_RED,KEY_RED,KEY_RED,KEY_CHANG,COLORFLAG);
		 for(j=0;j<3;j++)	//直线颜色渐变
	     {
	   	    LCD_DrawLineShade(KEY_XLEFTP-3+j,i*KEY_HIGH+4*(i+1)+(2-j),KEY_XLEFTP-3+j,(i+1)*(KEY_HIGH+4)-(4-j),\
								KEY_LINE_COL,KEY_LINE_COL,KEY_LINE_COL,KEY_CHANG, COLORFLAG); 
		      LCD_DrawLineShade(KEY_XRIGHT+j,i*KEY_HIGH+4*(i+1)+j,KEY_XRIGHT+j,(i+1)*(KEY_HIGH+4)-(j+2),\
								KEY_LINE_COL,KEY_LINE_COL,KEY_LINE_COL,KEY_CHANG,COLORFLAG);
	     }
	 }
}*/
//多边形渐变方框
void  Polygon_Box(void)
{
	 uint8_t i,j;
   for(i=0;i<4;i++)								 //第一行的右边两个矩形显示
   {
   		LCD_DrawRectShade(i*KEY_LENGHT+6,3,(i+1)*KEY_LENGHT-3,KEY_HIGH+4,\
						   POLYGON_RED,POLYGON_RED,POLYGON_RED,POLYGON_CHANG,COLORFLAG);  
	    for(j=0;j<3;j++)
	   {
	   	  LCD_DrawLineShade(i*KEY_LENGHT+3+j,6-j,(i)*KEY_LENGHT+3+j,KEY_HIGH+j,\
							 POLYGON_LINE,POLYGON_LINE,POLYGON_LINE,POLYGON_CHANG,COLORFLAG); 
		    LCD_DrawLineShade((i+1)*KEY_LENGHT-j-1,6-j,(i+1)*KEY_LENGHT-j-1,KEY_HIGH+j,\
							 POLYGON_LINE,POLYGON_LINE,POLYGON_LINE,POLYGON_CHANG,COLORFLAG); 
	   }
   }
   for(i=0;i<4;i++)		  					 //第二行的矩形显示
   {
     	LCD_DrawRectShade(i*KEY_LENGHT+6,(KEY_HIGH+7),(i+1)*KEY_LENGHT-3,(KEY_HIGH+4)*2,\
						   POLYGON_RED,POLYGON_RED,POLYGON_RED,POLYGON_CHANG,COLORFLAG); 	
		for(j=0;j<3;j++)
	   {
	   	  LCD_DrawLineShade(i*KEY_LENGHT+3+j,(KEY_HIGH+10-j),i*KEY_LENGHT+3+j,(2*KEY_HIGH+4)+j,\
								POLYGON_LINE,POLYGON_LINE,POLYGON_LINE,POLYGON_CHANG,COLORFLAG); 
		    LCD_DrawLineShade((i+1)*KEY_LENGHT-j-1,(KEY_HIGH+10-j),(i+1)*KEY_LENGHT-j-1,(2*KEY_HIGH+4)+j,\
								POLYGON_LINE,POLYGON_LINE,POLYGON_LINE,POLYGON_CHANG,COLORFLAG); 
	   }
   }
}
//系统设置里的多边形渐变方框
void SysSet_Polygon_Box(void)
{
	uint8_t i,j;
	LCD_DrawRectShade(3+3,3,KEY_LENGHT*2-3,45,POLYGON_RED,POLYGON_RED,POLYGON_RED,POLYGON_CHANG,COLORFLAG);	
   for(j=0;j<3;j++)
    {
		 LCD_DrawLineShade(3+j,3+(3-j),3+j,KEY_HIGH+j, POLYGON_LINE,POLYGON_LINE,POLYGON_LINE,POLYGON_CHANG,COLORFLAG); //左三条线，和右三条线的显示
		 LCD_DrawLineShade(2*KEY_LENGHT-j-1,3+(3-j),2*KEY_LENGHT-j-1,KEY_HIGH+j ,POLYGON_LINE,POLYGON_LINE,POLYGON_LINE,POLYGON_CHANG,COLORFLAG); 
    }
   for(i=0;i<2;i++)					//第一行的右边两个矩形显示
   {
   		LCD_DrawRectShade((i+2)*KEY_LENGHT+3+3,3,(i+3)*KEY_LENGHT-3,KEY_HIGH+4,\
						   POLYGON_RED,POLYGON_RED,POLYGON_RED,POLYGON_CHANG,COLORFLAG);  
	    for(j=0;j<3;j++)
	   {
	   	    LCD_DrawLineShade((i+2)*KEY_LENGHT+3+j,3+(3-j),(i+2)*KEY_LENGHT+3+j,KEY_HIGH+j,\
							   POLYGON_LINE,POLYGON_LINE,POLYGON_LINE,POLYGON_CHANG,COLORFLAG); 
		    LCD_DrawLineShade((i+3)*KEY_LENGHT-j-1,3+(3-j),(i+3)*KEY_LENGHT-j-1,KEY_HIGH+j,\
							  POLYGON_LINE,POLYGON_LINE,POLYGON_LINE,POLYGON_CHANG,COLORFLAG); 
	   }
   }
      for(i=0;i<3;i++)		   //第二行的矩形显示
   {
     	LCD_DrawRectShade(i*SYSSET_BOX_LEN+3+3,(KEY_HIGH+7),(i+1)*SYSSET_BOX_LEN-3,(KEY_HIGH+4)*2,\
						   POLYGON_RED,POLYGON_RED,POLYGON_RED,POLYGON_CHANG,COLORFLAG); 	
		for(j=0;j<3;j++)
	   {
	   	    LCD_DrawLineShade(i*SYSSET_BOX_LEN+3+j,(KEY_HIGH+7)+(3-j),i*SYSSET_BOX_LEN+3+j,(2*KEY_HIGH+4)+j,\
								POLYGON_LINE,POLYGON_LINE,POLYGON_LINE,POLYGON_CHANG,COLORFLAG); 
		    LCD_DrawLineShade((i+1)*SYSSET_BOX_LEN-j-1,(KEY_HIGH+7)+(3-j),(i+1)*SYSSET_BOX_LEN-j-1,(2*KEY_HIGH+4)+j,\
								POLYGON_LINE,POLYGON_LINE,POLYGON_LINE,POLYGON_CHANG,COLORFLAG);
	   }
   }
}

//画矩形外框	bevel_edge 	斜角边
void Print_Box(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint8_t bevel_edge,uint32_t color)
{	
	LCD_DrawLine(x1+bevel_edge-1,y1,x2-bevel_edge+1,y1,color);	//画水平线
	LCD_DrawLine(x1+bevel_edge-1,y2,x2-bevel_edge+1,y2,color);
	LCD_DrawLine(x1,y1+bevel_edge-2,x1,y2-bevel_edge+2,color);	//画垂直线
	LCD_DrawLine(x2,y1+bevel_edge-2,x2,y2-bevel_edge+2,color);
}
//显示方框
void Disp_Box(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint8_t bevel_edge,uint32_t color)
{
	uint8_t i;
	Print_Box(x1,y1,x2,y2,bevel_edge,color);
	Print_Box(x1-1,y1-1,x2+1,y2+1,bevel_edge+2,color);

	for(i=1;i<bevel_edge;i++)//填充斜边有左上角
	{
		LCD_SetPoint(x1+1,y1+i,color);
		LCD_SetPoint(x1+2,y1+i-1,color);
		LCD_SetPoint(x1+3,y1+i-2,color);

		LCD_SetPoint(x2-1,y1+i,color);
		LCD_SetPoint(x2-2,y1+i-1,color);
		LCD_SetPoint(x2-3,y1+i-2,color);

		LCD_SetPoint(x1+1,y2+i-4,color);
		LCD_SetPoint(x1+2,y2+i-3,color);
		LCD_SetPoint(x1+3,y2+i-2,color);

		LCD_SetPoint(x2-1,y2+i-4,color);
		LCD_SetPoint(x2-2,y2+i-3,color);
		LCD_SetPoint(x2-3,y2+i-2,color);
	}
}
/*void Disp_Num_Key(void)    //显示数字 单位，英文
{
	uint8_t i,j;
	Colour.Fword=White;
	for(i=1;i<5;i++)	//按键上显示u,m,k,M
		WriteString21(KEY_XLEFTP+36,14+i*KEY_TOTALWID,Key_Num_UpOrLow[i],0,\
							 KEY_WORD2,KEY_WORD2,KEY_WORD2,KEY_CHANG,COLORFLAG);
	for(i=1;i<5;i++)   //显示1--9
	for(j=0;j<3;j++)
	{
		if((i-1)*3+j!=9)
		    WriteString21(KEY_LENGHT*j+47,13+i*KEY_TOTALWID,Button_Num[(i-1)*3+j],0,\
							 POLYGON_WORD1,POLYGON_WORD1,POLYGON_WORD1,POLYGON_CHANG,COLORFLAG);
		else
			 WriteString21(KEY_LENGHT*j+37,13+i*KEY_TOTALWID,Button_Num[(i-1)*3+j],0,\
							 POLYGON_WORD1,POLYGON_WORD1,POLYGON_WORD1,POLYGON_CHANG,COLORFLAG);	
	}
	for(i=1;i<5;i++)	//显示四个英文 Esc .Backspace .Enter .Clear
	{
		if(i+11==13)
			WriteString21(KEY_LENGHT*3+6,13+i*KEY_TOTALWID,Button_Num[i+11],0,\
							 POLYGON_WORD1,POLYGON_WORD1,POLYGON_WORD1,POLYGON_CHANG,COLORFLAG);
		else if(i+11==12)
			WriteString21(KEY_LENGHT*3+37,13+i*KEY_TOTALWID,Button_Num[i+11],0,\
							 POLYGON_WORD1,POLYGON_WORD1,POLYGON_WORD1,POLYGON_CHANG,COLORFLAG);
		else
			WriteString21(KEY_LENGHT*3+27,13+i*KEY_TOTALWID,Button_Num[i+11],0,\
							 POLYGON_WORD1,POLYGON_WORD1,POLYGON_WORD1,POLYGON_CHANG,COLORFLAG);
	}
}
//数字按键方框
void Disp_Num_Keyboard_Box()
{
	uint8_t i,j;
	Colour.black=LCD_COLOR_TURQUOISE;//LCD_COLOR_CYAN;//
	for(i=1;i<5;i++)
	for(j=0;j<4;j++)
		Disp_Box(BOX_0_SITE+KEY_LENGHT*j,BOX_0_SITE+KEY_TOTALWID*i,KEY_LENGHT*(j+1),KEY_TOTALWID*(i+1),4,Colour.black);
	for(i=1;i<5;i++)
		Disp_Box(KEY_XLEFTP-4,BOX_0_SITE+KEY_TOTALWID*i,KEY_XRIGHT+3,KEY_TOTALWID*(i+1),4,Colour.black);

	switch(Button_Page.sumkey)
	{
		case 1:Colour.black=LCD_COLOR_ORANGE;
				Disp_Box(BOX_0_SITE,BOX_0_SITE+KEY_TOTALWID,KEY_LENGHT,KEY_TOTALWID*2,4,Colour.black);//
		break;
		case 2:Colour.black=LCD_COLOR_ORANGE;
				Disp_Box(BOX_0_SITE+KEY_LENGHT,BOX_0_SITE+KEY_TOTALWID,KEY_LENGHT*2,KEY_TOTALWID*2,4,Colour.black);//
		break;
		case 3:Colour.black=LCD_COLOR_ORANGE;
				Disp_Box(BOX_0_SITE+KEY_LENGHT*2,BOX_0_SITE+KEY_TOTALWID,KEY_LENGHT*3,KEY_TOTALWID*2,4,Colour.black);
		break;
		case 4:Colour.black=LCD_COLOR_ORANGE;
				Disp_Box(BOX_0_SITE+KEY_LENGHT*3,BOX_0_SITE+KEY_TOTALWID,KEY_LENGHT*4,KEY_TOTALWID*2,4,Colour.black);
		break;
		case 5:Colour.black=White;
				Disp_Box(KEY_XLEFTP-4,BOX_0_SITE+KEY_TOTALWID,KEY_XRIGHT+3,KEY_TOTALWID*2,4,Colour.black);
		break;
		case 6:Colour.black=LCD_COLOR_ORANGE;
				Disp_Box(BOX_0_SITE,BOX_0_SITE+KEY_TOTALWID*2,KEY_LENGHT,KEY_TOTALWID*3,4,Colour.black);
		break;
		case 7:Colour.black=LCD_COLOR_ORANGE;
				Disp_Box(BOX_0_SITE+KEY_LENGHT,BOX_0_SITE+KEY_TOTALWID*2,KEY_LENGHT*2,KEY_TOTALWID*3,4,Colour.black);
		break;
		case 8:Colour.black=LCD_COLOR_ORANGE;
				Disp_Box(BOX_0_SITE+KEY_LENGHT*2,BOX_0_SITE+KEY_TOTALWID*2,KEY_LENGHT*3,KEY_TOTALWID*3,4,Colour.black);
		break;
		case 9:Colour.black=LCD_COLOR_ORANGE;
				Disp_Box(BOX_0_SITE+KEY_LENGHT*3,BOX_0_SITE+KEY_TOTALWID*2,KEY_LENGHT*4,KEY_TOTALWID*3,4,Colour.black);
		break;
		case 10:Colour.black=White;
				Disp_Box(KEY_XLEFTP-4,BOX_0_SITE+KEY_TOTALWID*2,KEY_XRIGHT+3,KEY_TOTALWID*3,4,Colour.black);
		break;
		case 11:Colour.black=LCD_COLOR_ORANGE;
				Disp_Box(BOX_0_SITE,BOX_0_SITE+KEY_TOTALWID*3,KEY_LENGHT,KEY_TOTALWID*4,4,Colour.black);
		break;
		case 12:Colour.black=LCD_COLOR_ORANGE;
				Disp_Box(BOX_0_SITE+KEY_LENGHT,BOX_0_SITE+KEY_TOTALWID*3,KEY_LENGHT*2,KEY_TOTALWID*4,4,Colour.black);
		break;
		case 13:Colour.black=LCD_COLOR_ORANGE;
				Disp_Box(BOX_0_SITE+KEY_LENGHT*2,BOX_0_SITE+KEY_TOTALWID*3,KEY_LENGHT*3,KEY_TOTALWID*4,4,Colour.black);
		break;
		case 14:Colour.black=LCD_COLOR_ORANGE;
				Disp_Box(BOX_0_SITE+KEY_LENGHT*3,BOX_0_SITE+KEY_TOTALWID*3,KEY_LENGHT*4,KEY_TOTALWID*4,4,Colour.black);
		break;
		case 15:Colour.black=White;
				Disp_Box(KEY_XLEFTP-4,BOX_0_SITE+KEY_TOTALWID*3,KEY_XRIGHT+3,KEY_TOTALWID*4,4,Colour.black);
		break;
		case 16:Colour.black=LCD_COLOR_ORANGE;
				Disp_Box(BOX_0_SITE,BOX_0_SITE+KEY_TOTALWID*4,KEY_LENGHT,KEY_TOTALWID*5,4,Colour.black);
		break;
		case 17:Colour.black=LCD_COLOR_ORANGE;
				Disp_Box(BOX_0_SITE+KEY_LENGHT,BOX_0_SITE+KEY_TOTALWID*4,KEY_LENGHT*2,KEY_TOTALWID*5,4,Colour.black);
		break;
		case 18:Colour.black=LCD_COLOR_ORANGE;
				Disp_Box(BOX_0_SITE+KEY_LENGHT*2,BOX_0_SITE+KEY_TOTALWID*4,KEY_LENGHT*3,KEY_TOTALWID*5,4,Colour.black);
		break;
		case 19:Colour.black=LCD_COLOR_ORANGE;
				Disp_Box(BOX_0_SITE+KEY_LENGHT*3,BOX_0_SITE+KEY_TOTALWID*4,KEY_LENGHT*4,KEY_TOTALWID*5,4,Colour.black);
		break;
		case 20:Colour.black=White;
				Disp_Box(KEY_XLEFTP-4,BOX_0_SITE+KEY_TOTALWID*4,KEY_XRIGHT+3,KEY_TOTALWID*5,4,Colour.black);
		break;
	}
}*/
void Draw_LIN5(uint8_t x,uint8_t y,uint16_t len,uint32_t color)
{	LCD_DrawLine(x,y,x+len,y,color);	//画水平线
	LCD_DrawLine(x,y+1,x+len,y+1,color);
	
}
void Draw_LIN3_Y(uint8_t x,uint8_t y,uint16_t len,uint32_t color)
{	LCD_DrawLine(x,y,x+len,y,color);	//
	LCD_DrawLine(x+1,y,x+1,y+len,color);
	LCD_DrawLine(x+2,y,x+2,y+len,color);

}
//extern void red421(uint8_t k0);
//extern void Write421(uint8_t addr,uint8_t dat);
/*
void R_ADJ_Pro1(void)//校准
{uint8_t rx[4]={0},m9;

if(Button_Page.third<9)//if(Button_Page.sumkey==0)
{
Button_Page.key%=100000;
	WriteString_16_Shade(32,30,Mi_Key[0],0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);//mima
	WriteString_16_Shade(290,30,Mi_Key[1],0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);//Enter
	DispBuf[5]=0;

	DispBuf[0]='0'+Button_Page.key/10000;
	DispBuf[1]='0'+Button_Page.key%10000/1000;
	DispBuf[2]='0'+Button_Page.key%1000/100;
	DispBuf[3]='0'+Button_Page.key%100/10;
	DispBuf[4]='0'+Button_Page.key%10;

	WriteString_16_Shade(120,30,DispBuf,0,POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);
	Colour.black=LCD_COLOR_TURQUOISE;
	Draw_LIN5(120,50,7,Colour.black);
	Draw_LIN5(130,50,7,Colour.black);
	Draw_LIN5(140,50,7,Colour.black);
	Draw_LIN5(150,50,7,Colour.black);
	Draw_LIN5(160,50,7,Colour.black);
	Disp_Box(283,25,345,50,4,Colour.black);
if(Button_Page.third==1)		Draw_LIN5(120,50,7,LCD_COLOR_ORANGE);//9
if(Button_Page.third==2)		Draw_LIN5(130,50,7,LCD_COLOR_ORANGE);//2
if(Button_Page.third==3)		Draw_LIN5(140,50,7,LCD_COLOR_ORANGE);//5
if(Button_Page.third==4)		Draw_LIN5(150,50,7,LCD_COLOR_ORANGE);//1
if(Button_Page.third==5)		Draw_LIN5(160,50,7,LCD_COLOR_ORANGE);//8
if(Button_Page.third==6)	Disp_Box(283,25,345,50,4,LCD_COLOR_ORANGE);
}
else// cal val float
{Colour.black=LCD_COLOR_TURQUOISE;
WriteString_16_Shade(32,58,Mi_Key[2],0,\
	POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);//range
WriteString_16_Shade(32,98,Mi_Key[3],0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);//input:
WriteString_16_Shade(220,98,Mi_Key[4],0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);//end
WriteString_16_Shade(295,98,Mi_Key[5],0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);//end
WriteString_16_Shade(35,168,Mi_Key[6],0,\
	POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);//R:

	if(Button_Page.force>9)Button_Page.force=9;//rang dis
DispBuf[0]='0'+Button_Page.force;
	DispBuf[1]=0;
	WriteString_16_Shade(120,58,DispBuf,0,POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);

	//Button_Page.key=(uint32_t)SaveData.div[Button_Page.force].adx;
	DispBuf[6]=0;

	m9=SaveData.div[Button_Page.force].bx[1]&0xf;
//	if(m9>9)
//		DispBuf[0]='0'+9;
//	else
	DispBuf[0]='0'+m9;
	DispBuf[1]='.';
	m9=(SaveData.div[Button_Page.force].bx[2]>>4)&0xf;
	DispBuf[2]='0'+m9;
	m9=(SaveData.div[Button_Page.force].bx[2])&0xf;
	DispBuf[3]='0'+m9;
	m9=(SaveData.div[Button_Page.force].bx[3]>>4)&0xf;
	DispBuf[4]='0'+m9;
	m9=(SaveData.div[Button_Page.force].bx[3])&0xf;
	DispBuf[5]='0'+m9;
	WriteString_16_Shade(120,98,DispBuf,0,POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);

//SaveData.div[0].adx/=100;
rx[1]=SaveData.div[Button_Page.force].bx[0]/10000;
rx[2]=rx[1]>>4;
if(rx[2]<10)DispBuf[0]='0'+rx[2];
else
{
if(rx[2]==0xa)DispBuf[0]='a';
	if(rx[2]==0xb)DispBuf[0]='b';
	if(rx[2]==0xc)DispBuf[0]='c';
	if(rx[2]==0xd)DispBuf[0]='d';
	if(rx[2]==0xe)DispBuf[0]='e';
	if(rx[2]==0xf)DispBuf[0]='f';
}
rx[2]=rx[1]&0xf;
if(rx[2]<10)DispBuf[1]='0'+rx[2];
else
{
if(rx[2]==0xa)DispBuf[1]='a';
	if(rx[2]==0xb)DispBuf[1]='b';
	if(rx[2]==0xc)DispBuf[1]='c';
	if(rx[2]==0xd)DispBuf[1]='d';
	if(rx[2]==0xe)DispBuf[1]='e';
	if(rx[2]==0xf)DispBuf[1]='f';
}
rx[1]=SaveData.div[Button_Page.force].bx[1];
rx[2]=rx[1]>>4;
if(rx[2]<10)DispBuf[2]='0'+rx[2];
else
{
if(rx[2]==0xa)DispBuf[2]='a';
	if(rx[2]==0xb)DispBuf[2]='b';
	if(rx[2]==0xc)DispBuf[2]='c';
	if(rx[2]==0xd)DispBuf[2]='d';
	if(rx[2]==0xe)DispBuf[2]='e';
	if(rx[2]==0xf)DispBuf[2]='f';
}
rx[2]=rx[1]&0xf;
if(rx[2]<10)DispBuf[3]='0'+rx[2];
else
{
if(rx[2]==0xa)DispBuf[3]='a';
	if(rx[2]==0xb)DispBuf[3]='b';
	if(rx[2]==0xc)DispBuf[3]='c';
	if(rx[2]==0xd)DispBuf[3]='d';
	if(rx[2]==0xe)DispBuf[3]='e';
	if(rx[2]==0xf)DispBuf[3]='f';
}
rx[1]=SaveData.div[Button_Page.force].bx[2];
rx[2]=rx[1]>>4;
if(rx[2]<10)DispBuf[4]='0'+rx[2];
else
{
if(rx[2]==0xa)DispBuf[4]='a';
	if(rx[2]==0xb)DispBuf[4]='b';
	if(rx[2]==0xc)DispBuf[4]='c';
	if(rx[2]==0xd)DispBuf[4]='d';
	if(rx[2]==0xe)DispBuf[4]='e';
	if(rx[2]==0xf)DispBuf[4]='f';
}
rx[2]=rx[1]&0xf;
if(rx[2]<10)DispBuf[5]='0'+rx[2];
else
{
if(rx[2]==0xa)DispBuf[5]='a';
	if(rx[2]==0xb)DispBuf[5]='b';
	if(rx[2]==0xc)DispBuf[5]='c';
	if(rx[2]==0xd)DispBuf[5]='d';
	if(rx[2]==0xe)DispBuf[5]='e';
	if(rx[2]==0xf)DispBuf[5]='f';
}
rx[1]=SaveData.div[Button_Page.force].bx[3];
rx[2]=rx[1]>>4;
if(rx[2]<10)DispBuf[6]='0'+rx[2];
else
{
if(rx[2]==0xa)DispBuf[6]='a';
	if(rx[2]==0xb)DispBuf[6]='b';
	if(rx[2]==0xc)DispBuf[6]='c';
	if(rx[2]==0xd)DispBuf[6]='d';
	if(rx[2]==0xe)DispBuf[6]='e';
	if(rx[2]==0xf)DispBuf[6]='f';
}
rx[2]=rx[1]&0xf;
if(rx[2]<10)DispBuf[7]='0'+rx[2];
else
{
if(rx[2]==0xa)DispBuf[7]='a';
	if(rx[2]==0xb)DispBuf[7]='b';
	if(rx[2]==0xc)DispBuf[7]='c';
	if(rx[2]==0xd)DispBuf[7]='d';
	if(rx[2]==0xe)DispBuf[7]='e';
	if(rx[2]==0xf)DispBuf[7]='f';
}
DispBuf[8]=0;
WriteString_16_Shade(120,130,DispBuf,0,POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);

Colour.black=LCD_COLOR_TURQUOISE;
	Disp_Box(215,93,260,118,4,Colour.black);
	Disp_Box(290,93,370,118,4,Colour.black);
	Draw_LIN5(120,75,7,Colour.black);
	Draw_LIN5(120,118,7,Colour.black);
	Draw_LIN5(140,118,7,Colour.black);
	Draw_LIN5(150,118,7,Colour.black);
	Draw_LIN5(160,118,7,Colour.black);
	Draw_LIN5(170,118,7,Colour.black);
if(Button_Page.third==10)	Draw_LIN5(120,75,7,LCD_COLOR_ORANGE);//1
if(Button_Page.third==11)	Draw_LIN5(120,118,7,LCD_COLOR_ORANGE);//1
if(Button_Page.third==12)	Draw_LIN5(140,118,7,LCD_COLOR_ORANGE);//.
if(Button_Page.third==13)	Draw_LIN5(150,118,7,LCD_COLOR_ORANGE);//0
if(Button_Page.third==14)	Draw_LIN5(160,118,7,LCD_COLOR_ORANGE);//0
if(Button_Page.third==15)	Draw_LIN5(170,118,7,LCD_COLOR_ORANGE);//0

if(Button_Page.third==17)	Disp_Box(290,93,370,118,4,LCD_COLOR_ORANGE);
if(Button_Page.third==16){Disp_Box(215,93,260,118,4,LCD_COLOR_ORANGE);
//	SaveData.div[Button_Page.force].adx=(float)Button_Page.key
}
//read 421 Rx

	rx[0]=Test_Dat.RBuff[0]>>4;

DispBuf[0]='0'+(Test_Dat.RBuff[0]&15);//wan
if(rx[0]%3==0)
{DispBuf[1]='0'+(Test_Dat.RBuff[1]>>4);//qian
DispBuf[2]='.';
DispBuf[3]='0'+(Test_Dat.RBuff[1]&15);//bai
}
if(rx[0]%3==1)
{DispBuf[1]='0'+(Test_Dat.RBuff[1]>>4);//qian
DispBuf[2]='0'+(Test_Dat.RBuff[1]&15);//bai
	DispBuf[3]='.';
}
if(rx[0]%3==2)
{DispBuf[1]='.';
	DispBuf[2]='0'+(Test_Dat.RBuff[1]>>4);//qian
DispBuf[3]='0'+(Test_Dat.RBuff[1]&15);//bai
}
DispBuf[4]='0'+(Test_Dat.RBuff[2]>>4);//shi
DispBuf[5]='0'+(Test_Dat.RBuff[2]&15);//ge

DispBuf[6]='0'+(Test_Dat.RBuff[3]>>4);
DispBuf[7]='0'+(Test_Dat.RBuff[3]&15);
DispBuf[9]=0;

WriteString_16_Shade(100,168,DispBuf,0,POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);
}
DispBuf[2]=0;
	DispBuf[0]='0'+Button_Page.third/10;
	DispBuf[1]='0'+Button_Page.third%10;

	WriteString_16_Shade(190,5,DispBuf,0,POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);
}
//数值按键上显示上下限的字
void Disp_UpOrLow_Limit_Word()
{
	Colour.Fword=White;
	if(SaveData.Main.mode)
	{
		if(Button_Page.index==6)//
			WriteString21(46,24,Keyboard[0],0,(uint8_t)(LCD_COLOR_TURQUOISE>>16),(uint8_t)(LCD_COLOR_TURQUOISE>>8),(uint8_t)LCD_COLOR_TURQUOISE,0,COLORFLAG);
		else if(Button_Page.index==7)
			WriteString21(46,24,Keyboard[1],0,(uint8_t)(LCD_COLOR_TURQUOISE>>16),(uint8_t)(LCD_COLOR_TURQUOISE>>8),(uint8_t)LCD_COLOR_TURQUOISE,0,COLORFLAG);
	}
	else if(GetSystemStatus()==SYS_STATUS_SHIFTSET)
		WriteString21(66,24,Keyboard[2],0,(uint8_t)(LCD_COLOR_TURQUOISE>>16),(uint8_t)(LCD_COLOR_TURQUOISE>>8),(uint8_t)LCD_COLOR_TURQUOISE,0,COLORFLAG);
}
//数字按键深颜色色块
void Num_Key_Dark_Block(void)
{
	 uint8_t i,j;
	 for(i=1;i<5;i++)		//按键颜色渐变
	 {
		  LCD_DrawRectShade(KEY_XLEFTP,i*KEY_HIGH+4*(i+1)-1,KEY_XRIGHT,(i+1)*(KEY_HIGH+4),KEY_RED,KEY_RED,KEY_RED,KEY_CHANG,COLORFLAG);
		 for(j=0;j<3;j++)	//直线颜色渐变
	     {
	   	    LCD_DrawLineShade(KEY_XLEFTP-3+j,i*KEY_HIGH+4*(i+1)+(2-j),KEY_XLEFTP-3+j,(i+1)*(KEY_HIGH+4)-(4-j),\
								KEY_LINE_COL,KEY_LINE_COL,KEY_LINE_COL,KEY_CHANG, COLORFLAG); 
		      LCD_DrawLineShade(KEY_XRIGHT+j,i*KEY_HIGH+4*(i+1)+j,KEY_XRIGHT+j,(i+1)*(KEY_HIGH+4)-(j+2),\
								KEY_LINE_COL,KEY_LINE_COL,KEY_LINE_COL,KEY_CHANG, COLORFLAG);
	     }
	 }
}
//数字按键浅颜色色块
void Num_Key_Thin_Block(void)
{
   uint8_t i,j,k;
	for(k=1;k<5;k++)
	for(i=0;i<4;i++)		  				//第二行的矩形显示
   {
     	LCD_DrawRectShade(i*KEY_LENGHT+3+3,(KEY_TOTALWID*k+3),(i+1)*KEY_LENGHT-3,KEY_TOTALWID*(k+1),\
						   POLYGON_RED,POLYGON_RED,POLYGON_RED,POLYGON_CHANG,COLORFLAG);
		for(j=0;j<3;j++)
	   {
	   	    LCD_DrawLineShade(i*KEY_LENGHT+3+j,(KEY_TOTALWID*k+3)+(3-j),i*KEY_LENGHT+3+j,KEY_TOTALWID*(k+1)-(4-j),\
								POLYGON_LINE,POLYGON_LINE,POLYGON_LINE,POLYGON_CHANG,COLORFLAG); 
		    LCD_DrawLineShade((i+1)*KEY_LENGHT-j-1,(KEY_TOTALWID*k+3)+(3-j),(i+1)*KEY_LENGHT-j-1,KEY_TOTALWID*(k+1)-(4-j),\
								POLYGON_LINE,POLYGON_LINE,POLYGON_LINE,POLYGON_CHANG,COLORFLAG); 
	   }
   }
}
void Input_Bar(void) //输入条
{
//LCD_DrawRect(KEY_LENGHT+4,KEY_TOTALWID-22,KEY_LENGHT*4-1,KEY_TOTALWID,LCD_COLOR_DARKGREY);
	LCD_DrawRectShade(KEY_LENGHT+4,KEY_TOTALWID-30,4*KEY_LENGHT-1,KEY_TOTALWID,\
						   POLYGON_RED,POLYGON_RED,POLYGON_RED,POLYGON_CHANG,COLORFLAG);
	LCD_DrawLine(KEY_LENGHT+4,KEY_TOTALWID,KEY_LENGHT*4-1,KEY_TOTALWID,LCD_COLOR_BABYGREY);
	LCD_DrawLine(KEY_LENGHT*4-1,KEY_TOTALWID-30,KEY_LENGHT*4-1,KEY_TOTALWID,LCD_COLOR_BABYGREY);
}
//Button_Page_Typedef* Button_Page数字按键界面
void Num_Keyboard()
{
	LCD_DrawRect(0,0,480,272,LCD_COLOR_TURQUOISE);
	Num_Key_Dark_Block();
	Num_Key_Thin_Block();
	Input_Bar();
	Disp_Num_Key();
	Disp_UpOrLow_Limit_Word();
	//Disp_Num_Keyboard_Box();//Button_Page
//	while(1);
}
//显示按键功能值(Test page)
void  Disp_Test_Row(void)
{
	uint8_t i;
	Colour.Fword=White;//Yellow;         0x07FF
		for(i=0;i<3;i++)
			{
			if(SaveData.Main.beep)
				WriteString21(KEY_XLEFTP+1,KEY_TOTALWID*i+13,T_Right[i],0,KEY_WORD,KEY_WORD,KEY_WORD,KEY_CHANG,COLORFLAG);
			else
				WriteString21(KEY_XLEFTP+1,KEY_TOTALWID*i+13,T2_Right[i],0,KEY_WORD,KEY_WORD,KEY_WORD,KEY_CHANG,COLORFLAG);
			}
	WriteString21(KEY_XLEFTP+1,KEY_TOTALWID*5+13,T_Right[3],0,KEY_WORD,KEY_WORD,KEY_WORD,KEY_CHANG,COLORFLAG);
}
//显示按键功能值(Comp page)
void  Disp_Comp_Row(void)
{
//	uint8_t i;
	Colour.Fword=White;//Yellow;         0x07FF
//		for(i=0;i<2;i++)KEY_TOTALWID*i+
			WriteString21(KEY_XLEFTP+1,13,Comp_Set_Right[0],0,KEY_WORD,KEY_WORD,KEY_WORD,KEY_CHANG,COLORFLAG);
	//		WriteString21(KEY_XLEFTP+1,KEY_TOTALWID*2+3,Comp_Set_Right[2],0,KEY_WORD,KEY_WORD,KEY_WORD,KEY_CHANG,COLORFLAG);
			WriteString21(KEY_XLEFTP+1,KEY_TOTALWID*5+13,Comp_Set_Right[3],0,KEY_WORD,KEY_WORD,KEY_WORD,KEY_CHANG,COLORFLAG);
}
//显示按键功能值(SYS page)
void  Disp_Button_Sys(void)
{
	uint8_t i;
	Colour.Fword=White;//Yellow;         0x07FF
		for(i=0;i<3;i++)
			WriteString21(KEY_XLEFTP+1,KEY_TOTALWID*i+4,Comp_Set[i],0,KEY_WORD,KEY_WORD,KEY_WORD,KEY_CHANG,COLORFLAG);
	WriteString21(KEY_XLEFTP+1,KEY_TOTALWID*5+13,Comp_Set[3],0,KEY_WORD,KEY_WORD,KEY_WORD,KEY_CHANG,COLORFLAG);
}
//按键方框显示
void Disp_Key_Box(Button_Page_Typedef* Button_Page)
{
	uint8_t i;
	Colour.black=LCD_COLOR_TURQUOISE;
	for(i=0;i<6;i++)
		Disp_Box(KEY_XLEFTP-4,BOX_0_SITE+KEY_TOTALWID*i,KEY_XRIGHT+3,KEY_TOTALWID*(i+1),4,Colour.black);

	switch (Button_Page->sumkey)
	{
		case 1:			Colour.black=White;
			Disp_Box(KEY_XLEFTP-4,BOX_0_SITE,KEY_XRIGHT+3,KEY_TOTALWID,4,Colour.black);
		break;
		case 2:			Colour.black=White;
			Disp_Box(KEY_XLEFTP-4,BOX_0_SITE+KEY_TOTALWID,KEY_XRIGHT+3,KEY_TOTALWID*2,4,Colour.black);
		break;
		case 3:			Colour.black=White;
			Disp_Box(KEY_XLEFTP-4,BOX_0_SITE+KEY_TOTALWID*2,KEY_XRIGHT+3,KEY_TOTALWID*3,4,Colour.black);
		break;
		case 4:			Colour.black=White;
			Disp_Box(KEY_XLEFTP-4,BOX_0_SITE+KEY_TOTALWID*3,KEY_XRIGHT+3,KEY_TOTALWID*4,4,Colour.black);
		break;
		case 5:			Colour.black=White;
			Disp_Box(KEY_XLEFTP-4,BOX_0_SITE+KEY_TOTALWID*4,KEY_XRIGHT+3,KEY_TOTALWID*5,4,Colour.black);
		break;
		case 6:			Colour.black=White;
			Disp_Box(KEY_XLEFTP-4,BOX_0_SITE+KEY_TOTALWID*5,KEY_XRIGHT+3,KEY_TOTALWID*6,4,Colour.black);
		break;
}
}
void Disp_Test(void)//主测试页面
{
	uint8_t i;
	Colour.Fword=White;
//	LCD_DrawRect(0, 0, 480,272 , LCD_COLOR_TURQUOISE);
	Polygon_Box();
	KEY_COLORBLOCK();
	for(i=0;i<8;i++)
	{
		if(i<4)//H1
		{
		if(i)
		{if(SaveData.Main.mode)
		WriteString21(KEY_LENGHT*(i)+32,13,Disp_Com_Menu[i],0,POLYGON_WORD1,POLYGON_WORD1,POLYGON_WORD1,POLYGON_CHANG,COLORFLAG);
		else
		WriteString21(KEY_LENGHT*(i)+32,13,Disp_Set_Menu[i],0,POLYGON_WORD1,POLYGON_WORD1,POLYGON_WORD1,POLYGON_CHANG,COLORFLAG);
		}
		else
			{if(SaveData.Main.mode)
		WriteString21(10,13,Disp_Com_Menu[0],0,POLYGON_WORD1,POLYGON_WORD1,POLYGON_WORD1,POLYGON_CHANG,COLORFLAG);
		else
		WriteString21(10,13,Disp_Set_Menu[0],0,POLYGON_WORD1,POLYGON_WORD1,POLYGON_WORD1,POLYGON_CHANG,COLORFLAG);
		}
		}
			else//H2
		{//	Colour.Fword=Yellow;
		if(SaveData.Main.mode)
		{//if(i==5)
			//WriteString21(KEY_LENGHT*(i-4)+8,4+KEY_TOTALWID,Disp_Com_Menu[i],0,POLYGON_WORD2,POLYGON_WORD2,POLYGON_WORD2,POLYGON_CHANG,COLORFLAG);
			//else
			WriteString21(KEY_LENGHT*(i-4)+32,4+KEY_TOTALWID,Disp_Com_Menu[i],0,POLYGON_WORD2,POLYGON_WORD2,POLYGON_WORD2,POLYGON_CHANG,COLORFLAG);
		}
		else
		WriteString21(KEY_LENGHT*(i-4)+32,4+KEY_TOTALWID,Disp_Test_Menu[i],0,POLYGON_WORD2,POLYGON_WORD2,POLYGON_WORD2,POLYGON_CHANG,COLORFLAG);
		}
	}
//	Disp_Button_Test();
}

//测试设置界面
void  Disp_Test_Set(Button_Page_Typedef* Button_Page)
{
	uint8_t i;
	Colour.Fword=LCD_COLOR_BABYBLUE;
	Colour.black=LCD_COLOR_TURQUOISE;

	if(SaveData.Main.mode)//Disp_Set_Resist.Parameter
	WriteString_16_Shade(33,POLYGON_SEC,Comp_Parameter[SaveData.Main.compar],0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);//on off
	else//test
	WriteString_16_Shade(33,POLYGON_SEC,T_Parameter[Disp_Set_Resist.Parameter],0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);//R

if(SaveData.Main.mode)
	WriteString_16_Shade(32+KEY_LENGHT,POLYGON_SEC,T_Mode[0],0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);
	else
	WriteString_16_Shade(32+KEY_LENGHT,POLYGON_SEC,T_Rang[SaveData.Main.range],0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);//disp 200K //Disp_Set_Resist.Rang

	if(SaveData.Main.mode)
	{
		if(SaveData.Limit.Hi[0].Num)
	{
		Hex_Format(SaveData.Limit.Hi[0].Num,SaveData.Limit.Hi[0].Dot,6,0);//加单位
		WriteString_16_Shade(10+KEY_LENGHT*2,POLYGON_SEC,DispBuf,0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);
		WriteString_16_Shade(80+KEY_LENGHT*2,POLYGON_SEC,Button_Key_Num_UpOrLowM[SaveData.Limit.Hi[0].Unit],0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);
	}
	else
		WriteString_16_Shade(10+KEY_LENGHT*2,POLYGON_SEC,Compare_Uplimt[SaveData.Limit.Hi[0].Num],0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);
}
	else
	WriteString_16_Shade(27+KEY_LENGHT*2,POLYGON_SEC,T_Speed[SaveData.Main.speed],0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);//Disp_Set_Resist.Speed

	if(SaveData.Main.mode)
	{
	if(SaveData.Limit.Low[0].Num)
	{
		Hex_Format(SaveData.Limit.Low[0].Num,SaveData.Limit.Low[0].Dot,6,0);//加单位
		WriteString_16_Shade(10+KEY_LENGHT*3,POLYGON_SEC,DispBuf,0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);
		WriteString_16_Shade(80+KEY_LENGHT*3,POLYGON_SEC,Button_Key_Num_UpOrLowM[SaveData.Limit.Low[0].Unit],0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);
	}
	else
		WriteString_16_Shade(10+KEY_LENGHT*3,POLYGON_SEC,Compare_Uplimt[SaveData.Limit.Low[0].Num],0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);
	}

	else
	WriteString_16_Shade(37+KEY_LENGHT*3,POLYGON_SEC,T_Trigger[SaveData.Main.trig],0,\
							 POLYGON_EN,POLYGON_EN,POLYGON_EN,POLYGON_CHANG,COLORFLAG);//Disp_Set_Resist.Trigger
for(i=0;i<4;i++)
				{Disp_Box(BOX_0_SITE+i*96,BOX_0_SITE,96+i*96,45,4,LCD_COLOR_TURQUOISE);
				Disp_Box(BOX_0_SITE+i*96,47,96+i*96,90,4,LCD_COLOR_TURQUOISE);
				}
	switch(Button_Page->index)
	{
		case 0:		//	Colour.black=LCD_COLOR_ORANGE;
			Disp_Box(BOX_0_SITE,BOX_0_SITE,KEY_LENGHT,45,4,LCD_COLOR_ORANGE);//Colour.black
			break;
		case 1:			Colour.black=LCD_COLOR_ORANGE;
			Disp_Box(BOX_0_SITE+KEY_LENGHT,BOX_0_SITE,KEY_LENGHT*2,45,4,Colour.black);//Colour.black
			break;
		case 2:			Colour.black=LCD_COLOR_ORANGE;
			Disp_Box(BOX_0_SITE+KEY_LENGHT*2,BOX_0_SITE,KEY_LENGHT*3,45,4,Colour.black);
			break;
		case 3:			Colour.black=LCD_COLOR_ORANGE;
		  Disp_Box(BOX_0_SITE+KEY_LENGHT*3,BOX_0_SITE,KEY_LENGHT*4,45,4,Colour.black);//工具
			break;
		case 4:			Colour.black=LCD_COLOR_ORANGE;
			Disp_Box(BOX_0_SITE,BOX_0_SITE+KEY_TOTALWID,KEY_LENGHT,45+KEY_TOTALWID,4,Colour.black);//	参数
			break;
		case 5:			Colour.black=LCD_COLOR_ORANGE;
			Disp_Box(BOX_0_SITE+KEY_LENGHT,BOX_0_SITE+KEY_TOTALWID,KEY_LENGHT*2,45+KEY_TOTALWID,4,Colour.black);//量程			
			break;
		case 6:			Colour.black=LCD_COLOR_ORANGE;
			Disp_Box(BOX_0_SITE+KEY_LENGHT*2,BOX_0_SITE+KEY_TOTALWID,KEY_LENGHT*3,45+KEY_TOTALWID,4,Colour.black);//速度
			break;
		case 7:			Colour.black=LCD_COLOR_ORANGE;
			Disp_Box(BOX_0_SITE+KEY_LENGHT*3,BOX_0_SITE+KEY_TOTALWID,KEY_LENGHT*4,45+KEY_TOTALWID,4,Colour.black);//触发
			break;
	}
	KEY_COLORBLOCK();
	switch(Button_Page->index)//主页索引
	{
		case 0:			Disp_Test_Row();
			break;
		case 1:			Disp_Comp_Row();//系统
			break;
		case 20:	Colour.Fword=White;	//文件 Test_File
		    for(i=0;i<3;i++)
			{	if(i<2)
					WriteString21(KEY_XLEFTP+1,13+KEY_TOTALWID*i,Test_File[i],0,\
							  KEY_WORD,KEY_WORD,KEY_WORD,KEY_CHANG,COLORFLAG);
				else
					WriteString21(KEY_XLEFTP+1,4+KEY_TOTALWID*i,Test_File[i],0,\
							  KEY_LINE_COL,KEY_LINE_COL,KEY_LINE_COL,KEY_CHANG,COLORFLAG);			
			}
			if(Disp_Set_Resist.File==0)
				WriteString_16_Shade(KEY_XLEFTP+26,27+KEY_TOTALWID*2,Test_File_Save[Disp_Set_Resist.File],0,\
							 KEY_DIS_MODE1,KEY_DIS_MODE1,KEY_DIS_MODE1,KEY_CHANG,COLORFLAG);
			else 
				WriteString_16_Shade(KEY_XLEFTP+31,27+KEY_TOTALWID*2,Test_File_Save[Disp_Set_Resist.File],0,\
							 KEY_DIS_MODE1,KEY_DIS_MODE1,KEY_DIS_MODE1,KEY_CHANG,COLORFLAG);
			break;
		case 30:		Colour.Fword=White;//Test_Tool

			if(Disp_Set_Resist.Tool==0)
				WriteString_16_Shade(KEY_XLEFTP+26,27,Test_Tool[Disp_Set_Resist.Tool],0,\
							 KEY_DIS_MODE1,KEY_DIS_MODE1,KEY_DIS_MODE1,KEY_CHANG,COLORFLAG);
			else 
				WriteString_16_Shade(KEY_XLEFTP+31,27,Test_Tool[Disp_Set_Resist.Tool],0,\
							 KEY_DIS_MODE1,KEY_DIS_MODE1,KEY_DIS_MODE1,KEY_CHANG,COLORFLAG);
			break;
		case 4:			Colour.Fword=White;
			for(i=0;i<2;i++)
					{
						if(SaveData.Main.mode)
						WriteString_16_Shade(KEY_XLEFTP+26,17+i*KEY_TOTALWID,Comp_Parameter[i],0,\
							 KEY_WORD2,KEY_WORD2,KEY_WORD2,KEY_CHANG,COLORFLAG);//ON/OFF
						else
							WriteString_16_Shade(KEY_XLEFTP+26,17+i*KEY_TOTALWID,T_Parameter[i],0,\
							 KEY_WORD2,KEY_WORD2,KEY_WORD2,KEY_CHANG,COLORFLAG);//R/LPR
					}
			break;
		case 5:			Colour.Fword=White;
			if(SaveData.Main.mode)
			{for(i=0;i<2;i++)
			WriteString_16_Shade(KEY_XLEFTP+21,17+i*KEY_TOTALWID,User_LimitList_Value[i],0,\
							 KEY_WORD2,KEY_WORD2,KEY_WORD2,KEY_CHANG,COLORFLAG);//abs/%
			}
				else
					for(i=0;i<4;i++)
			{
				if(i<2)
					WriteString_16_Shade(KEY_XLEFTP+21,17+i*KEY_TOTALWID,Rang_Button_Tip[i],0,\
							 KEY_WORD2,KEY_WORD2,KEY_WORD2,KEY_CHANG,COLORFLAG);
				else
					WriteString_16_Shade(KEY_XLEFTP+33,17+i*KEY_TOTALWID,Rang_Button_Tip[i],0,\
							 KEY_WORD2,KEY_WORD2,KEY_WORD2,KEY_CHANG,COLORFLAG);					
			}
			break;
		case 6:			Colour.Fword=White;
			if(!SaveData.Main.mode)
			{
			for(i=0;i<3;i++)
			{
				if(i==0)
					WriteString_16_Shade(KEY_XLEFTP+11,17+i*KEY_TOTALWID,T_Speed[i],0,\
							 KEY_WORD2,KEY_WORD2,KEY_WORD2,KEY_CHANG,COLORFLAG);
				else
					WriteString_16_Shade(KEY_XLEFTP+16,17+i*KEY_TOTALWID,T_Speed[i],0,\
							 KEY_WORD2,KEY_WORD2,KEY_WORD2,KEY_CHANG,COLORFLAG);					
			}
			}
			break;
		case 7:	Colour.Fword=White;
			if(!SaveData.Main.mode)
			{for(i=0;i<2;i++)
				WriteString_16_Shade(KEY_XLEFTP+26,17+i*KEY_TOTALWID,T_Trigger[i],0,\
						 KEY_WORD2,KEY_WORD2,KEY_WORD2,KEY_CHANG,COLORFLAG);
			}
			break;
	}
}

void lcd_image(uint8_t *pt)
{
    unsigned long i;
	uint32_t color;
	unsigned long *pDst = (unsigned long *)LCD_VRAM_BASE_ADDR+480*272;
  
    for( i = 0; (C_GLCD_H_SIZE * C_GLCD_V_SIZE) > i; i++)
    {
		color=(uint32_t)*pt<<16|(uint32_t)*(pt+1)<<8|*(pt+2);
    	*pDst-- = color; 
		*pt++;
		*pt++;
		*pt++;
    }
}
*/
//uint8_t buff3[6]={0};
void Savetoeeprom(void)
{
	u8 *pt;

	SaveData.Main.mode%=2;
	SaveData.Main.alrm%=2;
	SaveData.Main.boud%=8;
//	SaveData.Main.speed%=3;
	SaveData.Main.beep%=2;

//	Saveeeprom.Save_Main.lockrang%=2;
//	Saveeeprom.Save_Main.lock%=2;

//	Saveeeprom.Save_Main.lockrang=SaveData.Main.lockrang;
//	Saveeeprom.Save_Main.lock=SaveData.Main.lock;

	Saveeeprom.Save_Main.adr=AddressVal;//abs  %
	Saveeeprom.Save_Main.check = Check_SetMod;
	Saveeeprom.Save_Main.alrm=Flag_Alarm_OFF;
	Saveeeprom.Save_Main.boud=BaudRate_SetVal;//SaveData.Main.boud;	
	Saveeeprom.Save_Main.mode=TMode;
	Saveeeprom.Save_Main.vrange=VRANGE;
	Saveeeprom.Save_Main.irange=IRANGE;
	Saveeeprom.Save_Main.filter=flag_SetFilter;
	Saveeeprom.Save_Main.iomode=flag_SetIOMode;
	Saveeeprom.Save_Main.clear=flag_SetAutoZero;
	Saveeeprom.Save_Main.lang=flag_SetLang;
	Saveeeprom.Save_Main.signal=flag_SetPower;
	Saveeeprom.Save_Main.usbmode=flag_SetUSBMode;
	Saveeeprom.Save_Main.beep=Flag_Beep_OFF;
	Saveeeprom.Save_Main.hotkey=flag_SetHotKey;
	
//	Saveeeprom.Save_Main.speed=SaveData.Main.speed;

//	Saveeeprom.Save_Main.beep=SaveData.Main.beep;
//	SaveData.Main.compar%=2;
//	Saveeeprom.Save_Main.compar=SaveData.Main.compar;
//	Saveeeprom.Save_Main_Func.buad=SaveData.Main_Func.buad;
//	Saveeeprom.div[0]=SaveData.div[0];
//	Saveeeprom.div[1]=SaveData.div[1];
//	Saveeeprom.div[2]=SaveData.div[2];
//	Saveeeprom.div[3]=SaveData.div[3];
//	Saveeeprom.div[4]=SaveData.div[4];
//	Saveeeprom.div[5]=SaveData.div[5];
//	Saveeeprom.div[6]=SaveData.div[6];
//	Saveeeprom.div[7]=SaveData.div[7];
//	Saveeeprom.div[8]=SaveData.div[8];
//	Saveeeprom.div[9]=SaveData.div[9];
//	
//	Saveeeprom.zer[0].ax=SaveData.zer[0].ax;
//	Saveeeprom.zer[1].ax=SaveData.zer[1].ax;
//	Saveeeprom.zer[2].ax=SaveData.zer[2].ax;
//	Saveeeprom.zer[3].ax=SaveData.zer[3].ax;
//	Saveeeprom.zer[4].ax=SaveData.zer[4].ax;
//	Saveeeprom.zer[5].ax=SaveData.zer[5].ax;
//	Saveeeprom.zer[6].ax=SaveData.zer[6].ax;
//	Saveeeprom.zer[7].ax=SaveData.zer[7].ax;
//	Saveeeprom.zer[8].ax=SaveData.zer[8].ax;
//	Saveeeprom.zer[9].ax=SaveData.zer[9].ax;

//	Saveeeprom.Limit=SaveData.Limit;
Saveeeprom.Limit.Hi[0].Num=CurrentLimit;
Saveeeprom.Limit.Hi[1].Num=POWLimit;

	pt=(u8*)&Saveeeprom;
	
	EEPROM_Write(0,0,pt,MODE_8_BIT,sizeof(Saveeeprom));
}
void ReadSavedata(void)
{
	u8 i;
	Saveeprom *pt;
	pt=&Saveeeprom;
	EEPROM_Read(0,0,(u8 *)pt,MODE_8_BIT, sizeof(Saveeeprom));
	for(i=0;i<12;i++)
	{
		if(*((u8 *)(pt+i))>50)			*(u8 *)(pt+i)=0;
	}
//.Range
//	SaveData.div[0]=Saveeeprom.div[0];
//	SaveData.div[1]=Saveeeprom.div[1];
//	SaveData.div[2]=Saveeeprom.div[2];
//	SaveData.div[3]=Saveeeprom.div[3];
//	SaveData.div[4]=Saveeeprom.div[4];
//	SaveData.div[5]=Saveeeprom.div[5];
//	SaveData.div[6]=Saveeeprom.div[6];
//	SaveData.div[7]=Saveeeprom.div[7];
//	SaveData.div[8]=Saveeeprom.div[8];
//	SaveData.div[9]=Saveeeprom.div[9];
//Saveeeprom.Save_Main.param%=2;
	AddressVal=Saveeeprom.Save_Main.adr;//SaveData.Main.adr
	
	Saveeeprom.Save_Main.mode%=2;
	SaveData.Main.mode=Saveeeprom.Save_Main.mode;
	
	Saveeeprom.Save_Main.alrm%=2;
	Flag_Alarm_OFF=Saveeeprom.Save_Main.alrm;
	
	Saveeeprom.Save_Main.boud%=8;
	BaudRate_SetVal=Saveeeprom.Save_Main.boud;
	
	Saveeeprom.Save_Main.check%=4;
	Check_SetMod=Saveeeprom.Save_Main.check;
	
	Saveeeprom.Save_Main.mode%=2;
	TMode = Saveeeprom.Save_Main.mode;
	
	Saveeeprom.Save_Main.vrange%=5;
	VRANGE = Saveeeprom.Save_Main.vrange;
	
	Saveeeprom.Save_Main.irange%=8;
	IRANGE = Saveeeprom.Save_Main.irange;
	
	Saveeeprom.Save_Main.filter%=2;
	flag_SetFilter = Saveeeprom.Save_Main.filter;
	
	Saveeeprom.Save_Main.iomode%=2;
	flag_SetIOMode = Saveeeprom.Save_Main.iomode;
	
	Saveeeprom.Save_Main.clear%=2;
	flag_SetAutoZero = Saveeeprom.Save_Main.clear;
	
	Saveeeprom.Save_Main.lang%=2;
	flag_SetLang = Saveeeprom.Save_Main.lang;
	
	Saveeeprom.Save_Main.signal%=2;
	flag_SetPower = Saveeeprom.Save_Main.signal;
	
	Saveeeprom.Save_Main.usbmode%=2;
	flag_SetUSBMode = Saveeeprom.Save_Main.usbmode;
	
	Saveeeprom.Save_Main.beep%=2;
	Flag_Beep_OFF = Saveeeprom.Save_Main.beep;
	
	Saveeeprom.Save_Main.hotkey%=2;
	flag_SetHotKey = Saveeeprom.Save_Main.hotkey;
	
//	Saveeeprom.Save_Main.speed%=3;
//	SaveData.Main.speed=Saveeeprom.Save_Main.speed;
//	Saveeeprom.Save_Main.beep%=2;
//	SaveData.Main.beep=Saveeeprom.Save_Main.beep;
//	Saveeeprom.Save_Main.compar%=2;
//	SaveData.Main.compar=Saveeeprom.Save_Main.compar;

//	SaveData.Main_Func.buad=Saveeeprom.Save_Main_Func.buad;
//Saveeeprom.Save_Main.lockrang%=2;
//	SaveData.Main.lockrang=Saveeeprom.Save_Main.lockrang;
//	Saveeeprom.Save_Main.lock%=2;
//	SaveData.Main.lock=Saveeeprom.Save_Main.lock;

//	SaveData.Limit=Saveeeprom.Limit;

	for(i=0;i<3;i++)
	{
	//	if(SaveData.Limit.Hi[i].Dot>5)			SaveData.Limit.Hi[i].Dot=1;
	//	if(SaveData.Limit.Hi[i].Unit>4)			SaveData.Limit.Hi[i].Unit=1;
		if(SaveData.Limit.Hi[i].Num>100000)	SaveData.Limit.Hi[i].Num=0;

//		if(SaveData.Limit.Low[i].Dot>5)			SaveData.Limit.Low[i].Dot=1;
//		if(SaveData.Limit.Low[i].Unit>4)		SaveData.Limit.Low[i].Unit=1;
//		if(SaveData.Limit.Low[i].Num>100000)SaveData.Limit.Low[i].Num=0;
	}
CurrentLimit=Saveeeprom.Limit.Hi[0].Num;
POWLimit=Saveeeprom.Limit.Hi[1].Num;
//					SaveData.zer[0].ax=Saveeeprom.zer[0].ax;
//					SaveData.zer[1].ax=Saveeeprom.zer[1].ax;
//					SaveData.zer[2].ax=Saveeeprom.zer[2].ax;
//					SaveData.zer[3].ax=Saveeeprom.zer[3].ax;
//					SaveData.zer[4].ax=Saveeeprom.zer[4].ax;
//					SaveData.zer[5].ax=Saveeeprom.zer[5].ax;
//					SaveData.zer[6].ax=Saveeeprom.zer[6].ax;
//					SaveData.zer[7].ax=Saveeeprom.zer[7].ax;
//					SaveData.zer[8].ax=Saveeeprom.zer[8].ax;
//					SaveData.zer[9].ax=Saveeeprom.zer[9].ax;
}

	void Disp_Sys_Screen(void)
{
//	Disp_TopBar_Color();
	LCD_DrawRect(0, 0, 112,22 , LCD_COLOR_TEST_BAR);
	//Disp_Fastbutton();//显示快速按键	  
//	Disp_ListScan_MidRect();//显示中间色块	 User_LimitList_Item  
}
const char All_TopName[][20]=
{
	{"<测量显示>"},
	{"<档号显示>"},
	{"<档计数显示>"},
	{"<列表扫描显示>"},
	{"<测量设置>"},
	{"<用户校正>"},
	{"<极限列表设置>"},
	{"<列表扫描设置>"},
	{"<系统设置>"},
	{"[LCR文件列表]"},
	{"<校正设置>"},

};
const char All_TopName_E[][20]=
{
	{"<MEAS DISPLAY>     "},
	{"<BIN No. DISP>     "},
	{"<BIN COUNT DISP>   "},
	{"<LIST SWEEP DISP>  "},
	{"<MEASURE SETUP>    "},
	{"<CORRECTION>       "},
	{"<LIMIT TABLE SETUP>"},
	{"<LIST SWEEP SETUP> "},
	{"<SYSTEM SETUP>     "},
	{"[LCR FILE LIST]    "},
	{"<CORRECTION SET>   "},

};
const char Sys_Setitem_E[][10+1]=
{
	{"MAIN FUNC:"},
	{"PASS BEEP:"},
//	{"FAIL BEEP:"},
	{"U  SWITCH:"},
	{"LANGUAGE :"},
	//{"PASS WORD:"},
	{"MENU DISP:"},
	{"DATA     :"},
	{"BAUD RATE:"},
	{"BIAS SRC :"},
	{"BUS MODE :"},
	{"GPIBADDR :"},
	{"TALK ONLY:"},
	{"TIME     :"}
};
//系统设置子函数
void Disp_SysLine(void)
{
 	uint32_t i;
	for(i=0;i<(sizeof(Sys_Setitem_E)/(sizeof(Sys_Setitem_E[0])));i++)
	{
		if(i<((sizeof(Sys_Setitem_E)/(sizeof(Sys_Setitem_E[0]))+1)/2))
			LCD_DrawLine( 95, FIRSTLINE+(i+1)*SPACE1-2, 90+100,FIRSTLINE+(i+1)*SPACE1-2, White );
		else
			LCD_DrawLine( 95+250, FIRSTLINE+(i-(sizeof(Sys_Setitem_E)/(sizeof(Sys_Setitem_E[0]))-1)/2)*SPACE1-2, 90+100+250,FIRSTLINE+(i-(sizeof(Sys_Setitem_E)/(sizeof(Sys_Setitem_E[0]))-1)/2)*SPACE1-2, White );
	}

}
// 显示系统逗号
static void  Disp_SysDot(void)
{
	uint8_t i;
	for(i=0;i<(sizeof(Sys_Setitem_E)/(sizeof(Sys_Setitem_E[0])));i++)
	{
		if(i<((sizeof(Sys_Setitem_E)/(sizeof(Sys_Setitem_E[0]))+1)/2))
			WriteString_16(LIST1+84, FIRSTLINE+SPACE1*i, ":",  0);
		else
			WriteString_16(LIST2+84, FIRSTLINE+SPACE1*(i-(sizeof(Sys_Setitem_E)/(sizeof(Sys_Setitem_E[0])))/2), ":",  0);	
	}
}
void Disp_Button_SysSet(void)
{
		Colour.Fword=White;
		Colour.black=LCD_COLOR_TEST_BUTON;
//		WriteString_16(83, 271-29, "密码设置",  0);
	//	WriteString_16(83, 271-29, "测量设置",  0);
	WriteString_16(83, 271-29, "Meas Set",  0);
//		WriteString_16(83, 271-29, "系统",  0);
//		WriteString_16(83, 271-29, "设置",  0);
//		WriteString_16(83+80, 271-29, "设置",  0);
//		WriteString_16(84+80+80, 271-40, "极限",  0);
//		WriteString_16(84+80+80, 271-20, "设置",  0);
//		WriteString_16(84+80+80+80, 271-40, "默认",  0);
//		WriteString_16(84+80+80+80, 271-20, "设置",  0);
//		WriteString_16(84+80+80+80+80, 271-40, "系统",  0);
//		WriteString_16(84+80+80+80+80, 271-20, "复位",  0);
}
//系统设置
void Disp_Sys_Item(void)
{
	uint32_t i;
	//Disp_Sys_Screen();
	Colour.Fword=White;
	Colour.black=Black;
	WriteString_16(0,4,All_TopName_E[8],0);
	//Colour.Fword=White;
	//Colour.black=Black;
//	WriteString_16(LIST1, FIRSTLINE, User_ListScan_Item[0],0);

	for(i=0;i<(sizeof(Sys_Setitem_E)/(sizeof(Sys_Setitem_E[0])));i++)
	if(i<sizeof(Sys_Setitem_E)/(sizeof(Sys_Setitem_E[0]))/2)
	
		WriteString_16(LIST1, FIRSTLINE+SPACE1*i,Sys_Setitem_E[i],0);
	
	else
	
		WriteString_16(LIST2,FIRSTLINE+SPACE1*(i-(sizeof(Sys_Setitem_E)/(sizeof(Sys_Setitem_E[0]))+1)/2),Sys_Setitem_E[i],0);
	
 	Disp_SysDot();
	Disp_SysLine();
	//Disp_Button_SysSet();
}
