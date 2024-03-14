/**
  ******************************************************************************
  * 文件名程: soem.c 
  * 作    者: 硬石嵌入式开发团队
  * 版    本: V1.0
  * 编写日期: 2018-09-01
  * 功    能: ecatuser源文件
  ******************************************************************************
  * 说明：S
  * 本例程配套硬石stm32开发板YS-F4STD使用。
  * 
  * 淘宝：
  * 论坛：http://www.ing10bbs.com
  * 版权归硬石嵌入式开发团队所有，请勿商用。
  ******************************************************************************
  */
/* 包含头文件 ----------------------------------------------------------------*/
	
#include "soem.h"
#include "stdio.h"
#include "string.h"
#include "stm32F4xx_hal.h"

/* 私有类型定义 --------------------------------------------------------------*/

/* 私有宏定义 ----------------------------------------------------------------*/
#define SYNC0TIME 1000000
#define DEBUG 1

/* 私有变量 ------------------------------------------------------------------*/

PDO_Outputs *outputs1;
PDO_Input *inputs1;

char IOmap[4096];
uint32_t Motor_Run=0;
int expectedWKC;

/* 扩展变量 ------------------------------------------------------------------*/

/* 私有函数原形 --------------------------------------------------------------*/

/* 函数体 --------------------------------------------------------------------*/
/**
  * 函数功能: 写入8位SDO数据
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 
  */
int write8(uint16  slave, uint16  index, uint8  subindex, int value)
{
	uint8 temp = value;

	int rtn = ec_SDOwrite(slave, index, subindex, FALSE, sizeof(temp), &temp, EC_TIMEOUTRXM );

	if (rtn == 0) { printf("SDOwrite to %#x failed !!! \r\n", index); }
	else if (DEBUG) { printf("SDOwrite to slave%d  index:%#x value:%x Successed !!! \r\n", slave, index, temp); }
	return rtn;
}

/**
  * 函数功能: 写入16位SDO数据
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 
  */
int write16(uint16  slave, uint16  index, uint8  subindex, int value)
{
	uint16 temp = value;

	int rtn = ec_SDOwrite(slave, index, subindex, FALSE, sizeof(temp), &temp, EC_TIMEOUTRXM * 20);

	if (rtn == 0) { printf("SDOwrite to %#x failed !!! \r\n", index); }
	else if (DEBUG) { printf("SDOwrite to slave%d  index:%#x value:%x Successed !!! \r\n", slave, index, temp); }
	return rtn;
}

/**
  * 函数功能: 写入32位SDO数据
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 
  */
int write32(uint16 slave, uint16 index, uint8 subindex, int value)
{
	uint32 temp = value;

	int rtn = ec_SDOwrite(slave, index, subindex, FALSE, sizeof(temp), &temp, EC_TIMEOUTRXM * 20);
	if (rtn == 0) { printf("SDOwrite to %#x failed !!! \r\n", index); }
	else if (DEBUG) { printf("SDOwrite to slave%d  index:%#x value:%x Successed !!! \r\n", slave, index, temp); }
	return rtn;
}

/**
  * 函数功能: Delta配置
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 
  */
int Delta_Nsetup(uint16 slvcnt)
{

	printf(" slvcnt = %d\r\n",slvcnt);
	write8(slvcnt, 0x1C12, 00, 0);				      //清0x1C12数据		
	write8(slvcnt, 0x1601, 00, 0);				      //清0x1601数据		
	write32(slvcnt, 0x1601, 01, 0x60400010);		//增加0x1601子索引		
	write32(slvcnt, 0x1601, 02, 0x607A0020);		//增加0x1601子索引		
	write32(slvcnt, 0x1601, 03, 0x60830020);		//增加0x1601子索引   
	write32(slvcnt, 0x1601, 04, 0x60840020);		//增加0x1601子索引		
	write32(slvcnt, 0x1601, 05, 0x60FF0020);		//增加0x1601子索引	
	write8(slvcnt, 0x1601, 00, 5);				      //设置子索引数量
	
	write16(slvcnt, 0x1C12, 01, 0x1601);			  //设置RxPDO映射			  
	write8(slvcnt, 0x1C12, 00, 1);

	write8(slvcnt, 0x1C13, 00, 00);				      //清0x1C12数据							
	write8(slvcnt, 0x1A01, 00, 00);				      //清0x1600数据							
	write32(slvcnt, 0x1A01, 01, 0x60410010);		//增加0x1A01子索引			
  write32(slvcnt, 0x1A01, 02, 0x60640020);		//增加0x1A01子索引	
  write32(slvcnt, 0x1A01, 03, 0x606C0020);		//增加0x1A01子索引	
  write8(slvcnt, 0x1A01, 00, 03);				      //设置子索引数量
 
	write16(slvcnt, 0x1C13, 01, 0x1A01);			  //设置TxPDO映射
	write8(slvcnt, 0x1C13, 00, 01);

	write8(1, 0x6060, 00, 3);                   //设置为速度模式

  return 0;
}

/**
  * 函数功能: ecat初始化
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void ecat_init(void)
{
	int chk, slc;
	int i;
	
    /* initialise SOEM, bind socket to ifname */
  if (ec_init("ServoDrive"))
	{
		printf("ec_init succeeded.\r\n");
        
		if ( ec_config_init(FALSE) > 0 )
		{
			printf("%x slaves found and configured.%x \r\n",ec_slave[1].eep_man,ec_slave[1].eep_id);
            
			if ( ec_slavecount >= 1 ) 
			{
				for(slc = 1; slc <= ec_slavecount; slc++)
				 {									 
					 //台达伺服
					 if((ec_slave[slc].eep_man == 0x01dd) && (ec_slave[slc].eep_id == 0x10305070))
					 {
							 printf("Found %s at position %d\r\n", ec_slave[slc].name, slc);
							 printf("Found %x at position %d\r\n", ec_slave[slc].configadr, slc);
							 ec_slave[slc].PO2SOconfig = &Delta_Nsetup; 
					 }
				 }
       }
            
      ec_configdc();
			
			ec_config_map(&IOmap);
			
			ec_dcsync0(1, TRUE, SYNC0TIME, 0); // SYNC0 on slave 1
			 
			printf("segments : %d : %d %d %d %d\n",ec_group[0].nsegments ,ec_group[0].IOsegment[0],ec_group[0].IOsegment[1],ec_group[0].IOsegment[2],ec_group[0].IOsegment[3]);

			ec_statecheck(0, EC_STATE_SAFE_OP,  EC_TIMEOUTSTATE);
	
		  printf("Request operational state for all slaves\n");
		  expectedWKC = (ec_group[0].outputsWKC * 2) + ec_group[0].inputsWKC;
		  printf("Calculated workcounter %d\n", expectedWKC);
		  ec_slave[0].state = EC_STATE_OPERATIONAL;

			ec_send_processdata();
			
			ec_receive_processdata(EC_TIMEOUTRET);
				
			ec_writestate(0);
			do
		  {
				ec_statecheck(0, EC_STATE_OPERATIONAL, 50000);
		  }     
		  while (chk-- && (ec_slave[0].state != EC_STATE_OPERATIONAL));			
				 
			printf("DC capable : %d\r\n",ec_configdc());
			
			//HAL_Delay(100);
			
			for( i=0; i<10; i++ )
			{
				ec_slave[0].state = EC_STATE_OPERATIONAL;
				ec_writestate(0);
			}
				 
			if (ec_slave[0].state == EC_STATE_OPERATIONAL )
			{					
				outputs1 = (PDO_Outputs *)ec_slave[1].outputs;
				inputs1  = (PDO_Input *)ec_slave[1].inputs;

				Motor_Run = 1;

				printf("all slaves reached operational state.\r\n");
			}			
			else
			{
				printf("E/BOX not found in slave configuration.\r\n");
			}
		}
		else
		{
			printf("No slaves found!\r\n");
		}
	}
	else
	{
		printf("No socket connection Excecute as root\r\n");
	}
    
}

/**
  * 函数功能: ecat循环
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void ecat_loop(void)
{
	if (Motor_Run>0)
	{
		ec_send_processdata();
		
		ec_receive_processdata(EC_TIMEOUTRET);        
		
	}
}

/**
  * 函数功能: 设备控制
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void ctrl_state(void)
{
    switch (outputs1->controlword)
    {
    case 0:
	      outputs1->decelerAtion=3000;
		    outputs1->accelerAtion=3000;
		    outputs1->targetVelocity=10000;
        outputs1->controlword = 6;
        break;
    case 6:

        outputs1->controlword = 7;
        break;
    case 7:
        outputs1->controlword = 0x0f;
        break;
    case 0x0f:
        break;
    default:
        outputs1->controlword = 6;
        break;
    }
    printf("\r\nctl = %d  \r\n",outputs1->controlword);
}

/********** (C) COPYRIGHT 2019-2030 硬石嵌入式开发团队 *******END OF FILE******/

