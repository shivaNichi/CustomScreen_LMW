#include "GCHomeScreen1.hpp"
#include "GCBasicControl.hpp"
#include "GCButton.hpp"
#include "GCCheckBox.hpp"
#include "GCLabel.hpp"
#include "GCList.hpp"
#include "GCPicture.hpp"
#include "GCProgressBar.hpp"
#include "GCRadioButton.hpp"
#include "GCTextBox.hpp"
#include "GCSampleScreen.hpp"
#include "GEvent.h"
#include "GResource.h"
#include "Common.h"


extern "C"
{

void GCIDeleteGCHomeScreen1( GBaseObject *pObject )
{
	GCHomeScreen1 *pPanel = (GCHomeScreen1*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCHomeScreen1( GBaseObject *pObject )
{
	GCHomeScreen1 *pPanel = new GCHomeScreen1;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCHomeScreen1;
	pPanel->SetGBaseObject( pObject );
	return TRUE;
}
}
/*
 *	<summary>		:	コンストラクタ。
 *
 *	<parameter>		:	なし
 *
 *	<return>		:	なし
 *
 *	<description>	:	コンストラクタ
 */
GCHomeScreen1::GCHomeScreen1()
{
}

/*
 *	<summary>		:	デストラクタ。
 *
 *	<parameter>		:	なし
 *
 *	<return>		:	なし
 *
 *	<description>	:	デストラクタ
 */
GCHomeScreen1::~GCHomeScreen1()
{

}

#include "GCHomeScreen1.prc"

short GCHomeScreen1::CreateChildren( )
{
	GBaseObject *pChild;

	unsigned int i;
	for( i = 1; i < sizeof(pProperty)/sizeof(GBaseWindowProperty*); i++ ){
		pChild = GCSCreateInstance( GCSGetScreen( m_pSelf ),
							pProperty[i]->usType, pProperty[i], GetGBaseObject() );
		if( pChild ){
			AddChild( pChild );
			GCSCreate( pChild, GetGBaseObject() );
		}
	}
	return TRUE;
}

GPropertyInfo* GCHomeScreen1::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}



long GCHomeScreen1::CUT_O_METEROnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(CUT_O_METER_SCREEN);
	return TRUE;
}

long GCHomeScreen1::DIAGNOSISOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(DIAGNOSIS_SCREEN);
	return TRUE;
}

long GCHomeScreen1::DURING_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(DURING_MACHINING_SCREEN);
	return TRUE;
}

long GCHomeScreen1::KEY_CUT_O_METEROnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(CUT_O_METER_SCREEN);
	return TRUE;
}

long GCHomeScreen1::KEY_DIAGNOSISOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(DIAGNOSIS_SCREEN);
	return TRUE;
}

long GCHomeScreen1::KEY_DOWNTIMEDATAOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(!bDownTimeDataWindowOpened){
		DisableButtonName();
		GCSCreateGWindow(GCSGetScreen(GetGBaseObject()),DOWNTIME_DATA_WINDOW);
		bDownTimeDataWindowOpened = true;
	}
	return TRUE;
}

long GCHomeScreen1::KEY_DURING_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(DURING_MACHINING_SCREEN);
	return TRUE;
}

long GCHomeScreen1::KEY_EXITOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(!bDownTimeDataWindowOpened)
		ScreenTransition(HMI_SCREEN);
	else
	{
		GBaseObject *pWindow, *pParent;

		pWindow = GCSGetWindow(GCSGetScreen(GetGBaseObject()), DOWNTIME_DATA_WINDOW + 1);

	
		if(pWindow)								// Closes Window
			GCSClose(pWindow);
		bDownTimeDataWindowOpened = false;
		EnableButtonName();
	}
	return TRUE;
}

long GCHomeScreen1::KEY_MAINTENANCEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(MAINTENANCE1_SCREEN);
	return TRUE;
}

long GCHomeScreen1::KEY_POST_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(POST_MACHINING_SCREEN);
	return TRUE;
}

long GCHomeScreen1::KEY_PRE_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(PRE_MACHINING_SCREEN);
	return TRUE;
}

long GCHomeScreen1::MAINTENANCEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(MAINTENANCE1_SCREEN);
	return TRUE;
}

long GCHomeScreen1::POST_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(POST_MACHINING_SCREEN);
	return TRUE;
}

long GCHomeScreen1::PRE_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(PRE_MACHINING_SCREEN);
	return TRUE;
}

long GCHomeScreen1::KEY_ACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;

	pChild = GCSGetChild(GetGBaseObject(), KEY_ACTION);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}

	//Initlization of tool type 
	
	sToolTypeArray[0] = ID_STRING01350;
	sToolTypeArray[1] = ID_STRING01351;
	sToolTypeArray[2] = ID_STRING01352;
	sToolTypeArray[3] = ID_STRING01353;
	sToolTypeArray[4] = ID_STRING01354;
	sToolTypeArray[5] = ID_STRING01355;
	sToolTypeArray[6] = ID_STRING01356;
	sToolTypeArray[7] = ID_STRING01357;
	sToolTypeArray[8] = ID_STRING01358;
	sToolTypeArray[9] = ID_STRING01359;
	sToolTypeArray[10] = ID_STRING01360;
	sToolTypeArray[11] = ID_STRING01361;
	sToolTypeArray[12] = ID_STRING01362;
	sToolTypeArray[13] = ID_STRING01363;

	Cursor_Pos = 0;
	bDownTimeDataWindowOpened = false;
	//ReadIconStatus(0);
	ReadIconStatus();
	ReadProgressBarStatus();
	
	return TRUE;
}

long GCHomeScreen1::KEY_ACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	GTCHAR inpBuff[10];
	char sData[10];
	int Scount = 0;
	short sEditPermit = 0;			// To store the edit permition y708

	pChild = GCSGetChild(GetGBaseObject(), KEY_ACTION);

	switch(lLParam)
	{
	case GK_F1:
		ScreenTransition(PRE_MACHINING_SCREEN);
		break;
	case GK_F2:
		ScreenTransition(DURING_MACHINING_SCREEN);
		break;
	case GK_F3:
		ScreenTransition(POST_MACHINING_SCREEN);
		break;
	case GK_F4:
		ScreenTransition(DIAGNOSIS_SCREEN);
		break;
	case GK_F5:
		ScreenTransition(MAINTENANCE1_SCREEN);
		break;
	case GK_F6:
		ScreenTransition(CUT_O_METER_SCREEN);
		break;
	case GK_F8:
		DisableButtonName();
		bDownTimeDataWindowOpened = true;
		GCSCreateGWindow(GCSGetScreen(GetGBaseObject()),DOWNTIME_DATA_WINDOW);
		break;
	case GK_F10:
		ScreenTransition(HMI_SCREEN);
		break;
	case GK_DOWN:ClearWarningMessage();
		if(Cursor_Pos < 6){
				Cursor_Pos++;
		}
		else if(Cursor_Pos == 6){
				Cursor_Pos = 1;
		}
		SetCursor(Cursor_Pos);
		break;
	case GK_UP:ClearWarningMessage();
		if(Cursor_Pos > 1){
				Cursor_Pos--;
		}
		else if(Cursor_Pos == 1){
				Cursor_Pos=6;
		}
		else if(Cursor_Pos==0)
		{
			Cursor_Pos=6;
		}
		SetCursor(Cursor_Pos);
		break;
	case GK_ESCAPE:
		Cursor_Pos = 0;
		SetCursor(Cursor_Pos);
	case GK_RETURN:ClearWarningMessage();
		switch(Cursor_Pos)
		{
			case 1:ScreenTransition(PRE_MACHINING_SCREEN);
					break;
			case 2:ScreenTransition(DURING_MACHINING_SCREEN);
					break;
			case 3:ScreenTransition(POST_MACHINING_SCREEN);
					break;
			case 4:ScreenTransition(DIAGNOSIS_SCREEN);
					break;
			case 5:ScreenTransition(MAINTENANCE1_SCREEN);
					break;
			case 6:ScreenTransition(CUT_O_METER_SCREEN);
					break;
		}
		break;
	default:
		break;
	}
	return TRUE;

}

long GCHomeScreen1::KEY_ACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	pChild = GCSGetChild(GetGBaseObject(), KEY_ACTION);
		
	if(pChild != NULL && !bDownTimeDataWindowOpened)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}
	

	static int nCounter;
	//static int i = 0;
	nCounter++;
	if(nCounter >=100) {
		//ReadIconStatus(i++);
		/*	if(i>7)
				i = 0;*/
		ReadIconStatus();
		nCounter = 0;
	}

	return TRUE;
}


void GCHomeScreen1::SetCursor(short cur_pos)
{
	GBaseObject *pTouchButton[6],*pKeyButton[6];
	//short position ;

	pTouchButton[0] = GCSGetChild(GetGBaseObject(), PRE_MACHINING);
	pTouchButton[1] = GCSGetChild(GetGBaseObject(), DURING_MACHINING);
	pTouchButton[2] = GCSGetChild(GetGBaseObject(), POST_MACHINING);
	pTouchButton[3] = GCSGetChild(GetGBaseObject(), DIAGNOSIS);
	pTouchButton[4] = GCSGetChild(GetGBaseObject(), MAINTENANCE);
	pTouchButton[5] = GCSGetChild(GetGBaseObject(), CUT_O_METER);

	pKeyButton[0] = GCSGetChild(GetGBaseObject(), KEY_PRE_MACHINING);
	pKeyButton[1] = GCSGetChild(GetGBaseObject(), KEY_DURING_MACHINING);
	pKeyButton[2] = GCSGetChild(GetGBaseObject(), KEY_POST_MACHINING);
	pKeyButton[3] = GCSGetChild(GetGBaseObject(), KEY_DIAGNOSIS);
	pKeyButton[4] = GCSGetChild(GetGBaseObject(), KEY_MAINTENANCE);
	pKeyButton[5] = GCSGetChild(GetGBaseObject(), KEY_CUT_O_METER);
	//position = cur_pos % GEAR1_TXTBOX;
	switch(cur_pos)
	{
	case 0:
		GCSButtonSetStatus(pTouchButton[0],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[1],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[2],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[3],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[4],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[5],GBTN_STATE_OFF);

		GCSButtonSetStatus(pKeyButton[0],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[1],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[2],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[3],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[4],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[5],GBTN_STATE_OFF);
		break;
	case 1:
		GCSButtonSetStatus(pTouchButton[0],GBTN_STATE_ON);
		GCSButtonSetStatus(pTouchButton[1],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[2],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[3],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[4],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[5],GBTN_STATE_OFF);

		GCSButtonSetStatus(pKeyButton[0],GBTN_STATE_ON);
		GCSButtonSetStatus(pKeyButton[1],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[2],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[3],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[4],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[5],GBTN_STATE_OFF);
		break;
	case 2:
		GCSButtonSetStatus(pTouchButton[0],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[1],GBTN_STATE_ON);
		GCSButtonSetStatus(pTouchButton[2],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[3],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[4],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[5],GBTN_STATE_OFF);

		GCSButtonSetStatus(pKeyButton[0],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[1],GBTN_STATE_ON);
		GCSButtonSetStatus(pKeyButton[2],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[3],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[4],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[5],GBTN_STATE_OFF);
		break;
	case 3:
		GCSButtonSetStatus(pTouchButton[0],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[1],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[2],GBTN_STATE_ON);
		GCSButtonSetStatus(pTouchButton[3],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[4],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[5],GBTN_STATE_OFF);

		GCSButtonSetStatus(pKeyButton[0],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[1],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[2],GBTN_STATE_ON);
		GCSButtonSetStatus(pKeyButton[3],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[4],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[5],GBTN_STATE_OFF);
		break;
	case 4:
		GCSButtonSetStatus(pTouchButton[0],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[1],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[2],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[3],GBTN_STATE_ON);
		GCSButtonSetStatus(pTouchButton[4],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[5],GBTN_STATE_OFF);

		GCSButtonSetStatus(pKeyButton[0],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[1],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[2],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[3],GBTN_STATE_ON);
		GCSButtonSetStatus(pKeyButton[4],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[5],GBTN_STATE_OFF);
		break;
	case 5:
		GCSButtonSetStatus(pTouchButton[0],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[1],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[2],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[3],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[4],GBTN_STATE_ON);
		GCSButtonSetStatus(pTouchButton[5],GBTN_STATE_OFF);

		GCSButtonSetStatus(pKeyButton[0],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[1],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[2],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[3],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[4],GBTN_STATE_ON);
		GCSButtonSetStatus(pKeyButton[5],GBTN_STATE_OFF);
		break;
	case 6:
		GCSButtonSetStatus(pTouchButton[0],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[1],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[2],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[3],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[4],GBTN_STATE_OFF);
		GCSButtonSetStatus(pTouchButton[5],GBTN_STATE_ON);

		GCSButtonSetStatus(pKeyButton[0],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[1],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[2],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[3],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[4],GBTN_STATE_OFF);
		GCSButtonSetStatus(pKeyButton[5],GBTN_STATE_ON);
		break;
	default:
		break;
	}
}


void GCHomeScreen1::ClearWarningMessage()
{
	GBaseObject *pLbl;
	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);
	GCSTextboxSetString(pLbl, (GTCHAR *)"");
}


void GCHomeScreen1::ScreenTransition(short ScreenNo)
{
	if(!bDownTimeDataWindowOpened)
		GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
}


void GCHomeScreen1::DisableButtonName()
{
	GBaseObject *pKeyButton[10];

	pKeyButton[0] = GCSGetChild(GetGBaseObject(), KEY_PRE_MACHINING);
	pKeyButton[1] = GCSGetChild(GetGBaseObject(), KEY_DURING_MACHINING);
	pKeyButton[2] = GCSGetChild(GetGBaseObject(), KEY_POST_MACHINING);
	pKeyButton[3] = GCSGetChild(GetGBaseObject(), KEY_DIAGNOSIS);
	pKeyButton[4] = GCSGetChild(GetGBaseObject(), KEY_MAINTENANCE);
	pKeyButton[5] = GCSGetChild(GetGBaseObject(), KEY_CUT_O_METER);
	pKeyButton[6] = GCSGetChild(GetGBaseObject(), KEY_DOWNTIMEDATA);
	pKeyButton[7] = GCSGetChild(GetGBaseObject(), KEY_EXIT);

	//ID_STRING00214 = Close
	//ID_STRING01300 = Empty Spaces
	GCSButtonSetStringID(pKeyButton[0], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[1], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[2], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[3], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[4], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[5], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[6], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[7], ID_STRING00214);
}


/************************************************************************************/
/* Function - User																	*/
/*																					*/
/* Purpose - Invoked by GCSUser to communicate data/info between panel and window	*/
/************************************************************************************/
long GCHomeScreen1::User(long lLParam, long lUParam)
{
	switch(lLParam)
	{
		case 0:	bDownTimeDataWindowOpened = false;
				EnableButtonName();
				break;	
	}
	return TRUE;
}


void GCHomeScreen1::EnableButtonName()
{
	GBaseObject *pKeyButton[10];

	pKeyButton[0] = GCSGetChild(GetGBaseObject(), KEY_PRE_MACHINING);
	pKeyButton[1] = GCSGetChild(GetGBaseObject(), KEY_DURING_MACHINING);
	pKeyButton[2] = GCSGetChild(GetGBaseObject(), KEY_POST_MACHINING);
	pKeyButton[3] = GCSGetChild(GetGBaseObject(), KEY_DIAGNOSIS);
	pKeyButton[4] = GCSGetChild(GetGBaseObject(), KEY_MAINTENANCE);
	pKeyButton[5] = GCSGetChild(GetGBaseObject(), KEY_CUT_O_METER);
	pKeyButton[6] = GCSGetChild(GetGBaseObject(), KEY_DOWNTIMEDATA);
	pKeyButton[7] = GCSGetChild(GetGBaseObject(), KEY_EXIT);

	//ID_STRING00077 = KEY_PRE_MACHINING
	//ID_STRING00079 = KEY_DURING_MACHINING
	//ID_STRING00078 = KEY_POST_MACHINING
	//ID_STRING00090 = KEY_MAINTENANCE
	//ID_STRING00100 = KEY_CUT_O_METER
	//ID_STRING00176A = KEY_DIAGNOSIS
	//ID_STRING00213 = KEY_DOWNTIMEDATA
	//ID_STRING00041 = KEY_EXIT

	GCSButtonSetStringID(pKeyButton[0], ID_STRING00077);
	GCSButtonSetStringID(pKeyButton[1], ID_STRING00079);
	GCSButtonSetStringID(pKeyButton[2], ID_STRING00078);
	GCSButtonSetStringID(pKeyButton[3], ID_STRING00176A);
	GCSButtonSetStringID(pKeyButton[4], ID_STRING00090);
	GCSButtonSetStringID(pKeyButton[5], ID_STRING00100);
	GCSButtonSetStringID(pKeyButton[6], ID_STRING00213);
	GCSButtonSetStringID(pKeyButton[7], ID_STRING00041);
}

//void GCHomeScreen1::ReadIconStatus(int i)
void GCHomeScreen1::ReadIconStatus()
{
	//ICON 1
	GBaseObject *pIconPicture;
	short sIconJogMode = 0;
	short sIconHandleMode = 0;
	short sIconIncMode = 0;
	short sIconZrnMode = 0;
	short sIconMemMode = 0;
	short sIconMdiMode = 0;
	short sIconRpdMode = 0;

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3072),0, &sIconJogMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3073),0, &sIconHandleMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3074),0, &sIconIncMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3076),0, &sIconZrnMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3080),0, &sIconMemMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3083),0, &sIconMdiMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(30110),0, &sIconRpdMode, T_SHORT); // To get the Data Protection Status
	
	pIconPicture = GCSGetChild(GetGBaseObject(), ICON1);

	if(sIconJogMode !=0)
	{	
		if(sIconRpdMode!=0)
		{
			GCSPictureSetStatus( pIconPicture,2);
		}
		else
		{
			GCSPictureSetStatus( pIconPicture,3);
		}
	}	
	else if(sIconHandleMode !=0)
	{	
		GCSPictureSetStatus( pIconPicture,6);	
	}	
	else if(sIconIncMode !=0)
	{	
		GCSPictureSetStatus( pIconPicture,4);	
	}
	else if(sIconZrnMode !=0)
	{	
		GCSPictureSetStatus( pIconPicture,5);	
	}	
	else if(sIconMemMode !=0)
	{	
		GCSPictureSetStatus( pIconPicture,1);	
	}
	else if(sIconMdiMode !=0)
	{	
		GCSPictureSetStatus( pIconPicture,0);	
	}	
	else if(sIconRpdMode !=0)
	{	
		GCSPictureSetStatus( pIconPicture,2);	
	}
	/*else
	{	
			GCSPictureSetStatus( pIconPicture,i);
	}	*/


	//ICON 2
	short sIconKey = 0;
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(1800),0, &sIconKey, T_SHORT); // To get the Data Protection Status
	pIconPicture = GCSGetChild(GetGBaseObject(), ICON2);
	if(sIconKey !=0)
	{	
		GCSSetVisibleStatus(pIconPicture,1);
		GCSPictureSetStatus( pIconPicture,0);	
	}
	else
	{
		GCSSetVisibleStatus(pIconPicture,0);
	}

	
	//ICON 3
	short sIconLube = 0;
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(592),0, &sIconLube, T_SHORT); // To get the Data Protection Status
	pIconPicture = GCSGetChild(GetGBaseObject(), ICON3);
	if(sIconLube !=0)
	{	
		GCSPictureSetStatus( pIconPicture,0);	
	}
	else
	{
		GCSPictureSetStatus(pIconPicture,1);
	}

	//ICON 4
	short sIconManual = 0;
	short sIconAuto = 0;
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_M_1SHOT(9103),0, &sIconManual, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_M_1SHOT(9104),0, &sIconAuto, T_SHORT); // To get the Data Protection Status
	pIconPicture = GCSGetChild(GetGBaseObject(), ICON4);
	GCSSetVisibleStatus(pIconPicture,1);
	if(sIconManual !=0)
	{	
		GCSPictureSetStatus(pIconPicture,0);	
	}
	else if(sIconAuto!=0)
	{
		GCSPictureSetStatus(pIconPicture,1);
	}
	else
	{
		GCSSetVisibleStatus(pIconPicture,0);
	}

	//ICON 5
	short sIconR69 = 0;
	short sIconXC98 = 0;
	short sIconXC99 = 0;
	short sIconXC9A = 0;
	short sIconXC9B = 0;
	short sIconXC9C = 0;
	short sIconX1886 = 0;
	short sIconM9101 = 0;

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT(69),1, &sIconR69, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_X_1SHOT(3224),0, &sIconXC98, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_X_1SHOT(3225),0, &sIconXC99, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_X_1SHOT(3226),0, &sIconXC9A, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_X_1SHOT(3227),0, &sIconXC9B, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_X_1SHOT(3228),0, &sIconXC9C, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_X_1SHOT(6278),0, &sIconX1886, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_M_1SHOT(9101),0, &sIconM9101, T_SHORT); // To get the Data Protection Status


	pIconPicture = GCSGetChild(GetGBaseObject(), ICON5);
	
	if(sIconR69 !=0)
	{	
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else if(sIconXC98!=0)
	{
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else if(sIconXC99!=0)
	{
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else if(sIconXC9A!=0)
	{
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else if(sIconXC9B!=0)
	{
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else if(sIconXC9C!=0)
	{
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else if(sIconX1886!=0)
	{
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else if(sIconM9101!=0)
	{
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else
	{
		GCSSetVisibleStatus(pIconPicture,0);
	}

	//ICON 6
	short sIconY1898 = 0;
	short sIconY1899 = 0;
	short sIconY189E = 0;

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(37123),0, &sIconY1898, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3224),0, &sIconY1899, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3225),0, &sIconY189E, T_SHORT); // To get the Data Protection Status
	

	pIconPicture = GCSGetChild(GetGBaseObject(), ICON6);
	
	if(sIconY1898 !=0)
	{	
		GCSPictureSetStatus(pIconPicture,0);
	}
	else if(sIconY1899!=0)
	{
		GCSPictureSetStatus(pIconPicture,1);
	}
	else if(sIconY189E!=0)
	{
		GCSPictureSetStatus(pIconPicture,3);
	}
	else
	{
		GCSPictureSetStatus(pIconPicture,2);
	}

	//ICON 7
	short sIconM9102 = 0;

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_M_1SHOT(9102),0, &sIconM9102, T_SHORT); // To get the Data Protection Status
	
	pIconPicture = GCSGetChild(GetGBaseObject(), ICON7);
	
	if(sIconM9102 !=0)
	{	
		GCSSetVisibleStatus(pIconPicture,1);
	}
	else
	{
		GCSSetVisibleStatus(pIconPicture,1);
	}
}


void GCHomeScreen1::ReadProgressBarStatus()
{
	GBaseObject *pProgressBar;
	short sPrgStatus = 0;
	double sSetPartCount = 0;
	double sCurrentPartCount = 0;
	double sPartCount = 0;
	double sSetToolLife = 0;
	double sCurrentToolLife = 0;
	double sToolLife = 0;
    short sToolType = 0;

	short sTolerancePValue = 0;
	short sToleranceQValue = 0;
	short sToleranceManualValue = 0;
	short sToleranceLevel = 0;

	short sXValue = 0;
	short sYValue = 0;
	short sZValue = 0;
	short s5thValue = 0;
	short s4thValue = 0;
	short sSPValue = 0;

	double sProgData;

	//for Updating the Progress of Prg Status
	pProgressBar = GCSGetChild(GetGBaseObject(), PRG_STATUS);

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PRG_EXEC_STAT, M_SSEC_PGST_ACT_MAIN_PER,0, &sPrgStatus, T_SHORT); // To get the Data Protection Status
	
	if(sPrgStatus>=0)
	{
		GCSProgressbarSetValue(pProgressBar,sPrgStatus);
	}

	//for Updating the Progress of Part Count
	pProgressBar = GCSGetChild(GetGBaseObject(), PART_COUNT);

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_BASEPRM, M_SSEC_BASEPRM_WCOUNT,0, &sCurrentPartCount , T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_BASEPRM, M_SSEC_BASEPRM_WCOUNTMAX,0, &sSetPartCount, T_SHORT); // To get the Data Protection Status
	
	if(sSetPartCount!=0){
		sPartCount =  (sCurrentPartCount/sSetPartCount)*100.00;
		if(sPartCount>=0)
		{
			sProgData = abs(sPartCount);
			GCSProgressbarSetValue(pProgressBar,sProgData);
		}
	}


	//for Updating the Progress of Tool Life
	pProgressBar = GCSGetChild(GetGBaseObject(), TOOL_LIFE);

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT(11834),0, &sSetToolLife, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT(11835),0, &sCurrentToolLife, T_SHORT); // To get the Data Protection Status
	
	if(sSetToolLife!=0){
		sToolLife =  (sCurrentToolLife/sSetToolLife)*100.00;
		if(sToolLife>=0)
		{
			sProgData = abs(sToolLife);
			GCSProgressbarSetValue(pProgressBar,sProgData);
		}
	}

	//need to Add for T and DRILL
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT(10620),1, &sToolType, T_SHORT); // To get the Data Protection Status
	if(sToolType!=0 && sToolType<=14)
	{
		GBaseObject *pToolType;
		pToolType = GCSGetChild(GetGBaseObject(), TOOL_LIFE_TOOL_NAME);
		/*if(sToolType==1)
			GCSLabelSetStringID(pToolType, ID_STRING01350);
		else*/
			GCSLabelSetStringID(pToolType, sToolTypeArray[sToolType-1]);

	}
	else{
		GBaseObject *pToolType;
		pToolType = GCSGetChild(GetGBaseObject(), TOOL_LIFE_TOOL_NAME);
		GCSLabelSetStringID(pToolType, ID_STRING01300);
	}

	//for Updating the Progress of Tolerance Level
	pProgressBar = GCSGetChild(GetGBaseObject(), TOLERANCE_BAR);

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_G_MODAL, M_SSEC_GMDL_MAC_APPLICATION,0, &sTolerancePValue, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_G_MODAL, M_SSEC_GMDL_MAC_ACC_LV,0, &sToleranceQValue, T_SHORT); // To get the Data Protection Status
	
	if(sTolerancePValue!=0 && sToleranceQValue!=0)
	{
		if(sTolerancePValue==1)
		{
			switch(sToleranceQValue)
			{
			case 1:
				sToleranceLevel =1;
				break;
			case 2:
				sToleranceLevel =2;
				break;
			case 3:
				sToleranceLevel =3;
				break;
			}
		}
		else if(sTolerancePValue==2)
		{
			switch(sToleranceQValue)
			{
			case 1:
				sToleranceLevel =4;
				break;
			case 2:
				sToleranceLevel =6;
				break;
			case 3:
				sToleranceLevel =7;
				break;
			}
		}
		else if(sTolerancePValue==3)
		{
			switch(sToleranceQValue)
			{
			case 1:
				sToleranceLevel =8;
				break;
			case 2:
				sToleranceLevel =9;
				break;
			case 3:
				sToleranceLevel =10;
				break;
			}
		}
		sToleranceLevel = 10 - sToleranceLevel;
		GCSProgressbarSetValue(pProgressBar,sToleranceLevel);
	}
	else if(sTolerancePValue==0 && sToleranceQValue==0)
	{
		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MPRM_PLC_CONST, M_SSEC_MP_PLC_CONST(101),0, &sToleranceManualValue, T_SHORT); // To get the Data Protection Status
		if(sToleranceManualValue!=0){
			sToleranceLevel = sToleranceManualValue;
			sToleranceLevel = 10 - sToleranceLevel;
			GCSProgressbarSetValue(pProgressBar,sToleranceLevel);
		}
	}

	//for Updating the Progress of X value
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MON_SV, M_SSEC_MSV_CURRENT,1, &sXValue, T_SHORT); // To get the Data Protection Status
	sProgData = abs(sXValue);
	sXValue = sProgData;
	if(sXValue>=0 && sXValue<=60)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), X_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,sXValue);
	}
	else if(sXValue>=61 && sXValue<=80)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), X_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), X_YELLOW_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,sXValue);
	}
	else if(sXValue>=81 && sXValue<=120)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), X_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), X_YELLOW_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,80);

		pProgressBar = GCSGetChild(GetGBaseObject(), X_RED_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,sXValue);
	}

	//for Updating the Progress of Y value
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MON_SV, M_SSEC_MSV_CURRENT,2, &sYValue, T_SHORT); // To get the Data Protection Status
	sProgData = abs(sYValue);
	sYValue = sProgData;
	if(sYValue>=0 && sYValue<=60)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), Y_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,sYValue);
	}
	else if(sYValue>=61 && sYValue<=80)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), Y_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), Y_YELLOW_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,sYValue);
	}
	else if(sYValue>=81 && sYValue<=120)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), Y_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), Y_YELLOW_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,80);

		pProgressBar = GCSGetChild(GetGBaseObject(), Y_RED_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,sYValue);
	}

	//for Updating the Progress of Z value
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MON_SV, M_SSEC_MSV_CURRENT,3, &sZValue, T_SHORT); // To get the Data Protection Status
	sProgData = abs(sZValue);
	sZValue = sProgData;
	if(sZValue>=0 && sZValue<=60)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), Z_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,sZValue);
	}
	else if(sZValue>=61 && sZValue<=80)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), Z_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), Z_YELLOW_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,sZValue);
	}
	else if(sZValue>=81 && sZValue<=120)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), Z_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), Z_YELLOW_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,80);

		pProgressBar = GCSGetChild(GetGBaseObject(), Z_RED_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,sZValue);
	}

	//for Updating the Progress of 4th value
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MON_SV, M_SSEC_MSV_CURRENT,4, &s4thValue, T_SHORT); // To get the Data Protection Status
	sProgData = abs(s4thValue);
	s4thValue = sProgData;
	if(s4thValue>=0 && s4thValue<=60)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), FOURTH_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,s4thValue);
	}
	else if(s4thValue>=61 && s4thValue<=80)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), FOURTH_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), FOURTH_YELLOW_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,s4thValue);
	}
	else if(s4thValue>=81 && s4thValue<=120)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), FOURTH_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), FOURTH_YELLOW_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,80);

		pProgressBar = GCSGetChild(GetGBaseObject(), FOURTH_RED_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,s4thValue);
	}

	//for Updating the Progress of 5th value
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MON_SV, M_SSEC_MSV_CURRENT,5, &s4thValue, T_SHORT); // To get the Data Protection Status
	sProgData = abs(s5thValue);
	s5thValue = sProgData;
	if(s5thValue>=0 && s5thValue<=60)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), FIFTH_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,s5thValue);
	}
	else if(s5thValue>=61 && s5thValue<=80)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), FIFTH_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), FIFTH_YELLOW_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,s5thValue);
	}
	else if(s5thValue>=81 && s5thValue<=120)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), FIFTH_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), FIFTH_YELLOW_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,80);

		pProgressBar = GCSGetChild(GetGBaseObject(), FIFTH_RED_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,s5thValue);
	}

	//for Updating the Progress of SP value
	//63/4/1
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MON_SP, M_SSEC_MSP_LOAD,1, &sSPValue, T_SHORT); // To get the Data Protection Status
	sProgData = abs(sSPValue);
	sSPValue = sProgData;
	if(sSPValue>=0 && sSPValue<=60)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), SP_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,sSPValue);
	}
	else if(sSPValue>=61 && sSPValue<=80)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), SP_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), SP_YELLOW_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,sSPValue);
	}
	else if(sSPValue>=81 && sSPValue<=120)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), SP_GREEN_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), SP_YELLOW_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,80);

		pProgressBar = GCSGetChild(GetGBaseObject(), SP_RED_PROGRESS);
		GCSProgressbarSetValue(pProgressBar,sSPValue);
	}
}
