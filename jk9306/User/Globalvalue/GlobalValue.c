//==========================================================
//文件名称：GlobalValue.c
//文件描述：全局变量定义
//文件版本：Ver1.0
//创建日期：2015.10.28
//修改日期：2015.10.28 15:38
//文件作者：黄宏灵
//备注说明：无
//注意事项：无
//==========================================================
#include "TypeDefine.h"	//数值类型
#include "Globalvalue/GlobalValue.h"

//==========================================================
//全局变量
Savee SaveData;
Saveeprom	Saveeeprom;
Test_Dispvalue Test_value;


Disp_Set_Typedef Disp_Set_Resist;			//测量电阻显示
Disp_CompareMenu_Typedef Disp_CompareMenu,Set_CompareMenu;//比较显示

Disp_Test_Date_T Test_Dat;

uint8_t Uart_Send_Flag;

 unsigned long SystemStatus;//系统状态

char DispBuf[12];


