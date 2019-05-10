/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "bsp_SysTick.h"
#include "my_register.h"

static void MODS_03H(void);

extern __IO int32_t OS_TimeMS;

extern struct bitDefine
{
	unsigned bit0: 1;
	unsigned bit1: 1;
	unsigned bit2: 1;
	unsigned bit3: 1;
	unsigned bit4: 1;
	unsigned bit5: 1;
	unsigned bit6: 1;
	unsigned bit7: 1;
} flagA,flagB,flagC,flagD,flagE,flagF;
/** @addtogroup Template_Project
  * @{
  */
float temp;
u8 g_mods_timeout = 0;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}


//串口1中断
void USART1_IRQHandler(void)
{
	flag_Tim_USART=1;
 	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
        g_mods_timeout = 2;
		UART_Buffer_Rece[UART_Buffer_Size]=USART_ReceiveData(USART1);
		UART_Buffer_Size++;
	}
}


//接收处理
void RecHandle(void)
{
    
    switch(UART_Buffer_Rece[1])
    {
        case 0x03:
        {
            MODS_03H();
        }break;
        case 0x06:
        {
            
        }break;
        default:break;
    }

}

//读取数据
static void MODS_03H(void)
{
    u8 crec[6];
    u8 *csend;
    static u8 *sendbuf;
    u8 sendlen;
    static u16 recrc;
    static u16 scrc;
    u8 i;
    
    if (UART_Buffer_Size != 8)
	{
		return;
	}
    switch(UART_Buffer_Rece[3])
    {
        case 0x00:
        {
            sendlen = 7;
            sendbuf = (u8 *)malloc(sizeof(u8) * sendlen);
            memset(sendbuf, 0, sendlen);
            csend = (u8 *)malloc(sizeof(u8) * sendlen-2);
            memset(csend, 0, sendlen-2);
            sendbuf[0] = UART_Buffer_Rece[0];
            sendbuf[1] = UART_Buffer_Rece[1];
            sendbuf[2] = 0x02;
            if(DISS_Voltage < 0.3)
            {
                sendbuf[3] = 0;
                sendbuf[4] = 0;
            }else{
                sendbuf[3] = (u8)(R_VLUE >> 8);
                sendbuf[4] = (u8)(R_VLUE);
            }
            for(i=0;i<sendlen-2;i++)
            {
                csend[i] = sendbuf[i];
            }
            scrc = CRC16(csend,sendlen-2);
            sendbuf[5] = (u8)(scrc);
            sendbuf[6] = (u8)(scrc>>8);
            for(i=0;i<sendlen;i++)
            {
                USART_SendData(USART1,sendbuf[i]);
                while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
            }
            flag_Tim_USART = 0;
        }break;
        case 0x01:
        {
            sendlen = 7;
            sendbuf = (u8 *)malloc(sizeof(u8) * sendlen);
            memset(sendbuf, 0, sendlen);
            csend = (u8 *)malloc(sizeof(u8) * sendlen-2);
            memset(csend, 0, sendlen-2);
            sendbuf[0] = UART_Buffer_Rece[0];
            sendbuf[1] = UART_Buffer_Rece[1];
            sendbuf[2] = 0x02;
            sendbuf[3] = (u8)((int)(DISS_Voltage*1000) >> 8);
            sendbuf[4] = (u8)((int)(DISS_Voltage*1000));
            for(i=0;i<sendlen-2;i++)
            {
                csend[i] = sendbuf[i];
            }
            scrc = CRC16(csend,sendlen-2);
            sendbuf[5] = (u8)(scrc);
            sendbuf[6] = (u8)(scrc>>8);
            for(i=0;i<sendlen;i++)
            {
                USART_SendData(USART1,sendbuf[i]);
                while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
            }
        }break;
        case 0x02:
        {
            sendlen = 7;
            sendbuf = (u8 *)malloc(sizeof(u8) * sendlen);
            memset(sendbuf, 0, sendlen);
            csend = (u8 *)malloc(sizeof(u8) * sendlen-2);
            memset(csend, 0, sendlen-2);
            sendbuf[0] = UART_Buffer_Rece[0];
            sendbuf[1] = UART_Buffer_Rece[1];
            sendbuf[2] = 0x02;
            sendbuf[3] = (u8)((int)(DISS_Current*1000) >> 8);
            sendbuf[4] = (u8)((int)(DISS_Current*1000));
            for(i=0;i<sendlen-2;i++)
            {
                csend[i] = sendbuf[i];
            }
            scrc = CRC16(csend,sendlen-2);
            sendbuf[5] = (u8)(scrc);
            sendbuf[6] = (u8)(scrc>>8);
            for(i=0;i<sendlen;i++)
            {
                USART_SendData(USART1,sendbuf[i]);
                while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
            }
        }break;
        case 0x03:
        {
            sendlen = 7;
            sendbuf = (u8 *)malloc(sizeof(u8) * sendlen);
            memset(sendbuf, 0, sendlen);
            csend = (u8 *)malloc(sizeof(u8) * sendlen-2);
            memset(csend, 0, sendlen-2);
            sendbuf[0] = UART_Buffer_Rece[0];
            sendbuf[1] = UART_Buffer_Rece[1];
            sendbuf[2] = 0x02;
            sendbuf[3] = (u8)((int)(DISS_POW_Voltage*100) >> 8);
            sendbuf[4] = (u8)((int)(DISS_POW_Voltage*100));
            for(i=0;i<sendlen-2;i++)
            {
                csend[i] = sendbuf[i];
            }
            scrc = CRC16(csend,sendlen-2);
            sendbuf[5] = (u8)(scrc);
            sendbuf[6] = (u8)(scrc>>8);
            for(i=0;i<sendlen;i++)
            {
                USART_SendData(USART1,sendbuf[i]);
                while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
            }
        }break;
        case 0x04:
        {
            sendlen = 7;
            sendbuf = (u8 *)malloc(sizeof(u8) * sendlen);
            memset(sendbuf, 0, sendlen);
            csend = (u8 *)malloc(sizeof(u8) * sendlen-2);
            memset(csend, 0, sendlen-2);
            sendbuf[0] = UART_Buffer_Rece[0];
            sendbuf[1] = UART_Buffer_Rece[1];
            sendbuf[2] = 0x02;
            sendbuf[3] = (u8)((int)(DISS_POW_Current*1000) >> 8);
            sendbuf[4] = (u8)((int)(DISS_POW_Current*1000));
            for(i=0;i<sendlen-2;i++)
            {
                csend[i] = sendbuf[i];
            }
            scrc = CRC16(csend,sendlen-2);
            sendbuf[6] = (u8)(scrc);
            sendbuf[7] = (u8)(scrc>>8);
            for(i=0;i<sendlen;i++)
            {
                USART_SendData(USART1,sendbuf[i]);
                while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
            }
        }break;
        default:break;
    }
}

uint16_t CRC16(uint8_t *puchMsg, uint8_t Len)
{
	uint8_t t, m,n,p;
	uint8_t uchCRCHi=0xFF; /* 高CRC字节初始化*/ 
	uint8_t uchCRCLo =0xFF; /* 低CRC 字节初始化*/ 
	for(t=0;t<Len;t++)
	{	
		uchCRCLo=uchCRCLo^puchMsg[t];
		for(n=0;n<8;n++)
		{
			m=uchCRCLo&1;p=uchCRCHi&1;uchCRCHi>>=1;
			uchCRCLo>>=1;

			if(p)
			{
				uchCRCLo|=0x80;
			}
			if(m)	
			{
				uchCRCHi=uchCRCHi^0xa0;
				uchCRCLo=uchCRCLo^1;
			}
		}
	}
	return (uchCRCHi<<8|uchCRCLo);
}


/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
