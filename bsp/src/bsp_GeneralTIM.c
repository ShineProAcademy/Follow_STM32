/**
  ******************************************************************************
  * 文件名程: bsp_GeneralTIM.c 
  * 作    者: 硬石嵌入式开发团队
  * 版    本: V1.0
  * 编写日期: 2018-09-01
  * 功    能: TIM头文件
  ******************************************************************************
  * 说明：
  * 本例程配套硬石stm32开发板YS-F4STD使用。
  * 
  * 淘宝：
  * 论坛：http://www.ing10bbs.com
  * 版权归硬石嵌入式开发团队所有，请勿商用。
  ******************************************************************************
  */
/* 包含头文件 ----------------------------------------------------------------*/
	
#include "bsp_GeneralTIM.h"

/* 私有类型定义 --------------------------------------------------------------*/

/* 私有宏定义 ----------------------------------------------------------------*/



/* 扩展变量 ------------------------------------------------------------------*/

/* 私有函数原形 --------------------------------------------------------------*/

/* 函数体 --------------------------------------------------------------------*/


/**
  * 函数功能: GetSec
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
uint32_t GetSec(void)
{
    return TIM3->CNT;
}
/**
  * 函数功能: GetUSec
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */

uint32_t GetUSec(void)
{
    return TIM2->CNT;
}


/********** (C) COPYRIGHT 2019-2030 硬石嵌入式开发团队 *******END OF FILE******/
