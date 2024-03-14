#ifndef __BSP_PC_USART_H__
#define __BSP_PC_USART_H__


#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "follow_para.h"
#define UART_BUFFSIZE 256

typedef struct{
    uint16_t Uart_SendLens;  
    uint16_t Uart_RecvLens;  
    uint8_t Uart_SentBuff[UART_BUFFSIZE];	
    uint8_t Uart_RecvBuff[UART_BUFFSIZE];		
 }UART_STR;

UART_STR* Get_usrt1_str();
 
 
extern UART_HandleTypeDef huart4;
extern DMA_HandleTypeDef hdma_uart4_rx;
extern tParaManager FollowParaManager;
 
void bsp_pc_usart_init();
void bsp_pc_usart_isr();
void bsp_pc_usart_Send_function(UART_STR* pUart_str);
void bsp_pc_usart_Analysis_function(UART_STR* pUart_str);

#endif  /* __BSP_DEBUG_USART_H__ */