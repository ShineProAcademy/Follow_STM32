#include "follow_para.h"

tParaManager FollowParaManager;

tParaManager* Get_FollowParaManager()
{
	return &FollowParaManager;
}

void InitFollowParam()
{
	tFollowPara *_pFollowParam = &Get_FollowParaManager()->para;
	
	_pFollowParam->nFollowKp = 2;
	_pFollowParam->nFollowKd = 0;
	
}