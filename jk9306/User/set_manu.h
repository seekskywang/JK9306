#ifndef __Set_manu_H
#define __Set_manu_H 

#define  StrNUM         16
#define  BaudRatePnt		0
#define  CheckPnt				1
#define  AddressPnt			2
#define  FilterPnt			3
#define  IOModePnt			4
#define  AutoZeroPnt    5
#define  LanguagePnt		6
#define  Wh					7
#define  PowerPnt				8
#define  USBModePnt			9
#define  HotKeyPnt			10
#define  BeeperPnt			11
#define  PLimitPnt			12
#define  ILimitPnt			13
#define  BeepPnt			14
#define  ParaNUM       15
#define Clearcur			0
//#define MAX_LPW  1
//#define MAX_LCUR  100
#define MAX_ADD  	254    
#define NULLsetMu			100 

//--------------EMWIN ä½¿ç”¨å˜é‡----------------//
#define MainsetMu			0 //ç”µå‹è®¾ç½®é¡µé¢

#define SYSsetMu			4 //ç³»ç»Ÿè®¾ç½®é¡µé¢
#define WavesetMu			5 //æ³¢å½¢æ˜¾ç¤ºé¡µé¢
#define UsbsetMu			6 //USBå­˜å‚¨é¡µé¢
#define NullsetMu			200 //ç”µå‹è®¾ç½®é¡µé¢

#define Allcur				0xff	 	//æ•°å­—å…¨éƒ¨å¡«å……
#define Nub1cur				2 			//æ•°å­—çš„æœ€é«˜ä½å•ç‹¬å¡«å……
#define Nub2cur				3 			//æ•°å­—çš„æ¬¡é«˜ä½å•ç‹¬å¡«å……
#define Nub3cur				4 			//ä¾æ¬¡å¾€å³
#define Nub4cur				5 			//ä¾æ¬¡å¾€å³
#define Nub5cur				6 			//ä¾æ¬¡å¾€å³

#define   Flag_GE                   (flagC.bit0)//¸öÎ»ÉÁË¸±êÖ¾
#define   Flag_SHI                  (flagC.bit1)//Ê®Î»ÉÁË¸±êÖ¾
#define   Flag_BAI                  (flagC.bit2)//°ÙÎ»ÉÁË¸±êÖ¾
#define   Flag_QIAN                 (flagC.bit3)//Ç§Î»ÉÁË¸±êÖ¾
#define   Flag_WANG                 (flagC.bit4)//ä¸‡ä½

#define MAX_PW  		99999//Para_Set[ULimitPnt].val 		
#define MAX_CUR  		50000//Para_Set[ILimitPnt].val

#define MENUOFFSETX  		10
struct RDispPara	
{
  int row;                    //???
  int col;                   //???
	int len;
	char flag;
	unsigned int max;
	unsigned int val;
  char En[StrNUM];    //??
  char Ch[StrNUM];    //??
};

#define   BaudRate_SetVal			(Para_Set[BaudRatePnt].val)			//²¨ÌØÂÊ	
#define   Check_SetMod  			(Para_Set[CheckPnt].val)				//Ğ£Ñé·½Ê½	  
#define   AddressVal          (Para_Set[AddressPnt].val)			//´®¿ÚµØÖ·	  
#define   flag_SetFilter 			(Para_Set[FilterPnt].val)			//ÏÔÊ¾µç×è»¹ÊÇµçÑ¹	  
#define   flag_SetIOMode  		(Para_Set[IOModePnt].val)				//´«¸ĞÆ÷¿ª¹Ø	  
#define   flag_SetAutoZero  	(Para_Set[AutoZeroPnt].val)     		//×Ô¼ì¿ª¹Ø	
#define   flag_SetLang  			(Para_Set[LanguagePnt].val)		//ÓïÑÔÉèÖÃÖĞÎÄÎª0,Ó¢ÎÄÎª1		
#define   flag_SetPower 			(Para_Set[PowerPnt].val)
//µçÔ´¿ª¹Ø	  
#define  	flag_SetWh			(Para_Set[Wh].val)
#define   flag_SetUSBMode			(Para_Set[USBModePnt].val)			//usbÄ£Ê½	  
#define  	flag_SetHotKey			(Para_Set[HotKeyPnt].val)				//¿ì½İ¼ü¿ª¹Ø	
#define 	Flag_Beep_OFF 			(Para_Set[BeeperPnt].val)				//·äÃùÆ÷¿ª¹Ø	
#define 	Flag_Alarm_OFF 			(Para_Set[BeepPnt].val)   //±¨¾¯¿ª¹Ø
#define  	POWLimit        (Para_Set[PLimitPnt].val)	//ÏŞ¹¦ÂÊÖµ			  
#define  	CurrentLimit        (Para_Set[ILimitPnt].val)	//ÏŞÁ÷Öµ
#define  	TMode	        (Para_main[0].val)	//Ä£Ê½
#define  	VRANGE	        (Para_main[1].val)	//V·¶Î§
#define  	IRANGE 	        (Para_main[2].val)	//I·¶Î§

extern unsigned char BlankP;       // ?????????????
extern struct RDispPara Para_Set[ParaNUM];
extern struct RDispPara Para_main[9];
extern unsigned char CursorP  ;
void Disp_Sys_set(void);
void Disp_Main_set(void);
extern char DisULInputNum[10];	//
extern char DisILInputNum[10];	//
extern char DisADDInputNum[3];	//
extern unsigned char TSetInput;	
void DisBlank(unsigned char blank,unsigned char mode);
#endif 
