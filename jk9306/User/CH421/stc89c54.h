

sfr PCA_PWM0=0xf2;
sfr CCON= 0xD8;
sfr CMOD=0XD9;
sfr CL=0XE9;
sfr CH=0XF9;
sfr CCAP0L=0XEA;
sfr CCAP0H=0XFA;
sfr CCAPM0=0XDA;
sfr CCAPM1=0XDB;
sbit CR=0XDE;


sfr SP   = 0x81; //Stack Pointer                                                            0000,0111
sfr DPL  = 0x82; //Data Pointer Low Byte                                                    0000,0000
sfr DPH  = 0x83; //Data Pointer High Byte                                                   0000,0000
//                                      7     6     5     4     3     2     1     0         Reset Value
sfr P0   = 0x80; //8 bitPort0          P0.7  P0.6  P0.5  P0.4  P0.3  P0.2  P0.1  P0.0       1111,1111
sfr P1   = 0x90; //8 bitPort1          P1.7  P1.6  P1.5  P1.4  P1.3  P1.2  P1.1  P1.0       1111,1111
sfr P2   = 0xA0; //8 bitPort2          P2.7  P2.6  P2.5  P2.4  P2.3  P2.2  P2.1  P2.0       1111,1111
sfr P3   = 0xB0; //8 bitPort3          P3.7  P3.6  P3.5  P3.4  P3.3  P3.2  P3.1  P3.0       1111,1111
sfr P4   = 0xe8;
//--------------------------------------------------------------------------------
sfr ACC  = 0xE0; //Accumulator                                                              0000,0000
sfr B    = 0xF0; //B Register                                                               0000,0000

sfr T2CON=0xc8;
sfr T2MOD=0xc9;
sfr RCAP2L=0xca;
sfr RCAP2H=0xcb;
sfr TL2=0xcc;
sfr TH2=0xcd;
sbit TR2=T2CON^2;
sbit TF2=T2CON^7;
sfr	ET2=0xad;

//--------------------------------------------------------------------------------
//新一代 1T 8051系列 单片机系统管理特殊功能寄存器
//                                          7     6      5    4     3      2    1     0     Reset Value
sfr PCON   = 0x87; //Power Control        SMOD  SMOD0  LVDF  POF   GF1    GF0   PD   IDL    0001,0000
//                                        7     6       5      4     3      2      1      0   Reset Value
//新一代 1T 8051系列 单片机定时器特殊功能寄存器
//                                            Reset Value
sfr TCON = 0x88; //T0/T1 Control            0000,0000
//-----------------------------------
sbit TF1 = TCON^7;
sbit TR1 = TCON^6;
sbit TF0 = TCON^5;
sbit TR0 = TCON^4;
sbit IE1 = TCON^3;
sbit IT1 = TCON^2;
sbit IE0 = TCON^1;
sbit IT0 = TCON^0;

sfr TMOD = 0x89; //T0/T1 Modes             GATE1 C/T1  M1_1  M1_0  GATE0 C/T0  M0_1  M0_0   0000,0000
sfr TL0  = 0x8A; //T0 Low Byte                                                              0000,0000
sfr TH0  = 0x8C; //T0 High Byte                                                             0000,0000
sfr TL1  = 0x8B; //T1 Low Byte                                                              0000,0000
sfr TH1  = 0x8D; //T1 High Byte                                                             0000,0000

sfr AUXR  = 0x8E; //Auxiliary Register  T0x12 T1x12 UART_M0x6 BRTR S2SMOD BRTx12 EXTRAM S1BRS  0000,0000
//-----------------------------------
//                                          7     6     5     4     3     2     1     0     Reset Value
sfr SCON = 0x98; //Serial Control         SM0/FE SM1   SM2   REN   TB8   RB8    TI    RI    0000,0000
//-----------------------------------
sbit SM0 = SCON^7;  //SM0/FE
sbit SM1 = SCON^6;
sbit SM2 = SCON^5;
sbit REN = SCON^4;
sbit TB8 = SCON^3;
sbit RB8 = SCON^2;
sbit TI  = SCON^1;
sbit RI  = SCON^0;
//-----------------------------------
sfr SBUF = 0x99; //Serial Data Buffer                                                     xxxx,xxxx
sfr AUXR1 = 0xA2; //Auxiliary Register 1  -  PCA_P4  SPI_P4  S2_P4  GF2    ADRJ   -    DPS  0000,0000
//                                         7      6      5     4     3     2     1     0    Reset Value
//                                           7     6     5    4     3    2    1    0   Reset Value
sfr IE      = 0xA8;  //中断控制寄存器        EA  ELVD  EADC   ES   ET1  EX1  ET0  EX0  0x00,0000
//-----------------------
sbit EA     = IE^7;
sbit ELVD   = IE^6; //低压监测中断允许位
sbit EADC   = IE^5; //ADC 中断允许位
sbit ES     = IE^4;
sbit ET1    = IE^3;
sbit EX1    = IE^2;
sbit ET0    = IE^1;
sbit EX0    = IE^0;
//-----------------------
sfr IE2     = 0xAF;  //Auxiliary Interrupt   -     -     -    -     -    -  ESPI  ES2  0000,0000B


sfr IPH   = 0xB7; //中断优先级高位       PPCAH  PLVDH  PADCH  PSH  PT1H  PX1H  PT0H  PX0H   0000,0000
//                                          7     6     5    4    3    2    1    0    Reset Value
sfr IP    = 0xB8; //中断优先级低位      PPCA  PLVD  PADC  PS   PT1  PX1  PT0  PX0   0000,0000
//--------

sbit PT2   = IP^5;  //ADC 中断优先级
sbit PS    = IP^4;
sbit PT1   = IP^3;
sbit PX1   = IP^2;
sbit PT0   = IP^1;
sbit PX0   = IP^0;

sfr SADEN = 0xB9; //Slave Address Mask                                                    0000,0000
sfr SADDR = 0xA9; //Slave Address                                                         0000,0000

//新一代 1T 8051系列 单片机I/O 口特殊功能寄存器
sfr XICON= 0xC0; //8 bitPort4          P4.7  P4.6  P4.5  P4.4  P4.3  P4.2  P4.1  P4.0       1111,1111
//                                      7      6         5         4      3     2     1     0     Reset Value

//--------------------------------------------------------------------------------
//新一代 1T 8051系列 单片机串行口特殊功能寄存器
//-----------------------------------
sfr PSW  = 0xD0; //Program Status Word      CY    AC    F0    RS1   RS0    OV    F1    P    0000,0000
//-----------------------------------
sbit CY  = PSW^7;
sbit AC  = PSW^6;
sbit F0  = PSW^5;
sbit RS1 = PSW^4;
sbit RS0 = PSW^3;
sbit OV  = PSW^2;
sbit P   = PSW^0;
//--------------------------------------------------------------------------------
//新一代 1T 8051系列 单片机看门狗定时器特殊功能寄存器
sfr WDT = 0xe1; //Watch-Dog-Timer Control register
//                                      7     6     5      4       3      2   1   0     Reset Value
//                                  WDT_FLAG  -  EN_WDT CLR_WDT IDLE_WDT PS2 PS1 PS0    xx00,0000
//新一代 1T 8051系列 单片机 IAP/ISP 特殊功能寄存器
sfr ISP_DATA    = 0xe2;
sfr ISP_ADDRH   = 0xe3;
sfr ISP_ADDRL   = 0xe4;
//                                                7    6    5      4    3    2    1     0    Reset Value
sfr ISP_CMD     = 0xe5; //IAP Mode Table          0    -    -      -    -    -   MS1   MS0   0xxx,xx00
sfr ISP_TRIG    = 0xe6;
sfr ISP_CONTR   = 0xe7; //IAP Control Register  IAPEN SWBS SWRST CFAIL  -   WT2  WT1   WT0   0000,x000
//ad转换
sfr ADC_CTR	=0xc5;
sfr ADC_DATA	=0xc6;//a/d data h8
sfr ADC_LOW	=0xbe;//a/d data L2
//定义ISP/IAP命令及等待时间
#define ISP_REA	1	//字节读
#define ISP_PRO	2	//字节编程
#define ISP_ERA	3	//扇区擦除
#define W_TIME	0x81	//设置等待时间，40M>0,20M>1,10M>2,5M>3
#define	UCHAR	unsigned char
#define	UINT	unsigned int
#define	UINT32	unsigned long int
sfr	P1M0	=0x91;
sfr	P1M1	=0x92;