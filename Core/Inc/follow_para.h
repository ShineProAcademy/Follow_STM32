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
	u8 nDir;				// bit0:�ŷ�����bit1:��������
	u32 nPulsePerRound;		// ÿת���������,p/r
	u16 nPitch;					// �ݾ�,			��λ0.01mm
	u16 nMaxSpeed;			// ��������ٶ�     	mm/min
	u16 nMaxAccSpeed;		// ���������ٶ� 	mm/S^2
	u16 nInRange;			// ��λ��Χ         		 0.01mm
	s32 nZLimitUp;			// �����ԭ��λ�õ�����λ���룬��λ��um��
	s32 nZLimitDown;		// �����ԭ��λ�õ�����λ���룬��λ��um��
	s32 nParkingPos;		// ͣ����λ�� ,��λ:um��
	u32 nTouchCap;			// �������
	u16 nPosTouchDelay;		// λ��ģʽ������ʱ 	ms
	u16 nFollowTouchDelay;	// �涯ģʽ������ʱ	ms
	u16 nFollowHeight;		// �涯�߶�    		0.01mm
	u8 nFrogLeapHeight;		// �����߶�   		mm
	u8 nEnable;						// ��λ���������ÿ��أ�bit0:����ײ����
	u16 nSafetyHeight;		// ��̧�İ�ȫ�߶�	��λ:mm
	u8 nMissPanelTolerance;	// ���ȿ��ʲ��λ��mm
	u8 nFeedForward;				// �涯ǰ���� 0~100
	u8 nSuppressRatio;			// ������ϵ�� :Ŀǰ��Ϊ0~5��ϵ�� 0->5����ǿ��Խ��
	u8 nFindEdgeLiftMode;   // ������̧ģʽ 0Ĭ��������ԭ���ź���Ϊ���߷�ʽ;1�������԰�ȫ�߶���̧
	u8 nZAxisIndex;					// Z������
	u32 nZAxisMaxRevSpeed; 	// Z�������ת�٣�������ƹ��r/min
	u16 nPierceTouchDelay; // ����������ʱ  ��λms
	s32 nCompenCap;// ��������ֵ
	u16 nReachBoardMinDistance; // �ﵽ������С���룬��λ0.01mm

	// ��λ���·�����ͻ������ֵ����ʱ��
	s32 nCapSaltusDetectTime;   // ��λ���·��ĵ���ͻ����ʱ�� (��λms)
	s32 nCapSaltusThreshold;    // ��λ���·��ĵ���ͻ������ֵ (��λ0.1mm)

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