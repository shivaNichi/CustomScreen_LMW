#include "CPotManager.hpp"
#include "Common.h"

/************************************************************************************/
/* Initialize Screen parameters data structure										*/
/************************************************************************************/
PotInfo *pInfo = NULL;
tooldata tData;
/************************************************************************************/
/* Function - InitPotInfo															*/
/*																					*/
/* Purpose - Initialize Screen parameters data structure							*/
/************************************************************************************/
int InitPotInfo()
{
	pInfo = (PotInfo *)malloc(sizeof(PotInfo)); // allocating Dynamic memory to Screen parameters data structure	
	if(pInfo == NULL)							
	{
		return FALSE;
	}
	memset(pInfo ,0, sizeof(PotInfo));

	return TRUE;
}
/************************************************************************************/
/* Function - GetPotInfo															*/
/*																					*/
/* Purpose - Get Screen parameters data structure									*/
/************************************************************************************/
void GetPotInfo(PotInfo *pt)
{
	pt->usPotsPerPage = pInfo->usPotsPerPage;
	pt->usRemainPots = pInfo->usRemainPots;
	pt->usTotPages = pInfo->usTotPages;
	pt->usTotTool = pInfo->usTotTool;
	pt->usInitIndex[0] = pInfo->usInitIndex[0];
	pt->usInitIndex[1] = pInfo->usInitIndex[1];
	pt->usInitIndex[2] = pInfo->usInitIndex[2];
	pt->usPageNo = pInfo->usPageNo;
}
/************************************************************************************/
/* Function - SetPotInfo															*/
/*																					*/
/* Purpose - Set Screen parameters data structure									*/
/************************************************************************************/
void SetPotInfo(PotInfo *pt)
{
	pInfo->usPotsPerPage = pt->usPotsPerPage;
	pInfo->usRemainPots = pt->usRemainPots;
	pInfo->usTotPages = pt->usTotPages;
	pInfo->usTotTool = pt->usTotTool;
	pInfo->usInitIndex[0] = pt->usInitIndex[0];
	pInfo->usInitIndex[1] = pt->usInitIndex[1];
	pInfo->usInitIndex[2] = pt->usInitIndex[2];
	pInfo->usPageNo = pt->usPageNo;
}