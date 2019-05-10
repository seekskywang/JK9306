#ifndef __use_disp_H_
#define __use_disp_H_
#include  "stdint.h"
#include  "Globalvalue/globalvalue.h"
#define FIRSTLINE	26
#define	SPACE1		22
#define LIST1		0
#define LIST2		250
#define SELECT_1END 192
#define SELECT_2END (410+32)

#define   KEY_XLEFTP     391		//按键左边的X位置
#define   KEY_XRIGHT     473		//按键右边的X位置
#define   KEY_HIGH		 41			 //按键的宽度
#define   KEY_LENGHT     96			//按键的长度
#define   KEY_TOTALWID   45			 
#define   KEY_RED		 130			 //按键的基色
#define   KEY_GREEN		 130
#define   KEY_BLUE		 130
#define   KEY_CHANG      3
#define   COLORFLAG      7
#define   KEY_WORD       103
#define   POLYGON_RED	 160		 //多边形渐变底色 KEY_TOTALWID 120
#define   POLYGON_CHANG	 2			//多边形渐变大小
#define   POLYGON_WORD1	 140  	//多边形第一行字的显示颜色
#define   POLYGON_WORD2	 160
#define   KEY_LINE_COL   126   
#define   POLYGON_LINE	 158		//显示多边形线条的渐变底色200
#define   POLYGON_SEC    72
#define   POLYGON_EN	 112		//显示英文字符
#define   KEY_WORD2      90 

#define   LINE_DISTAN    31
#define   KEY_DIS_MODE1  58			//按键显示最下面的字颜色
#define   BOX_0_SITE  2

#define   SYSSET_BOX_LEN  128		//系统设置方框长度

#define  SCREENWIDE   480
#define  SCREENHIGH   272
#define  INSTRUCT_TO_DEBUG	Delay(0x3f);
#define  SHORT_DELAY  Delay(0x1f);
#define  INSTR_FIVE   0x03
#define  SITE         5
#define  CORRE_SITE   5
#define  INSTR_FOUR   0x00
#define  LONGDELAY	  Delay(0x2ff);


Sort_TypeDef Time_Set_Cov(Sort_TypeDef *Time);
Sort_TypeDef Freq_Set_Cov(Sort_TypeDef *Freq);

Sort_TypeDef Input_Set_Cov(Sort_TypeDef *Input_Ref);

void Send_Main_Ord(void);
//测试时档号显示界面的显示
void Disp_Range_ComDispValue(Button_Page_Typedef *Button_Page);
void Disp_RangeDispvalue(uint8_t data);
void Disp_Range_DispMainUnit(uint8_t num,uint8_t unit);//档号显示中Cp的单位
void Disp_Range_DispSecondUnit(uint8_t num,uint8_t unit);//档号显示中Rp的单位
void Disp_RangeTestvalue(void);//档号显示中的Cp和Rp的值

void Disp_Button_ItemScanSet(uint32_t value);
void Disp_Button_ItemScan_no(void);

Sort_TypeDef Input_Set_CovPre(Sort_TypeDef *Input_Ref);
void Disp_Test_Unit_v(uint32_t x,uint32_t y);
void Disp_Test_Unit_mA(uint32_t x,uint32_t y);
void Send_UartStart(void);
void Savetoeeprom(void);
void ReadSavedata(void);

void Communiction_Protocol(Button_Page_Typedef* Button_Page );
void lcd_image(uint8_t *pt);

void Disp_Start_Corr(void);//显示开始校正
void Start_Correction(void);//开始校正
void Init_C(void);//电容初始化校正
void Correction_C(Button_Page_Typedef* Button_Page)	;	//电容校正
void Save_C(void);	//保存电容值

void Init_R(void);//初始化电阻
void Correction_R(Button_Page_Typedef* Button_Page);		//电阻校正
void Save_R(void);	//保存电阻值
void Exit_correction(void);	//退出校正
void Clear_Instr(void);  //清除校正

void Disp_Test(void);
void	Disp_Setup(void);
void Disp_Test_Set(Button_Page_Typedef* Button_Page);	//测试设置界面
void Disp_Shift(void);      //档显示界面
void Disp_Shift_Set(Button_Page_Typedef* Button_Page);//档显示设置
void Disp_ShiftSet(void);   //档设置
void Disp_ShiftSet_Set(Button_Page_Typedef* Button_Page);//档设置中的设置
void Disp_System(void);	    //显示系统设置界面
void Disp_SysSet_Set(Button_Page_Typedef* Button_Page);	//系统设置的设置

void Disp_Key_Box(Button_Page_Typedef* Button_Page);			//按键方框显示
void Disp_Num_Keyboard_Box(void);   //Button_Page_Typedef* Button_Page数字按键方框
void Disp_UpOrLow_Limit_Word(void); //Button_Page_Typedef* Button_Page数值按键上显示上下限的字

void Num_Keyboard(void);	//Button_Page_Typedef* Button_Page数字按键界面
void Manage_File(void);		//文件管理界面
void Draw_LIN5(uint8_t x,uint8_t y,uint16_t len,uint32_t color);
void Draw_LIN3_Y(uint8_t x,uint8_t y,uint16_t len,uint32_t color);
extern const char All_TopName_E[][20];	
extern const char All_TopName[][20];
#endif
