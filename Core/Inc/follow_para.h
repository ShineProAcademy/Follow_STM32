#ifndef __FOLLOW_PARA_H__
#define __FOLLOW_PARA_H__

#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdio.h>

#pragma pack(push, 1)
typedef struct
{
	u8 nPosKp;
	u8 nFollowKp;
	u8 nFollowKd;
	u8 nDir;				// bit0:伺服方向，bit1:反馈方向
	u32 nPulsePerRound;		// 每转的脉冲个数,p/r
	u16 nPitch;					// 螺距,			单位0.01mm
	u16 nMaxSpeed;			// 运行最大速度     	mm/min
	u16 nMaxAccSpeed;		// 运行最大加速度 	mm/S^2
	u16 nInRange;			// 到位范围         		 0.01mm
	s32 nZLimitUp;			// 相对于原点位置的上限位距离，单位：um。
	s32 nZLimitDown;		// 相对于原点位置的下限位距离，单位：um。
	s32 nParkingPos;		// 停靠点位置 ,单位:um。
	u32 nTouchCap;			// 碰板电容
	u16 nPosTouchDelay;		// 位置模式碰板延时 	ms
	u16 nFollowTouchDelay;	// 随动模式碰板延时	ms
	u16 nFollowHeight;		// 随动高度    		0.01mm
	u8 nFrogLeapHeight;		// 蛙跳高度   		mm
	u8 nEnable;						// 上位机功能配置开关，bit0:防侧撞功能
	u16 nSafetyHeight;		// 上抬的安全高度	单位:mm
	u8 nMissPanelTolerance;	// 防踩空允差，单位：mm
	u8 nFeedForward;				// 随动前馈量 0~100
	u8 nSuppressRatio;			// 振动抑制系数 :目前分为0~5个系数 0->5抑制强度越大
	u8 nFindEdgeLiftMode;   // 出边上抬模式 0默认以有无原点信号作为出边方式;1、出边以安全高度上抬
	u8 nZAxisIndex;					// Z轴索引
	u32 nZAxisMaxRevSpeed; 	// Z轴电机最大转速（电机铭牌规格）r/min
	u16 nPierceTouchDelay; // 穿孔碰板延时  单位ms
	s32 nCompenCap;// 补偿电容值
	u16 nReachBoardMinDistance; // 达到板面最小距离，单位0.01mm

	// 上位机下发电容突变检测阈值与检测时间
	s32 nCapSaltusDetectTime;   // 上位机下发的电容突变检测时间 (单位ms)
	s32 nCapSaltusThreshold;    // 上位机下发的电容突变检测阈值 (单位0.1mm)

}tFollowPara;
#pragma pack(pop)

typedef struct
{
	u8 bUpdate;
	tFollowPara para;
}tParaManager;

void InitFollowParam();
extern tParaManager FollowParaManager;


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 #endif