#ifndef FOLLOW_CONTROLLER_H_
#define FOLLOW_CONTROLLER_H_

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "follow_para.h"
#include <stdbool.h>
#include "bsp_led.h"
typedef enum
{
	SM_NOT_READY,     //未就绪
	SM_IDLE,          //空闲
	SM_POSITONING,    //定位状态  
	SM_FOLLOWING,     //随动状态
	SM_PARKING,       //回停靠点
	SM_DRYRUNNING,
	SM_ERROR,         //错误状态
}SM_STATUS;
                    
typedef struct
{
	u8 nWorkState;
	u8 nWarnState1;
	u8 nWarnState2;
}WarnState;

// 以下对应WarnState里面的bit位信息
#define BIT_SIZE	8
typedef enum
{
	IDLEING = 0,        // 静止中
	POSITIONING,        // 指令定位中
	SERVOCALIBING,		// 伺服标定中
	FOLLOWING,		    // 跟随中
	PARKING,		    // 回停靠中
	DRY_RUNNING,		// 空移中
	FOLLOW_ERROR,		// 随动出错中
	FLOATCALIBING,		// 浮头标定中
}tWorkStatus;

typedef enum
{
	WS_NOT_FOLLOWCALIB = 8,// 未随动标定
	WS_FROG_LEAPING,		// 蛙跳中
	WS_FROG_ERROR,	// 蛙跳指令错误
	WS_BUMPING_ALARM,		// 碰板告警
	WS_FOLLOW_INPLACE,		// 随动到位
	WS_SOFTWARE_LIMIT_DOWN,		// 软件下限位
	WS_CAP_JUMP,			// 电容突变
	WS_MISSPANEL,			// 踏空报警

	WS_SOFTWARE_LIMIT_UP = 16, // 软件上限位
	WS_HOLD_STATE = 17,	// Hold反馈状态
	WS_REACHED_BOARD = 18,
}tWarnStatus;

//todo：此处的部分参数似乎应该归到相应模块中，后续需要整理 --陈豫
typedef struct
{
	SM_STATUS State;			// 状态集
	SM_STATUS PreState;
	WarnState WarnState;		// 警示状态

	//功能控制IO
	bool bFollowEnable;			// 随动开关
	bool bServoCalibEnable;		// 伺服标定开关
	bool bTouchParkEnable;		// 碰板上抬使能
	bool bDetcetedCapSaltus;   	// 电容突变检测开关

	//状态标记
	bool bZLimited;				// 限位状态
	bool bPosTouchPanel;		// 空运行碰板标志
	bool bUpdatePosTouchPanel;  // 碰板更新标识,使用上升沿触发方式
	bool bFollowTouchPanel;     // 随动碰板
	bool bFloatCaliTouchPanel;  // 浮头标定碰板
	bool bMachining;        	// 是否处于加工状态
	bool bDisConnect;			// 断开通信
	bool bEdgeParking;			// 寻边边缘上抬
	bool bPiercing;				// 是否处于加工穿孔中

	////////////////////////////////////////////////////
	s32 nCapSaltusWarnDurationT;        // 电容突变信号持续时间
	s32 nParkingDurationT;			// 上抬信号持续时间
	s32 nLimitedDownWarnDurationT;		// 下限位告警信号持续时间
	s32 nLimitedUpWarnDurationT;		// 上限位告警信号持续时间
	s32 nMissPanelWarnDurationT;	// 踩空告警延时

}FollowController;

FollowController*  FollowController_Get();

WarnState*  WarmState_Get(FollowController* pSelf_);

s32 FollowController_OnStep(FollowController* pSelf_);

void FollowController_Reset(FollowController* pSelf_);
void FollowController_Init(FollowController* pSelf_);

#endif
