#include "bsp_pc_usart.h"
#include "follow_para.h"
#include "string.h"
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))

static UART_STR Uart1_Str;

UART_STR* Get_usrt1_str()
{
	return &Uart1_Str;
}

void bsp_pc_usart_init()
{
	 __HAL_UART_ENABLE_IT(&huart4, UART_IT_IDLE);
    HAL_UART_Receive_DMA(&huart4, Uart1_Str.Uart_RecvBuff, sizeof(Uart1_Str.Uart_RecvBuff)-1);
}

void bsp_pc_usart_isr()
{
	if (__HAL_UART_GET_FLAG(&huart4, UART_FLAG_IDLE) != RESET)
		{
        __HAL_UART_CLEAR_IDLEFLAG(&huart4);	
        HAL_UART_DMAStop(&huart4);	
        Uart1_Str.Uart_RecvLens = UART_BUFFSIZE - __HAL_DMA_GET_COUNTER(&hdma_uart4_rx);	
        //HAL_UART_Transmit_DMA(&huart4, Uart1_Str.Uart_RecvBuff, Uart1_Str.Uart_RecvLens);	
				bsp_pc_usart_Analysis_function(Get_usrt1_str());
				bsp_pc_usart_Send_function(Get_usrt1_str());
        HAL_UART_Receive_DMA(&huart4, Uart1_Str.Uart_RecvBuff, sizeof(Uart1_Str.Uart_RecvBuff)-1);	//ÖØÖÃDMA
    }
}

void bsp_pc_usart_Send_function(UART_STR* pUart_str)
{

//	²âÊÔ´úÂë
	s32 _nLen = MIN(Uart1_Str.Uart_RecvLens, sizeof(FollowParaManager.para));
	_nLen = MAX(_nLen, 3);
	memcpy(pUart_str->Uart_SentBuff, &FollowParaManager.para, _nLen);
	HAL_UART_Transmit_DMA(&huart4, pUart_str->Uart_SentBuff, _nLen);	
	
}
void bsp_pc_usart_Analysis_function(UART_STR* pUart_str)
{
// test
	s32 _nLen = MIN(sizeof(pUart_str->Uart_RecvBuff), sizeof(FollowParaManager.para));
	memset(&FollowParaManager.para, 0, sizeof(FollowParaManager.para));
	memcpy(&FollowParaManager.para, pUart_str->Uart_RecvBuff, _nLen);
	FollowParaManager.para.nPosKp = 65;
	FollowParaManager.para.nFollowKp = 66;
	FollowParaManager.para.nFollowKd = 67;
	
}