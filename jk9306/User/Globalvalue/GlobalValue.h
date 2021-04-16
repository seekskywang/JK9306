//==========================================================
//文件名称：GlobalValue.h
//文件描述：全局变量头文件
//文件版本：Ver1.0
//创建日期：2015.10.26 
//修改日期：2015.10.28 15:38
//文件作者：黄宏灵
//备注说明：无
//注意事项：无
//==========================================================
#ifndef __GlobalValue_h__
#define __GlobalValue_h__
#include "stdint.h"
//#include "TypeDefine.h"
#define FIT_INUM    12
//==========================================================
//软件版本：10
#define SOFTWARE_VERSION		(0x10)

//==========================================================
//默认出厂编号(0)
#define DEFAULT_MACHINE_ID 		(0)

//默认出厂密码(0)
#define DEFAULT_PASSWORD 		(0)

//默认开机次数(0)
#define SET_BOOT_DEFAULT		(0)

//==========================================================
//调试配置
#define _DEBUG_CONFIG_FALSE		(0)
#define _DEBUG_CONFIG_TRUE		(1)

//==========================================================
//仿真调试
//#define DEBUG_SUPPORT			(_DEBUG_CONFIG_TRUE)
#define DEBUG_SUPPORT			(_DEBUG_CONFIG_FALSE)

//==========================================================
//ISP开关配置，仿真调试用
#if DEBUG_SUPPORT
	#define HW_ISP_SUPPORT		(_DEBUG_CONFIG_FALSE)
#else
	#define HW_ISP_SUPPORT		(_DEBUG_CONFIG_TRUE)
#endif

//==========================================================
//Uart开关配置
#define HW_UART_SUPPORT			(_DEBUG_CONFIG_TRUE)

//==========================================================
//蜂鸣器开关配置
#define HW_BEEP_SUPPORT			(_DEBUG_CONFIG_TRUE)

//==========================================================
//AD值滤波配置，增加数据稳定度
#define AD_FILTER_SUPPORT		(_DEBUG_CONFIG_TRUE)

//==========================================================
#define SETUP_MENU_MAX  	(2)//最大设置菜单

#define DEBUG_MENU_MAX  	(6)//最大校准菜单

#define PARAMETER_MENU_MAX	(3)//最大参数菜单

#define SYSTEM_MENU_MAX		(4)//最大系统菜单

#define CONFIG_MENU_MAX		(3)//最大配置项(0-2)

#define PW_LENGTH 			(4)//最大密码位数

#define RANGE_MAX 			(4-1)//最大量程

#define AD_BUF_LENGTH		(8)//A/D值缓冲区长度

#define MAX_R_RANGE			(5)//电阻最大量程

#define BUTTOM_X_VALUE		(84)//显示下面提示显示的第一个X位置

#define BUTTOM_MID_VALUE	(80)//显示下面提示显示的中间间隔位置

#define BUTTOM_Y_VALUE		(271-30)//显示下面提示显示的第一个Y位置

#define KEY_NUM				(4)	//按键灵敏度

#define NUM_LENTH 			(6)//显示长度
#define NUM_FREQ 			(33+4)//显示长度			

//==========================================================
#define OHM 				(0xF4)	//CGROM中有Ω字符，编码为0xF4

//==========================================================
//显示分区的X坐标
#define MSG_ADDR_X 			(1)
#define AUTO_ADDR_X 		(12)
#define RANGE_ADDR_X 		(17)

#define RES_ADDR_X 			(1)
#define VOL_ADDR_X 			(12)

#define DISP_UNIT_XPOS	380-8
#define DISP_UNIT_YPOS	92
//==========================================================
//标题长度
#define TITLE_LEN_MAX		(8)

typedef struct
{
	float first_value;
	float comp_highvalue[5];
	float comp_lowvalue[5];
}Comp_Testvalue_Typedef;
extern Comp_Testvalue_Typedef  Comp_Testvalue;

typedef struct
{
	uint8_t Main_Funbuff[8];
	uint8_t Main_Secondbuff[8];
	uint8_t Main_Vmbuff[8];
//	uint8_t Main_Imbuff[8];
}Test_DispBCD_Typedef;
typedef struct
{
	uint8_t Main_flag;
	uint8_t Second_falg;
}Main_Second_TypeDed;
/*
typedef struct
{
	uint8_t buff[5];
	uint32_t Num;
	uint32_t Dot;
	uint32_t Unit;
}Range_Set_Typedef;
typedef struct
{
	Range_Set_Typedef all[4];
}All_Compvalue_Typedef;
extern All_Compvalue_Typedef Comp_Change;
*/
//==========================================================
//带小数点和单位的数
typedef struct 
{
	uint8_t Wei;
	uint32_t Num;
	uint8_t Dot;
	uint8_t Unit;
	uint8_t Dotp;
}Sort_TypeDef;
typedef struct
{
	uint8_t buff[10];
	uint8_t Vmvaluebuff[10];
	uint8_t Imvaluebuff[10];
}Test_Dispvalue;
extern Test_Dispvalue Test_value;
/*
typedef struct
{
    Sort_TypeDef Low;
    Sort_TypeDef Hi;
}Comp_V_Typedef;*/
//极限列表设置
typedef struct
{
    uint8_t Param;//参数
    uint8_t Comp;//比较开关
	Sort_TypeDef Low[5];
    Sort_TypeDef Hi[5];
}Limit_Tab;
/*
typedef struct
{
	uint32_t Year;
	uint32_t Mon;
	uint32_t data;
}Data_Value_Typedef;
typedef struct
{
	uint32_t Hour;
	uint32_t Min;
	uint32_t Sec;
}Timer_Value_Typedef;*/
//系统设置
typedef struct
{
    uint32_t Main_Func;
    uint32_t Menu_Disp;
    uint32_t Baue_Rate;
}Sys_Setup_Typedef;

typedef struct
{
	uint8_t adr;
	uint8_t mode;
	uint8_t check;
	uint8_t filter;
	uint8_t iomode;//	uint8_t page;
	uint8_t clear;
	uint8_t lang;
	uint8_t signal;
	uint8_t beep;
	uint8_t alrm;
	uint8_t boud;	//	Sort_TypeDef Trig_time;//  Sort_TypeDef Temp_time;
	uint8_t vrange;
	uint8_t irange;
	uint8_t usbmode;
	uint8_t hotkey;
	uint8_t whswitch;
}Main_Func_TypeDef;
typedef union UUUU
{
	float	adx;//
	uint32_t ax;
//	int32_t sx;
	uint8_t	bx[4];
}fcc;
typedef struct
{
//	Sys_Setup_Typedef	Sys_Setup;
	union UUUU	div[10];
	union UUUU	zer[10];
	Main_Func_TypeDef	Main;
	Limit_Tab	Limit;
}Savee;
extern Savee SaveData;

typedef struct
{
	Main_Func_TypeDef	Save_Main;
	Limit_Tab	Limit;
	union UUUU	div[10];
	union UUUU	zer[10];
}Saveeprom;
extern Saveeprom	Saveeeprom;

typedef struct
{
	uint8_t page;
	uint8_t index;
	uint8_t row;
	uint32_t key;
	uint8_t force;
	uint8_t sumkey;
	uint8_t test;
	uint8_t third;
}Button_Page_Typedef;
extern Button_Page_Typedef Button_Page;

typedef struct
{
	uint16_t xpos;
	uint16_t ypos;
	uint16_t lenth;
}Disp_Coordinates_Typedef;
typedef struct
{
	uint8_t Ordel;
	uint8_t name;
} Send_Ord_Typedef;

typedef struct
{
	Send_Ord_Typedef first;
	Send_Ord_Typedef second;
	Send_Ord_Typedef third;
}Send_Mainord_Typedef;

extern Send_Mainord_Typedef Send_Mainord;
typedef struct
{
	uint8_t File;			//测量显示---文件
	uint8_t Tool;			//测量显示---工具
	uint8_t Parameter;		//测量显示---参数
	uint8_t Rang;			//测量显示---量程
	uint8_t Speed;			//测量显示---速度
	uint8_t Trigger;		//测量显示---触发
} Disp_Set_Typedef;
extern Disp_Set_Typedef Disp_Set_Resist;

typedef struct 
{
	uint8_t Display;	//		比较显示--工具--显示
	uint8_t Ring;		//		比较显示--工具--讯响
	uint8_t Count;		//		比较显示--工具--计数
	uint8_t Mode;		//		比较显示--工具--模式
}Compare_Tool_Typedef;

typedef struct 
{
	uint8_t File;								//比较显示---文件
	Compare_Tool_Typedef Compare_Tool ;//比较显示---工具
	uint8_t Comp;								//比较显示---比较
	uint8_t Compar_Mode;						//比较显示---比较模式
	Sort_TypeDef Toplimt;							//比较显示---上限
	Sort_TypeDef Lowlimt;							//比较显示---下限
}Disp_CompareMenu_Typedef;
extern Disp_CompareMenu_Typedef Disp_CompareMenu,Set_CompareMenu;

typedef struct 
{
	uint8_t File;		       //档显示---文件
	uint8_t Tool;			   //档显示---工具
	uint8_t Shift;			   //档显示---档
	uint8_t Shfit_Bell;		   //档显示---档讯响
}Disp_Set_Shift_Typedef;

extern Disp_Set_Shift_Typedef Disp_Set_Shift;

typedef struct 
{
	uint8_t Shift_Mode;		//档设置--工具--档模式
	uint8_t Shift_Ring;		//档设置--工具--档讯响
}ShiftSet_Tool;

typedef struct				//档设置中的状态1.2.3
{
	uint8_t First;
	uint8_t Second;
	uint8_t Third;
}ShiftSet_Num_Typedef ;

typedef  struct 
{
	Sort_TypeDef First;
	Sort_TypeDef Second;
	Sort_TypeDef Third;
}Limit_Set_Typedef;
/*
typedef struct 
{
	uint8_t File;						//档设置--文件
	ShiftSet_Tool Tool;					//档设置--工具
	ShiftSet_Num_Typedef Shift;			//档设置--档
	ShiftSet_Num_Typedef State;			//档设置--状态
	Limit_Set_Typedef UpLimit;			//档设置--上限
	Limit_Set_Typedef LowLimit;			//档设置--下限
	ShiftSet_Num_Typedef Nominal_Value; //档设置--标称值
	ShiftSet_Num_Typedef Per;			//档设置--百分数
}Disp_Set_ShiftSet_Typedef;
*/
//extern Disp_Set_ShiftSet_Typedef Disp_Set_ShiftSet;
/*
typedef struct
{
	uint32_t Baud;     					//系统设置中的波特率

}Disp_Set_SysSet_T;

extern Disp_Set_SysSet_T Disp_Set_SysSet;
*/
typedef struct 
{
	uint8_t  RBuff[16];	  		//显示测试的R值
	uint8_t  chn;
	uint8_t  EXTG;
	uint8_t  read421ok;
}Disp_Test_Date_T;

extern Disp_Test_Date_T Test_Dat;

//==========================================================
//全局变量
extern  unsigned long SystemStatus;//系统状态
extern unsigned long SystemMessage;//系统信息
extern char DispBuf[12];
extern unsigned long Count_buff[12];
extern uint8_t Uart_Send_Flag;
//==========================================================
//系统状态
enum SysStatusEnum
{	
	SYS_STATUS_ERROR,			//异常
	SYS_STATUS_RESET,			//复位
	SYS_STATUS_POWER,			//开机
	SYS_STATUS_DATASTORE,	//数据保存
	SYS_STATUS_FILE,			//文件管理
	SYS_STATUS_SETUPTEST,//测量设置
	SYS_STATUS_TEST,			//测试
	SYS_STATUS_RANGE,		//档号显示
	SYS_STATUS_RANGECOUNT,	//档计数显示
	SYS_STATUS_ITEM,			//列表扫描显示
	SYS_STATUS_USERDEBUG,//用户校正 
	SYS_STATUS_FACRDEBUG, //工厂校正
	SYS_STATUS_SYSSET,     //系统设置
  SYS_STATUS_LIMITSET, //极限设置
  SYS_STATUS_ITEMSET,//列表扫描设置
	SYS_STATUS_TOOL,//工具
	SYS_STATUS_RESIST,   //电阻测试显示界面
	SYS_STATUS_COMPARE,  //电阻测试比较界面
	SYS_STATUS_SHIFT,    //电阻测试档界面
	SYS_STATUS_SHIFTSET, //电阻测试档设置界面
	SYS_STATUS_SYSTEMSET,//电阻测试系统设置界面
	SYS_STATUS_MAIN,//界面
};
//==========================================================
//分选状态
/*enum SlectStatusEnum
{
	RH_FAIL,
	RL_FAIL,
	VH_FAIL,
	VL_FAIL,
	ALL_FAIL,
	ALL_PASS,
};*/
//==========================================================
//系统消息
enum SysMessageEnum
{
	MSG_CLEAR , 
	MSG_IDLE , 
	MSG_TEST , 
	MSG_ABORT , 
	MSG_PASS ,
//	MSG_FAIL ,
	MSG_HIGH , 
	MSG_LOW , 
};

//==========================================================
//函数列表
//void InitGlobalValue(void);//全局变量初始化
void LoadDefaultSet(void);//加载默认设置值
void LoadDefaultParameter(void);//加载默认参数值
void LoadDefaultSystem(void);//加载默认系统值
void LoadDefaultConfig(void);//加载默认配置值
void LoadDefaultCalibrate(void);//加载默认校准值
void ReadSaveData(void);//读取保存参数
//void WriteSaveData(void);//写入保存参数

#define SetSystemStatus(status) (SystemStatus=status)
#define GetSystemStatus() (SystemStatus)
#define GetSystemMessage() (SystemMessage)
#define SetSystemMessage(msg) (SystemMessage=msg)

void Check_Calibrate_Limit(void);//校准值检查
void Hex_Format(uint32_t dat , uint8_t Dot , uint8_t len , uint8_t dispzero);

#endif
