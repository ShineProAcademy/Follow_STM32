/**
  ******************************************************************************
  * 文件名程: lan8720.c 
  * 作    者: 硬石嵌入式开发团队
  * 版    本: V1.0
  * 编写日期: 2018-09-01
  * 功    能: lan8720头文件
  ******************************************************************************
  * 说明：
  * 本例程配套硬石stm32开发板YS-F4Pro使用。
  * 
  * 淘宝：
  * 论坛：http://www.ing10bbs.com
  * 版权归硬石嵌入式开发团队所有，请勿商用。
  ******************************************************************************
  */
#ifndef _LAN8720_H_
#define _LAN8720_H_
/* 包含头文件 ----------------------------------------------------------------*/

/* 私有类型定义 --------------------------------------------------------------*/

/* 宏定义 --------------------------------------------------------------------*/


#define  LAN8720_STATUS_READ_ERROR            ((int32_t)-5)
#define  LAN8720_STATUS_WRITE_ERROR           ((int32_t)-4)
#define  LAN8720_STATUS_ADDRESS_ERROR         ((int32_t)-3)
#define  LAN8720_STATUS_RESET_TIMEOUT         ((int32_t)-2)
#define  LAN8720_STATUS_ERROR                 ((int32_t)-1)
#define  LAN8720_STATUS_OK                    ((int32_t) 0)
#define  LAN8720_STATUS_LINK_DOWN             ((int32_t) 1)
#define  LAN8720_STATUS_100MBITS_FULLDUPLEX   ((int32_t) 2)
#define  LAN8720_STATUS_100MBITS_HALFDUPLEX   ((int32_t) 3)
#define  LAN8720_STATUS_10MBITS_FULLDUPLEX    ((int32_t) 4)
#define  LAN8720_STATUS_10MBITS_HALFDUPLEX    ((int32_t) 5)
#define  LAN8720_STATUS_AUTONEGO_NOTDONE      ((int32_t) 6)


#define LAN8720_BCR      ((uint16_t)0x0000U)
#define LAN8720_BSR      ((uint16_t)0x0001U)
#define LAN8720_PHYI1R   ((uint16_t)0x0002U)
#define LAN8720_PHYI2R   ((uint16_t)0x0003U)
#define LAN8720_ANAR     ((uint16_t)0x0004U)
#define LAN8720_ANLPAR   ((uint16_t)0x0005U)
#define LAN8720_ANER     ((uint16_t)0x0006U)
#define LAN8720_ANNPTR   ((uint16_t)0x0007U)
#define LAN8720_ANNPRR   ((uint16_t)0x0008U)
#define LAN8720_MMDACR   ((uint16_t)0x000DU)
#define LAN8720_MMDAADR  ((uint16_t)0x000EU)
#define LAN8720_ENCTR    ((uint16_t)0x0010U)
#define LAN8720_MCSR     ((uint16_t)0x0011U)
#define LAN8720_SMR      ((uint16_t)0x0012U)
#define LAN8720_TPDCR    ((uint16_t)0x0018U)
#define LAN8720_TCSR     ((uint16_t)0x0019U)
#define LAN8720_SECR     ((uint16_t)0x001AU)
#define LAN8720_SCSIR    ((uint16_t)0x001BU)
#define LAN8720_CLR      ((uint16_t)0x001CU)
#define LAN8720_ISFR     ((uint16_t)0x001DU)
#define LAN8720_IMR      ((uint16_t)0x001EU)
#define LAN8720_PHYSCSR  ((uint16_t)0x001FU)

#define LAN8720_SMR_MODE       ((uint16_t)0x00E0U)
#define LAN8720_SMR_PHY_ADDR   ((uint16_t)0x001FU)

#define LAN8720_BCR_SOFT_RESET         ((uint16_t)0x8000U)
#define LAN8720_BCR_LOOPBACK           ((uint16_t)0x4000U)
#define LAN8720_BCR_SPEED_SELECT       ((uint16_t)0x2000U)
#define LAN8720_BCR_AUTONEGO_EN        ((uint16_t)0x1000U)
#define LAN8720_BCR_POWER_DOWN         ((uint16_t)0x0800U)
#define LAN8720_BCR_ISOLATE            ((uint16_t)0x0400U)
#define LAN8720_BCR_RESTART_AUTONEGO   ((uint16_t)0x0200U)
#define LAN8720_BCR_DUPLEX_MODE        ((uint16_t)0x0100U) 


#define LAN8720_BSR_100BASE_T4       ((uint16_t)0x8000U)
#define LAN8720_BSR_100BASE_TX_FD    ((uint16_t)0x4000U)
#define LAN8720_BSR_100BASE_TX_HD    ((uint16_t)0x2000U)
#define LAN8720_BSR_10BASE_T_FD      ((uint16_t)0x1000U)
#define LAN8720_BSR_10BASE_T_HD      ((uint16_t)0x0800U)
#define LAN8720_BSR_100BASE_T2_FD    ((uint16_t)0x0400U)
#define LAN8720_BSR_100BASE_T2_HD    ((uint16_t)0x0200U)
#define LAN8720_BSR_EXTENDED_STATUS  ((uint16_t)0x0100U)
#define LAN8720_BSR_AUTONEGO_CPLT    ((uint16_t)0x0020U)
#define LAN8720_BSR_REMOTE_FAULT     ((uint16_t)0x0010U)
#define LAN8720_BSR_AUTONEGO_ABILITY ((uint16_t)0x0008U)
#define LAN8720_BSR_LINK_STATUS      ((uint16_t)0x0004U)
#define LAN8720_BSR_JABBER_DETECT    ((uint16_t)0x0002U)
#define LAN8720_BSR_EXTENDED_CAP     ((uint16_t)0x0001U)

#define LAN8720_PHYSCSR_AUTONEGO_DONE   ((uint16_t)0x1000U)
#define LAN8720_PHYSCSR_HCDSPEEDMASK    ((uint16_t)0x001CU)
#define LAN8720_PHYSCSR_10BT_HD         ((uint16_t)0x0004U)
#define LAN8720_PHYSCSR_10BT_FD         ((uint16_t)0x0014U)
#define LAN8720_PHYSCSR_100BTX_HD       ((uint16_t)0x0008U)
#define LAN8720_PHYSCSR_100BTX_FD       ((uint16_t)0x0018U) 

/* 扩展变量 ------------------------------------------------------------------*/

/* 函数声明 ------------------------------------------------------------------*/
int LAN8720_Init(void);
int LAN8720_GetLinkState(void);
void LAN8720A_StartAutoNego(void);


#endif /* __BSP_LAN8720_H__ */


/********** (C) COPYRIGHT 2019-2030 硬石嵌入式开发团队 *******END OF FILE******/

