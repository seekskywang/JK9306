

#include "LCD/lpc177x_8x_lcd.h"
#include "lpc177x_8x_uart.h"
#include "Globalvalue/GlobalValue.h"
#include "use_disp.h"
#include "EX_SDRAM/EX_SDRAM.H"
#include "stdint.h"
#include "key/key.h"
#include "uart.h"
#include "timer.h"
#include "lpc177x_8x_eeprom.h"
#include "math.h"
#include "LCD/AsciiLib.h"
#include  "stdio.h"
#include "ch421.h"
#include "test/Test.h"

//#include "debug_frmwrk.h"
//const uint8_t Uart_Ordel[]={0x60,0x70,0x71,0x80,0x90,0xa0,0xb0,0xc0,0xe0};
//const uint8_t READDATA[7]={0xAB,0x01,0x06,0x03,0x08,0xbf,'\0'};
//const uint8_t Disp_Main_Ord[][3]={
//	{1,1,0},
//	{1,1,1},
//	{1,1,2},
//	{1,1,3},//Cp
//	
//	{0,1,0},
//	{0,1,1},
//	{0,1,3},//Cs
//	{1,0,0},
//	{1,0,0},
//	{1,0,0},
//	{1,0,1},//Lp
//	{1,0,3},
//	{1,0,4},
//	{1,0,0},
//	{0,0,0},//Ls
//	{0,0,1},
//	{0,0,5},
//	{0,0,4},
//	{0,3,6},//Z
//	{0,3,7},
//	{0,4,6},//Y
//	{0,4,7},
//	{0,2,8},//R
//	{1,2,1},
//	{0,2,1},
//	{1,1,0},
//	{1,5,9},//GB
//	//{1,1,0},
//	};
/*
const uint8_t Disp_Main_Ord[][3]={
	{1,1,6},
	{1,1,7},
	{1,1,5},
	{1,1,2},//Cp-D,CP-Q,CP-G,CP-RP,
	
	{0,1,6},
	{0,1,7},
	{0,1,2},//Cs-D,Cs-Q,Cs-Rs
	
	{1,0,7},
	{1,0,2},
	{1,0,2},
	{1,0,6},//Lp-Q,Lp-Rp,Lp-Rd,Lp-D
	
	{0,0,6},
	{0,0,7},
	{0,0,2},
	{0,0,2},//Ls-D,Ls-Q,Ls-Rs,Ls-Rd
	
	{0,3,6},
	{0,3,2},//Z-d,Z-r
	{0,4,6},
	{0,4,2},//Y-d,Y-r
	{0,2,8},//R-X
	{1,2,7},//Rp-Q
	{0,2,7},//Rs-Q
	{0,5,9},//G-B
	};	*/
//==========================================================
//函数名称：Power_Process
//函数功能：上电处理
//入口参数：无
//出口参数：无
//创建日期：2015.10.26
//修改日期：2015.10.26 08:53
//备注说明：开机长按SET进入校准调试模式
//==========================================================

void Power_Process(void)
{
//	uint16_t i;
//	u8 buff[4096];
//	u8 key;
//
	InitGlobalValue();//初始化全局变量
	init_timer(0, 20);//定时器初始化
	enable_timer(0);
	Uart_Send_Flag=0;
	EEPROM_Init();
//	i=sizeof(SaveData);
//	for(i=0;i<4096;i++)
//	buff[i]=i+1;
//	EEPROM_Write(0, 0, buff, MODE_8_BIT, 4000);
//	EEPROM_Read(0, 0, buff, MODE_8_BIT, 4095);
//	Set_Compbcd_float();
	ReadSavedata();
//	ReadSaveData();//读取保存数据
//	SaveData.Config.BootNum++;//开机次数	
//	SaveConfig();//保存开机次数
//
//	Hardware_Init();//硬件初始化
//	Disp_Clr( );//清屏
//	Beep_Long();//蜂鸣器长响一声
//	//Disp_PowerOn_Menu();//显示开机界面
//	MenuIndex=0;//待机菜单项
//	Limit_Control(0);
//	Electric_currentAmp(0);
//	VOLTAGE_Ampchoice(0);
//	//CH450_Write(CH450_SYSON2);
//if(SaveData.Parameter.Range!=0)
//			Range=SaveData.Parameter.Range-1;
//		else
//			Range=3;
//		Range_Control(Range);
//	i=0;//显示延时
	while(GetSystemStatus()==SYS_STATUS_POWER)
	{
//		i++;
//		if(i>POWERON_DISP_TIME)//延时20*100mS=2s后自动退出
//			SetSystemStatus(SYS_STATUS_TEST);//待测状态
			SetSystemStatus(SYS_STATUS_RESIST);
		
		
//		key=Key_Read_WithTimeOut(TICKS_PER_SEC_SOFTTIMER/10);//等待按键(100*10ms/10=100ms)
//		switch(key)
//		{
////			case KEY_SET:		//设置键
//			case L_KEY_SET:		//长按设置键
//				SetSystemStatus(SYS_STATUS_DEBUG);//调试状态
//				Beep_One();//蜂鸣器响一声
//				break;
//	
//			case KEY_UP:		//上键
//			case L_KEY_UP:		//长按上键
//				break;
//	
//			case KEY_DOWN:		//下键
//			case L_KEY_DOWN:	//长按下键
//				break;
//	
//			case KEY_LEFT:		//左键
//			case L_KEY_LEFT:	//长按左键
//				break;
//
//			case KEY_RIGHT:		//右键
//			case L_KEY_RIGHT:	//长按右键
//				break;
//
//			case KEY_ENTER:		//确认键
//			case L_KEY_ENTER:	//长按确认键
//				break;
//	
//			case KEY_START:		//启动键
//			case L_KEY_START:	//长按启动键
//				break;
//	
//			case KEY_RESET:		//复位键
//			case L_KEY_RESET:	//长按复位键
//				i=POWERON_DISP_TIME;//显示延时结束
//				break;
//			
//			default:
//				break;
//		}
		
		//Delay_1ms(50);
		//Range_Control(3);
	}
}
	
//测试程序
/*void Test_Process(void)
{
	Button_Page_Typedef Button_Page;
//	Main_Second_TypeDed Main_Second;//主参数和幅参赛的序号
	uint32_t keynum=0;
	uint8_t key;
    uint8_t page=1;
	uint8_t Disp_Flag=1;
//	uint8_t uart_count;

//	Send_Ord_Typedef Uart;
//	const uint8_t DISP_UnitMain[]=
//	{ 0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,3,3,2,2,2};
//	const uint8_t DISP_UnitSecond[]=
//	{ 6,6,3,2,6,6,2,6,2,2,6,6,6,2,2,5,4,5,4,2,6,6};

	Button_Page.page=0;
	Button_Page.index=0;
	Button_Page.third=0xff;
	Disp_Test_Item();	
//	Main_Second.Main_flag=0;
//	Main_Second.Second_falg=0;

	Delay_Key();
//	uart_count=0;
//	sprintf((char *)DispBuf,"%2d",SaveData.Main_Func.Param.test);
//	WriteString_16(210, 4, DispBuf,  0);
	Send_UartStart();//开始时的串口发送数据
	while(GetSystemStatus()==SYS_STATUS_TEST)
	{
		
		if(Disp_Flag==1)
		{
			Disp_Test_value(&Button_Page);
			
			Disp_Flag=0;
		
		}//
		//_printf("CoreClock: %s\n",READDATA); 
		Uart_Process();
		Colour.black=LCD_COLOR_TEST_MID;
//	sprintf((char *)DispBuf,"%2d",SaveData.Main_Func.Param.test);
//	WriteString_16(210, 4, DispBuf,  0);
		switch(SaveData.Main_Func.Param.test)
		{
			case 0:
				Disp_Cp_D();
				
//			WriteString_Big((uint8_t)Set_Unit[Test_Dispvalue.Mainvalue.Unit]);
				//Disp_Big_MainUnit(Test_Dispvalue.Unit[0],0);
				break;
			case 1:
				Disp_Cp_Q();
				//Test_Dispvalue.Mainvalue.Unit=1;
				//Disp_Big_MainUnit(Test_Dispvalue.Unit[0],0);
				break;
			case 2:
				Disp_Cp_G();
				//Test_Dispvalue.Mainvalue.Unit=1;
				//Disp_Big_MainUnit(Test_Dispvalue.Unit[0],0);
			
				//Test_Dispvalue.Secondvalue.Dot=3;
				//Disp_Big_SecondUnit(Test_Dispvalue.Unit[1],3);
				break;
			case 3:
				Disp_Cp_Rp();
				//Test_Dispvalue.Mainvalue.Unit=1;
				//Disp_Big_MainUnit(Test_Dispvalue.Unit[0],0);
			
				
				break;
			case 4:
				//
				Disp_Cs_D();
				//Disp_Big_MainUnit(Test_Dispvalue.Unit[0],0);
			
				break;
				
			default:
				break;
		
		
		}

		if(timer0_counter>0)//请求数据
		{
			switch(Uart_Send_Flag)
			{
				case 0:
				//	Send_Request();
					break;
				case 1:
//					if(uart_count++>5)
//						Uart_Send_Flag=0;
					Send_Main_Ord();
//						SHORT_DELAY;
//						while(i)	
//						{
//								i--;
//							if(ComBuf.rec.buf[5]==0x00)
//								i=0;
//							else 
//									Send_Main_Ord();
//						SHORT_DELAY;
//						}				
				
					Uart_Send_Flag=0;
					break;
				case 2:
	//			Send_Freq(&Uart);
//				SHORT_DELAY;
//						i=3;
//						while(i)	
//						{
//								i--;
//							if(ComBuf.rec.buf[5]==0x00)
//								i=0;
//							else 
//									Send_Freq(&Uart);
//							SHORT_DELAY;
//						
//						}
					
				Uart_Send_Flag=0;
					break;
				default:
					//Send_Request();
					break;
			}
			timer0_counter=0;
		}
		//Test_Dispvalue.Mainvalue.Unit=1;timer0_counter
//		Disp_Big_MainUnit(Test_Dispvalue.Unit[0],DISP_UnitMain[SaveData.Main_Func.Param.test]);//显示单位
//		Test_Dispvalue.Secondvalue.Dot=3;
//		Disp_Big_SecondUnit(Test_Dispvalue.Unit[1],DISP_UnitSecond[SaveData.Main_Func.Param.test]);//副参数单位
		Disp_Testvalue();
		//分选比较打开
		if(SaveData.Limit_Tab.Comp)
			Test_Comp(&Comp_Change);
		//		_printf("CoreClock: %s\n","12345678"); 
//		Disp_NumKeyboard_Set();
//		Disp_Cp();
		
	  key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==KEY_NUM)
		{	
			Disp_Flag=1;
			switch(key)
			{
				case Key_F1:
				//	BUZZER();
                    switch(Button_Page.index)
					{
						case 0:
							//if(Button_Page.page==0)
								SetSystemStatus(SYS_STATUS_SETUPTEST);
							break;
						case 1:
							switch(Button_Page.page)
							{
								case 0:
									Button_Page.force=0;
									Disp_Button_Fun_Set(LIST1+88, FIRSTLINE,
								(uint8_t *)Cp_Button_Tip,&Button_Page);
								Uart_Send_Flag=1;
								//Send_Main_Ord();
								//Button_Page.page=0;
								//	SaveData.Main_Func.Param.page=0;
									//SaveData.Main_Func.Param.test=0;
									break;
								case 1:
									Button_Page.force=4;
									
									Disp_Button_Fun_Set(LIST1+88, FIRSTLINE,
									(uint8_t *)Z_Button_Tip,&Button_Page);
									Uart_Send_Flag=1;
									//Send_Main_Ord();
									//Button_Page.page=1;
									break;
								case 2:
									SaveData.Main_Func.Param.page=8;
									//SaveData.Main_Func.Param.test=8;
									break;
								default:
									break;
							}
							
							break;
						case 2:
							if(SaveData.Main_Func.Freq>14)
								SaveData.Main_Func.Freq-=10;
							else
								SaveData.Main_Func.Freq=4;
			//				Uart.Ordel=Uart_Ordel[3];
				//			Uart.name=SaveData.Main_Func.Freq;
							Uart_Send_Flag=2;
					
							break;
						case 3:
							if(SaveData.Main_Func.Level>0)
								SaveData.Main_Func.Level--;
				//			Uart.Ordel=Uart_Ordel[4];
				//			Uart.name=SaveData.Main_Func.Level;
							//Send_Freq(&Uart);
							Uart_Send_Flag=2;
							//SaveData.Main_Func.Level=0;
							break;
						
						case 4:
							SaveData.Main_Func.Range.Range=0;
				//			Uart.Ordel=Uart_Ordel[6];
				//			Uart.name=SaveData.Main_Func.Range.Range;
							Uart_Send_Flag=2;
							break;
						case 5:
							SaveData.Main_Func.Speed=0;
					//		Uart.Ordel=Uart_Ordel[5];
					//		Uart.name=SaveData.Main_Func.Speed;
							Uart_Send_Flag=2;
							break;
						case 6:
							
							if(SaveData.Main_Func.Bias>0)
								SaveData.Main_Func.Bias--;
							break;
						
						default:
							break;
					}
					Savetoeeprom();
				break;
				case Key_F2:
			//		BUZZER();
					switch(Button_Page.index)
					{
						case 0:
							if(page==1)
//							   SetSystemStatus(SYS_STATUS_SYSSET);
								SetSystemStatus(SYS_STATUS_RANGE);
							break;
						case 1:
							switch(Button_Page.page)
							{
								case 0:
									Button_Page.force=1;
									
									Disp_Button_Fun_Set(LIST1+88, FIRSTLINE,
									(uint8_t *)Cs_Button_Tip,&Button_Page);
									//	SaveData.Main_Func.Param.page=0;
									
									Uart_Send_Flag=1;
								break;
								case 1:

									Button_Page.force=5;
									Disp_Button_Fun_Set(LIST1+88, FIRSTLINE,
									(uint8_t *)Y_Button_Tip,&Button_Page);
									Uart_Send_Flag=1;
								//Button_Page.page=0;
									break;
								case 2:
//									SaveData.Main_Func.Param.page=2;
//									SaveData.Main_Func.Param.test=8;
									break;
								default:
									break;
							}
							
							break;
						case 2:
							if(SaveData.Main_Func.Freq>4)
								SaveData.Main_Func.Freq--;
				//			Uart.Ordel=Uart_Ordel[3];
					//		Uart.name=SaveData.Main_Func.Freq;
							Uart_Send_Flag=2;								
							break;
						case 3:
							if(SaveData.Main_Func.Level<2)
								SaveData.Main_Func.Level++;
					//		Uart.Ordel=Uart_Ordel[4];
					//		Uart.name=SaveData.Main_Func.Level;
							Uart_Send_Flag=2;
								
							break;
						
						case 4:
							//SaveData.Main_Func.Range.Auto=0;
					//		Uart.Ordel=Uart_Ordel[6];
					//		Uart.name=SaveData.Main_Func.Range.Range;
							Uart_Send_Flag=2;
							break;
						case 5:
							SaveData.Main_Func.Speed=1;
					//		Uart.Ordel=Uart_Ordel[5];
					//		Uart.name=SaveData.Main_Func.Speed;
							Uart_Send_Flag=2;
							break;
						case 6:
//							if(SaveData.Main_Func.Bias<5000)
//								SaveData.Main_Func.Bias++;
							break;
						default:
							break;
					}
					Savetoeeprom();
				break;
				case Key_F3:
					BUZZER();
					switch(Button_Page.index)
					{
						case 0:
							if(page==1)
								SetSystemStatus(SYS_STATUS_RANGECOUNT);
							break;
						case 1:
							switch(Button_Page.page)
							{
								case 0:
									Button_Page.force=2;									
									Disp_Button_Fun_Set(LIST1+88, FIRSTLINE,
									(uint8_t *)Lp_Button_Tip1,&Button_Page);
								    Uart_Send_Flag=1;
								//	Send_Main_Ord();
								//Button_Page.page=0;
									break;
								case 1:
									Button_Page.force=6;
									
									Disp_Button_Fun_Set(LIST1+88, FIRSTLINE,
									(uint8_t *)R_Button_Tip,&Button_Page);
									Uart_Send_Flag=1;
									break;
								case 2:
//									SaveData.Main_Func.Param.page=2;
//									SaveData.Main_Func.Param.test=8;
									break;
								default:
									break;
							
							
							}
							
							break;
						case 2:
							if(SaveData.Main_Func.Freq<NUM_FREQ)
								SaveData.Main_Func.Freq++;
					//		Uart.Ordel=Uart_Ordel[3];
					//		Uart.name=SaveData.Main_Func.Freq;
							Uart_Send_Flag=2;
				
							break;
//						case 3:
//							break;
						
						case 4://MAX_R_RANGE
							//SaveData.Main_Func.Range.Auto=0;
							if(SaveData.Main_Func.Range.Range>0)
								SaveData.Main_Func.Range.Range--;
				//			Uart.Ordel=Uart_Ordel[6];
				//			Uart.name=SaveData.Main_Func.Range.Range;
							Uart_Send_Flag=2;
							break;
						case 5:
							SaveData.Main_Func.Speed=2;
					//		Uart.Ordel=Uart_Ordel[5];
					//		Uart.name=SaveData.Main_Func.Speed;
							Uart_Send_Flag=2;
							break;
//						case 6:
//							
//							break;
						
						default:
							break;
					
					
					}
					Savetoeeprom();
				break;
				case Key_F4:
					BUZZER();
					switch(Button_Page.index)
					{
						case 0:
//							if(page==1)
//								SetSystemStatus(SYS_STATUS_ITEM);
							break;
						case 1:
							switch(Button_Page.page)
							{
								case 0:
									Button_Page.force=3;
									
									Disp_Button_Fun_Set(LIST1+88, FIRSTLINE,
									(uint8_t *)Ls_Button_Tip,&Button_Page);
									Uart_Send_Flag=1;
								//Button_Page.page=0;
									break;
								case 1:
									SaveData.Main_Func.Param.test=22;
									Uart_Send_Flag=1;
//									SaveData.Main_Func.Param.page=1;
//									SaveData.Main_Func.Param.test=7;
									break;
								case 2:
//									SaveData.Main_Func.Param.page=2;
//									SaveData.Main_Func.Param.test=8;
									break;
								default:
									break;
							
							
							}
							
							break;
						case 2:
							if(SaveData.Main_Func.Freq<NUM_FREQ-10)
								SaveData.Main_Func.Freq+=10;
							else
								SaveData.Main_Func.Freq=NUM_FREQ;
				//			Uart.Ordel=Uart_Ordel[3];
				//			Uart.name=SaveData.Main_Func.Freq;
							Uart_Send_Flag=2;

							break;
//						case 3:
//							break;

					
						case 4:
							//SaveData.Main_Func.Range.Auto=0;
							if(SaveData.Main_Func.Range.Range<MAX_R_RANGE)
								SaveData.Main_Func.Range.Range++;
					//		Uart.Ordel=Uart_Ordel[6];
					//		Uart.name=SaveData.Main_Func.Range.Range;
							Uart_Send_Flag=2;
							break;
//						case 5:
//							break;
//						case 6:
//							break;
//						default:
//							break;
					
					
					}	
					Savetoeeprom();
				break;
				case Key_F5:
					BUZZER();
					if(Button_Page.index==1)
					{
						if(Button_Page.page==0)
							Button_Page.page=1;
						else
							Button_Page.page=0;
					
					
					}
//					if(Button_Page.third!=0xff)
//					{
//						Button_Page.third=0xff;
//					
//					}else
//					{
//                    if(Button_Page.page==0)
//						Button_Page.page=1;
//					else
//						Button_Page.page=0;
//					}
                    //Disp_Button_value1(Button_Page.page);
				break;
				case Key_Disp:
					BUZZER();
                    SetSystemStatus(SYS_STATUS_TEST);
				break;
				case Key_SETUP:
					BUZZER();
                    SetSystemStatus(SYS_STATUS_SETUPTEST);
				break;
				case Key_FAST:
					BUZZER();
				break;
				case Key_LEFT:
					BUZZER();
					if(Button_Page.index==0)
						Button_Page.index=6;
					else
					if(Button_Page.index>3)
						Button_Page.index-=3;
					else
						Button_Page.index+=2;
					Button_Page.page=0;
				break;
				case Key_RIGHT:
					BUZZER();
					if(Button_Page.index==0)
						Button_Page.index=1;
					else
					if(Button_Page.index<=3)
						Button_Page.index+=3;
					else
						Button_Page.index-=2;
					Button_Page.page=0;
						
				break;
				case Key_DOWN:
					BUZZER();
					if(Button_Page.index>5)
						Button_Page.index=0;
					else
						Button_Page.index++;
					Button_Page.page=0;
					
				break;
				case Key_UP:
					BUZZER();
					if(Button_Page.index<1)
						Button_Page.index=6;
					else
						Button_Page.index--;
					Button_Page.page=0;
				break;
				
//				case Key_NUM1:
				//break;
//				case Key_NUM2:
				//break;
	//			case Key_NUM3:
				//break;
		//		case Key_NUM4:
				//break;
			//	case Key_NUM5:
				//break;
//				case Key_NUM6:
				//break;
//				case Key_NUM7:
				//break;
//				case Key_NUM8:
				//break;
//				case Key_NUM9:
				//break;
//				case Key_NUM0:
				//break;
//				case Key_DOT:
//					BUZZER();
//					if(Button_Page.index==2)
//					{ 	Disp_Coordinates_Typedef Coordinates;
//						Coordinates.xpos=LIST1+88;
//						Coordinates.ypos=FIRSTLINE+SPACE1*1;
//						Coordinates.lenth=86;
//			//			SaveData.Main_Func.Freq=Freq_Set_Num(&Coordinates);
//						Uart.Ordel=Uart_Ordel[3];
//							Uart.name=SaveData.Main_Func.Freq;
//							Uart_Send_Flag=2;
//					
//					}
//				break;
//				case Key_BACK:
//					BUZZER();
//				break;
//				case Key_LOCK:
//					BUZZER();
//				break;
//				case Key_BIAS:
//					BUZZER();
//				break;
//				case Key_REST:
//					BUZZER();
//				break;
//				case Key_TRIG:
//					BUZZER();
//				break;
//				default:
//					BUZZER();
//				break;
					
			}
		
		
		}
	
	
	}

}*/
//文件管理程序
/*void File_Process(void)
{
	 uint32_t keynum=0;
	 uint8_t key;
	Delay_Key();
  	while(GetSystemStatus()==SYS_STATUS_FILE)
	{
	 key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==2)
		{
			switch(key)
			{
				case Key_F1:
				break;
				case Key_F2:
				break;
				case Key_F3:
				break;
				case Key_F4:
				break;
				case Key_F5:
				break;
				case Key_Disp:
				break;
				case Key_SETUP:
				break;
				case Key_FAST:
				break;
				case Key_LEFT:
				break;
				case Key_RIGHT:
				break;
				case Key_UP:
				break;
				case Key_DOWN:
				break;
				case Key_NUM1:
				break;
				case Key_NUM2:
				break;
				case Key_NUM3:
				break;
				case Key_NUM4:
				break;
				case Key_NUM5:
				break;
				case Key_NUM6:
				break;
				case Key_NUM7:
				break;
				case Key_NUM8:
				break;
				case Key_NUM9:
				break;
				case Key_NUM0:
				break;
				case Key_DOT:
				break;
				case Key_BACK:
				break;
				case Key_LOCK:
				break;
				case Key_BIAS:
				break;
				case Key_REST:
				break;
				case Key_TRIG:
				break;
				default:
				break;
					
			}
		
		
		}
	

	
	}

}	*/
//参数设置程序  测量设置
/*
void Setup_Process(void)
{

	Button_Page_Typedef Button_Page;
	Disp_Coordinates_Typedef  Coordinates;
	Send_Ord_Typedef Uart;
	
	uint32_t keynum=0;
	uint8_t key;
//    uint8_t page=1;
	uint8_t Disp_Flag=1;
//	uint8_t index=0;
//	uint32_t *pt;
//	pt=(uint32_t *)&SaveData.Main_Func;
	Button_Page.index=0;
	Button_Page.page=0;
    Disp_Test_Set_Item();
	Delay_Key();
 	while(GetSystemStatus()==SYS_STATUS_SETUPTEST)
	{
	    
		if(Disp_Flag==1)
		{
			DispSet_value(&Button_Page);
			Disp_Flag=0;
		
		}
		if(timer0_counter>0)//请求数据
		{
			switch(Uart_Send_Flag)
			{
				case 0:
//					Send_Request();
					break;
				case 1:
					Send_Main_Ord();
					break;
				case 2:
					Send_Freq(&Uart);
					break;
				default:
//					Send_Request();
					break;
			
			}
			Uart_Send_Flag=0;
			
			timer0_counter=0;
		
		
		}
		key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==4)
		{	Disp_Flag=1;
			switch(key)
			{
				case Key_F1:
					BUZZER();
					switch(Button_Page.index)
					{
						case 0:
							if(Button_Page.page==0)
								SetSystemStatus(SYS_STATUS_TEST);//
							else
								SetSystemStatus(SYS_STATUS_FILE);
								
							break;
						case 1:
							switch(Button_Page.page)
							{
								case 0:
									Button_Page.force=0;
									Disp_Button_Fun_Set(LIST1+88, FIRSTLINE,
								(uint8_t *)Cp_Button_Tip,&Button_Page);
									
									//Send_Main_Ord();
								Uart_Send_Flag=1;
									break;
								case 1:
									Button_Page.force=4;

									Disp_Button_Fun_Set(LIST1+88, FIRSTLINE,
									(uint8_t *)Z_Button_Tip,&Button_Page);
									Uart_Send_Flag=1;
									//Button_Page.page=1;
									
									break;
								case 2:
									SaveData.Main_Func.Param.page=8;
									//SaveData.Main_Func.Param.test=8;
									break;
								default:
									break;
							
							
							}
							
							break;
						case 2:
							if(SaveData.Main_Func.Freq>14)
								SaveData.Main_Func.Freq-=10;
							else
								SaveData.Main_Func.Freq=4;
				//			Uart.Ordel=Uart_Ordel[3];
							Uart.name=SaveData.Main_Func.Freq;
							
							Uart_Send_Flag=2;
								
							
							break;
						case 3:
							if(SaveData.Main_Func.Level>0)
								SaveData.Main_Func.Level--;
				//			Uart.Ordel=Uart_Ordel[4];
							Uart.name=SaveData.Main_Func.Level;
							Uart_Send_Flag=2;
							//SaveData.Main_Func.Level=0;
							break;
//						case 4:
//							SaveData.Main_Func.Trig=0;
//							break;
//						case 5:
//							SaveData.Main_Func.Alc=0;
//							break;
						case 6:
							
							SaveData.Main_Func.Rsou=0;
					//		Uart.Ordel=Uart_Ordel[8];
							Uart.name=SaveData.Main_Func.Rsou;
							Uart_Send_Flag=2;
							break;
						case 7:
							if(SaveData.Main_Func.Trig_time.Num>0)
								SaveData.Main_Func.Trig_time.Num--;
							break;
						case 8:
							if(SaveData.Main_Func.Temp_time.Num>0)
								SaveData.Main_Func.Temp_time.Num--;
							break;
						case 9:
							SaveData.Main_Func.beep=0;
							break;
						case 10:
							SaveData.Main_Func.Range.Range=0;
						
					//		Uart.Ordel=Uart_Ordel[6];
							Uart.name=SaveData.Main_Func.Range.Range;
							Uart_Send_Flag=2;
							break;
						case 11:
//							if(SaveData.Main_Func.Bias>0)
//								SaveData.Main_Func.Bias--;
							SaveData.Main_Func.Speed=0;
				//			Uart.Ordel=Uart_Ordel[5];
							Uart.name=SaveData.Main_Func.Speed;
							Uart_Send_Flag=2;
							break;

						case 13:
							if(SaveData.Main_Func.Avg>1)
								SaveData.Main_Func.Avg--;
					//		Uart.Ordel=Uart_Ordel[7];
							Uart.name=SaveData.Main_Func.Avg;
							Uart_Send_Flag=2;
							break;
//						case 14:
//							SaveData.Main_Func.V_i=0;
//							break;
//						case 15:
//							SaveData.Main_Func.Dcr=0;
//							break;
						case 16:
							SaveData.Main_Func.DC_Range.Auto=1;
					//		Uart.Ordel=Uart_Ordel[6];
							Uart.name=SaveData.Main_Func.Range.Auto;
							Uart_Send_Flag=2;
							break;
						case 17:
							if(SaveData.Main_Func.DC_Level>0)
								SaveData.Main_Func.DC_Level--;
							break;
						case 18://这里进行数据测量
							if(SaveData.Main_Func.buad>0)
								SaveData.Main_Func.buad--;
							break;
						default:
							break;
					
					
					}

				break;
				case Key_F2:
					BUZZER();

					switch(Button_Page.index)
					{
						case 0:
							if(Button_Page.page==0)
								SetSystemStatus(SYS_STATUS_USERDEBUG);
							else
								SetSystemStatus(SYS_STATUS_SYSSET);
								
							break;
						case 1:
							switch(Button_Page.page)
							{
								case 0:
									Button_Page.force=1;

									Disp_Button_Fun_Set(LIST1+88, FIRSTLINE,
									(uint8_t *)Cs_Button_Tip,&Button_Page);
									Uart_Send_Flag=1;
									//	SaveData.Main_Func.Param.page=0;
								
								//Button_Page.page=0;
									break;
								case 1:

									Button_Page.force=5;
									Disp_Button_Fun_Set(LIST1+88, FIRSTLINE,
									(uint8_t *)Y_Button_Tip,&Button_Page);
									Uart_Send_Flag=1;
								//Button_Page.page=0;
									break;
								case 2:
//									SaveData.Main_Func.Param.page=2;
//									SaveData.Main_Func.Param.test=8;
									break;
								default:
									break;
							
							
							}
							
							break;
						case 2:
							if(SaveData.Main_Func.Freq>4)
								SaveData.Main_Func.Freq--;
				//			Uart.Ordel=Uart_Ordel[3];
							Uart.name=SaveData.Main_Func.Freq;
							Uart_Send_Flag=2;
							
							
							break;
						case 3:
							if(SaveData.Main_Func.Level<2)
							SaveData.Main_Func.Level++;
					//		Uart.Ordel=Uart_Ordel[4];
							Uart.name=SaveData.Main_Func.Level;
							Uart_Send_Flag=2;
							break;
						case 4:
							SaveData.Main_Func.Trig=1;
							break;
						case 5:
							SaveData.Main_Func.Alc=1;
							break;
						case 6:
							SaveData.Main_Func.Rsou=1;
				//			Uart.Ordel=Uart_Ordel[8];
							Uart.name=SaveData.Main_Func.Rsou;
							Uart_Send_Flag=2;
							break;
//						case 7:
//							if(SaveData.Main_Func.Trig_time.Num<60000)
//								SaveData.Main_Func.Trig_time.Num++;
//							break;
//						case 8:
//							if(SaveData.Main_Func.Temp_time.Num<60000)
//								SaveData.Main_Func.Temp_time.Num++;
//							break;
						case 9:
							SaveData.Main_Func.beep=1;
							break;
						case 10:
							//SaveData.Main_Func.Range.Auto=0;
					//		Uart.Ordel=Uart_Ordel[6];
							Uart.name=SaveData.Main_Func.Range.Range;
							Uart_Send_Flag=2;
							break;
						case 11:
							SaveData.Main_Func.Speed=1;
				//			Uart.Ordel=Uart_Ordel[5];
							Uart.name=SaveData.Main_Func.Speed;
							Uart_Send_Flag=2;
							break;
						case 12:
//							if(SaveData.Main_Func.Bias<5000)
//								SaveData.Main_Func.Bias++;
							
							break;
						case 13:
							if(SaveData.Main_Func.Avg<25)
								SaveData.Main_Func.Avg++;
				//			Uart.Ordel=Uart_Ordel[7];
							Uart.name=SaveData.Main_Func.Avg;
							Uart_Send_Flag=2;
							break;
//						case 14:
//							SaveData.Main_Func.V_i=1;
//							break;
//						case 15:
//							SaveData.Main_Func.Dcr=1;
//							break;
						case 16:
							SaveData.Main_Func.DC_Range.Auto=0;
							break;
						case 17:
							if(SaveData.Main_Func.DC_Level<5000)
								SaveData.Main_Func.DC_Level++;
							break;
						case 18:
							if(SaveData.Main_Func.buad<6)
								SaveData.Main_Func.buad++;
							break;
						default:
							break;
					
					
					}				
				

				break;
				case Key_F3:
		//			BUZZER();
					switch(Button_Page.index)
					{
						case 0:
							if(Button_Page.page==0)
								SetSystemStatus(SYS_STATUS_LIMITSET);
							else
								SetSystemStatus(SYS_STATUS_TOOL);
							break;
						case 1:
							switch(Button_Page.page)
							{
								case 0:
									Button_Page.force=2;
									Disp_Button_Fun_Set(LIST1+88, FIRSTLINE,
									(uint8_t *)Lp_Button_Tip1,&Button_Page);
									Uart_Send_Flag=1;
								//Button_Page.page=0;
									break;
								case 1:
									Button_Page.force=6;
									Disp_Button_Fun_Set(LIST1+88, FIRSTLINE,
									(uint8_t *)R_Button_Tip,&Button_Page);
									Uart_Send_Flag=1;
								//Button_Page.page=0;
									break;
								case 2:
//									SaveData.Main_Func.Param.page=2;
//									SaveData.Main_Func.Param.test=8;
									break;
								default:
									break;
							}
							
							break;
						case 2:
							if(SaveData.Main_Func.Freq<NUM_FREQ)
								SaveData.Main_Func.Freq++;
				//			Uart.Ordel=Uart_Ordel[3];
							Uart.name=SaveData.Main_Func.Freq;
							Uart_Send_Flag=2;
							break;
						case 3:
							break;
						case 4:
							SaveData.Main_Func.Trig=2;
							break;
//						case 5:
//							break;
//						case 6:
//							break;
//						case 7:
//							break;
//						case 8:
//							break;
						case 9:
							SaveData.Main_Func.beep=2;
							break;
						case 10://MAX_R_RANGE
							//SaveData.Main_Func.Range.Auto=0;
							if(SaveData.Main_Func.Range.Range>0)
								SaveData.Main_Func.Range.Range--;
				//			Uart.Ordel=Uart_Ordel[6];
							Uart.name=SaveData.Main_Func.Range.Range;
							Uart_Send_Flag=2;
							break;
						case 11:
							SaveData.Main_Func.Speed=2;
							break;
						case 12:
							
							break;
						case 13:
							break;
						case 14:
							break;
						case 15:
							break;
						case 16:
							if(SaveData.Main_Func.DC_Range.Range>0)
								SaveData.Main_Func.DC_Range.Range--;
							break;
						case 17:
							break;
						case 18:
							break;
						case 19:
							break;
						default:
							break;
					
					
					}	
					
				break;
				case Key_F4:
					BUZZER();
					switch(Button_Page.index)
					{
						case 0:
							if(Button_Page.page==0)				//SYS_STATUS_SYSSET
							    SetSystemStatus(SYS_STATUS_SYSSET);
//								if(Button_Page.page==0)
//								SetSystemStatus(SYS_STATUS_ITEMSET);
							break;
						case 1:
							switch(Button_Page.page)
							{
								case 0:
									Button_Page.force=3;
									Disp_Button_Fun_Set(LIST1+88, FIRSTLINE,
									(uint8_t *)Ls_Button_Tip,&Button_Page);
									Uart_Send_Flag=1;
								//Button_Page.page=0;
									break;
								case 1:
									SaveData.Main_Func.Param.test=22;
									Uart_Send_Flag=1;
//									SaveData.Main_Func.Param.page=1;
//									SaveData.Main_Func.Param.test=7;
									break;
								case 2:
//									SaveData.Main_Func.Param.page=2;
//									SaveData.Main_Func.Param.test=8;
									break;
								default:
									break;
							
							
							}
							
							break;
						case 2:
							if(SaveData.Main_Func.Freq<NUM_FREQ-10)
								SaveData.Main_Func.Freq+=10;
							else
								SaveData.Main_Func.Freq=NUM_FREQ;
				//			Uart.Ordel=Uart_Ordel[3];
							Uart.name=SaveData.Main_Func.Freq;
							Uart_Send_Flag=2;
							break;
						case 3:
							break;
						case 4:
							SaveData.Main_Func.Trig=3;
							break;
						case 5:
							break;
						case 6:
							break;
						case 7:
							break;
						case 8:
							break;
						case 9:
							break;
						case 10:
							//SaveData.Main_Func.Range.Auto=0;
							if(SaveData.Main_Func.Range.Range<MAX_R_RANGE)
								SaveData.Main_Func.Range.Range++;
				//			Uart.Ordel=Uart_Ordel[6];
							Uart.name=SaveData.Main_Func.Range.Range;
							Uart_Send_Flag=2;
							break;
						case 11:
							break;
						case 12:
							break;
						case 13:
							break;
						case 14:
							break;
						case 15:
							break;
						case 16:
							if(SaveData.Main_Func.DC_Range.Range<MAX_R_RANGE)
								SaveData.Main_Func.DC_Range.Range++;
							break;
						case 17:
							break;
						case 18:
							break;
						case 19:
							break;
						default:
							break;
					
					
					}	
				
				break;
				case Key_F5:
					BUZZER();
					switch(Button_Page.index)
					{
						case 0:
							if(Button_Page.page==0)
								Button_Page.page=1;
							else
								Button_Page.page=0;
//							page=2;
//							Disp_Button_TestSet(page);
						break;
						case 1:
							if(Button_Page.page<1)
								Button_Page.page++;
							else
								Button_Page.page=0;

						
						break;
					
					
					}
                    
					
				break;
				case Key_Disp:
						BUZZER();
                        SetSystemStatus(SYS_STATUS_TEST);
				break;
				case Key_SETUP:
						BUZZER();
                        SetSystemStatus(SYS_STATUS_SETUPTEST);
				break;
				case Key_FAST:
					BUZZER();
				break;
				case Key_LEFT:
					BUZZER();
					if(Button_Page.index==0)
						Button_Page.index=18;
					else
					if(Button_Page.index>9)
						Button_Page.index-=9;
					else
//						if(Button_Page.index==1)
//							Button_Page.index=0;
//						
//						else
							Button_Page.index+=8;
					Button_Page.page=0;
						
				break;
				case Key_RIGHT:
					BUZZER();
					if(Button_Page.index==0)
						Button_Page.index=1;
					else
					if(Button_Page.index<=9)
						Button_Page.index+=9;
					else
						Button_Page.index-=8;
					Button_Page.page=0;
						
				break;
				case Key_DOWN:
					BUZZER();
					if(Button_Page.index>17)
						Button_Page.index=0;
					else
						Button_Page.index++;
					Button_Page.page=0;
					
				break;
				case Key_UP:
					BUZZER();
					if(Button_Page.index<1)
						Button_Page.index=17;
					else
						Button_Page.index--;
					Button_Page.page=0;
				break;
				case Key_NUM1:
					
						
				//break;
				case Key_NUM2:
				//break;
				case Key_NUM3:
				//break;
				case Key_NUM4:
				//break;
				case Key_NUM5:
				//break;
				case Key_NUM6:
				//break;
				case Key_NUM7:
				//break;
				case Key_NUM8:
				//break;
				case Key_NUM9:
				//break;
				case Key_NUM0:
				//break;
				case Key_DOT:
					BUZZER();
					if(Button_Page.index==2)
					{
						Coordinates.xpos=LIST1+88;
						Coordinates.ypos=FIRSTLINE+SPACE1*1;
						Coordinates.lenth=86;
			//			SaveData.Main_Func.Freq=Freq_Set_Num(&Coordinates);
					
					}
					if(Button_Page.index==7)
					{
						//LCD_DrawRect( LIST1+88, FIRSTLINE+SPACE1*6-2,SELECT_1END , FIRSTLINE+SPACE1*7-4 , Colour.black ) ;
						Coordinates.xpos=LIST1+88;
						Coordinates.ypos=FIRSTLINE+SPACE1*6;
						Coordinates.lenth=86;
						
						SaveData.Main_Func.Trig_time=Disp_Set_Num(&Coordinates);
					
					
					}
					if(Button_Page.index==8)
					{
						//LCD_DrawRect( LIST1+88, FIRSTLINE+SPACE1*6-2,SELECT_1END , FIRSTLINE+SPACE1*7-4 , Colour.black ) ;
						Coordinates.xpos=LIST1+88;
						Coordinates.ypos=FIRSTLINE+SPACE1*7;
						Coordinates.lenth=86;
						SaveData.Main_Func.Temp_time=Disp_Set_Num(&Coordinates);
					
					
					}
					if(Button_Page.index==13)
					{
						//LCD_DrawRect( LIST1+88, FIRSTLINE+SPACE1*6-2,SELECT_1END , FIRSTLINE+SPACE1*7-4 , Colour.black ) ;
						Coordinates.xpos=LIST2+88;
						Coordinates.ypos=FIRSTLINE+SPACE1*3;
						
						SaveData.Main_Func.Avg=Avg_Set_Num(&Coordinates);
				//		Uart.Ordel=Uart_Ordel[7];
						Uart.name=SaveData.Main_Func.Avg;
						Send_Freq(&Uart);
					
					
					}
					
					if(Button_Page.index==18)//Sort_TypeDef Disp_Set_InputNum(Disp_Coordinates_Typedef *Coordinates)
				
					{
						//LCD_DrawRect( LIST1+88, FIRSTLINE+SPACE1*6-2,SELECT_1END , FIRSTLINE+SPACE1*7-4 , Colour.black ) ;
						Coordinates.xpos=LIST2+88;
						Coordinates.ypos=FIRSTLINE+SPACE1*8;
						
						SaveData.Main_Func.Ref_A=Disp_Set_InputNum(&Coordinates);
					
					
					}
					
					break;
				case Key_BACK:
					BUZZER();
				break;
				case Key_LOCK:
					BUZZER();
				break;
				case Key_BIAS:
					BUZZER();
				break;
				case Key_REST:
					BUZZER();
				break;
				case Key_TRIG:
					BUZZER();
				break;
				default:
					BUZZER();
				break;
					
			}
		
		
		}
	 	
	
	
	
	}
	Savetoeeprom();
}*/
//数据保存程序
void Data_StoreProcess(void)
{
	uint32_t keynum=0;
	uint8_t key;
//	Button_Page_Typedef Button_Page;
//	Button_Page.index=0;
//	Button_Page.page=0;
	Delay_Key();
 	while(GetSystemStatus()==SYS_STATUS_DATASTORE)
	{
	 key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==2)
		{
			switch(key)
			{
				case Key_F1:
				break;
				case Key_F2:
				break;
				case Key_F3:
				break;
				case Key_F4:
				break;
				case Key_F5:
				break;
				case Key_Disp:
				break;
				case Key_SETUP:
				break;
				case Key_FAST:
				break;
				case Key_LEFT:
				break;
				case Key_RIGHT:
				break;
				case Key_UP:
				break;
				case Key_DOWN:
				break;
				case Key_NUM1:
				break;
				case Key_NUM2:
				break;
				case Key_NUM3:
				break;
				case Key_NUM4:
				break;
				case Key_NUM5:
				break;
				case Key_NUM6:
				break;
				case Key_NUM7:
				break;
				case Key_NUM8:
				break;
				case Key_NUM9:
				break;
				case Key_NUM0:
				break;
				case Key_DOT:
				break;
				case Key_BACK:
				break;
				case Key_LOCK:
				break;
				case Key_BIAS:
				break;
				case Key_REST:
				break;
				case Key_TRIG:
				break;
				default:
				break;
					
			}
		
		
		}
	 	
	
	}
}
//档号显示
void Range_Process(void)
{
	
	uint32_t keynum=0;
	uint8_t key;
	Send_Ord_Typedef Uart;
//    uint8_t page=1;
	uint8_t Disp_flag=1;
//	uint8_t index=0;
	Button_Page_Typedef Button_Page;
	Button_Page.index=0;
	Button_Page.page=0;
	Disp_Range_Item();
	Delay_Key();
 	while(GetSystemStatus()==SYS_STATUS_RANGE)
	{
		if(Disp_flag==1)
		{
			Disp_RangeDispValue(&Button_Page);
			Disp_flag=0;	
		}
		Uart_Process();
		
		if(timer0_counter>0)//请求数据
		{
			switch(Uart_Send_Flag)
			{
				case 0:
//					Send_Request();
					break;
				case 1:
					Send_Main_Ord();
					break;
				case 2:
					Send_Freq(&Uart);
					break;
				default:
//					Send_Request();
					break;
			
			}
			Uart_Send_Flag=0;
			
			timer0_counter=0;
		
		
		}
		if(SaveData.Limit_Tab.Comp)
			Test_Comp(&Comp_Change);
		Disp_RangeTestvalue();
	 	key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==KEY_NUM)
		{
			Disp_flag=1;
			switch(key)
			{
				case Key_F1:
					BUZZER();
					if(Button_Page.index==0)
					{
						if(Button_Page.page==0)
							SetSystemStatus(SYS_STATUS_TEST);
					}
					else
						SaveData.Limit_Tab.Comp=0;
				break;
				case Key_F2:
					BUZZER();
					if(Button_Page.index==0)
					{
						if(Button_Page.page==0)
							SetSystemStatus(SYS_STATUS_RANGE);
					}
					else
						SaveData.Limit_Tab.Comp=1;
				break;
				case Key_F3:
					BUZZER();
					if(Button_Page.index==0)
					{
						if(Button_Page.page==0)
							SetSystemStatus(SYS_STATUS_RANGECOUNT);
					}
				break;
				case Key_F4:
					BUZZER();
//					if(Button_Page.index==0)
//					{
//						if(Button_Page.page==0)
//							SetSystemStatus(SYS_STATUS_ITEM);
//					}
				break;
				case Key_F5:
					BUZZER();
//					if(Button_Page.index==0)
//					{
//						if(Button_Page.page==1)
//							Button_Page.page=0;
//						else
//							Button_Page.page=1;
//						Disp_Button_value1(Button_Page.page);
//					}
				break;
				case Key_Disp:
					BUZZER();
                    SetSystemStatus(SYS_STATUS_TEST);
				break;
				case Key_SETUP:
					BUZZER();
                    SetSystemStatus(SYS_STATUS_SETUPTEST);
				break;
				case Key_FAST:
					
//				break;
				case Key_LEFT:
//				break;
				case Key_RIGHT:
//				break;
				case Key_UP:
//				break;
				case Key_DOWN:
					BUZZER();
					if(Button_Page.index)
						Button_Page.index=0;
					else
						Button_Page.index=1;
				break;
				case Key_NUM1:
					BUZZER();
				break;
				case Key_NUM2:
					BUZZER();
				break;
				case Key_NUM3:
					BUZZER();
				break;
				case Key_NUM4:
					BUZZER();
				break;
				case Key_NUM5:
					BUZZER();
				break;
				case Key_NUM6:
					BUZZER();
				break;
				case Key_NUM7:
					BUZZER();
				break;
				case Key_NUM8:
					BUZZER();
				break;
				case Key_NUM9:
					BUZZER();
				break;
				case Key_NUM0:
					BUZZER();
				break;
				case Key_DOT:
					BUZZER();
				break;
				case Key_BACK:
					BUZZER();
				break;
				case Key_LOCK:
					BUZZER();
				break;
				case Key_BIAS:
					BUZZER();
				break;
				case Key_REST:
					BUZZER();
				break;
				case Key_TRIG:
					BUZZER();
				break;
				default:
					BUZZER();
				break;
					
			}
		
		
		}
	
	
	}
}
//档计数显示
/*void Range_CountProcess(void)
{
   	 uint32_t keynum=0;
	uint32_t uart_count=0;
	 uint8_t key;
	u8 i;
	uint8_t Disp_flag=1;
//	 uint8_t page=1;
	Button_Page_Typedef Button_Page;
	Button_Page.index=0;
	Button_Page.page=0;
	Disp_Range_Count_Item();
	Delay_Key();
//	Set_Compbcd_float();
	for(i=0;i<=10;i++)
		Count_buff[i]=0;
 	while(GetSystemStatus()==SYS_STATUS_RANGECOUNT)
	{
		key=HW_KeyScsn();
		if(Disp_flag==1)
		{
			Disp_Range_ComDispValue(&Button_Page);
			Disp_flag=0;
			
		}
		uart_count=Uart_Process();
		if(timer0_counter>0)//请求数据
		{
			switch(Uart_Send_Flag)
			{
				case 0:
//					Send_Request();
					break;
				case 1:
					Send_Main_Ord();
					break;
				case 2:
					//Send_Freq(&Uart);
					break;
				default:
//					Send_Request();
					break;
			
			}
			Uart_Send_Flag=0;
			
			timer0_counter=0;
				
		}
		if(SaveData.Limit_Tab.Comp&&uart_count==1)
			Test_Comp(&Comp_Change);
		//Disp_RangeTestvalue();
		if(SaveData.Limit_Tab.Param)//附属比较
			;
		Disp_RangeCount();//增加分选结果计数
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==KEY_NUM)
		{	Disp_flag=1;
			switch(key)
			{
				case Key_F1:
					BUZZER();
                    if(Button_Page.index==0)
					{
						if(Button_Page.page==0)
							SetSystemStatus(SYS_STATUS_TEST);
					}
					else
						SaveData.Limit_Tab.count=0;
				break;
				case Key_F2:
					BUZZER();
					if(Button_Page.index==0)
					{
                    if(Button_Page.page==0)
                        SetSystemStatus(SYS_STATUS_RANGE);
					}
					else
						SaveData.Limit_Tab.count=1;
				break;
				case Key_F3:
					BUZZER();
					if(Button_Page.index==0)
                    if(Button_Page.page==0)
                        SetSystemStatus(SYS_STATUS_RANGECOUNT);
				break;
				case Key_F4:
					BUZZER();
//					if(Button_Page.index==0)
//                    if(Button_Page.page==0)
//                        SetSystemStatus(SYS_STATUS_ITEM);
				break;
				case Key_F5:
					BUZZER();
//                    if(Button_Page.page==1)
//						Button_Page.page=0;
//					else
//						Button_Page.page=1;
//                    Disp_Button_value1(Button_Page.page);
				break;
				case Key_Disp:
					BUZZER();
                    SetSystemStatus(SYS_STATUS_TEST);
				break;
				case Key_SETUP:
					BUZZER();
                    SetSystemStatus(SYS_STATUS_SETUPTEST);
				break;
				case Key_FAST:
					BUZZER();
				break;
				case Key_LEFT:
				//break;
				case Key_RIGHT:
				//break;
				case Key_UP:
				//break;
				case Key_DOWN:
					BUZZER();
					if(Button_Page.index==0)
						Button_Page.index=1;
					else
						Button_Page.index=0;
				break;
				case Key_NUM1:
				case Key_NUM2:
				case Key_NUM3:
				case Key_NUM4:
				case Key_NUM5:
				case Key_NUM6:
				case Key_NUM7:
				case Key_NUM8:
				case Key_NUM9:
				case Key_NUM0:
				case Key_DOT:
				case Key_BACK:
				case Key_LOCK:
				case Key_BIAS:
				case Key_REST:
				case Key_TRIG:
					BUZZER();
				break;
				default:
					BUZZER();
				break;
					
			}
		
		
		}
	
	
	}
}*/
// 列表显示
/*void ItemProcess(void)
{
	
	uint32_t keynum;
	uint8_t key;
	uint8_t Disp_flag=1;
//    uint8_t page=1;
	
	Button_Page_Typedef Button_Page;
	SaveData.Limit_ScanValue.num=0;
	Button_Page.index=0;
	Button_Page.page=0;
	Disp_List_Count_Item();
	Delay_Key();
 	while(GetSystemStatus()==SYS_STATUS_ITEM)
	{
		if(Disp_flag)
		{
			Disp_flag=0;
			Disp_LIMIT_ComDispValue(&Button_Page);
		}
		
		Disp_Scan_Compvalue(0);
		key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==KEY_NUM)
		{
			Disp_flag=1;
			switch(key)
			{
				case Key_F1:
					BUZZER();
                    if(Button_Page.index==0)
					{
						if(Button_Page.page==0)
							SetSystemStatus(SYS_STATUS_TEST);
					}
					else if(Button_Page.index==1)
						SaveData.Limit_ScanValue.fun=0;
					
				break;
				case Key_F2:
					 BUZZER();
					if(Button_Page.index==0)
					{
						if(Button_Page.page==0)
							SetSystemStatus(SYS_STATUS_RANGE);
					
					}else if(Button_Page.index==1)
						SaveData.Limit_ScanValue.fun=1;
					
				break;
				case Key_F3:
					BUZZER();
					if(Button_Page.index==0)
					{
						if(Button_Page.page==0)
							SetSystemStatus(SYS_STATUS_RANGECOUNT);
					
					}
				break;
				case Key_F4:
					BUZZER();
					if(Button_Page.index==0)
					{
						if(Button_Page.page==0)
							SetSystemStatus(SYS_STATUS_ITEM);
					}
					else if(Button_Page.index==2)
					{
						if(SaveData.Limit_ScanValue.num<1)
							SaveData.Limit_ScanValue.num=20;
						else
							SaveData.Limit_ScanValue.num--;
					
					}
				break;
				case Key_F5:
					BUZZER();
					if(Button_Page.index==0)
					{
						if(Button_Page.page==0)
							Button_Page.page=1;
						else
							Button_Page.page=0;
						Disp_Button_value1(Button_Page.page);
					}
					else if(Button_Page.index==2)
					{
						if(SaveData.Limit_ScanValue.num>=20)
							SaveData.Limit_ScanValue.num=0;
						else
							SaveData.Limit_ScanValue.num++;
					
					}
				break;
				case Key_Disp:
					BUZZER();
                    SetSystemStatus(SYS_STATUS_TEST);
				break;
				case Key_SETUP:
					BUZZER();
                    SetSystemStatus(SYS_STATUS_SETUPTEST);
				break;
				case Key_FAST:
					BUZZER();
				break;
				case Key_LEFT:
					BUZZER();
				break;
				case Key_RIGHT:
					BUZZER();
				break;
				case Key_UP:
					BUZZER();
					if(Button_Page.index>0)
						Button_Page.index--;
				break;
				case Key_DOWN:
					BUZZER();
					if(Button_Page.index<2)
						Button_Page.index++;
				break;
				case Key_NUM1:
				case Key_NUM2:
				case Key_NUM3:
				case Key_NUM4:
				case Key_NUM5:
				case Key_NUM6:
				case Key_NUM7:
				case Key_NUM8:
				case Key_NUM9:
				case Key_NUM0:
				case Key_DOT:
				case Key_BACK:
				case Key_LOCK:
				case Key_BIAS:
				case Key_REST:
				case Key_TRIG:
					BUZZER();
				break;
				default:
					BUZZER();
				break;
					
			}		
		}
	
	}
}*/
//列表扫描设置
/*void Use_ITEMSetProcess(void)
{
	Disp_Coordinates_Typedef  Coordinates;
	uint32_t keynum=0;
	uint8_t key;
//    uint8_t page=0;
	uint8_t Disp_flag=1;
	Button_Page_Typedef Button_Page;
	
	Button_Page.index=0;
	Button_Page.page=0;
	Button_Page.third=0;
	Button_Page.force=0;
	SaveData.Limit_ScanValue.num=0;
	Disp_ListScan_Item();
	Delay_Key();
 	while(GetSystemStatus()==SYS_STATUS_ITEMSET)
	{
	  	
		if(Disp_flag)
		{
			Disp_flag=0;
		
			Disp_Scan_SetCompvalue(&Button_Page);
		}
		key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==KEY_NUM)
		{
			Disp_flag=1;
			switch(key)
			{
				case Key_F1:
					BUZZER();
					if(Button_Page.index==0)
					{
						if(Button_Page.page==0)
							SetSystemStatus(SYS_STATUS_SETUPTEST);
						else
							SetSystemStatus(SYS_STATUS_FILE);
					}
						
				break;
				case Key_F2:
					BUZZER();
					if(Button_Page.index==0)
					{
						if(Button_Page.page==0)
							SetSystemStatus(SYS_STATUS_USERDEBUG);
						else
							SetSystemStatus(SYS_STATUS_SYSSET);
					}
				break;
				case Key_F3://
					BUZZER();
					if(Button_Page.index==0)
					{
						if(Button_Page.page==0)
							SetSystemStatus(SYS_STATUS_LIMITSET);
						else
							SetSystemStatus(SYS_STATUS_TOOL);
					}
				break;
				case Key_F4:
					BUZZER();
					if(Button_Page.index==0)
					{
						if(Button_Page.page==0)
							SetSystemStatus(SYS_STATUS_ITEMSET);
					}else 
					if(Button_Page.index>1)
					{
						if(Button_Page.force>0)
							Button_Page.force--;
					
					}
					
				break;
				case Key_F5:
					BUZZER();
					if(Button_Page.index==0)
					{
						if(Button_Page.page)
							Button_Page.page=0;
						else
							Button_Page.page=1;
						Disp_Button_TestSet(Button_Page.page);
					}else
					if(Button_Page.force<20)
						Button_Page.force++;
				break;
				case Key_Disp:
					BUZZER();
                    SetSystemStatus(SYS_STATUS_TEST);
				break;
				case Key_SETUP:
					BUZZER();
                    SetSystemStatus(SYS_STATUS_SETUPTEST);
				break;
				case Key_FAST:
					BUZZER();
				break;
				case Key_LEFT:
					BUZZER();
					if(Button_Page.third>0)
						Button_Page.third--;
						
					
				break;
				case Key_RIGHT:
					BUZZER();
					if(Button_Page.third<5)
						Button_Page.third++;
					else
						Button_Page.third=5;
				break;
				case Key_UP:
					BUZZER();
					if(Button_Page.index>0)
						Button_Page.index--;
					else
						Button_Page.page=0;
						
				break;
				case Key_DOWN:
					BUZZER();
					if(Button_Page.index<12)
						Button_Page.index++;
					else
						Button_Page.index=12;
				break;
				case Key_NUM1:
				//break;
				case Key_NUM2:
				//break;
				case Key_NUM3:
				//break;
				case Key_NUM4:
				//break;
				case Key_NUM5:
				//break;
				case Key_NUM6:
				//break;
				case Key_NUM7:
				//break;
				case Key_NUM8:
				//break;
				case Key_NUM9:
				//break;
				case Key_NUM0:
				//break;
				case Key_DOT:
				//break;
					BUZZER();
					if(Button_Page.index>2)
					{
						if(Button_Page.third==0)
						{
							Coordinates.xpos=40;//FIRSTLINE+SPACE1+3+ (i-2)*16
							Coordinates.ypos=FIRSTLINE+SPACE1+3+(Button_Page.index-2)*16;
							
				//			SaveData.Limit_ScanValue.freq[Button_Page.force*10+
					//		(Button_Page.index-3)]=Freq_Set_Num(&Coordinates);
						}else 
						if(Button_Page.third==1)
						{
						
						}else
						if(Button_Page.third==2)
						{
						
						}else
						if(Button_Page.third==3)
						{
						
						}else
						if(Button_Page.third==4)
						{
							Coordinates.xpos=420;
							Coordinates.ypos=FIRSTLINE+SPACE1+3+(Button_Page.index-2)*16;
							Coordinates.lenth=60;
							SaveData.Limit_ScanValue.time[Button_Page.force*10+
							(Button_Page.index-3)]=Disp_Set_Num(&Coordinates);
						
						
						}
					
					}
				case Key_BACK:
					BUZZER();
				break;
				case Key_LOCK:
					BUZZER();
				break;
				case Key_BIAS:
					BUZZER();
				break;
				case Key_REST:
					BUZZER();
				break;
				case Key_TRIG:
					BUZZER();
				break;
				default:
					BUZZER();
				break;
					
			}
		
		
		}
	
	
	}
}*/
//极限设置 
/*void Use_LimitSetProcess(void)
{
	
	uint32_t keynum=0;
	uint8_t key,i;
	Disp_Coordinates_Typedef Coordinates;
//    uint8_t page=1;
	uint8_t Disp_flag=1;
	Button_Page_Typedef Button_Page;
	Button_Page.index=0;
	Button_Page.page=0;
	Disp_LimitList_Item();
	Delay_Key();
 	while(GetSystemStatus()==SYS_STATUS_LIMITSET)
	{
	  	if(Disp_flag)
		{
			Disp_flag=0;
			Disp_LimitSEt_value(& Button_Page);
		}
		key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==KEY_NUM)
		{
			Disp_flag=1;
			switch(key)
			{
				case Key_F1:
					BUZZER();
					if(Button_Page.index==0)
					{
						if(Button_Page.page==0)
							SetSystemStatus(SYS_STATUS_SETUPTEST);
						else
							SetSystemStatus(SYS_STATUS_FILE);
					
					}else if(Button_Page.index==1)
					;
//					else if(Button_Page.index==2)
//						;
//					else if(Button_Page.index==3)
//					{
//						SaveData.Limit_Tab.Mode=0;
//					
//					}
//					else if(Button_Page.index==4)
//					{
//						SaveData.Limit_Tab.Param=0;
//					}
					else if(Button_Page.index==5)
					{
						SaveData.Limit_Tab.Comp=0;
					}else
					{
						if(Button_Page.index>15)
						{
						SaveData.Limit_Tab.Comp_Value[Button_Page.index-16].high.Num=0;
						SaveData.Limit_Tab.Comp_Value[Button_Page.index-16].low.Num=0;	
						}else if(Button_Page.index>5)
						{
						SaveData.Limit_Tab.Comp_Value[Button_Page.index-6].high.Num=0;
						SaveData.Limit_Tab.Comp_Value[Button_Page.index-6].low.Num=0;	
						
						}
					
					
					}
						
				break;
//				case Key_F2:
//					BUZZER();
//					if(Button_Page.index==0)
//					{
//						if(Button_Page.page==0)
//							SetSystemStatus(SYS_STATUS_USERDEBUG);
//						else
//							SetSystemStatus(SYS_STATUS_SYSSET);
//					}
//					else if(Button_Page.index==1)
//					;
//					else if(Button_Page.index==2)
//						;
//					else if(Button_Page.index==3)
//					{
//						SaveData.Limit_Tab.Mode=1;
//					
//					}
//					else if(Button_Page.index==4)
//					{
//						SaveData.Limit_Tab.Param=1;
//					}
//					else if(Button_Page.index==5)
//					{
//						SaveData.Limit_Tab.Comp=1;
//					}
//				break;
				case Key_F3:
					BUZZER();
					if(Button_Page.index==0)
					{
						if(Button_Page.page==0)
							SetSystemStatus(SYS_STATUS_LIMITSET);
						else
							SetSystemStatus(SYS_STATUS_TOOL);
					}
				break;
				case Key_F4:
					BUZZER();
				    if(Button_Page.index==0)
					{
						if(Button_Page.page==0)
							SetSystemStatus(SYS_STATUS_SYSSET);
					}
//					if(Button_Page.index==0)
//					{
//						if(Button_Page.page==0)
//							SetSystemStatus(SYS_STATUS_ITEMSET);
//					}
				break;
				case Key_F5:
					BUZZER();
					if(Button_Page.index==0)
					{
//						if(Button_Page.page)
//							Button_Page.page=0;
//						else
//						Button_Page.page=1;
//						Disp_Button_TestSet(Button_Page.page);
					}else if(Button_Page.index>5)
					{
						for(i=0;i<10;i++)
						{
							SaveData.Limit_Tab.Comp_Value[i].low.Num=0;
							SaveData.Limit_Tab.Comp_Value[i].high.Num=0;
						}
						Button_Page.index=0;
					}
				break;
				case Key_Disp:
					BUZZER();
                    SetSystemStatus(SYS_STATUS_TEST);
				break;
				case Key_SETUP:
					BUZZER();
                    SetSystemStatus(SYS_STATUS_SETUPTEST);
				break;
				case Key_FAST:
					BUZZER();
				break;
				case Key_LEFT:
					BUZZER();
					if(Button_Page.index!=0)
					{
						if(Button_Page.index<=5)
						{
							Button_Page.index--;
						}
						else
						{
							if(Button_Page.index>15)
								Button_Page.index-=10;
							else
								Button_Page.index+=9;
						}
					}
				break;
				case Key_RIGHT:
					BUZZER();
					if(Button_Page.index!=0)
					{
//						if(Button_Page.index<=5)
//						{
//							Button_Page.index++;
//						
//						}
//						else
						//if(Button_Page.index)
						{
							if(Button_Page.index>15)
								Button_Page.index-=9;
							else
								//if(Button_Page.index<)
								Button_Page.index+=10;
						}
					}
				break;
				case Key_UP:
					BUZZER();
					if(Button_Page.index>16)
						Button_Page.index--;
					else if(Button_Page.index==16)
						Button_Page.index=5;
					else
						
					if(Button_Page.index>0)
						Button_Page.index--;
				break;
				case Key_DOWN:
					BUZZER();
					if(Button_Page.index<15)
						Button_Page.index++;
					else if(Button_Page.index==15)
						Button_Page.index=0;
					else
						
					if(Button_Page.index<25)
						Button_Page.index++;
					else
						Button_Page.index=0;
						
				break;
//				case Key_NUM1:
//				break;
//				case Key_NUM2:
//				break;
//				case Key_NUM3:
//				break;
//				case Key_NUM4:
//				break;
//				case Key_NUM5:
//				break;
//				case Key_NUM6:
//				break;
//				case Key_NUM7:
//				break;
//				case Key_NUM8:
//				break;
//				case Key_NUM9:
//				break;
//				case Key_NUM0:
//				break;
				case Key_DOT:
					BUZZER();
					if(Button_Page.index==2)//LIST2-24, FIRSTLINE,
					{
							Coordinates.xpos=LIST2-24;//FIRSTLINE+SPACE1+3+ (i-2)*16
							Coordinates.ypos=FIRSTLINE;
							Coordinates.lenth=66;
							SaveData.Limit_Tab.Nom=Disp_Set_InputNum(&Coordinates);
					}else if(Button_Page.index>5&&Button_Page.index<=15)
						{
							//LIST2-90, 76+(i-6)*15
							Coordinates.xpos=LIST2-90;//FIRSTLINE+SPACE1+3+ (i-2)*16
							Coordinates.ypos=76+(Button_Page.index-6)*15;
							Coordinates.lenth=60;
							SaveData.Limit_Tab.Comp_Value[Button_Page.index-6].low=Disp_Set_InputpreNum(&Coordinates);
							SaveData.Limit_Tab.Comp_Value[Button_Page.index-6].high=SaveData.Limit_Tab.Comp_Value[Button_Page.index-6].low;
							//Sort_TypeDef Disp_Set_InputpreNum(Disp_Coordinates_Typedef *Coordinates)
						}else if(Button_Page.index>15)
						{
							Coordinates.xpos=LIST2+70;//FIRSTLINE+SPACE1+3+ (i-2)*16
							Coordinates.ypos=76+(Button_Page.index-16)*15;
							Coordinates.lenth=60;
							SaveData.Limit_Tab.Comp_Value[Button_Page.index-16].high=Disp_Set_InputpreNum(&Coordinates);
						
						}
						do{
							key=HW_KeyScsn();
						}
						while(key!=0xff);
						
				break;
//				case Key_BACK:
//					BUZZER();
//				break;
//				case Key_LOCK:
//					BUZZER();
//				break;
//				case Key_BIAS:
//					BUZZER();
//				break;
//				case Key_REST:
//					BUZZER();
//				break;
//				case Key_TRIG:
//					BUZZER();
//				break;
//				default:
//					BUZZER();
//				break;
					
			}
		
		
		}
	
	
	}
//	Set_Compbcd_float();
	Savetoeeprom();
}
*/
/*

//系统设置
void Use_SysSetProcess(void)
{
	uint32_t  passwordnum=123769;
	uint32_t keynum=0;
	uint8_t key;	//,i=5
	uint8_t Disp_flag=1;
//	uint16_t i=100;
	Button_Page_Typedef Button_Page;
	SaveData.Sys_Setup.Cipher=0;
	Button_Page.index=0;
	Button_Page.page=0;
	Disp_Sys_Item();
	Delay_Key();
 	while(GetSystemStatus()==SYS_STATUS_SYSSET)
	{
	  				
		if(timer0_counter>0)//请求数据
		{
			switch(Uart_Send_Flag)
			{
				case 0:
					break;
				case 1:	
						Start_Correction();
						INSTRUCT_TO_DEBUG;
						Init_C();
					break;
				case 2:
					Correction_C(&Button_Page);
				    Correc_successflag=1;
					break;
				case 3:
					  Save_C();
					  INSTRUCT_TO_DEBUG;
					  Init_R();
					break ;
				case 4:
						Correction_R(&Button_Page);
				        Correc_successflag=1;
					break;
				case 5:
					Save_R();
					INSTRUCT_TO_DEBUG;
					Exit_correction();
					INSTRUCT_TO_DEBUG;
					Exit_correction();
                    SetSystemStatus(SYS_STATUS_SETUPTEST);
					break ;
				case 6:
						Save_R();
						INSTRUCT_TO_DEBUG;
						Exit_correction();
						INSTRUCT_TO_DEBUG;
						Exit_correction();
						SetSystemStatus(SYS_STATUS_TEST);
					break;
				default:
					break;
			
			}
			Uart_Send_Flag=0;			
			timer0_counter=0;				
		}
			if(Disp_flag==1)
		{
			if(Button_Page.page==0)
			  Disp_Sys_value(&Button_Page);
			else if(Button_Page.page==1) 
			  Disp_Correction_Set(&Button_Page);
			else if(Button_Page.page==2)
				Disp_Correction_SetR(&Button_Page);
			Disp_flag=0;
		}
		key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==5)
		{
			Disp_flag=1;
			Correc_successflag=0;
			switch(key)
			{
				case Key_F1:
					BUZZER();
					if(Button_Page.page==0)
					switch(Button_Page.index)
					{ 
						case 0:
//							if(Button_Page.page==0)
								SetSystemStatus(SYS_STATUS_SETUPTEST);
//							else
//							{
//								SetSystemStatus(SYS_STATUS_SYSSET);
//								Button_Page.index=0;
//								Button_Page.page=0;								
//							}
							break;
						case 1:
							break;
						case 2:
							SaveData.Sys_Setup.Pass_Beep=0;
							break;
						case 3:
							SaveData.Sys_Setup.Fail_Beep=0;
							break;
						case 4:
							SaveData.Sys_Setup.Language=0;
							break;
						case 5:
							SaveData.Sys_Setup.Password=1;
							break;
						case 6:
							break;
						case 7:
							if(SaveData.Sys_Setup.Data_Value.Year<1)
								SaveData.Sys_Setup.Data_Value.Year=99;
							else
								SaveData.Sys_Setup.Data_Value.Year--;
							break;
						case 8:
							if(SaveData.Sys_Setup.Data_Value.Mon<=1)
								SaveData.Sys_Setup.Data_Value.Mon=12;
							else
								SaveData.Sys_Setup.Data_Value.Mon--;
							break;
						case 9:
							if(SaveData.Sys_Setup.Data_Value.data<=1)
								SaveData.Sys_Setup.Data_Value.data=31;
							else
								SaveData.Sys_Setup.Data_Value.data--;
							break;
						case 10:
							break ;
						case 11:
							if(SaveData.Sys_Setup.Baue_Rate<1)
								SaveData.Sys_Setup.Baue_Rate=5;
							else
								SaveData.Sys_Setup.Baue_Rate--;
							break;
						case 12:
							SaveData.Sys_Setup.Bias=0;
							break;
						case 13:
							SaveData.Sys_Setup.Bus_Mode=0;
							break;
						case 14:
							if(SaveData.Sys_Setup.GP_Addr<1)
								SaveData.Sys_Setup.GP_Addr=99;
							else
								SaveData.Sys_Setup.GP_Addr--;
							break;
						case 15:
							SaveData.Sys_Setup.Talk_Only=1;
							break;
						case 16:
							if(SaveData.Sys_Setup.Timer_Value.Hour<1)
								SaveData.Sys_Setup.Timer_Value.Hour=12;
							else
								SaveData.Sys_Setup.Timer_Value.Hour--;
							break;
						case 17:
							if(SaveData.Sys_Setup.Timer_Value.Min<1)
								SaveData.Sys_Setup.Timer_Value.Min=59;
							else
								SaveData.Sys_Setup.Timer_Value.Min--;
							break;
						case 18:
							if(SaveData.Sys_Setup.Timer_Value.Sec<1)
								SaveData.Sys_Setup.Timer_Value.Sec=59;
							else
								SaveData.Sys_Setup.Timer_Value.Sec--;
							break;
						default:
							break;
					
					}
					
					else  if(Button_Page.page==1)
						switch(Button_Page.index)
					{ 
//						case 0:
//							break ;
//						case 1:
//						case 2:										  
//						case 3:
//						case 4:
//						case 5:							
//						case 6:					
//						case 7:
						case 8:
//							Uart_Send_Flag=2;
							Correction_C(&Button_Page);		
							Correc_successflag=1;
							break;
						default:
							break;						
					}
					else  if(Button_Page.page==2)
						switch(Button_Page.index)
						{
//							case 0:
//								 break ;
//							case 1:
//							case 2:
//							case 3:
//							case 4:
							case 5:
	//							Uart_Send_Flag=4;
								Correction_R(&Button_Page);	
								Correc_successflag=1;
								break ;
								default :
									break ;
						}
					else
					{
						Button_Page.page=1;
						Button_Page.index=0;
						Disp_Serve_correction();
						Init_C();							
					}
						
                    
				break;
				case Key_F2:
					BUZZER();
					if(Button_Page.page==0)
					switch(Button_Page.index)
					{
						case 0:
						//	SetSystemStatus(SYS_STATUS_SETUPTEST);
							break;
						case 1:
							break;
						case 2:
							SaveData.Sys_Setup.Pass_Beep=1;
							break;
						case 3:
							SaveData.Sys_Setup.Fail_Beep=1;
							break;
						case 4:
							SaveData.Sys_Setup.Language=1;
							break;
						case 5:
							SaveData.Sys_Setup.Password=0;
							break;
						case 6:
							break;
						case 7:
							if(SaveData.Sys_Setup.Data_Value.Year>99)
								SaveData.Sys_Setup.Data_Value.Year=0;
							else
								SaveData.Sys_Setup.Data_Value.Year++;
							break;
						case 8:
							if(SaveData.Sys_Setup.Data_Value.Mon>12)
								SaveData.Sys_Setup.Data_Value.Mon=1;
							else
								SaveData.Sys_Setup.Data_Value.Mon++;
							break;
						case 9:
							if(SaveData.Sys_Setup.Data_Value.data>31)
								SaveData.Sys_Setup.Data_Value.data=1;
							else
								SaveData.Sys_Setup.Data_Value.data++;
							break;
						case 10:
							break ;							
						case 11:
							if(SaveData.Sys_Setup.Baue_Rate>4)
								SaveData.Sys_Setup.Baue_Rate=0;
							else
								SaveData.Sys_Setup.Baue_Rate++;
							break;
						case 12:
							SaveData.Sys_Setup.Bias=1;
							break;
						case 13:
							SaveData.Sys_Setup.Bus_Mode=1;
							break;
						case 14:
							if(SaveData.Sys_Setup.GP_Addr>99)
								SaveData.Sys_Setup.GP_Addr=0;
							else
								SaveData.Sys_Setup.GP_Addr++;
							break;
						case 15:
							SaveData.Sys_Setup.Talk_Only=0;
							break;
						case 16:
							if(SaveData.Sys_Setup.Timer_Value.Hour>12)
								SaveData.Sys_Setup.Timer_Value.Hour=0;
							else
								SaveData.Sys_Setup.Timer_Value.Hour++;
							break;
						case 17:
							if(SaveData.Sys_Setup.Timer_Value.Min>59)
								SaveData.Sys_Setup.Timer_Value.Min=0;
							else
								SaveData.Sys_Setup.Timer_Value.Min++;
							break;
						case 18:
							if(SaveData.Sys_Setup.Timer_Value.Sec>59)
								SaveData.Sys_Setup.Timer_Value.Sec=0;
							else
								SaveData.Sys_Setup.Timer_Value.Sec++;
							break;
						default:
							break;
					
					}
					else if(Button_Page.page==3)
					{
							Button_Page.page=2;
							Button_Page.index=0;
							Disp_Serve_correctionR();
							Init_R();	
					}
					else if(Button_Page.page==1)
						switch(Button_Page.index)
						{
//							case 0:
//								break ;
//							case 1:
//							case 2:
//							case 3:
//							case 4:
							case 5:
								Save_C();
								Button_Page.page=3;
								Button_Page.index=0;
								Disp_Start_Corr();
								break ;
								default :
									break ;
						}
//						if(Button_Page.index!=0)
//						{
//							Save_C();
//							Button_Page.page=3;
//							Button_Page.index=0;
//							Disp_Start_Corr();
//						}
					else  if(Button_Page.page==2)
					switch(Button_Page.index)
					{ 
//						case 0:
//							break ;
//						case 1:
//						case 2:										  
//						case 3:
//						case 4:
//						case 5:							
//						case 6:					
//						case 7:
						case 8:
							Save_R();
							Button_Page.page=3;
							Button_Page.index=0;
							Disp_Start_Corr();
							break;
						default:
							break;						
					}
//						if(Button_Page.index!=0)
//						{
//							Save_R();
//							Button_Page.page=3;
//							Button_Page.index=0;
//							Disp_Start_Corr();
//						}					                   
				break;
				case Key_F3:
					BUZZER();
					if(Button_Page.page==0)
					switch(Button_Page.index)
					{
						case 12:
							SaveData.Sys_Setup.Bus_Mode=2;
							
						break;
						default:
						break;
					
					}
					else  if(Button_Page.page==3)
						switch(Button_Page.index)
					{
						case 0:
//						   Uart_Send_Flag=5;
//						Save_R();
//					INSTRUCT_TO_DEBUG;
						Exit_correction();
						INSTRUCT_TO_DEBUG
						Exit_correction();
						SetSystemStatus(SYS_STATUS_TEST);
						break;
						default:
						break;
					 
					}
						
						
				break;
				case Key_F4:
					BUZZER();
					if(Button_Page.page==0)
					switch(Button_Page.index)
					{
						case 0:
							break;//恢复默认设置
						case 12:
							SaveData.Sys_Setup.Bus_Mode=3;
							
						break;
						default:
						break;
					
					}
				break;
				case Key_F5:
					BUZZER();
					if(Button_Page.page==0)
					switch(Button_Page.index)
					{
						case 0:
							break;//恢复系统复位
						case 12:
							SaveData.Sys_Setup.Bus_Mode=4;
							
						break;
						default:
						break;
					
					}
					else if(Button_Page.page==3)
					{	
						Exit_correction();
						LONGDELAY;
						Clear_Instr();
					}
				break;
				case Key_Disp:
					BUZZER();
					if(Button_Page.page==3)	
//						Uart_Send_Flag=6;
					{	
						Exit_correction();
						INSTRUCT_TO_DEBUG
						Exit_correction();
						SetSystemStatus(SYS_STATUS_TEST);
					
					}
					else if(Button_Page.page==0)
						SetSystemStatus(SYS_STATUS_TEST);

				break;
				case Key_SETUP:					
					BUZZER();
					 if(Button_Page.page==3)
//						Uart_Send_Flag=5; 
					 {
						Exit_correction();
						INSTRUCT_TO_DEBUG 
						Exit_correction();
						SetSystemStatus(SYS_STATUS_SETUPTEST);
						 
					 }
					 else  if(Button_Page.page==0)
						SetSystemStatus(SYS_STATUS_SETUPTEST); 

				break;
				case Key_FAST:
					BUZZER();
				break;
				case Key_LEFT:
					BUZZER();
					if(Button_Page.page==0)
					{
						if(Button_Page.index>9&&Button_Page.index<16)
							Button_Page.index-=9;
						else if(Button_Page.index==17||Button_Page.index==18)
							Button_Page.index-=1;
						else if(Button_Page.index==9||Button_Page.index==8)
							Button_Page.index-=1;
						else if(Button_Page.index==16)
							Button_Page.index-=7;
				    }
				break;
				case Key_RIGHT:
					BUZZER();
					if(Button_Page.page==0)
					{
						if(Button_Page.index<7)
							Button_Page.index+=9;
						else if(Button_Page.index<9)	//Button_Page.index==7||Button_Page.index==8
							Button_Page.index+=1;
						else if(Button_Page.index==16||Button_Page.index==17)
							Button_Page.index+=1;
						else if(Button_Page.index==9)
							Button_Page.index+=7;
					}
				break;
				case Key_DOWN:
					BUZZER();
					if(Button_Page.page==0)
					{
						if(Button_Page.index>17)
							Button_Page.index=0;
						else
							Button_Page.index++;
					}
					else if(Button_Page.page==1)
					{
						if(Button_Page.index>7)
							Button_Page.index=0;
						else
							Button_Page.index++;					
					}
					else
					{
						if(Button_Page.index>4)
							Button_Page.index=0;
						else
							Button_Page.index++;	
					
					}
				break;
				case Key_UP:
					BUZZER();
					if(Button_Page.page==0)
					{
						if(Button_Page.index<1)
							Button_Page.index=18;
						else
							Button_Page.index--;
				    }
					else if(Button_Page.page==1)
					{
						if(Button_Page.index<1)
							Button_Page.index=8;
						else
							Button_Page.index--;
					
					}
					else
					{
					
						if(Button_Page.index<1)
							Button_Page.index=5;
						else
							Button_Page.index--;
					
					}
				break;
				case Key_NUM1:		//passwordnum
					BUZZER();
					if(Button_Page.index==10)
					if(SaveData.Sys_Setup.Cipher<100000)
					    SaveData.Sys_Setup.Cipher=SaveData.Sys_Setup.Cipher*10+1;
				break;
				case Key_NUM2:
					BUZZER();
					if(Button_Page.index==10)
					if(SaveData.Sys_Setup.Cipher<100000)
						SaveData.Sys_Setup.Cipher=SaveData.Sys_Setup.Cipher*10+2;
				break;
				case Key_NUM3:
					BUZZER();
					if(Button_Page.index==10)
					if(SaveData.Sys_Setup.Cipher<100000)
					    SaveData.Sys_Setup.Cipher=SaveData.Sys_Setup.Cipher*10+3;
				break;
				case Key_NUM4:
					BUZZER();
					if(Button_Page.index==10)
					if(SaveData.Sys_Setup.Cipher<100000)
						SaveData.Sys_Setup.Cipher=SaveData.Sys_Setup.Cipher*10+4;
				break;
				case Key_NUM5:
					BUZZER();
					if(Button_Page.index==10)
					if(SaveData.Sys_Setup.Cipher<100000)
						SaveData.Sys_Setup.Cipher=SaveData.Sys_Setup.Cipher*10+5;
				break;
				case Key_NUM6:
					BUZZER();
					if(Button_Page.index==10)
					if(SaveData.Sys_Setup.Cipher<100000)
						SaveData.Sys_Setup.Cipher=SaveData.Sys_Setup.Cipher*10+6;
				break;
				case Key_NUM7:
					BUZZER();
					if(Button_Page.index==10)
					if(SaveData.Sys_Setup.Cipher<100000)
						SaveData.Sys_Setup.Cipher=SaveData.Sys_Setup.Cipher*10+7;
				break;
				case Key_NUM8:
					BUZZER();
					if(Button_Page.index==10)
					if(SaveData.Sys_Setup.Cipher<100000)
						SaveData.Sys_Setup.Cipher=SaveData.Sys_Setup.Cipher*10+8;
				break;
				case Key_NUM9:
					BUZZER();
					if(Button_Page.index==10)
					if(SaveData.Sys_Setup.Cipher<100000)
						SaveData.Sys_Setup.Cipher=SaveData.Sys_Setup.Cipher*10+9;
					if(passwordnum!=SaveData.Sys_Setup.Cipher)
					{
						
						Button_Page.index=0;
						Button_Page.page=3;
						Disp_Start_Corr();
//						Disp_Serve_correction();
//						Uart_Send_Flag=1;
						Start_Correction();
					}
				break;
				case Key_NUM0:
					BUZZER();
					if(Button_Page.index==10)
					if(SaveData.Sys_Setup.Cipher<100000)
						SaveData.Sys_Setup.Cipher=SaveData.Sys_Setup.Cipher*10+0;
				break;
//				case Key_DOT:
//					BUZZER();
//				break;
//				case Key_BACK:
//					BUZZER();
//				break;
//				case Key_LOCK:
//					BUZZER();
//				break;
//				case Key_BIAS:
//					BUZZER();
//				break;
//				case Key_REST:
//					BUZZER();
//				break;
//				case Key_TRIG:
//					BUZZER();
//				break;
//				default:
//					BUZZER();
//				break;
					
			}
		
		
		}
	
	
	}
}
*/
//用户校正
void Use_DebugProcess(void)
{
	
	uint32_t keynum=0;
	uint8_t key;
//    uint8_t page=1;
	uint8_t Disp_flag=1;
	Button_Page_Typedef Button_Page;
	Button_Page.index=0;
	Button_Page.page=0;
	Disp_UserCheck_Item();
	Delay_Key();
 	while(GetSystemStatus()==SYS_STATUS_USERDEBUG)
	{
		if(Disp_flag==1)
		{
			Disp_Debug_value(&Button_Page);
			Disp_flag=0;	
		}
	  	
			if(timer0_counter>0)//请求数据
		{
			switch(Uart_Send_Flag)
			{
				case 0:
					break;
				case 1:	
			//		 Open_Clear();	
					break;
				case 2:	
			//		Short_Clear();
					break;
				case 3:	
			//		Close_Clear();
					break;
				default:
					break;
			
			}
			
			Uart_Send_Flag=0;
			timer0_counter=0;		
		
		}
		
		
		key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==KEY_NUM)
		{
			Disp_flag=1;
			switch(key)
			{
				case Key_F1:
					BUZZER();
                    if(Button_Page.page==0)
					 switch(Button_Page.index)
						{
							case 0:
								SetSystemStatus(SYS_STATUS_SETUPTEST);
								break;
							case 1:	
								SaveData.User_Correction.Open=0;
								Uart_Send_Flag=3;
								break;
							case 2:	
								SaveData.User_Correction.Short=0;
								Uart_Send_Flag=3;
								break;
							default:
								break;
						
						}
//                        SetSystemStatus(SYS_STATUS_SETUPTEST);
//					else
//						SetSystemStatus(SYS_STATUS_FILE);
						
				break;
				case Key_F2:
					BUZZER();
                    if(Button_Page.page==0)
						switch(Button_Page.index)
						{
							case 0:
								SetSystemStatus(SYS_STATUS_USERDEBUG);
								break;
							case 1:	
								SaveData.User_Correction.Open=1;
								Uart_Send_Flag=1;
								break;
							case 2:	
								SaveData.User_Correction.Short=1;
								Uart_Send_Flag=2;
								break;
							default:
								break;
						
						}
//                        SetSystemStatus(SYS_STATUS_USERDEBUG);
//					else
//						SetSystemStatus(SYS_STATUS_SYSSET);
				break;
				case Key_F3:
					BUZZER();
                    if(Button_Page.page==0)
                        SetSystemStatus(SYS_STATUS_LIMITSET);
					else
						SetSystemStatus(SYS_STATUS_TOOL);
				break;
				case Key_F4:
					BUZZER();
                    if(Button_Page.page==0)
                        SetSystemStatus(SYS_STATUS_SYSSET);					
//                    if(Button_Page.page==0)
//                        SetSystemStatus(SYS_STATUS_ITEMSET);
				break;
				case Key_F5:
					BUZZER();
//					if(Button_Page.page)
//						Button_Page.page=0;
//					else
//						Button_Page.page=1;
//                    Disp_Button_TestSet(Button_Page.page);
				break;
				case Key_Disp:
					BUZZER();
                    SetSystemStatus(SYS_STATUS_TEST);
				break;
				case Key_SETUP:
					BUZZER();
                    SetSystemStatus(SYS_STATUS_SETUPTEST);
				break;
				case Key_FAST:
					BUZZER();
				break;
				case Key_LEFT:
					BUZZER();
				break;
				case Key_RIGHT:
					BUZZER();
				break;
				case Key_UP:
					    BUZZER();
						if(Button_Page.index>0)
							Button_Page.index--;
						else
							Button_Page.index=1;
							
				break;
				case Key_DOWN:
					BUZZER();
					if(Button_Page.index>1)
						Button_Page.index=0;
					else
						Button_Page.index++;
				break;
				case Key_NUM1:
				//break;
				case Key_NUM2:
				//break;
				case Key_NUM3:
				//break;
				case Key_NUM4:
				//break;
				case Key_NUM5:
				//break;
				case Key_NUM6:
				//break;
				case Key_NUM7:
				//break;
				case Key_NUM8:
				//break;
				case Key_NUM9:
				//break;
				case Key_NUM0:
				//break;
				case Key_DOT:
					BUZZER();
//					if(Button_Page.index==5)
//					{ 	Disp_Coordinates_Typedef Coordinates;
//						Coordinates.xpos=LIST1+92;
//						Coordinates.ypos=FIRSTLINE+SPACE1*4;
//						Coordinates.lenth=86;
//						
//						SaveData.Main_Func.Freq=Freq_Set_Num(&Coordinates);
//					
//					}
				break;
				case Key_BACK:
					BUZZER();
				break;
				case Key_LOCK:
					BUZZER();
				break;
				case Key_BIAS:
					BUZZER();
				break;
				case Key_REST:
					BUZZER();
				break;
				case Key_TRIG:
					BUZZER();
				break;
				default:
					BUZZER();
				break;
					
			}
		
		
		}
	
	
	}
}

//公司校正
void Fac_DebugProcess(void)
{
	uint32_t keynum=0;
	uint8_t key;
 	while(GetSystemStatus()==SYS_STATUS_FACRDEBUG)
	{
		key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==2)
		{
			switch(key)
			{
				case Key_F1:
				break;
				case Key_F2:
				break;
				case Key_F3:
				break;
				case Key_F4:
				break;
				case Key_F5:
				break;
				case Key_Disp:
				break;
				case Key_SETUP:
				break;
				case Key_FAST:
				break;
				case Key_LEFT:
				break;
				case Key_RIGHT:
				break;
				case Key_UP:
				break;
				case Key_DOWN:
				break;
				case Key_NUM1:
				break;
				case Key_NUM2:
				break;
				case Key_NUM3:
				break;
				case Key_NUM4:
				break;
				case Key_NUM5:
				break;
				case Key_NUM6:
				break;
				case Key_NUM7:
				break;
				case Key_NUM8:
				break;
				case Key_NUM9:
				break;
				case Key_NUM0:
				break;
				case Key_DOT:
				break;
				case Key_BACK:
				break;
				case Key_LOCK:
				break;
				case Key_BIAS:
				break;
				case Key_REST:
				break;
				case Key_TRIG:
				break;
				default:
				break;
					
			}
		
		
		}
	
	
	}
}	
//==========================================================
//函数名称：Uart_Process
//函数功能：串口处理
//入口参数：无
//出口参数：无
//创建日期：2015.10.26 
//修改日期：2015.10.26 10:02
//备注说明：无
//==========================================================
u8 Uart_Process(void)
{
	uint8_t i;
#if HW_UART_SUPPORT
//	u8 kind=0xff;
	u8 data=0;
//#if DEBUG_SUPPORT
	u8 str[(FRAME_LEN_MAX-FRAME_LEN_MIN)+1];//收发数据缓冲
//#else
//	u8 str[(FRAME_LEN_MAX-FRAME_LEN_MIN)+1];//收发数据缓冲
//#endif

//	if(SaveData.Sys_Setup.Bus_Mode==0)//串口有效
	{
		if (ComBuf.rec.end)//接收数据结束
		{data=1;
			memset(str,'\0',(FRAME_LEN_MAX-FRAME_LEN_MIN+1));//清空缓冲
			{
				//memcpy(str,&ComBuf.rec.buf[PDATASTART],ComBuf.send.len-FRAME_LEN_MIN);//数据包
		//		kind=ComBuf.rec.buf[PFRAMEKIND];//命令字
//				Test_Dispvalue.Mainvalue.Num=ComBuf.rec.buf[4];	
//				Test_Dispvalue.Mainvalue.Num<<=8;
//				Test_Dispvalue.Mainvalue.Num|=ComBuf.rec.buf[5];
//				Test_Dispvalue.Mainvalue.Num<<=8;
//				Test_Dispvalue.Mainvalue.Num|=ComBuf.rec.buf[6];
				
				for(i=0;i<5;i++)
				{
					Test_Dispvalue.Main_valuebuff[i]=ComBuf.rec.buf[i+5]+'0';
					Comp_Change.all[0].buff[i]=Test_Dispvalue.Main_valuebuff[i]-'0';
					Test_Dispvalue.Secondvaluebuff[i]=ComBuf.rec.buf[i+13]+'0';
					Comp_Change.all[1].buff[i]=Test_Dispvalue.Secondvaluebuff[i]-'0';
					Test_Dispvalue.Vmvaluebuff[i]=ComBuf.rec.buf[i+21]+'0';
					Comp_Change.all[2].buff[i]=Test_Dispvalue.Vmvaluebuff[i]-'0';
					Test_Dispvalue.Imvaluebuff[i]=ComBuf.rec.buf[i+29]+'0';
					Comp_Change.all[3].buff[i]=Test_Dispvalue.Imvaluebuff[i]-'0';
					
								
				}
				Test_Dispvalue.Dot[0]=ComBuf.rec.buf[10];				
				Test_Dispvalue.Dot[1]=ComBuf.rec.buf[18];
				Test_Dispvalue.Dot[2]=ComBuf.rec.buf[26];
				Test_Dispvalue.Dot[3]=ComBuf.rec.buf[34];
				
				Set_daot(Test_Dispvalue.Main_valuebuff,Test_Dispvalue.Dot[0]);
				Set_daot(Test_Dispvalue.Secondvaluebuff,Test_Dispvalue.Dot[1]);
				Set_daot(Test_Dispvalue.Vmvaluebuff,Test_Dispvalue.Dot[2]);
				Set_daot(Test_Dispvalue.Imvaluebuff,Test_Dispvalue.Dot[3]);
				Test_Dispvalue.Unit[0]=ComBuf.rec.buf[11];
				Test_Dispvalue.Unit[1]=ComBuf.rec.buf[19];
				Test_Dispvalue.Unit[2]=ComBuf.rec.buf[27];
				Test_Dispvalue.Unit[3]=ComBuf.rec.buf[35];
				for(i=0;i<4;i++)
				{
					Comp_Change.all[i].Dot=Test_Dispvalue.Dot[i];
					Comp_Change.all[i].Unit=Test_Dispvalue.Unit[i];
				
				}
				//
//				Test_Dispvalue.Secondvalue.Num=ComBuf.rec.buf[7];	
//				Test_Dispvalue.Secondvalue.Num<<=8;
//				Test_Dispvalue.Secondvalue.Num|=ComBuf.rec.buf[8];
//				Test_Dispvalue.Secondvalue.Num<<=8;
//				Test_Dispvalue.Secondvalue.Num|=ComBuf.rec.buf[9];
				
				
//				Test_Dispvalue.Vmvalue.Num=ComBuf.rec.buf[10];	
//				Test_Dispvalue.Vmvalue.Num<<=8;
//				Test_Dispvalue.Vmvalue.Num|=ComBuf.rec.buf[11];
//				Test_Dispvalue.Vmvalue.Num<<=8;
//				Test_Dispvalue.Vmvalue.Num|=ComBuf.rec.buf[12];
//				
//				Test_Dispvalue.Imvalue.Num=ComBuf.rec.buf[13];	
//				Test_Dispvalue.Imvalue.Num<<=8;
//				Test_Dispvalue.Imvalue.Num|=ComBuf.rec.buf[14];
//				Test_Dispvalue.Imvalue.Num<<=8;
//				Test_Dispvalue.Imvalue.Num|=ComBuf.rec.buf[15];
////			Test_Dispvalue.Mainvalue.Num=12345;
//			Test_Dispvalue.Mainvalue.Dot=3;
////			Test_Dispvalue.Secondvalue.Num=12345;
//			Test_Dispvalue.Secondvalue.Dot=3;
////			Test_Dispvalue.Vmvalue.Num=12345;
//			Test_Dispvalue.Vmvalue.Dot=3;
//////			Test_Dispvalue.Imvalue.Num=12345;
//			Test_Dispvalue.Imvalue.Dot=3;
			}
			//准备接收下一帧数据sprintf
			ComBuf.rec.end=0;//接收缓冲可读标志复位
			ComBuf.rec.ptr=0;//接收指针清零
		}
	}
//	WriteString_Big(0, 150, (uint8_t *)&ComBuf.rec.buf[1]);
	ComBuf.rec.end=0;

//	switch(kind)
//	{
//		case FRAME_READ_RESULT://读取结果
//			//串口发送测试数据:电压(5)+电阻(6)+时间(4)+分选(1)=16字节
//			switch (GetSystemMessage())//系统信息
//			{
//				case MSG_ABORT:
//					kind=0x9B;//测试中止
//					break;
//				case MSG_PASS:
//					kind=0x91;//测试通过
//					break;
//				case MSG_HIGH:
//					kind=0x92;//上限报警
//					break;
//				case MSG_LOW:
//					kind=0x92;//下限报警
//					break;
//				default:
//					kind=0x90;//正常测试
//					break;
//			}		
//			ComBuf.send.buf[1+5+6+4]=kind;
//			ComBuf.send.begin=0;
//			ComBuf.send.len=PackStandFrame(ComBuf.send.buf , &ComBuf.send.buf[1] , 16  );
////			if(SendDataToCom()==0)//发送成功判别
////			{
////			//	Delay_1ms(100);//延时
////			//	SendDataToCom();//发送
////			}
//			break;
//		
//		case FRAME_START://启动
//			SetSystemStatus(SYS_STATUS_TEST);//系统状态-启动测试
//			break;

//		case FRAME_RESET://复位
//			//SetSystemStatus(SYS_STATUS_IDLE);//系统状态-待机
//			break;

//		case FRAME_WRITE_SN://写序列号
//			break;
//		
//		case FRAME_CLR_BOOT_NUM://清开机次数
//			break;
//		
//		case FRAME_DATA://数据帧
//			break;

//		default:
//			break;
//	}
	return data;
#endif
}

////全局变量
//u8 WaitRecTimeOver;

//==========================================================
//函数名称：PackStandFrame
//函数功能：将数据打包成帧
//入口参数：*framebuf:帧数据缓冲
//			*datbuf:数据缓冲
//			len:数据长度
//出口参数：一帧数据长度
//创建日期：2014.04.11
//修改日期：2014.04.11 10:28
//备注说明：旧的发送协议
//开始(0xAB)，电压(5) 电阻(6) 时间(4)，分选(1)，结束(0xAF)=18字节
//==========================================================
int8_t PackStandFrame(int8_t * framebuf, int8_t * datbuf, int8_t len)
{
	if(len>(SEND_LEN_MAX-2))//数据的最大长度
		len=(SEND_LEN_MAX-2);
	framebuf[0]=UART_SEND_BEGIN;//帧头
	memcpy(&framebuf[1], datbuf, len);//数据
	framebuf[len+1]=UART_SEND_END;//帧尾
	return (len+1);//返回一帧数据长度
}

const u32 UNIT_VALUE[15]=
{
	1,1E3,1E6

};
Sort_TypeDef Input_compvalue(Disp_Coordinates_Typedef *Coordinates)
{
	u8 key;		//,i
	u8 page=0;
	u8 disp_flag=1;
//	u8 index=0;
	u8 disp_cound=0;
//	u8 disp_pow=0;
//	u8 input_flag=0;
//	u32 unit_c;
	u8 dot=5;//小数点
	u8 dot_num=0;
	uint8_t While_flag=1;
	uint32_t keynum=0;
	uint8_t Disp_buff[10];
	uint8_t key_count;
	uint8_t dot_num1;
	uint8_t del_flag=0;
	Sort_TypeDef   Sort_set;

//	u8 unit=0;//单位
//	u32 Word;
	
	float conp_value=0;
//	float old_value;
	key_count=0;
//	old_value=SaveData.SetParameter.Nominal_value.comp_value;
//	if(SaveData.SysParameter.language==0)
//		Disp_Inputback("输入数值");//背景色
//	else
//		Disp_Inputback("INPUTNUM");//背景色
	LCD_DrawRect( Coordinates->xpos, Coordinates->ypos,Coordinates->xpos+Coordinates->lenth , 
	Coordinates->ypos+16 , Red );
	while(While_flag)
	{
		key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==KEY_NUM)
		{
			disp_flag=1;
			switch(key)
			{
				case Key_F1:
					//unit_c=UNIT_VALUE[DispBuf[disp_cound]-'0'];
						conp_value*=pow(10,5-(disp_cound-dot_num));
						//Sort_set.Num=	conp_value *unit_c/pow(10,dot);
						Sort_set.Num=conp_value;
						Sort_set.Dot=dot;
						if(page==0)
							Sort_set.Unit=0;
						else
							Sort_set.Unit=4;
							
						While_flag=0;
					break;
				case Key_F2:
						conp_value*=pow(10,5-(disp_cound-dot_num));
						//Sort_set.Num=	conp_value *unit_c/pow(10,dot);
						Sort_set.Num=conp_value;
						Sort_set.Dot=dot;
						if(page==0)
							Sort_set.Unit=1;
						else
							Sort_set.Unit=5;
						While_flag=0;
					break;
				case Key_F3:
					conp_value*=pow(10,5-(disp_cound-dot_num));
						//Sort_set.Num=	conp_value *unit_c/pow(10,dot);
						Sort_set.Num=conp_value;
						Sort_set.Dot=dot;
						if(page==0)
							Sort_set.Unit=2;
						else
							Sort_set.Unit=6;
						While_flag=0;
					break;
				case Key_F4:
						if(page==0)
						{
						conp_value*=pow(10,5-(disp_cound-dot_num));
						//Sort_set.Num=	conp_value *unit_c/pow(10,dot);
						Sort_set.Num=conp_value;
						Sort_set.Dot=dot;
						Sort_set.Unit=3;
						While_flag=0;
						}
					break;
//				case Key_F5:
//					if(page)
//						page=0;
//					else
//						page=1;
//				
//					break;
				case Key_Disp:
					SetSystemStatus(SYS_STATUS_TEST);
					While_flag=0;
					Sort_set.Updata_flag=0;
				break;
				case Key_SETUP:
					While_flag=0;
					Sort_set.Updata_flag=0;
				SetSystemStatus(SYS_STATUS_SETUPTEST);
				break;
//				case Key_FAST:
//				break;
//				case Key_LEFT:
//				break;
//				case Key_RIGHT:
//				break;
//				case Key_UP:
//				break;
//				case Key_DOWN:
//				break;
//				case Key_NUM1:
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='1';
//						key_count++;
//						Word=Disp_buff[disp_cound]-'0';
//						conp_value=conp_value*10+Word;
//						disp_pow++;
//						disp_cound++;
//						if(dot_num==0)
//							dot--;
//							
//					}
//				break;
//				case Key_NUM2:
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='2';
//						key_count++;
//						Word=Disp_buff[disp_cound]-'0';
//						conp_value=conp_value*10+Word;
//						disp_pow++;
//						disp_cound++;
//						if(dot_num==0)
//							dot--;
//					}
//				break;
//				case Key_NUM3:
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='3';
//						key_count++;
//						Word=Disp_buff[disp_cound]-'0';
//						conp_value=conp_value*10+Word;
//						disp_pow++;
//						disp_cound++;
//						if(dot_num==0)
//							dot--;
//					}
//				break;
//				case Key_NUM4:
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='4';
//						key_count++;
//						Word=Disp_buff[disp_cound]-'0';
//						conp_value=conp_value*10+Word;
//						disp_pow++;
//						disp_cound++;
//						if(dot_num==0)
//							dot--;
//					}
//					
//				break;
//				case Key_NUM5:
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='5';
//						key_count++;
//						Word=Disp_buff[disp_cound]-'0';
//						conp_value=conp_value*10+Word;
//						disp_pow++;
//						disp_cound++;
//						if(dot_num==0)
//							dot--;
//					}
//				break;
//				case Key_NUM6:
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='6';
//						key_count++;
//						Word=Disp_buff[disp_cound]-'0';
//						conp_value=conp_value*10+Word;
//						disp_pow++;
//						disp_cound++;
//						if(dot_num==0)
//							dot--;
//					}
//				break;
//				case Key_NUM7:
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='7';
//						
//						Word=Disp_buff[disp_cound]-'0';
//						key_count++;
//						conp_value=conp_value*10+Word;
//						disp_pow++;
//						disp_cound++;
//						if(dot_num==0)
//							dot--;
//					}
//				break;
//				case Key_NUM8:
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='8';
//						key_count++;
//						Word=Disp_buff[disp_cound]-'0';
//						conp_value=conp_value*10+Word;
//						disp_pow++;
//						disp_cound++;
//						if(dot_num==0)
//							dot--;
//					}
//				break;
//				case Key_NUM9:
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='9';
//						key_count++;
//						Word=Disp_buff[disp_cound]-'0';
//						conp_value=conp_value*10+Word;
//						disp_pow++;
//						disp_cound++;
//						if(dot_num==0)
//							dot--;
//					}
//				break;
//				case Key_NUM0:
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='0';
//						key_count++;
//						Word=Disp_buff[disp_cound]-'0';
//						conp_value=conp_value*10+Word;
//						disp_pow++;
//						disp_cound++;
//						if(dot_num==0)
//							dot--;
//					}
//				break;
//				case Key_DOT:
//					if(dot_num==0)
//					{
//						dot_num1=key_count;
//						Disp_buff[key_count]='.';
//						dot_num=1;
//						key_count++;
//						disp_cound++;
//					}
//					break;
				case Key_BACK:
					if(key_count>0)
					{	key_count--;
						Disp_buff[key_count]=' ';
						if(dot_num1==key_count)
						{
							dot_num=0;
							dot_num1=0;
							
						}
						del_flag=1;
					
					}
//					else
//					{
//						if(Disp_buff[key_count]==0)
//								Disp_buff[key_count]='-';
//							else if(Disp_buff[key_count]=='-')
//								Disp_buff[key_count]='+';
//							else
//								Disp_buff[key_count]='-';
//							key_count++;
//					}
				break;
//				case Key_LOCK:
//				break;
//				case Key_BIAS:
//				break;
//				case Key_REST:
//				break;
//				case Key_TRIG:
//				break;
				default:
				break;
					
			}
			if(disp_flag)
			{
				disp_flag=0;
				Disp_button_Num_Input(page);
				Colour.Fword=White;
				Colour.black=Red;
				if(del_flag)
				{
					PutChar( Coordinates->xpos+(key_count+1)*10, Coordinates->ypos, 
					Disp_buff[key_count], Colour.Fword, Colour.black ); 
					del_flag=0;
					
				}
				else if(key_count>0)				
					PutChar( Coordinates->xpos+key_count*10, Coordinates->ypos, 
					Disp_buff[key_count-1], Colour.Fword, Colour.black );
			}
		}	
	}
	return Sort_set;
}
	
	

//数字键输入显示
Sort_TypeDef Disp_NumKeyboard_Set(Disp_Coordinates_Typedef *Coordinates )
{
	uint8_t While_flag=1;
	uint8_t Disp_buff[10]={"         ",};
	uint8_t key,i;
	uint8_t dispflag=1;
	uint8_t dot_num=0,dot_num1=0;
	uint8_t page=0;
	uint32_t keynum=0;
	uint8_t key_count=0;
//	uint32_t Num[6]={1,10,100,1e3,1e4,1e5};
	Sort_TypeDef   Sort_set;
	Sort_set.Dot=0;
	Sort_set.Num=0;
	Sort_set.Unit=0;
	Sort_set.Num=0;
//	for(i=0;i<6;i++)
//	Disp_buff[i]=' ';
	Disp_buff[7]=0;
	
	while(While_flag)
	{
		key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==5)
		{
			dispflag=1;
			switch(key)
			{
				case Key_F1:
					BUZZER();
					if(page==0)
						Sort_set.Unit=0;
					else
						Sort_set.Unit=5;
					While_flag=0;
					if(key_count<NUM_LENTH)
					{
						if(dot_num==0)
						{
							if(key_count>0)
							{
								Disp_buff[key_count]='.';
								dot_num1=key_count;
								key_count++;													
							}
							dot_num++;
						}					
					}
					Sort_set.Updata_flag=1;
					
				break;
				case Key_F2:
					BUZZER();
					if(page==0)
						Sort_set.Unit=1;
					else
						Sort_set.Unit=6;
					While_flag=0;
					if(key_count<NUM_LENTH)
					{
						if(dot_num==0)
						{
							if(key_count>0)
							{
								Disp_buff[key_count]='.';
								dot_num1=key_count;
								key_count++;
							}
							dot_num++;
						}
					}
					Sort_set.Updata_flag=1;
				break;
				case Key_F3:
					BUZZER();
					if(page==0)
						Sort_set.Unit=2;
					else
						Sort_set.Unit=8;
					While_flag=0;
					if(key_count<NUM_LENTH)
					{
						if(dot_num==0)
						{
							if(key_count>0)
							{
								Disp_buff[key_count]='.';
								dot_num1=key_count;
								key_count++;
							}
							dot_num++;
						}
					}
					Sort_set.Updata_flag=1;
				break;
				case Key_F4:
					BUZZER();
					if(page==0)
						Sort_set.Unit=3;
					else
						Sort_set.Unit=7;
					While_flag=0;
					if(key_count<NUM_LENTH)
					{
						if(dot_num==0)
						{
							if(key_count>0)
							{
								Disp_buff[key_count]='.';
								dot_num1=key_count;
								key_count++;
							}
							dot_num++;
						}
					}
					Sort_set.Updata_flag=1;
				break;
				case Key_F5:
					BUZZER();
					if(page==0)
						page=1;
					else
					page=0;
				break;
				case Key_Disp:
					BUZZER();
					SetSystemStatus(SYS_STATUS_TEST);
					While_flag=0;
					Sort_set.Updata_flag=0;
				break;
				case Key_SETUP:
					BUZZER();
					While_flag=0;
					Sort_set.Updata_flag=0;
				SetSystemStatus(SYS_STATUS_SETUPTEST);
				break;
				case Key_FAST:
					BUZZER();
				break;
				case Key_LEFT:
					BUZZER();
				break;
				case Key_RIGHT:
					BUZZER();
				break;
				case Key_UP:
					BUZZER();
				break;
				case Key_DOWN:
					BUZZER();
				break;
//				case Key_NUM1:
//					BUZZER();
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='1';					
//						key_count++;
//					}
//				break;
//				case Key_NUM2:
//					BUZZER();
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='2';
//						key_count++;
//					}
//				break;
//				case Key_NUM3:
//					 BUZZER();
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='3';
//						key_count++;
//					}
//				break;
//				case Key_NUM4:
//					BUZZER();
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='4';
//						key_count++;
//					}
//				break;
//				case Key_NUM5:
//					BUZZER();
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='5';
//						key_count++;
//					}
//				break;
//				case Key_NUM6:
//					 BUZZER();
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='6';
//						key_count++;
//					}
//				break;
//				case Key_NUM7:
//					BUZZER();
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='7';
//						key_count++;
//					}
//				break;
//				case Key_NUM8:
//					BUZZER();
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='8';
//						key_count++;
//					}
//				break;
//				case Key_NUM9:
//					BUZZER();
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='9';
//						key_count++;
//					}
//				break;
//				case Key_NUM0:
//					BUZZER();
//					if(key_count<NUM_LENTH)
//					{
//						Disp_buff[key_count]='0';
//						key_count++;
//					}
//				break;
				case Key_DOT:
					BUZZER();
					if(key_count<NUM_LENTH&&key_count>0)
					{
						if(dot_num==0)
						{
							if(key_count>0)
							{
								Disp_buff[key_count]='.';
								dot_num1=key_count;
								key_count++;
							
							
							}
							dot_num++;
						}
					}
//					else 
//					{
//						if(Disp_buff[key_count]==0)
//							Disp_buff[key_count]='-';
//						else if(Disp_buff[key_count]=='-')
//							Disp_buff[key_count]='+';
//						else
//							Disp_buff[key_count]='-';
//						key_count++;
//							
//					
//					
//					
//					
//					}
				break;
				case Key_BACK:
					BUZZER();
					if(key_count>0)
					{	key_count--;
						Disp_buff[key_count]=' ';
						if(dot_num1==key_count)
						{
							dot_num=0;
							dot_num1=0;
							
						}
					
					}
					else
					{
						if(Disp_buff[key_count]==0)
								Disp_buff[key_count]='-';
							else if(Disp_buff[key_count]=='-')
								Disp_buff[key_count]='+';
							else
								Disp_buff[key_count]='-';
							key_count++;
					}
				break;
				case Key_LOCK:
					BUZZER();
				break;
				case Key_BIAS:
					BUZZER();
				break;
				case Key_REST:
					BUZZER();
				break;
				case Key_TRIG:
					BUZZER();
				break;
				default:
					BUZZER();
				break;
					
			}
		
		
		}
		if(dispflag)
		{
			dispflag=0;
			LCD_DrawRect( Coordinates->xpos, Coordinates->ypos,Coordinates->xpos+Coordinates->lenth , Coordinates->ypos+16 , Red );
			Colour.Fword=White;
			Colour.black=Red;
			WriteString_16(Coordinates->xpos, Coordinates->ypos, Disp_buff,  0);
			//dispflag=0;
		}
	
	}
	for(i=key_count;i<NUM_LENTH;i++)
		Disp_buff[i]='0';
	for(i=0;i<NUM_LENTH;i++)
	{
		if(Disp_buff[0]>='0'&&(Disp_buff[0]<='9'))
		{
			if(Disp_buff[i]>='0'&&(Disp_buff[i]<='9'))
			{
			
				if(dot_num1>i)
				{
					Sort_set.Num*=10;
					Sort_set.Num+=Disp_buff[i]-'0';
				
				}
				else
				{
					Sort_set.Num*=10;
					Sort_set.Num+=Disp_buff[i]-'0';
				}
			}
			//Sort_set.Num+=(Disp_buff[key_count-1]-'0');
		}
	}
	Sort_set.Dot=dot_num1;
//	if(Disp_buff[0]>='0'&&(Disp_buff[0]<'9'))
//		{
//			if(Disp_buff[key_count-1]!='.')		
//			{
//				Sort_set.Num*=Num[key_count-dot_num-1];
//				Sort_set.Num+=(Disp_buff[key_count-1]-'0');//*Num[key_count-dot_num-1];
//				
//			}				
//			//*(Disp_buff[key_count-1]-'0'))+=Num[key_count-dot_num-1];
//			else
//			{
//			
//			}
//		
//		
//		}
//			
//		else 
//			;//(Disp_buff[key_count-1]-'0')*Sort_set.Num+=Num[key_count-dot_num-2];
	return Sort_set;

}

Sort_TypeDef Disp_Set_Num(Disp_Coordinates_Typedef *Coordinates)
{
	Sort_TypeDef Sort_num,Sort_num1;
	Disp_button_Num_time();
	Sort_num=Disp_NumKeyboard_Set(Coordinates);
	Sort_num1=Time_Set_Cov(&Sort_num);
	if(Sort_num1.Updata_flag==0)
	{
		Sort_num1.Dot=0;
		Sort_num1.Num=0;
		Sort_num1.Unit=0;
	
	}
		
	return Sort_num1;

}
Sort_TypeDef Disp_Set_CompNum(Disp_Coordinates_Typedef *Coordinates)
{
	Sort_TypeDef Sort_num,Sort_num1;
	Disp_button_Num_time();
	Sort_num=Disp_NumKeyboard_Set(Coordinates);
	Sort_num1=Time_Set_Cov(&Sort_num);
	if(Sort_num1.Updata_flag==0)
	{
		Sort_num1.Dot=0;
		Sort_num1.Num=0;
		Sort_num1.Unit=0;
	
	}
		
	return Sort_num1;

}
Sort_TypeDef Disp_Set_InputNum(Disp_Coordinates_Typedef *Coordinates)
{
	Sort_TypeDef Sort_num1;		//Sort_num,
	Disp_button_Num_Input(0);
	Sort_num1=Input_compvalue(Coordinates);
	//if(SaveData.Limit_Tab.Mode==0)
	Sort_num1=Input_Set_Cov(&Sort_num1);
	//else
	//Sort_num1=Input_Set_CovPre(&Sort_num1);
	if(Sort_num1.Updata_flag==0)
	{
		Sort_num1.Dot=0;
		Sort_num1.Num=0;
		Sort_num1.Unit=0;
	}
	return Sort_num1;
}
Sort_TypeDef Disp_Set_InputpreNum(Disp_Coordinates_Typedef *Coordinates)
{
	Sort_TypeDef Sort_num1;  //Sort_num,
	Disp_button_Num_Input(0);
	Sort_num1=Input_compvalue(Coordinates);//Input_Set_Cov
	if(SaveData.Limit_Tab.Mode==0)
		Sort_num1=Input_Set_Cov(&Sort_num1);
	else
		Sort_num1=Input_Set_CovPre(&Sort_num1);
	if(Sort_num1.Updata_flag==0)
	{
		Sort_num1.Dot=0;
		Sort_num1.Num=0;
		Sort_num1.Unit=0;
	}
	return Sort_num1;
}

/*
uint8_t Freq_Set_Num(Disp_Coordinates_Typedef *Coordinates)//频率设置
{
	Sort_TypeDef Sort_num,Sort_num1;
	uint8_t i;
	uint8_t num;
	Disp_button_Num_Freq();
	Sort_num=Disp_NumKeyboard_Set(Coordinates);
	Sort_num1=Freq_Set_Cov(&Sort_num);
	if(Sort_num1.Updata_flag==0)
	{
		Sort_num1.Dot=0;
		Sort_num1.Num=0;
		Sort_num1.Unit=0;
	
	}
	for(i=4;i<NUM_FREQ+1;i++)
	{
		if(Sort_num1.Num>=FreqNum[i]&&Sort_num1.Num<FreqNum[i+1])
		{
			num=i;
			break;
		}
		else
			num=4;			
	}
	return num;
}*/
uint8_t Avg_Set_Num(Disp_Coordinates_Typedef *Coordinates)//平均数设置
{
	Sort_TypeDef Sort_num,Sort_num1;
	uint8_t i;
	uint8_t num;
	Disp_button_Num_Avg();
	Sort_num=Disp_NumKeyboard_Set(Coordinates);
	Sort_num1=Freq_Set_Cov(&Sort_num);
	if(Sort_num1.Updata_flag==0)
	{
		Sort_num1.Dot=0;
		Sort_num1.Num=0;
		Sort_num1.Unit=0;
	
	}
	if(Sort_num1.Dot==0)
	{
		if(Sort_num1.Num>32)
			Sort_num1.Num=32;
	
	} else
	if(Sort_num1.Dot==1)
	{
		for(i=0;i<5;i++)
		{
			if(Sort_num1.Num>0&&Sort_num1.Num<=9)
				break;
			else
				Sort_num1.Num/=10;
		}
	
	}else if(Sort_num1.Dot==2)
	{
		for(i=0;i<5;i++)
		{
			if(Sort_num1.Num>10&&Sort_num1.Num<=99)
				break;
			else
				Sort_num1.Num/=10;
		}
		if(Sort_num1.Num>32)
			Sort_num1.Num=32;
	}else
	{
		Sort_num1.Num=32;
	}
	num=Sort_num1.Num;
	if(num==0)
		num=1;
	return num;
}
void Set_daot(uint8_t *buff,uint8_t dot)
{
	uint8_t i;
	for(i=0;i<dot;i++)
	{
		buff[5-i]=buff[5-i-1];		
	}
	if(dot==0)
		buff[5]=' ';
	else
	buff[5-dot]='.';
	for(i=0;i<6;i++)
	{
		if(buff[i]>0x80)
			buff[i]='0';
	}
	buff[6]=0;
}
void Test_Comp(All_Compvalue_Typedef *pt)
{
	float value;
	float data;
	uint8_t i;
	for(i=0;i<5;i++)
	{
		data=pt->all[0].buff[i];
		value+=(pow(10,4-i)*data);//从下位机接收来的数据
	}
	value=value*pow(1000,pt->all[0].Unit);
	value/=(pow(10,pt->all[0].Dot));
	
	if(SaveData.Limit_Tab.Mode)//百分比比较
	{
		for(i=0;i<9;i++)
		{
			if(SaveData.Limit_Tab.Comp_Value[i].low.Num!=0)
			{
				if(value>Comp_Testvalue.comp_highvalue[i])//大于上限
					Count_buff[10]++;
				else if(value<Comp_Testvalue.comp_lowvalue[i])//小于下限 加合格标志位
									//计数
					Count_buff[10]++;
				else Count_buff[i]++;
			}
		}
	
	}
//	else
//	{
//	
//	
//	}//ABS比较

}//Comp_Testvalue  Comp_Testvalue
/*
float Inttofloat(Sort_TypeDef *pt)//int转换为float  INT包含小数点和单位
{
	float value;
//	uint8_t i;
	value=pt->Num;
	value=value*pow(1000,pt->Unit);
	value/=pow(10,pt->Dot);
	return value;
}
void Set_Compbcd_float(void)//把设置比较数据转换为float数据  把这个数据与标称值进行运算，得到
	//可以直接比较的值  这个分为2种，一种是ABS一种是%
{
	uint8_t i;
	float value;
	for(i=0;i<9;i++)
	{
		Comp_Testvalue.comp_highvalue[i]=Inttofloat( &SaveData.Limit_Tab.Comp_Value[i].high);
		Comp_Testvalue.comp_lowvalue[i]=Inttofloat( &SaveData.Limit_Tab.Comp_Value[i].low);
	}
	Comp_Testvalue.comp_highvalue[9]=Inttofloat( &SaveData.Limit_Tab.Comp_Value_2nd.high);
	Comp_Testvalue.comp_lowvalue[9]=Inttofloat( &SaveData.Limit_Tab.Comp_Value_2nd.low);
	value=Inttofloat(&SaveData.Limit_Tab.Nom);
	if(SaveData.Limit_Tab.Mode)//百分比比较
	{
		for(i=0;i<9;i++)
		{
			Comp_Testvalue.comp_highvalue[i]=(100000+Comp_Testvalue.comp_highvalue[i])*value;
			Comp_Testvalue.comp_highvalue[i]/=100000;
			Comp_Testvalue.comp_lowvalue[i]=(100000-Comp_Testvalue.comp_lowvalue[i])*value;
			Comp_Testvalue.comp_lowvalue[i]/=100000;
		}
	}
	else
	{
		for(i=0;i<9;i++)
		{
			Comp_Testvalue.comp_highvalue[i]+=value;
			Comp_Testvalue.comp_lowvalue[i]-=value;
		}
		//Comp_Testvalue.comp_highvalue[9]=
	}//ABS比较
}*/
extern void UARTPuts(LPC_UART_TypeDef *UARTx, const void *str);
extern void Disp_Range_DispMainUnit(uint8_t num,uint8_t unit);
extern void red421(uint8_t k0);
uint8_t rd421(uint8_t adr);
extern void test421(void);

void  Resist_Test(void)
{
	Button_Page_Typedef Button_Page;	
	uint32_t keynum=0;
	uint8_t key,rangr,sped;
	uint8_t Disp_flag=1,Gee,Shi,Bai,Qian,Wan,readf;
//	const uint8_t DISP_UnitMain[]=,wadf
//	{ 0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,3,3,2,2,2};

	Button_Page.index=0;
	Button_Page.page=0;
	Button_Page.third=0;
	Button_Page.force=0;
	Button_Page.five=0;
//	uint8_t str[]="00000";
//	Num_Keyboard();
    Disp_Test();
	Delay_Key();

 	while(GetSystemStatus()==SYS_STATUS_RESIST)//电阻显示
	{ //test421();
red421(0x20);
//else
//	red421(1);
//Disp_Test_Date.Main_RBuff[19]=0xbf;

if(readf==1||readf==127)
{
	UARTPuts( LPC_UART3, Disp_Test_Date.Main_RBuff);
readf++;
}
Colour.black=LCD_COLOR_TEST_BACK;
	//Disp_Test_Date.Main_RBuff[i]	
		LCD_ShowFontCN_40_55(21,140,40,55,(uint8_t*)Out_Assic+5*5*55);//R
		Test_Dispvalue.Main_valuebuff[0]=':';
rangr=Disp_Test_Date.Main_RBuff[5]>>4&0x0f;
readf=rangr;
Wan=Disp_Test_Date.Main_RBuff[5]&0x0f;
		Test_Dispvalue.Main_valuebuff[1]='0'+Wan;
if(readf%3==0)
{
Test_Dispvalue.Main_valuebuff[2]='.';
Qian=(Disp_Test_Date.Main_RBuff[6]>>4);
Qian&=0xf;
		Test_Dispvalue.Main_valuebuff[3]='0'+Qian;
	Bai=Disp_Test_Date.Main_RBuff[6]&0x0f;
	Test_Dispvalue.Main_valuebuff[4]='0'+Bai;
}
if(readf%3==1)
{
Qian=(Disp_Test_Date.Main_RBuff[6]>>4);
Qian&=0xf;
		Test_Dispvalue.Main_valuebuff[2]='0'+Qian;
		Test_Dispvalue.Main_valuebuff[3]='.';
Bai=Disp_Test_Date.Main_RBuff[6]&0x0f;
		Test_Dispvalue.Main_valuebuff[4]='0'+Bai;
}
if(readf%3==2)
{
	Qian=(Disp_Test_Date.Main_RBuff[6]>>4);
Qian&=0xf;
	Test_Dispvalue.Main_valuebuff[2]='0'+Qian;
Bai=Disp_Test_Date.Main_RBuff[6]&0x0f;
		Test_Dispvalue.Main_valuebuff[3]='0'+Bai;
		Test_Dispvalue.Main_valuebuff[4]='.';
}
Shi=(Disp_Test_Date.Main_RBuff[7]>>4);
Shi&=0xf;
		Test_Dispvalue.Main_valuebuff[5]='0'+Shi;

Gee=Disp_Test_Date.Main_RBuff[7]&0x0f;
		Test_Dispvalue.Main_valuebuff[6]='0'+Gee;
		WriteString_Big(61,140 ,Test_Dispvalue.Main_valuebuff);//
//dia
if(rangr>8)
	LCD_ShowFontCN_40_55(285,190,40,55,(uint8_t*)Out_Assic+13*5*55);//M
		else if(rangr>5)
			LCD_ShowFontCN_40_55(285,140,40,55,(uint8_t*)Out_Assic+14*5*55);//k

	else	if(rangr>3)
		LCD_ShowFontCN_40_55(285,140,40,55,(uint8_t*)Out_Assic+22*5*55);//
else
	LCD_ShowFontCN_40_55(285,140,40,55,(uint8_t*)Out_Assic+17*5*55);//m

	LCD_ShowFontCN_40_55(325,140,40,55,(uint8_t*)Out_Assic+20*5*55);//Ω

Test_Dispvalue.Main_valuebuff[1]='0'+readf;
Test_Dispvalue.Main_valuebuff[5]='0'+((rangr>>4)&0x0f);

rangr=rd421(0x40);
Gee=rangr;
Gee>>=4;
Test_Dispvalue.Main_valuebuff[0]='0'+(Gee&0x0f);
Test_Dispvalue.Main_valuebuff[1]='0'+(rangr&0x0f);

rangr=rd421(0x41);
Gee=rangr;
Gee>>=4;
Test_Dispvalue.Main_valuebuff[2]='0'+(Gee&0x0f);
Test_Dispvalue.Main_valuebuff[3]='0'+(rangr&0x0f);

sped=rd421(0x42);
Gee=sped;
Gee>>=4;
Test_Dispvalue.Main_valuebuff[4]='0'+(Gee&0xf);
Test_Dispvalue.Main_valuebuff[5]='0'+(sped&0x0f);

rangr=rd421(0x43);
Gee=rangr;
Gee>>=4;
Test_Dispvalue.Main_valuebuff[6]='0'+(Gee&0x0f);
Test_Dispvalue.Main_valuebuff[7]='0'+(rangr&0x0f);

//Test_Dispvalue.Main_valuebuff[6]='0'+(wadf&0x0f);
WriteString_Big(61,199 ,Test_Dispvalue.Main_valuebuff);
		if(Disp_flag==1)
		{
			Disp_Test_Set(&Button_Page);
			Disp_flag=0;
		}
		key=HW_KeyScsn();
		if(key==0xff)
			keynum=0;

		else
			keynum++;
		if(keynum==8)
		{
			BUZZER();
			Disp_flag=1;
			switch(key)
			{
				case KEY_Disp:       SetSystemStatus(SYS_STATUS_RESIST);
				break;
				case KEY_Setup:      SetSystemStatus(SYS_STATUS_SYSTEMSET);
				break;//green led key

				case KEY_UP:
					if(Button_Page.force==0)
					{
						if(Button_Page.index==1)
							Button_Page.index+=3;
						else if(Button_Page.index<4&&Button_Page.index>0)
							Button_Page.index+=4;
						else if(Button_Page.index==4)
							Button_Page.index-=3;
						else if(Button_Page.index>4)
							Button_Page.index-=4;
						else if(Button_Page.index==0)
							Button_Page.index=1;
					 }
					else
					{
						if(Button_Page.five>1)
							Button_Page.five--;									
					}
				break;
				case KEY_Down:
					if(Button_Page.force==0)
					{							
					   if(Button_Page.index==1)
							Button_Page.index+=3;
						else if(Button_Page.index<4&&Button_Page.index>0)
							Button_Page.index+=4;
						else if(Button_Page.index==4)
							Button_Page.index-=3;
						else if(Button_Page.index>4)
							Button_Page.index-=4;
						else if(Button_Page.index==0)
							Button_Page.index=1;
					}
					else
					{
						if(Button_Page.five<Button_Page.third)
							Button_Page.five++;												
					}
				break;
				case KEY_Left:					
					if(Button_Page.index>0)
						Button_Page.index--;
					else
						Button_Page.index=7;
					Button_Page.force=0;
					Button_Page.five=0;
					Button_Page.page=0;
				break;
				case KEY_Right:					
					if(Button_Page.index<7)
						Button_Page.index++;
					else
						Button_Page.index=0;
					Button_Page.force=0;
					Button_Page.five=0;
					Button_Page.page=0;
				break;
					
//				case KEY_File:
//					
//				break;
//				case KEY_0ADJ:
//					
//				break;
				
				case KEY_Enter:										
                    if(Button_Page.page==1)
					 switch(Button_Page.index)
					{
//							case 0:

//								break;
							case 1:					//测量显示
								switch(Button_Page.five)
								{
//									case 0:										
//										
//									break;
//									case 1:
//										
//									break;
									case 2:		SetSystemStatus(SYS_STATUS_COMPARE);
									break;
									case 3:		SetSystemStatus(SYS_STATUS_SHIFT);
									break;
									case 4:		SetSystemStatus(SYS_STATUS_SHIFTSET);
									break;
									case 5:		SetSystemStatus(SYS_STATUS_SYSTEMSET);
									break;
									default :
									break;
								}							
								break;
							case 2:		//文件
								switch(Button_Page.five)
								{
//									case 0:										
//										
//									break;
//									case 1:
//										
//									break;
//									case 2:
//										
//									break;
									case 3:
										if(Disp_Set_Resist.File==0)
											Disp_Set_Resist.File=1;
										else
											Disp_Set_Resist.File=0;
									break;									
									default :
									break;
								}
								break;
							
							case 3:		//工具
								switch(Button_Page.five)
								{
//									case 0:	
//									break;
									case 1:
										if(Disp_Set_Resist.Tool==0)
											Disp_Set_Resist.Tool=1;
										else
											Disp_Set_Resist.Tool=0;
									break;
//									case 2:

//									break;
//									default :
//									break;
								}							
								break;
							case 4:		//参数
								switch(Button_Page.five)
								{
//									case 0:	
//									break;
									case 1:				Disp_Set_Resist.Parameter=0;	
									break;
									case 2:				Disp_Set_Resist.Parameter=1;
									break;
									default :
									break;
								
								}																					
							break ;
							
							case 5:		//量程
								switch(Button_Page.five)
								{
//									case 0:										
//										
//									break;
									case 1:
										Disp_Set_Resist.Rang=0;
									break;
									case 2:
										if(Disp_Set_Resist.Parameter==1&&Disp_Set_Resist.Rang==0)
											Disp_Set_Resist.Rang=3;
										else if(Disp_Set_Resist.Parameter==0&&Disp_Set_Resist.Rang==0)
											Disp_Set_Resist.Rang=2;
									break;
									case 3:
										if(Disp_Set_Resist.Parameter==0&&Disp_Set_Resist.Rang>2)
											Disp_Set_Resist.Rang--;
										else if(Disp_Set_Resist.Parameter==0&&Disp_Set_Resist.Rang==0)
											Disp_Set_Resist.Rang=2;
										else if(Disp_Set_Resist.Parameter==1&&Disp_Set_Resist.Rang>3)
											Disp_Set_Resist.Rang--;
										else if(Disp_Set_Resist.Parameter==1&&Disp_Set_Resist.Rang==0)
											Disp_Set_Resist.Rang=3;
								
									break;
									case 4:
										if(Disp_Set_Resist.Parameter==0&&Disp_Set_Resist.Rang<10&&Disp_Set_Resist.Rang>1)
											Disp_Set_Resist.Rang++;
										else if(Disp_Set_Resist.Parameter==0&&Disp_Set_Resist.Rang==0)
											Disp_Set_Resist.Rang=2;
										else if(Disp_Set_Resist.Parameter==1&&Disp_Set_Resist.Rang<8&&Disp_Set_Resist.Rang>2)
											Disp_Set_Resist.Rang++;
										else if(Disp_Set_Resist.Parameter==1&&Disp_Set_Resist.Rang==0)
											Disp_Set_Resist.Rang=3;
									break;									
									default :
									break;
								}
								break;
							case 6:		//速度
								switch(Button_Page.five)
								{
//									case 0:										
//										
//									break;
									case 1:			Disp_Set_Resist.Speed=0;//fast
									break;
									case 2:			Disp_Set_Resist.Speed=1;//med
									break;
									case 3:			Disp_Set_Resist.Speed=2;//low
									break;
									case 4:
//										Disp_Set_Resist.Speed=3;
									break;									
									default :
									break;
								}
								break;
							case 7:		//触发
								switch(Button_Page.five)
								{
//									case 0:										
//										
//									break;
									case 1:			Disp_Set_Resist.Trigger=0;
									break;
									case 2:			Disp_Set_Resist.Trigger=1;
									break;
									case 3:			Disp_Set_Resist.Trigger=2;
									break;
									case 4:			Disp_Set_Resist.Trigger=3;
									break;									
									default :
									break;
								}	
							break;				
							default:
							break;
					}	
					if(Button_Page.index!=0)
					if(Button_Page.page==0)
					{
						Button_Page.page=1;
						Button_Page.force=1;
						Button_Page.five=1;
						switch(Button_Page.index)
						{
//							case 0:
//								
//							break;
							case 1:				Button_Page.third=5;
							break;
							case 2:				Button_Page.third=3;
							break;
							case 3:				Button_Page.third=2;
							break;
							case 4:				Button_Page.third=2;
							break;							
							case 5:				Button_Page.third=4;
							break;
							case 6:				Button_Page.third=3;
							break;
							case 7:				Button_Page.third=4;
							break;
							default :							
							break;
						}
				    }	
				break;
//				case KEY_Trig:
//					
//				break;		
				default:					
				break;
			}			
		}
	}
}


//比较测试
void  Compare_Process(void)
{
	Button_Page_Typedef Button_Page;	
	uint32_t keynum=0;
	uint8_t key;
	uint8_t Disp_flag=1;
	Button_Page.index=0;
	Button_Page.page=0;
	Button_Page.third=0;
	Button_Page.force=0;
	Button_Page.five=0;
    Disp_Compare();
	Delay_Key();
 	while(GetSystemStatus()==SYS_STATUS_COMPARE)
	{
		if(Disp_flag==1)		
		{
			Disp_Compare_Set(&Button_Page);			
			Disp_flag=0;	
		}
			
		key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==8)
		{
			BUZZER();
			Disp_flag=1;
			switch(key)				
			{  
				case KEY_Disp:	SetSystemStatus(SYS_STATUS_RESIST);
				break;
				case KEY_Setup:	SetSystemStatus(SYS_STATUS_SYSTEMSET);
				break;
	
				case KEY_UP:
					if(Button_Page.force==0)
					{
						if(Button_Page.index==1)							Button_Page.index+=3;
						else if(Button_Page.index<4&&Button_Page.index>0)
							Button_Page.index+=4;
						else if(Button_Page.index==4)
							Button_Page.index-=3;
						else if(Button_Page.index>4)
							Button_Page.index-=4;
						else if(Button_Page.index==0)
							Button_Page.index=1;
					 }
					else
					{
						if(Button_Page.five>1)							Button_Page.five--;									
					}
				break;
				case KEY_Down:
					if(Button_Page.force==0)
					{							
					   if(Button_Page.index==1)							Button_Page.index+=3;
						else if(Button_Page.index<4&&Button_Page.index>0)
							Button_Page.index+=4;
						else if(Button_Page.index==4)
							Button_Page.index-=3;
						else if(Button_Page.index>4)
							Button_Page.index-=4;
						else if(Button_Page.index==0)
							Button_Page.index=1;
					}
					else
					{
						if(Button_Page.five<Button_Page.third)
							Button_Page.five++;												
					}
				break;
				case KEY_Left:					
					if(Button_Page.index>0)						Button_Page.index--;
					else
						Button_Page.index=7;
					Button_Page.force=0;
					Button_Page.five=0;
					Button_Page.page=0;
				break;
				case KEY_Right:					
					if(Button_Page.index<7)						Button_Page.index++;
					else
						Button_Page.index=0;
					Button_Page.force=0;
					Button_Page.five=0;
					Button_Page.page=0;
				break;
					
//				case KEY_File:
//					
//				break;
//				case KEY_0ADJ:
//					
//				break;
				case KEY_Enter:											
                    if(Button_Page.page==1)
					 switch(Button_Page.index)
						{
//							case 0:

//								break;
							case 1:					//比较显示								
								switch(Button_Page.five)
								{
//									case 0:										
//										
//									break;
									case 1:					SetSystemStatus(SYS_STATUS_RESIST);
									break;
//									case 2:
//										
//									break;
									case 3:					SetSystemStatus(SYS_STATUS_SHIFT);
									break;
									case 4:					SetSystemStatus(SYS_STATUS_SHIFTSET);
									break;
									case 5:					SetSystemStatus(SYS_STATUS_SYSTEMSET);
									break;
									default :
									break;
								}							
								break;
							case 2:		//文件								
								switch(Button_Page.five)
								{
//									case 0:										
//										
//									break;
//									case 1:
//										
//									break;
//									case 2:
//										
//									break;
									case 3:
										if(Disp_CompareMenu.File==0)					Disp_CompareMenu.File=1;
										else
											Disp_CompareMenu.File=0;
									break;									
									default :
									break;
								}
								break;
							case 3:		//工具								
								switch(Button_Page.five)
								{
//									case 0:	
//									break;
									case 1:
										if(Disp_CompareMenu.Compare_Tool.Display==0)
											Disp_CompareMenu.Compare_Tool.Display=1;
										else
											Disp_CompareMenu.Compare_Tool.Display=0;
									break;
									case 2:
										if(Disp_CompareMenu.Compare_Tool.Ring<2)
											Disp_CompareMenu.Compare_Tool.Ring++;
										else 
											Disp_CompareMenu.Compare_Tool.Ring=0;
									break;
									case 3:
										if(Disp_CompareMenu.Compare_Tool.Count==0)
											Disp_CompareMenu.Compare_Tool.Count=1;
										else
											Disp_CompareMenu.Compare_Tool.Count=0;
									break;
//									case 4:
//									
//									break;
									case 5:
										if(Disp_CompareMenu.Compare_Tool.Mode==0)
											Disp_CompareMenu.Compare_Tool.Mode=1;
										else
											Disp_CompareMenu.Compare_Tool.Mode=0;
									break;
									default :
									break;
								}							
								break;
							case 4:		//比较							
								switch(Button_Page.five)
								{
									case 0:	
									break;
									case 1:					Disp_CompareMenu.Comp=0;	
									break;
									case 2:					Disp_CompareMenu.Comp=1;
									break;
									default :
									break;
								}																					
							break ;
							
							case 5:		//比较模式								
								switch(Button_Page.five)
								{
									case 0:										
										
									break;
									case 1:					Disp_CompareMenu.Compar_Mode=0;
									break;
									case 2:					Disp_CompareMenu.Compar_Mode=1;
									break;																		
									default :
									break;
								}
								break;
//							case 6:		//上限								
//																	
//								break;
//							case 7:		//下限							
//																
//								break;				
							default:
								break;
						}
						if(Button_Page.index!=0)
						if(Button_Page.page==0)
						{
							Button_Page.page=1;
							Button_Page.force=1;
							Button_Page.five=1;
							switch(Button_Page.index)
							{
								case 0:
									
								break;
								case 1:						Button_Page.third=5;
								break;
								case 2:						Button_Page.third=3;
								break;
								case 3:						Button_Page.third=5;
								break;
								case 4:						Button_Page.third=2;
								break;							
								case 5:						Button_Page.third=2;
								break;
								case 6:
									Button_Page.third=0;							
									Button_Page.force=0;
									Button_Page.page=0;
									Disp_CompareMenu.Toplimt=Num_KeyBoard_Input(&Button_Page);
									Button_Page.five=0;	
									Button_Page.page=0;
								break;
								case 7:						
									Button_Page.third=0;
									Button_Page.force=0;
									Button_Page.page=0;
									Disp_CompareMenu.Lowlimt=Num_KeyBoard_Input(&Button_Page);	
									Button_Page.five=0;
									Button_Page.page=0;
								break;
								default :							
								break;
							}
						}
				break;
				case KEY_Trig:
					
				break;		
				default:					
				break;	
			}
		}
	}
}

//档测试界面
void  Shfit_Test(void)
{
	Button_Page_Typedef Button_Page;	
	uint32_t keynum=0;
	uint8_t key;
	uint8_t Disp_flag=1;
	Button_Page.index=0;
	Button_Page.page=0;
	Button_Page.third=0;
	Button_Page.force=0;
	Button_Page.five=0;
    Disp_Shift();
	Delay_Key();
 	while(GetSystemStatus()==SYS_STATUS_SHIFT)
	{
		if(Disp_flag==1)
		{
			Disp_Shift_Set(&Button_Page);		
			Disp_flag=0;	
		}
			
		key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==8)
		{
			BUZZER();
			Disp_flag=1;
			switch(key)				
			{  
				case KEY_Disp:	    SetSystemStatus(SYS_STATUS_RESIST);
				break;
				case KEY_Setup:	    SetSystemStatus(SYS_STATUS_SYSTEMSET);
				break;
	
				case KEY_UP:
					if(Button_Page.force==0)
					{
						if(Button_Page.index==1)
							Button_Page.index+=3;
						else if(Button_Page.index<4&&Button_Page.index>0)
							Button_Page.index+=4;
						else if(Button_Page.index==4)
							Button_Page.index-=3;
						else if(Button_Page.index==5)
							Button_Page.index-=4;
						else if(Button_Page.index==0)
							Button_Page.index=1;
					 }
					else
					{
						if(Button_Page.five>1)
							Button_Page.five--;									
					}
				break;
				case KEY_Down:
					if(Button_Page.force==0)
					{							
					    if(Button_Page.index==1)
							Button_Page.index+=3;
						else if(Button_Page.index<4&&Button_Page.index>0)
							Button_Page.index=Button_Page.index;
						else if(Button_Page.index==4)
							Button_Page.index-=3;
						else if(Button_Page.index==5)
							Button_Page.index-=4;
						else if(Button_Page.index==0)
							Button_Page.index=1;
					}
					else
					{
						if(Button_Page.five<Button_Page.third)
							Button_Page.five++;												
					}
				break;
				case KEY_Left:					
					if(Button_Page.index>0)					Button_Page.index--;
					else
						Button_Page.index=5;
					Button_Page.force=0;
					Button_Page.five=0;
					Button_Page.page=0;
				break;
				case KEY_Right:					
					if(Button_Page.index<5)					Button_Page.index++;
					else
						Button_Page.index=0;
					Button_Page.force=0;
					Button_Page.five=0;
					Button_Page.page=0;
				break;
					
				case KEY_File:
					
				break;
				case KEY_0ADJ:
					
				break;

				case KEY_Enter:															
                    if(Button_Page.page==1)
					 switch(Button_Page.index)
						{
							case 0:

								break;
							case 1:					//档显示							
								switch(Button_Page.five)
								{
									case 0:										
										
									break;
									case 1:						SetSystemStatus(SYS_STATUS_RESIST);
									break;
									case 2:						SetSystemStatus(SYS_STATUS_COMPARE);
									break;
									case 3:
										
									break;
									case 4:						SetSystemStatus(SYS_STATUS_SHIFTSET);
									break;
									case 5:						SetSystemStatus(SYS_STATUS_SYSTEMSET);
									break;
									default :
									break;
								}
								break;
							case 2:		//文件								
								switch(Button_Page.five)
								{
									case 0:										
										
									break;
									case 1:
										
									break;
									case 2:
										
									break;
									case 3:
										if(Disp_Set_Shift.File==0)					Disp_Set_Shift.File=1;
										else
											Disp_Set_Shift.File=0;
									break;									
									default :
									break;
								}
								break;
							
							case 3:		//工具								
								switch(Button_Page.five)
								{
									case 0:	
									break;
									case 1:
										if(Disp_Set_Shift.Tool==0)					Disp_Set_Shift.Tool=1;
										else
											Disp_Set_Shift.Tool=0;
									break;									
									default :
									break;
								}							
								break;
							case 4:		//档								
								switch(Button_Page.five)
								{
									case 0:	
									break;
									case 1:										Disp_Set_Shift.Shift=0;	
									break;
									case 2:										Disp_Set_Shift.Shift=1;
									break;
									default :
									break;

								}																					
							break ;

							case 5:		//档讯响								
								switch(Button_Page.five)
								{
									case 0:										
										
									break;
									case 1:										Disp_Set_Shift.Shfit_Bell=0;
									break;
									case 2:										Disp_Set_Shift.Shfit_Bell=1;
									break;
									case 3:										Disp_Set_Shift.Shfit_Bell=2;
									break ;
									default :
									break;
								}
								break;
							case 6:		//
								switch(Button_Page.five)
								{
									case 0:										
										
									break;																
									default :
									break;
								}
								break;
							case 7:		//
								switch(Button_Page.five)
								{
									case 0:										
										
									break;																	
									default :
									break;
								}
								break;				
							default:
								break;
						
					}
					if(Button_Page.index!=0)
					if(Button_Page.page==0)
					{
						Button_Page.page=1;
						Button_Page.force=1;
						Button_Page.five=1;
						switch(Button_Page.index)
						{
							case 0:
								
							break;
							case 1:								Button_Page.third=5;
							break;
							case 2:								Button_Page.third=3;
							break;
							case 3:								Button_Page.third=1;
							break;
							case 4:								Button_Page.third=2;
							break;							
							case 5:								Button_Page.third=3;
							break;							
							default :							
							break;
						}
				    }	
				break;
				case KEY_Trig:
					
				break;		
				default:					
				break;
			}
		}
	}
}

//档设置测试界面
void  ShfitSet_Test(void)
{
	Button_Page_Typedef Button_Page;	
	uint32_t keynum=0;
	uint8_t key;
	uint8_t Disp_flag=1;
	Button_Page.index=0;
	Button_Page.page=0;
	Button_Page.third=0;
	Button_Page.force=0;
	Button_Page.five=0;
    Disp_ShiftSet();
	Delay_Key();
 	while(GetSystemStatus()==SYS_STATUS_SHIFTSET)
	{
		if(Disp_flag==1)
		{
			Disp_ShiftSet_Set(&Button_Page);			
			Disp_flag=0;	
		}
			
		key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==8)
		{
			BUZZER();
			Disp_flag=1;
			switch(key)				
			{  
				case KEY_Disp:              SetSystemStatus(SYS_STATUS_RESIST);
				break;
				case KEY_Setup:             SetSystemStatus(SYS_STATUS_SYSTEMSET);
				break;
	
				case KEY_UP:
					if(Button_Page.force==0)
					{
						if(Button_Page.index==1)							Button_Page.index+=11;
						else if(Button_Page.index<4&&Button_Page.index>1)
							Button_Page.index+=12;
						else if(Button_Page.index==4)
							Button_Page.index-=3;
						else if(Button_Page.index==0)
							Button_Page.index=1;
						else
							Button_Page.index-=4;
					 }
					else
					{
						if(Button_Page.five>1)
							Button_Page.five--;									
					}
				break;
				case KEY_Down:
					if(Button_Page.force==0)
					{							
					     if(Button_Page.index==1)							Button_Page.index+=3;
						else if(Button_Page.index<12&&Button_Page.index>0)
							Button_Page.index+=4;
						else if(Button_Page.index==12)
							Button_Page.index-=11;						
						else if(Button_Page.index==0)
							Button_Page.index=1;
						else 
							Button_Page.index-=12;
					}
					else
					{
						if(Button_Page.five<Button_Page.third)
							Button_Page.five++;												
					}
				break;
				case KEY_Left:					
					if(Button_Page.index>0)
						Button_Page.index--;
					else
						Button_Page.index=15;
					Button_Page.force=0;
					Button_Page.five=0;
					Button_Page.page=0;
				break;
				case KEY_Right:					
					if(Button_Page.index<15)
						Button_Page.index++;
					else
						Button_Page.index=0;
					Button_Page.force=0;
					Button_Page.five=0;
					Button_Page.page=0;
				break;
					
				case KEY_File:
					
				break;
				case KEY_0ADJ:
					
				break;
				
				case KEY_Enter:															
                    if(Button_Page.page==1)
					 switch(Button_Page.index)
						{
							case 0:

								break;
							case 1:					//档显示								
								switch(Button_Page.five)
								{
									case 0:										
										
									break;
									case 1:										SetSystemStatus(SYS_STATUS_RESIST);
									break;
									case 2:										SetSystemStatus(SYS_STATUS_COMPARE);
									break;
									case 3:										SetSystemStatus(SYS_STATUS_SHIFT);
									break;
									case 4:
										
									break;
									case 5:										SetSystemStatus(SYS_STATUS_SYSTEMSET);
									break;
									default :
									break;
								}							
								break;
							case 2:		//文件								
								switch(Button_Page.five)
								{
									case 0:										
										
									break;
									case 1:
										
									break;
									case 2:
										
									break;																	
									default :
									break;
								}
								break;

							case 3:		//工具							
								switch(Button_Page.five)
								{
									case 0:	
									break;
									case 1:
										if(Disp_Set_ShiftSet.Tool.Shift_Mode==0)
											Disp_Set_ShiftSet.Tool.Shift_Mode=1;
										else
											Disp_Set_ShiftSet.Tool.Shift_Mode=0;
									break;
									case 2:
										if(Disp_Set_ShiftSet.Tool.Shift_Ring<2)
											Disp_Set_ShiftSet.Tool.Shift_Ring++;
										else
											Disp_Set_ShiftSet.Tool.Shift_Ring=0;
									break;
									case 3:
										
									break;
									default :
									break;
								}							
								break;
							case 4:		//档1								
								switch(Button_Page.five)
								{
									case 0:	
									break;
									case 1:
										
									break;								
									default :
									break;
								}																					
							break ;
							case 5:		//状态1								
								switch(Button_Page.five)
								{
									case 0:										
										
									break;
									case 1:										Disp_Set_ShiftSet.State.First=0;
									break;
									case 2:										Disp_Set_ShiftSet.State.First=1;
									break;									
									default :
									break;
								}	
								break;
							case 6:		// 上限1								
								switch(Button_Page.five)
								{
									case 0:										
										
									break;																
									default :
									break;
								}	
								break;
							case 7:		//								
								switch(Button_Page.five)
								{
									case 0:										
										
									break;																	
									default :
									break;
								}	
								break;	
							case 8:		//档2								
								switch(Button_Page.five)
								{
									case 0:	
									break;
									case 1:
										
									break;								
									default :
									break;
								}
								break ;
							case 9:		//状态2								
								switch(Button_Page.five)
								{
									case 0:										
										
									break;
									case 1:										Disp_Set_ShiftSet.State.Second=0;
									break;
									case 2:										Disp_Set_ShiftSet.State.Second=1;
									break;									
									default :
									break;
								}
								break;
							case 10:								
								switch(Button_Page.five)
								{
									case 0:										
										
									break;																
									default :
									break;
								}	
								break ;
							case 11:
								switch(Button_Page.five)
								{
									case 0:										
										
									break;																
									default :
									break;
								}	
								break;
							case 12:	//档3							
								switch(Button_Page.five)
								{
									case 0:	
									break;
									case 1:
										
									break;								
									default :
									break;
								}
								break ;
							case 13:	//状态3								
								switch(Button_Page.five)
								{
									case 0:										
										
									break;
									case 1:										Disp_Set_ShiftSet.State.Third=0;
									break;
									case 2:										Disp_Set_ShiftSet.State.Third=1;
									break;									
									default :
									break;
								}
								break;
							case 14:								
								switch(Button_Page.five)
								{
									case 0:										
										
									break;																
									default :
									break;
								
								}	
								break ;
							case 15:							
								switch(Button_Page.five)
								{
									case 0:										
										
									break;																
									default :
									break;
								
								}	
								break;	
							default:
								break;
						
					}
					if(Button_Page.index!=0)
					if(Button_Page.page==0)
					{
						Button_Page.page=1;
						Button_Page.force=1;
						Button_Page.five=1;
						switch(Button_Page.index)
						{
							case 0:
								
							break;
							case 1:								Button_Page.third=5;
							break;
							case 2:								Button_Page.third=2;
							break;
							case 3:								Button_Page.third=3;
							break;
							case 4:								Button_Page.third=1;
							break;							
							case 5:								Button_Page.third=2;
							break;
							case 6:
								Button_Page.third=0;							
								Button_Page.force=0;
								Button_Page.page=0;
//								Disp_Set_ShiftSet.UpLimit.First=ShiftSet_KeyBoard_Input(&Button_Page);
								Button_Page.five=0;	
								Button_Page.page=0;
							break;
							case 7:
								Button_Page.third=0;							
								Button_Page.force=0;
								Button_Page.page=0;
//								Disp_Set_ShiftSet.LowLimit.First=ShiftSet_KeyBoard_Input(&Button_Page);
								Button_Page.five=0;	
								Button_Page.page=0;
							break;
							case 8:								Button_Page.third=1;
							break;
							case 9:								Button_Page.third=2;
							break;
							case 10:
								Button_Page.third=0;
								Button_Page.page=0;
								Button_Page.force=0;
								Button_Page.five=0;
							break;
							case 11:
								Button_Page.third=0;
								Button_Page.page=0;
								Button_Page.force=0;
								Button_Page.five=0;
							break;
							case 12:								Button_Page.third=1;
							break;
							case 13:								Button_Page.third=2;
							break;
							case 14:
								Button_Page.third=0;
								Button_Page.page=0;
								Button_Page.force=0;
								Button_Page.five=0;
							break;
							case 15:
								Button_Page.third=0;
								Button_Page.page=0;
								Button_Page.force=0;
								Button_Page.five=0;
							break;							
							default :							
							break;
						}
				    }		
				break;
				case KEY_Trig:
					
				break;		
				default:					
				break;	
			}
		}
	}
}


//系统测试界面
void  SysSet_Process(void)
{
	Button_Page_Typedef Button_Page;	
	uint32_t keynum=0;
	uint8_t key;
	uint8_t Disp_flag=1;
	Button_Page.index=0;
	Button_Page.page=0;
	Button_Page.third=0;
	Button_Page.force=0;
	Button_Page.five=0;
    Disp_System();
	Delay_Key();
 	while(GetSystemStatus()==SYS_STATUS_SYSTEMSET)
	{
		if(Disp_flag==1)
		{
			Disp_SysSet_Set(&Button_Page);		
			Disp_flag=0;	
		}
			
		key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==8)
		{
			BUZZER();
			Disp_flag=1;
			switch(key)				
			{  
				case KEY_Disp:           SetSystemStatus(SYS_STATUS_RESIST);
				break;
				case KEY_Setup:          SetSystemStatus(SYS_STATUS_SYSTEMSET);
				break;
	
				case KEY_UP:
					if(Button_Page.force==0)
					{
						if(Button_Page.index==1)							Button_Page.index+=3;
						else if(Button_Page.index==4)
							Button_Page.index-=3;
						else if(Button_Page.index==0)
							Button_Page.index=1;
					 }
					else
					{
						if(Button_Page.five>1)
							Button_Page.five--;									
					}
				break;
				case KEY_Down:
					if(Button_Page.force==0)
					{							
					    if(Button_Page.index==1)						Button_Page.index+=3;
						else if(Button_Page.index==4)
							Button_Page.index-=3;
						else if(Button_Page.index==0)
							Button_Page.index=1;
					}
					else
					{
						if(Button_Page.five<Button_Page.third)							Button_Page.five++;												
					}
				break;
				case KEY_Left:					
					if(Button_Page.index>0)						Button_Page.index--;
					else
						Button_Page.index=4;
					Button_Page.force=0;
					Button_Page.five=0;
					Button_Page.page=0;
				break;
				case KEY_Right:					
					if(Button_Page.index<4)						Button_Page.index++;
					else
						Button_Page.index=0;
					Button_Page.force=0;
					Button_Page.five=0;
					Button_Page.page=0;
				break;
					
				case KEY_File:
					
				break;
				case KEY_0ADJ:
					
				break;
				
				case KEY_Enter:										
                    if(Button_Page.page==1)
					 switch(Button_Page.index)
						{
							case 0:

								break;
							case 1:					//系统设置								
								switch(Button_Page.five)
								{
									case 0:										
										
									break;
									case 1:										SetSystemStatus(SYS_STATUS_RESIST);
									break;
									case 2:										SetSystemStatus(SYS_STATUS_COMPARE);
									break;
									case 3:										SetSystemStatus(SYS_STATUS_SHIFT);
									break;
									case 4:										SetSystemStatus(SYS_STATUS_SHIFTSET);
									break;
									case 5:
										
									break;
									default :
									break;
								
								}							
								break;
							case 2:		//文件								
								switch(Button_Page.five)
								{
									case 0:										
										
									break;
									case 1:
										
									break;
									case 2:
										
									break;																	
									default :
									break;
								}
								break;
							
							case 3:		//工具								
								switch(Button_Page.five)
								{
									case 0:	
									break;
									case 1:
									
									break;									
									default :
									break;
								}							
								break;
							case 4:		//波特率								
								switch(Button_Page.five)
								{
									case 0:	
									break;
									case 1:										Disp_Set_SysSet.Baud=0;	
									break;
									case 2:										Disp_Set_SysSet.Baud=1;
									break;
									case 3:										Disp_Set_SysSet.Baud=2;
									break;
									case 4:										Disp_Set_SysSet.Baud=3;
									break;
									case 5:										Disp_Set_SysSet.Baud=4;
									break;
									case 6:										Disp_Set_SysSet.Baud=5;
									break;
								
									default :
									break;
								}																					
							break ;								
							default:
								break;
					}
					if(Button_Page.index!=0)
					if(Button_Page.page==0)
					{
						Button_Page.page=1;
						Button_Page.force=1;
						Button_Page.five=1;
						switch(Button_Page.index)
						{
							case 0:

							break;
							case 1:								Button_Page.third=5;
							break;
							case 2:								Button_Page.third=2;
							break;
							case 3:
								Button_Page.third=0;
								Button_Page.page=0;
								Button_Page.force=0;
								Button_Page.five=0;
							break;
							case 4:								Button_Page.third=6;
							break;							
													
							default :							
							break;
						}
				    }		
				break;
				case KEY_Trig:
					
				break;		
				default:					
				break;
			}
		}
	}
}


//上下限修改时 根据值的判断来修改
Sort_TypeDef Judge_UpOrLow_limit(Sort_TypeDef* Sort_num1,Button_Page_Typedef* Button_Page)
{
	uint32_t value;
	
	if(Sort_num1->Updata_flag==1)//设置的上限值要大于下限值
	{		
			if(Button_Page->index==6)			//上限
			{
				if(Sort_num1->Unit<Disp_CompareMenu.Lowlimt.Unit)
				{
					Sort_num1->Dot=Disp_CompareMenu.Toplimt.Dot;
					Sort_num1->Num=Disp_CompareMenu.Toplimt.Num;
					Sort_num1->Unit=Disp_CompareMenu.Toplimt.Unit;				
				}
				else if(Sort_num1->Unit==Disp_CompareMenu.Lowlimt.Unit&&
				Sort_num1->Num<Disp_CompareMenu.Lowlimt.Num)
				{
					Sort_num1->Dot=Disp_CompareMenu.Toplimt.Dot;
					Sort_num1->Num=Disp_CompareMenu.Toplimt.Num;
					Sort_num1->Unit=Disp_CompareMenu.Toplimt.Unit;
				}
				else if(Sort_num1->Unit==Disp_CompareMenu.Lowlimt.Unit&&
				Sort_num1->Num<Disp_CompareMenu.Lowlimt.Num&&Sort_num1->Dot>Disp_CompareMenu.Lowlimt.Dot)
				{
					Sort_num1->Dot=Disp_CompareMenu.Toplimt.Dot;
					Sort_num1->Num=Disp_CompareMenu.Toplimt.Num;
					Sort_num1->Unit=Disp_CompareMenu.Toplimt.Unit;				
				}
				else if(Sort_num1->Unit==Disp_CompareMenu.Lowlimt.Unit&&
					Sort_num1->Num>Disp_CompareMenu.Lowlimt.Num&&Sort_num1->Dot>Disp_CompareMenu.Lowlimt.Dot)
				{
					Sort_num1->Dot=Disp_CompareMenu.Toplimt.Dot;
					Sort_num1->Num=Disp_CompareMenu.Toplimt.Num;
					Sort_num1->Unit=Disp_CompareMenu.Toplimt.Unit;				
				}
				else if(Sort_num1->Unit==4)				//单位是M的时候限制值的大小小于9
				{
					value=pow(10.0,(float)Sort_num1->Dot);
					value=Sort_num1->Num/value;
					if(value>3)
					{
						Sort_num1->Dot=Disp_CompareMenu.Toplimt.Dot;
						Sort_num1->Num=Disp_CompareMenu.Toplimt.Num;
						Sort_num1->Unit=Disp_CompareMenu.Toplimt.Unit;	
					}				
				}
			}
		   else if(Button_Page->index==7)	//下限
		   {
				if(Sort_num1->Unit>Disp_CompareMenu.Toplimt.Unit)
				{
					Sort_num1->Dot=Disp_CompareMenu.Lowlimt.Dot;
					Sort_num1->Num=Disp_CompareMenu.Lowlimt.Num;
					Sort_num1->Unit=Disp_CompareMenu.Lowlimt.Unit;				
				}	
				else if(Sort_num1->Unit==Disp_CompareMenu.Toplimt.Unit&&
					Sort_num1->Num>Disp_CompareMenu.Toplimt.Num)
				{
					Sort_num1->Dot=Disp_CompareMenu.Lowlimt.Dot;
					Sort_num1->Num=Disp_CompareMenu.Lowlimt.Num;
					Sort_num1->Unit=Disp_CompareMenu.Lowlimt.Unit;
				}
				else if(Sort_num1->Unit==Disp_CompareMenu.Toplimt.Unit&&
					Sort_num1->Num>Disp_CompareMenu.Toplimt.Num&&Sort_num1->Dot<Disp_CompareMenu.Toplimt.Dot)
				{
					Sort_num1->Dot=Disp_CompareMenu.Lowlimt.Dot;
					Sort_num1->Num=Disp_CompareMenu.Lowlimt.Num;
					Sort_num1->Unit=Disp_CompareMenu.Lowlimt.Unit;				
				}				
				else if(Sort_num1->Unit==Disp_CompareMenu.Toplimt.Unit&&
					Sort_num1->Num<Disp_CompareMenu.Toplimt.Num&&Sort_num1->Dot<Disp_CompareMenu.Toplimt.Dot)
				{
					Sort_num1->Dot=Disp_CompareMenu.Lowlimt.Dot;
					Sort_num1->Num=Disp_CompareMenu.Lowlimt.Num;
					Sort_num1->Unit=Disp_CompareMenu.Lowlimt.Unit;				
				}	
				else if(Sort_num1->Unit==4)	//单位是M的时候限制值的大小小于9
				{
					value=pow(10.0,(float)Sort_num1->Dot);
					value=Sort_num1->Num/value;
					if(value>3)
					{
						Sort_num1->Dot=Disp_CompareMenu.Lowlimt.Dot;
						Sort_num1->Num=Disp_CompareMenu.Lowlimt.Num;
						Sort_num1->Unit=Disp_CompareMenu.Lowlimt.Unit;
					}
				}
		   }	
	}

	if(Sort_num1->Updata_flag==0)							//没有输入的时候上下限的值不改变
	{
			if(Button_Page->index==6)					//判断是否要改变上下限值
			{
				Sort_num1->Dot=Disp_CompareMenu.Toplimt.Dot;
				Sort_num1->Num=Disp_CompareMenu.Toplimt.Num;
				Sort_num1->Unit=Disp_CompareMenu.Toplimt.Unit;
			}
			else if(Button_Page->index==7)
			{
				Sort_num1->Dot=Disp_CompareMenu.Lowlimt.Dot;
				Sort_num1->Num=Disp_CompareMenu.Lowlimt.Num;
				Sort_num1->Unit=Disp_CompareMenu.Lowlimt.Unit;						
			}
	}
	return *Sort_num1;
}

//比较显示的键盘输入
Sort_TypeDef  Num_KeyBoard_Input(Button_Page_Typedef* Button_Page )
{
	Sort_TypeDef Sort_num1;  //Sort_num,	
	Num_Keyboard(Button_Page);
	Sort_num1=Input_Up_Or_Low_Limit(Button_Page);
	Sort_num1=Input_Set_Cov(&Sort_num1);
	LCD_DrawRect(0, 0, 480,272 , LCD_COLOR_TURQUOISE);

	Sort_num1=Judge_UpOrLow_limit(&Sort_num1,Button_Page);
	return Sort_num1;
}

//档设置的上下限的键盘输入
Sort_TypeDef  ShiftSet_KeyBoard_Input(Button_Page_Typedef* Button_Page )
{

	Sort_TypeDef Sort_num1;  //Sort_num,	
	Num_Keyboard(Button_Page);
	Sort_num1=Input_Up_Or_Low_Limit(Button_Page);
	Sort_num1=Input_Set_Cov(&Sort_num1);
	LCD_DrawRect(0, 0, 480,272 , LCD_COLOR_TURQUOISE);

//	Sort_num1=Judge_UpOrLow_limit(&Sort_num1,Button_Page);
	return Sort_num1;
}

Sort_TypeDef Input_Up_Or_Low_Limit(Button_Page_Typedef* Button_Page)
{
	uint8_t	While_flag=1;
	uint8_t key,i;
	uint8_t Disp_flag=1;
	uint8_t disp_flag=1;
	uint8_t dot_num1;
	uint32_t keynum=0;
	uint8_t Disp_buff[10];
	uint8_t disp_cound=0;
	uint8_t key_count=0;
	float conp_value=0;
	uint32_t Word=0;
	uint8_t dot=6;//小数点
	uint8_t dot_num=0;
	uint8_t del_flag=0;
	Sort_TypeDef   Sort_set;
	
	
	while(While_flag)
	{
		if(Disp_flag==1)
		{
			Disp_Num_Keyboard_Box(Button_Page);
			Disp_flag=0;	
		}
		key=HW_KeyScsn();
		if(key==0xff)
		{
			keynum=0;
		}
		else
			keynum++;
		if(keynum==KEY_NUM)
		{
			disp_flag=1;
			Disp_flag=1;
			switch(key)
			{
				case KEY_Disp:              SetSystemStatus(SYS_STATUS_RESIST);
					Sort_set.Updata_flag=0;
				    While_flag=0;
				break;
				case KEY_Setup:             SetSystemStatus(SYS_STATUS_SYSTEMSET);
					Sort_set.Updata_flag=0;
					While_flag=0;
				break;
				case KEY_UP:
					if(Button_Page->five>0&&Button_Page->five<6)
						Button_Page->five+=15;
					else if(Button_Page->five>5)
						Button_Page->five-=5;
				break;
				case KEY_Down:
					if(Button_Page->five>15)
						Button_Page->five-=15;
					else if(Button_Page->five<16)
						Button_Page->five+=5;
				break;
				case KEY_Left:
					if(Button_Page->five>1)
						Button_Page->five--;
					else
						Button_Page->five=20;
				break;
				case KEY_Right:
					if(Button_Page->five<20)
						Button_Page->five++;
					else
						Button_Page->five=1;
				break;
				case KEY_File:
					
				break;
				case KEY_0ADJ:
					
				break;
				case KEY_Enter:
					if(Button_Page->page==1)
					switch(Button_Page->five)
					{
						case 1:				// 7
							if(key_count<NUM_LENTH)
							{
								Disp_buff[key_count]='7';
								key_count++;
								Word=Disp_buff[disp_cound]-'0';
								conp_value=conp_value*10+Word;						
								disp_cound++;
								if(dot_num==0)
									dot--;
							}
						break;
						case 2:			  // 8
							if(key_count<NUM_LENTH)
							{
								Disp_buff[key_count]='8';
								key_count++;
								Word=Disp_buff[disp_cound]-'0';
								conp_value=conp_value*10+Word;
								disp_cound++;
								if(dot_num==0)
									dot--;
							}
						break;
						case 3:			// 9
							if(key_count<NUM_LENTH)
							{
								Disp_buff[key_count]='9';
								key_count++;
								Word=Disp_buff[disp_cound]-'0';
								conp_value=conp_value*10+Word;
								disp_cound++;
								if(dot_num==0)
									dot--;
							}
						break;
						case 4:			// Esc
							Sort_set.Updata_flag=0;
							While_flag=0;							
						break;
						case 5:			// u
							conp_value*=pow(10,6-(disp_cound-dot_num));						
							Sort_set.Num=conp_value;
							Sort_set.Dot=dot;	
							Sort_set.Unit=1;	
							Sort_set.Updata_flag=1;
							While_flag=0;
						break;
						case 6:			// 4
							if(key_count<NUM_LENTH)
							{
								Disp_buff[key_count]='4';
								key_count++;
								Word=Disp_buff[disp_cound]-'0';
								conp_value=conp_value*10+Word;
								disp_cound++;
								if(dot_num==0)
									dot--;
							}
						break;
						case 7:			//5
							if(key_count<NUM_LENTH)
							{
								Disp_buff[key_count]='5';
								key_count++;
								Word=Disp_buff[disp_cound]-'0';
								conp_value=conp_value*10+Word;
								disp_cound++;
								if(dot_num==0)
									dot--;
							}
						break;
						case 8:			// 6
							if(key_count<NUM_LENTH)
							{
								Disp_buff[key_count]='6';                  
								key_count++;
								Word=Disp_buff[disp_cound]-'0';
								conp_value=conp_value*10+Word;
								disp_cound++;
								if(dot_num==0)
									dot--;
							}
						break;
						case 9:		  // Backspace
							if(key_count>0)
							{	
								disp_cound--;
								Word=Disp_buff[disp_cound]-'0';
								conp_value=(conp_value-Word)/10;
								key_count--;								
								Disp_buff[key_count]=' ';	
								dot++;
								if(dot_num1==key_count)
								{
									dot_num=0;
									dot_num1=0;
								}
								del_flag=1;							
							}
						break;
						case 10:	 // m
							conp_value*=pow(10,6-(disp_cound-dot_num));						
							Sort_set.Num=conp_value;
							Sort_set.Dot=dot;	
							Sort_set.Unit=2;
							Sort_set.Updata_flag=1;
							While_flag=0;
						break;
						case 11:	 // 1
							if(key_count<NUM_LENTH)
							{
								Disp_buff[key_count]='1';
								key_count++;
								Word=Disp_buff[disp_cound]-'0';
								conp_value=conp_value*10+Word;
								disp_cound++;
								if(dot_num==0)
									dot--;
							}
						break;
						case 12:	 // 2
							if(key_count<NUM_LENTH)
							{
								Disp_buff[key_count]='2';
								key_count++;
								Word=Disp_buff[disp_cound]-'0';
								conp_value=conp_value*10+Word;
								disp_cound++;
								if(dot_num==0)
									dot--;
							}
						break;
						case 13:	// 3
							if(key_count<NUM_LENTH)
							{
								Disp_buff[key_count]='3';
								key_count++;
								Word=Disp_buff[disp_cound]-'0';
								conp_value=conp_value*10+Word;
								disp_cound++;
								if(dot_num==0)
									dot--;							
							}
						break;
						case 14:	// Clear
							if(key_count>0)
							{
								del_flag=key_count;																	
								for(i=0;i<key_count;i++)
									Disp_buff[i]=' ';
								dot_num=0;
								dot_num1=0;
								disp_cound=0;
								key_count=0;
								conp_value=0;
								dot=6;															
							}
						break;
						case 15:	//K
							conp_value*=pow(10,6-(disp_cound-dot_num));						
							Sort_set.Num=conp_value;
							Sort_set.Dot=dot;	
							Sort_set.Unit=3;
							Sort_set.Updata_flag=1;
							While_flag=0;
						break;
						case 16:	// +/-

						break;
						case 17:	// 0
							if(key_count<NUM_LENTH)
							{
								Disp_buff[key_count]='0';
								key_count++;
								Word=Disp_buff[disp_cound]-'0';
								conp_value=conp_value*10+Word;
								disp_cound++;
								if(dot_num==0)
									dot--;
							}
						break;
						case 18:	// .
							if(dot_num==0)
							{
								dot_num1=key_count;
								Disp_buff[key_count]='.';
								dot_num=1;
								key_count++;
								disp_cound++;
							}
						break;
						case 19:	// Enter
							conp_value*=pow(10,6-(disp_cound-dot_num));						
							Sort_set.Num=conp_value;
							Sort_set.Dot=dot;	
							Sort_set.Unit=3;
							Sort_set.Updata_flag=1;
							While_flag=0;							
						break;
						case 20:	// M
							conp_value*=pow(10,6-(disp_cound-dot_num));						
							Sort_set.Num=conp_value;
							Sort_set.Dot=dot;	
							Sort_set.Unit=4;
							Sort_set.Updata_flag=1;
							While_flag=0;
						break;
						default:							
						break;
					}	
					if(Button_Page->page==0)
						Button_Page->page=1;
				break;
				case KEY_Trig:
					
				break;
				case KEY_Mid:
					
				break;	
				default :
				break;
			}
			
			if(disp_flag)
			{
				disp_flag=0;
				Colour.Fword=LCD_COLOR_BLACK;
				Colour.black=LCD_COLOR_DARKGREY;
				if(del_flag==1)
				{
					PutChar( 192+(key_count+1)*10, 26, Disp_buff[key_count], Colour.Fword, Colour.black ); 
					del_flag=0;
				}				
				else if(del_flag!=1&&del_flag!=0)
				{
					for(i=0;i<del_flag;i++)
						PutChar( 192+(i+1)*10, 26, Disp_buff[i], Colour.Fword, Colour.black ); 
					del_flag=0;
				}
				else if(key_count>0)				
					PutChar( 192+key_count*10, 26,Disp_buff[key_count-1], Colour.Fword, Colour.black ); 
			}
		}
	}
	return Sort_set;
}


//Sort_TypeDef Disp_Set_InputpreNum(Disp_Coordinates_Typedef *Coordinates)
//{
//	Sort_TypeDef Sort_num1;  //Sort_num,
//	Disp_button_Num_Input(0);
//	Sort_num1=Input_compvalue(Coordinates);//Input_Set_Cov
//	if(SaveData.Limit_Tab.Mode==0)
//		Sort_num1=Input_Set_Cov(&Sort_num1);
//	else
//		Sort_num1=Input_Set_CovPre(&Sort_num1);
//	if(Sort_num1.Updata_flag==0)
//	{
//		Sort_num1.Dot=0;
//		Sort_num1.Num=0;
//		Sort_num1.Unit=0;
//	
//	}
//		
//	return Sort_num1;	
//}


