/******************************************************************/
/* ĻԆĈTIM3 PWM                                                */
/* Чڻú                                                        */
/* ŚɝúӺʺһٶ200HZ ֽռࠕ҈ú60.9% غռࠕ҈ú30.9%քPWM      */
/* ط֟únֱ                                                    */
/* jϵ׽ʽúQQ:363116119                                        */
/******************************************************************/
#include "my_register.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx.h"
#include "tim5.h"
#include "MainTask.h"
#include "ssd1963.h"
#include "modbus_slave.h"
/*****************************************************************/
/*****************************************************************/


u32 Tick_10ms=0;
u32 OldTick;



//定时器初始化，10ms定时器配置为TIM5_Int_Init(10-1,8400-1);
void TIM5_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE); //ÙʹŜ TIM3 ʱד
    TIM_TimeBaseInitStructure.TIM_Period = arr; //ؔ֯טװ՘ֵ
    TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //֨ʱǷؖƵ
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //вʏ݆˽ģʽ
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);// ÚԵʼۯ֨ʱǷ TIM3
    TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //ÛՊѭ֨ʱǷ 3 ټтא׏
    NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //֨ʱǷ 3 א׏
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //ȀռԅЈܶ 1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02; //ЬӦԅЈܶ 3
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);// ÜԵʼۯ NVIC
    TIM_Cmd(TIM5,ENABLE); //ÝʹŜ֨ʱǷ 3
}

//定时器中断
void TIM5_IRQHandler(void)
{
    
    if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //ӧԶא׏
    {
        TIM_ClearITPendingBit(TIM5,TIM_IT_Update); //清除中断标志位
        Tick_10ms ++;
        MODS_Poll();
    }
}


void MODS_Poll(void)
{
	uint16_t addr;
	static uint16_t crc1;
    static u32 testi;
	/* 超过3.5个字符时间后执行MODH_RxTimeOut()函数。全局变量 g_rtu_timeout = 1; 通知主程序开始解码 */
//	if (g_mods_timeout == 0)	
//	{
//		return;								/* 没有超时，继续接收。不要清零 g_tModS.RxCount */
//	}

    testi=UART_Buffer_Size;
    testi=UART_Buffer_Size;
    testi=UART_Buffer_Size;
	if(testi>7)				/* 接收到的数据小于4个字节就认为错误 */
	{
		testi=testi;
	}
	testi=UART_Buffer_Size;
    if(testi==8)				/* 接收到的数据小于4个字节就认为错误 */
	{
		testi=testi+1;
	}
	 //判断通讯接收是否超时
	if(OldTick!=Tick_10ms)
  	{  
	  OldTick=Tick_10ms;
	   if(g_mods_timeout>0)
      { 
	    g_mods_timeout--;
      }
	  if(g_mods_timeout==0 && UART_Buffer_Size>0)   //有数但超时了
      { 
		// goto err_ret;
	
      }
      else if(g_mods_timeout==0 && UART_Buffer_Size==0) //没数超时了
         return;
      else //没超时了，继续收
         return;
	}
	else   //没有到10ms，不进入解析
		return;
	//g_mods_timeout = 0;	 					/* 清标志 */

	if (UART_Buffer_Size < 4)				/* 接收到的数据小于4个字节就认为错误 */
	{
		return;
	}

	/* 计算CRC校验和 */
	crc1 = CRC16(UART_Buffer_Rece, UART_Buffer_Size);
	if (crc1 != 0)
	{
		return;
	}

// 	/* 站地址 (1字节） */
// 	addr = g_tModS.RxBuf[0];				/* 第1字节 站号 */
// 	if (addr != SADDR485)		 			/* 判断主机发送的命令地址是否符合 */
// 	{
// 		goto err_ret;
// 	}

	/* 分析应用层协议 */
	RecHandle();						
	
// err_ret:
// #if 0										/* 此部分为了串口打印结果,实际运用中可不要 */
// 	g_tPrint.Rxlen = g_tModS.RxCount;
// 	memcpy(g_tPrint.RxBuf, g_tModS.RxBuf, g_tModS.RxCount);
// #endif
// 	
 	UART_Buffer_Size = 0;					/* 必须清零计数器，方便下次帧同步 */
}