#ifndef FOLLOW_CONTROLLER_H_
#define FOLLOW_CONTROLLER_H_

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "follow_para.h"
#include <stdbool.h>
#include "bsp_led.h"
typedef enum
{
	SM_NOT_READY,     //δ����
	SM_IDLE,          //����
	SM_POSITONING,    //��λ״̬  
	SM_FOLLOWING,     //�涯״̬
	SM_PARKING,       //��ͣ����
	SM_DRYRUNNING,
	SM_ERROR,         //����״̬
}SM_STATUS;
                    
typedef struct
{
	u8 nWorkState;
	u8 nWarnState1;
	u8 nWarnState2;
}WarnState;

// ���¶�ӦWarnState�����bitλ��Ϣ
#define BIT_SIZE	8
typedef enum
{
	IDLEING = 0,        // ��ֹ��
	POSITIONING,        // ָ�λ��
	SERVOCALIBING,		// �ŷ��궨��
	FOLLOWING,		    // ������
	PARKING,		    // ��ͣ����
	DRY_RUNNING,		// ������
	FOLLOW_ERROR,		// �涯������
	FLOATCALIBING,		// ��ͷ�궨��
}tWorkStatus;

typedef enum
{
	WS_NOT_FOLLOWCALIB = 8,// δ�涯�궨
	WS_FROG_LEAPING,		// ������
	WS_FROG_ERROR,	// ����ָ�����
	WS_BUMPING_ALARM,		// ����澯
	WS_FOLLOW_INPLACE,		// �涯��λ
	WS_SOFTWARE_LIMIT_DOWN,		// �������λ
	WS_CAP_JUMP,			// ����ͻ��
	WS_MISSPANEL,			// ̤�ձ���

	WS_SOFTWARE_LIMIT_UP = 16, // �������λ
	WS_HOLD_STATE = 17,	// Hold����״̬
	WS_REACHED_BOARD = 18,
}tWarnStatus;

//todo���˴��Ĳ��ֲ����ƺ�Ӧ�ù鵽��Ӧģ���У�������Ҫ���� --��ԥ
typedef struct
{
	SM_STATUS State;			// ״̬��
	SM_STATUS PreState;
	WarnState WarnState;		// ��ʾ״̬

	//���ܿ���IO
	bool bFollowEnable;			// �涯����
	bool bServoCalibEnable;		// �ŷ��궨����
	bool bTouchParkEnable;		// ������̧ʹ��
	bool bDetcetedCapSaltus;   	// ����ͻ���⿪��

	//״̬���
	bool bZLimited;				// ��λ״̬
	bool bPosTouchPanel;		// �����������־
	bool bUpdatePosTouchPanel;  // ������±�ʶ,ʹ�������ش�����ʽ
	bool bFollowTouchPanel;     // �涯����
	bool bFloatCaliTouchPanel;  // ��ͷ�궨����
	bool bMachining;        	// �Ƿ��ڼӹ�״̬
	bool bDisConnect;			// �Ͽ�ͨ��
	bool bEdgeParking;			// Ѱ�߱�Ե��̧
	bool bPiercing;				// �Ƿ��ڼӹ�������

	////////////////////////////////////////////////////
	s32 nCapSaltusWarnDurationT;        // ����ͻ���źų���ʱ��
	s32 nParkingDurationT;			// ��̧�źų���ʱ��
	s32 nLimitedDownWarnDurationT;		// ����λ�澯�źų���ʱ��
	s32 nLimitedUpWarnDurationT;		// ����λ�澯�źų���ʱ��
	s32 nMissPanelWarnDurationT;	// �ȿո澯��ʱ

}FollowController;

FollowController*  FollowController_Get();

WarnState*  WarmState_Get(FollowController* pSelf_);

s32 FollowController_OnStep(FollowController* pSelf_);

void FollowController_Reset(FollowController* pSelf_);
void FollowController_Init(FollowController* pSelf_);

#endif
