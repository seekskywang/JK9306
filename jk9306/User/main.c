
#include "..\Libraries\Drivers\include\lpc177x_8x_gpio.h"
//#include "lpc177x_8x_clkpwr.h"
#include "EX_SDRAM/EX_SDRAM.H"
#include "LCD/lpc177x_8x_lcd.h"
#include "LCD/logo.h"
#include "LCD/AsciiLib.h"
#include "TouchPanel/TouchPanel.h"
//#include "UseDisp/Use_Disp.h"
#include "Key/key.h"
//#include "stdio.h"
#include "TypeDefine.h"	
#include "test/Test.h"
//#include "GlobalValue.h"
#include "..\emWin\Header\GUI.h"
//#include<stdbool.h>
// "application/MassStorageHost.h"
//#include "ch421/ch421.h"
//#include "fsusb_cfg.h"
//#include "ff.h"
#include "set_manu.h"
#define LPC_SYSCTL_BASE           0x400FC000

#define LPC_SYSCTL      ((LPC_SYSCTL_T *) LPC_SYSCTL_BASE)
/* SysTick Counter */
union fc
{
    float f;
	uint32_t sum;
    uint8_t c[4];
};
volatile unsigned long SysTickCnt;
extern	void 	Disp_Box(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint8_t bevel_edge,uint32_t color);
extern	union fc V_val,A_val,P_val,HZ_val,PF_val,VA_val,E_val,VAR_val,VHz_val,IHz_val;	
uint32_t color_table[]={0x000000,0xFFFFFF,0x0000FF,0x00FF00,0xFF0000};


void SysTick_Handler (void)
{
	SysTickCnt++;
}

void Delay (unsigned long tick)
{
	unsigned long systickcnt;

	systickcnt = SysTickCnt;
	while ((SysTickCnt - systickcnt) < tick);
}



//union fc V_val,A_val,P_val,HZ_val,PF_val,VA_val;

//extern void red421(uint8_t k0);

//typedef struct
//			{
//				struct
//				{
//					uint8_t  DataINPipeNumber; /**< Pipe number of the Mass Storage interface's IN data pipe. */
//					bool     DataINPipeDoubleBank; /**< Indicates if the Mass Storage interface's IN data pipe should use double banking. */

//					uint8_t  DataOUTPipeNumber; /**< Pipe number of the Mass Storage interface's OUT data pipe. */
//					bool     DataOUTPipeDoubleBank; /**< Indicates if the Mass Storage interface's OUT data pipe should use double banking. */
//					uint8_t  PortNumber;		/**< Port number that this interface is running.
//												*/
//				} Config; /**< Config data for the USB class interface within the device. All elements in this section
//				           *   <b>must</b> be set or the interface will fail to enumerate and operate correctly.
//				           */
//				struct
//				{
//					bool     IsActive; /**< Indicates if the current interface instance is connected to an attached device, valid
//					                    *   after @ref MS_Host_ConfigurePipes() is called and the Host state machine is in the
//					                    *   Configured state.
//					                    */
//					uint8_t  InterfaceNumber; /**< Interface index of the Mass Storage interface within the attached device. */

//					uint16_t DataINPipeSize; /**< Size in bytes of the Mass Storage interface's IN data pipe. */
//					uint16_t DataOUTPipeSize;  /**< Size in bytes of the Mass Storage interface's OUT data pipe. */

//					uint32_t TransactionTag; /**< Current transaction tag for data synchronizing of packets. */
//				} State; /**< State data for the USB class interface within the device. All elements in this section
//						  *   <b>may</b> be set to initial values, but may also be ignored to default to sane values when
//						  *   the interface is enumerated.
//						  */
//			} USB_ClassInfo_MS_Host_t;

/** LPCUSBlib Mass Storage Class driver interface configuration and state information. This structure is
 *  passed to all Mass Storage Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
//static USB_ClassInfo_MS_Host_t FlashDisk1_MS_Interface = {
//	.Config = {
//		.DataINPipeNumber       = 1,
//		.DataINPipeDoubleBank   = false,

//		.DataOUTPipeNumber      = 2,
//		.DataOUTPipeDoubleBank  = false,
//		.PortNumber = 1,
//	},
//};
				#define MAX_USB_CORE					2
#define SYSCTL_PLL_ENABLE   (1 << 0)/*!< PLL enable flag */

/**
 * @brief LPC17XX/40XX Clock and Power PLL register block structure
 */
typedef struct {
	__IO uint32_t PLLCON;					/*!< (R/W)  PLL Control Register */
	__IO uint32_t PLLCFG;					/*!< (R/W)  PLL Configuration Register */
	__I  uint32_t PLLSTAT;					/*!< (R/ )  PLL Status Register */
	__O  uint32_t PLLFEED;					/*!< ( /W)  PLL Feed Register */
	uint32_t RESERVED1[4];
} SYSCTL_PLL_REGS_T;
			
/**
 * Selectable PLLs
 */
typedef enum {
	SYSCTL_MAIN_PLL,			/*!< Main PLL (PLL0) */
	SYSCTL_USB_PLL,				/*!< USB PLL (PLL1) */
} CHIP_SYSCTL_PLL_T;

/* Enables or connects a PLL */
void Chip_Clock_EnablePLL(CHIP_SYSCTL_PLL_T pllNum, uint32_t flags) {
	uint32_t temp;

//	temp = LPC_SYSCTL->PLL[pllNum].PLLCON;
	temp |= flags;
	//LPC_SYSCTL->PLL[pllNum].PLLCON = temp;
	//Chip_Clock_FeedPLL(pllNum);
}
#ifdef __CC_ARM
#define INLINE  __inline
#else
#define INLINE inline
#endif
/**
 * @brief	Returns PLL status
 * @param	pllNum:		PLL number
 * @return	Current enabled flags, Or'ed SYSCTL_PLLSTS_* states
 * @note	Note flag positions for PLL0 and PLL1 differ on the LPC175x/6x devices.
 */
/*STATIC INLINE uint32_t Chip_Clock_GetPLLStatus(CHIP_SYSCTL_PLL_T pllNum)
{
	return LPC_SYSCTL->PLL[pllNum].PLLSTAT;
}*/
void HAL_USBInit(uint8_t corenum)
{
	/* Enable PLL1 for 48MHz output */
	Chip_Clock_EnablePLL(SYSCTL_USB_PLL, SYSCTL_PLL_ENABLE);
//#if defined(__LPC175X_6X__)
//	while ((Chip_Clock_GetPLLStatus(SYSCTL_USB_PLL) & SYSCTL_PLL1STS_LOCKED) == 0);
//#else
//	while ((Chip_Clock_GetPLLStatus(SYSCTL_USB_PLL) & SYSCTL_PLLSTS_LOCKED) == 0);
//#endif

	if(corenum == 0)
	{
//		Chip_IOCON_PinMux(LPC_IOCON, 0, 29, IOCON_MODE_INACT, IOCON_FUNC1);	/* P0.29 D1+, P0.30 D1- */
//		Chip_IOCON_PinMux(LPC_IOCON, 0, 30, IOCON_MODE_INACT, IOCON_FUNC1);

//#if defined(USB_CAN_BE_HOST)
//		Chip_IOCON_PinMux(LPC_IOCON, 1, 19, IOCON_MODE_INACT, IOCON_FUNC2);	/* USB_Power switch */
//#endif
//		
//#if defined(USB_CAN_BE_DEVICE)
//		Chip_IOCON_PinMux(LPC_IOCON, 2, 9, IOCON_MODE_INACT, IOCON_FUNC1);	/* USB_SoftConnect */
//#endif
  }
	else
	{
//		Chip_IOCON_PinMux(LPC_IOCON, 0, 31, IOCON_MODE_INACT, IOCON_FUNC1);	/* P0.31 D1+ */
//		
//		Chip_IOCON_PinMux(LPC_IOCON, 0, 12, IOCON_MODE_INACT, IOCON_FUNC1);	/* USB_Power switch 2 */
	}	
//	
//	LPC_SYSCTL->PCONP |= (1UL << 31);					/* USB PCLK -> enable USB Per.*/

//#if defined(USB_CAN_BE_DEVICE)
//	LPC_USB->USBClkCtrl = 0x12;					/* Dev, PortSel, AHB clock enable */
//	while ((LPC_USB->USBClkSt & 0x12) != 0x12) ;

//	HAL_Reset(corenum);
//#endif
}
volatile uint8_t USB_CurrentMode[MAX_USB_CORE];

//void USB_ResetInterface(uint8_t corenum, uint8_t mode)
//{
//	if (mode == USB_MODE_Device) {
//		#if defined(USB_CAN_BE_DEVICE)
//		USB_Init_Device(corenum);
//		#endif
//	}
//	else if (mode == USB_MODE_Host) {
//		#if defined(USB_CAN_BE_HOST)
//		USB_Init_Host(corenum);
//		#endif
//	}
//}
//volatile bool    USB_IsInitialized;
//void USB_Init(uint8_t corenum, uint8_t mode)
//{
//#if defined(USB_CAN_BE_HOST)	
//	if (mode == USB_MODE_Host && Mem_IsInitialized == false)
//	{
//	  USB_Memory_Init(USBRAM_BUFFER_SIZE);
//		Mem_IsInitialized = true;
//	}
//#endif
//	USB_CurrentMode[corenum] = mode;
//	HAL_USBInit(corenum);
//	USB_ResetInterface(corenum, mode);
//	USB_IsInitialized = true;
//}

uint8_t  Send_232[11]={
	0xab,0x20,0xaa,0xaa,
	0xaa,0xaa,0xaa,0xaa,
	0x01,0x00,0xaf};//tv,
extern Com_TypeDef ComBuf3;
//extern void init421_adj(void);
extern	void do232(void);
extern	void read5463(void);
//uint8_t km;//,spedadx0,r41h,w40h,
uint8_t key,key_flg,key_sum,R_flg;//,tste;//,SetPage,DisPage,	
extern	void 	Disp_Box(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint8_t bevel_edge,uint32_t color);
int main(void)
{
	uint32_t cclk = CLKPWR_GetCLK(CLKPWR_CLKTYPE_CPU);

char  buff[15]={0};
//uint32_t test_r;

	SysTick_Config(cclk/1000 - 1);
	HW_keyInt();
 //   debug_frmwrk_init();
//debug_uart0_init(9600);//串口3初始化
debug_uart0_init(19200);
//  	init_timer(0, 10);//定时器初始化
//enable_timer(0);
   SDRAM_Init();
//	CH421_Init_CWRA();
BUZZER();
//usb init
//USB_Init(FlashDisk1_MS_Interface.Config.PortNumber, USB_MODE_Host);
//SetupHardware();
/*Disable LCD controller*/
	GLCD_Ctrl(FALSE);
	/*Init LCD and copy picture in video RAM*/
	GLCD_Init (LogoPic.pPicStream, NULL);
   	/*Enable LCD*/
	GLCD_Ctrl(TRUE);
//    touch_init();
//    TouchPanel_Calibrate();
	HW_Sendvalueto164(0);
//LCD_DrawRect(0,0,480,272,Colour.black);
//1 wr 42h=11h
Delay(100);

Colour.black=LCD_COLOR_TURQUOISE;
LCD_DrawRect(0,0,480,272,Colour.black);

Power_Process();
//Colour.black=LCD_COLOR_TURQUOISE;
//LCD_DrawRect(0,0,480,272,Colour.black);
////2.2
//buff[0]='2';buff[1]='0';buff[2]='1';buff[3]='9';
//buff[4]='.';buff[5]='0';buff[6]='3';
//buff[7]=0;
//	WriteString_Big(110,120,buff);
Delay(550);
Colour.black=Black;
LCD_DrawRect(0,0,480,272,Colour.black);

//Resist_Test(key);

Button_Page.page=1;
Button_Page.index=0;

lcd_Clear(LCD_COLOR_TEST_BACK);
//lcd_Clear(LCD_COLOR_TURQUOISE);
	Disp_R(1);
/*V_val.sum=1000;
A_val.sum=2100;
P_val.sum=1020;
HZ_val.sum=1400;
PF_val.sum=1010;
VA_val.sum=1030;
E_val.sum=2200;
VAR_val.sum=11000;
VHz_val.sum=12000;
IHz_val.sum=14000;*/
while(1)
    {
			D2_L
			D1_L

//232pro
//if((Test_Dat.EXTG&&SaveData.Main.trig)||!SaveData.Main.trig)
{//Send_232[9]=0xc0;
//Send_232[10]=0xaf;
//UARTPuts(LPC_UART3, Send_232);
}
/*if(ComBuf3.rec.end)
{ComBuf3.rec.end=0;
	do232();
}*/

if(Button_Page.index==18)//adj0 dely
	Delay(28);
SetSystemStatus(SYS_STATUS_MAIN);
Use_MainProcess();
    }
	}

/*****************************************************************************
                            End Of File
**/

