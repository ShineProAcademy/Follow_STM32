#include "follow_controller.h"


FollowController s_Controller;
static SM_STATUS OnControl(FollowController* pSelf_);
static void SetState(FollowController* pSelf_, SM_STATUS state_);
FollowController*  FollowController_Get()
{
	return &s_Controller;
}

WarnState*  WarmState_Get(FollowController* pSelf_)
{
	return &pSelf_->WarnState;
}

s32 FollowController_OnStep(FollowController* pSelf_)
{
	OnControl(pSelf_);
	return 0;
}

static u32 testCount = 0;
SM_STATUS OnControl(FollowController* pSelf_)
{
	SM_STATUS _state = pSelf_->State;
  
	testCount++;
	
	switch (_state)
	{
	case SM_NOT_READY:
		{
			LED1_ON;
			LED1_OFF;
			if(testCount % 1000 == 0)
			SetState(pSelf_, SM_IDLE);
		}
		break;

	case SM_IDLE:
		{
			LED2_ON;
			LED1_OFF;
			if(testCount % 2000 == 0)
			SetState(pSelf_, SM_POSITONING);			
		}
		break;


	case SM_POSITONING:
		{
			LED2_OFF;
			LED1_ON;
			if(testCount % 3000 == 0)
			{
				SetState(pSelf_, SM_NOT_READY);	
				testCount = 0;
			}

		}
		break;

	case SM_FOLLOWING:
		{

		}
		break;

	case SM_PARKING:
		{

		}
		break;

	case SM_DRYRUNNING:
		{	

		}
		break;

	case SM_ERROR:
		{

		}

		break;

	default:
		break;
	}
}

void FollowController_Init(FollowController* pSelf_)
{

	InitFollowParam();
	FollowController_Reset(pSelf_);
}
void FollowController_Reset(FollowController* pSelf_)
{
	pSelf_->State = SM_NOT_READY;
	pSelf_->PreState = SM_NOT_READY;
	pSelf_->WarnState.nWorkState = 0;
	pSelf_->WarnState.nWarnState1 = 0;
	pSelf_->WarnState.nWarnState2 = 0;

	pSelf_->bPosTouchPanel = false;
	pSelf_->bFollowTouchPanel = false;
	pSelf_->bFloatCaliTouchPanel = false;
	pSelf_->bFollowEnable = false;
	pSelf_->bServoCalibEnable = false;
	pSelf_->bTouchParkEnable = false;
	pSelf_->bDetcetedCapSaltus = false;
	pSelf_->bZLimited = false;
	pSelf_->bDisConnect = false;
	pSelf_->bMachining = false;
	pSelf_->bUpdatePosTouchPanel = false;
	pSelf_->bEdgeParking = false;
	pSelf_->bPiercing = false;

	pSelf_->nParkingDurationT = 0;
	pSelf_->nCapSaltusWarnDurationT = 0;
	pSelf_->nMissPanelWarnDurationT = 0;
	pSelf_->nLimitedDownWarnDurationT = 0;
	pSelf_->nLimitedUpWarnDurationT = 0;

}

static void SetState(FollowController* pSelf_, SM_STATUS state_)
{
	pSelf_->State = state_;
}

