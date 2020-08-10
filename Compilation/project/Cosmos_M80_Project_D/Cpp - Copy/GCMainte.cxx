#include "GCMainte.hpp"
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

void GCIDeleteGCMainte( GBaseObject *pObject )
{
	GCMainte *pPanel = (GCMainte*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCMainte( GBaseObject *pObject )
{
	GCMainte *pPanel = new GCMainte;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCMainte;
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
GCMainte::GCMainte()
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
GCMainte::~GCMainte()
{

}

#include "GCMainte.prc"

short GCMainte::CreateChildren( )
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

GPropertyInfo* GCMainte::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}



long GCMainte::BACKUP_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	//ScreenTransition(EASY_BACKUP_SCREEN);
	return TRUE;
}

long GCMainte::DAILY_CHECK_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	///ScreenTransition(DAILY_MAINT_CHK_SCREEN);
	return TRUE;
}

long GCMainte::KEY_ACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;

	pChild = GCSGetChild(GetGBaseObject(), KEY_ACTION);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}
	Cursor_Pos = 0;
	Tab_Pos = -1;
	bCalcWindowOpened = false;
	//ReadIconStatus(0);
	ReadIconStatus();
	return TRUE;
}

long GCMainte::KEY_ACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
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
		case GK_F6:
					ScreenTransition(CUT_O_METER_SCREEN);
					break;
		case GK_F7:
					DisableButtonName();
					bCalcWindowOpened = true;
					GCSCreateGWindow(GCSGetScreen(GetGBaseObject()),CALCULATOR_WINDOW);
					break;
		case GK_F10:
					ScreenTransition(HOME_SCREEN);
					break;
		case GK_DOWN:	ClearWarningMessage();
					if(Tab_Pos == -1)
					{
						Tab_Pos = 0;
						Cursor_Pos = 1;
						SetCursor(Cursor_Pos);
					}
					else{
						switch(Tab_Pos)
						{
						case 0:	if(Cursor_Pos < 5){
										Cursor_Pos++;
								}
								else if(Cursor_Pos == 5){
										Cursor_Pos = 1;
										Tab_Pos = 0;
								}
								SetCursor(Cursor_Pos);
								break;
						}
					}
					break;
		case GK_UP:ClearWarningMessage();
					if(Tab_Pos == -1)
					{
						Tab_Pos = 0;
						Cursor_Pos = 5;
						SetCursor(Cursor_Pos);
					}
					else{
						switch(Tab_Pos)
						{
						case 0:	if(Cursor_Pos > 1){
										Cursor_Pos--;
								}
								else if(Cursor_Pos == 1){
										Cursor_Pos = 5;
										Tab_Pos = 0;
								}
								SetCursor(Cursor_Pos);
								break;
						}
					}
					break;
		case GK_RIGHT:ClearWarningMessage();
					if(Tab_Pos == -1)
					{
						Tab_Pos = 0;
						Cursor_Pos = 1;
						SetCursor(Cursor_Pos);
					}
					break;
		case GK_LEFT:ClearWarningMessage();
					if(Tab_Pos == -1)
					{
						Tab_Pos = 0;
						Cursor_Pos = 1;
						SetCursor(Cursor_Pos);
					}
					break;
		case GK_ESCAPE:
			Cursor_Pos = 0;
			Tab_Pos = -1;
			SetCursor(Cursor_Pos);
		case GK_RETURN:ClearWarningMessage();
			switch(Cursor_Pos)
			{
				/*case 1:ScreenTransition(DAILY_MAINT_CHK_SCREEN);
						break;
				case 2:ScreenTransition(MONTHLY_MAINT_CHK_SCREEN);
						break;
				case 3:ScreenTransition(QUATERLY_MAINT_CHK_SCREEN);
						break;
				case 4:ScreenTransition(PREVENTIVE_MAINT_CHK_SCREEN);
						break;
				case 5:ScreenTransition(EASY_BACKUP_SCREEN);
						break;*/
			}
			break;
		default:
			break;
	}
	return TRUE;
}

long GCMainte::KEY_ACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	pChild = GCSGetChild(GetGBaseObject(), KEY_ACTION);
		
	if(pChild != NULL && !bCalcWindowOpened)
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

long GCMainte::KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(!bCalcWindowOpened)
		ScreenTransition(HOME_SCREEN);
	else if(bCalcWindowOpened)
	{
		GBaseObject *pWindow, *pParent;

		pWindow = GCSGetWindow(GCSGetScreen(GetGBaseObject()), CALCULATOR_WINDOW + 1);

	
		if(pWindow)								// Closes Window
			GCSClose(pWindow);
		bCalcWindowOpened = false;
		EnableButtonName();
	}
	return TRUE;
}

long GCMainte::KEY_CALC_WINDOWOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(!bCalcWindowOpened){
		DisableButtonName();
		bCalcWindowOpened = true;
		GCSCreateGWindow(GCSGetScreen(GetGBaseObject()),CALCULATOR_WINDOW);
	}
	return TRUE;
}

long GCMainte::KEY_CUT_O_METEROnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(CUT_O_METER_SCREEN);
	return TRUE;
}

long GCMainte::KEY_DIAGNOSISOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(DIAGNOSIS_SCREEN);
	return TRUE;
}

long GCMainte::KEY_DURING_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(DURING_MACHINING_SCREEN);
	return TRUE;
}

long GCMainte::KEY_POST_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(POST_MACHINING_SCREEN);
	return TRUE;
}

long GCMainte::KEY_PRE_MACHININGOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(PRE_MACHINING_SCREEN);
	return TRUE;
}

long GCMainte::MONTHLY_CHECK_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	//ScreenTransition(MONTHLY_MAINT_CHK_SCREEN);
	return TRUE;
}

long GCMainte::PREVENT_CHECK_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	///ScreenTransition(PREVENTIVE_MAINT_CHK_SCREEN);
	return TRUE;
}

long GCMainte::QUATERLY_CHECK_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	//ScreenTransition(QUATERLY_MAINT_CHK_SCREEN);
	return TRUE;
}

void GCMainte::SetCursor(short cur_pos)
{
	GBaseObject *pTouchButton[13];
	//short position ;

	pTouchButton[0] = GCSGetChild(GetGBaseObject(), DAILY_CHECK_BUTTON);
	pTouchButton[1] = GCSGetChild(GetGBaseObject(), MONTHLY_CHECK_BUTTON);
	pTouchButton[2] = GCSGetChild(GetGBaseObject(), QUATERLY_CHECK_BUTTON);
	pTouchButton[3] = GCSGetChild(GetGBaseObject(), PREVENT_CHECK_BUTTON);
	pTouchButton[4] = GCSGetChild(GetGBaseObject(), BACKUP_BUTTON);
	

	if(cur_pos==0)
	{
		for(int i=1;i<=5;i++)
		{
			GCSButtonSetStatus(pTouchButton[i-1],GBTN_STATE_OFF);
		}
	}
	for(int i=1;i<=5;i++)
	{
		if(i==cur_pos)
		{
			GCSButtonSetStatus(pTouchButton[i-1],GBTN_STATE_ON);
		}
		else
		{
			GCSButtonSetStatus(pTouchButton[i-1],GBTN_STATE_OFF);
		}

	}
}


void GCMainte::ClearWarningMessage()
{
	GBaseObject *pLbl;
	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);
	GCSTextboxSetString(pLbl, (GTCHAR *)"");
}


void GCMainte::ScreenTransition(short ScreenNo)
{
	if(!bCalcWindowOpened){
		GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
	}
}


void GCMainte::DisableButtonName()
{
	GBaseObject *pKeyButton[10];

	pKeyButton[0] = GCSGetChild(GetGBaseObject(), KEY_DURING_MACHINING);
	pKeyButton[1] = GCSGetChild(GetGBaseObject(), KEY_POST_MACHINING);
	pKeyButton[2] = GCSGetChild(GetGBaseObject(), KEY_PRE_MACHINING);
	pKeyButton[3] = GCSGetChild(GetGBaseObject(), KEY_DIAGNOSIS);
	pKeyButton[4] = GCSGetChild(GetGBaseObject(), KEY_CUT_O_METER);
	pKeyButton[5] = GCSGetChild(GetGBaseObject(), KEY_CALC_WINDOW);
	pKeyButton[6] = GCSGetChild(GetGBaseObject(), KEY_BACK);

	//ID_STRING00214 = Close
	//ID_STRING01300 = Empty Spaces
	GCSButtonSetStringID(pKeyButton[0], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[1], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[2], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[3], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[4], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[5], ID_STRING01300);
	GCSButtonSetStringID(pKeyButton[6], ID_STRING00214);
}


/************************************************************************************/
/* Function - User																	*/
/*																					*/
/* Purpose - Invoked by GCSUser to communicate data/info between panel and window	*/
/************************************************************************************/
long GCMainte::User(long lLParam, long lUParam)
{
	switch(lLParam)
	{
		case 0:	bCalcWindowOpened = false;
				EnableButtonName();
				break;	
	}
	return TRUE;
}


void GCMainte::EnableButtonName()
{
	GBaseObject *pKeyButton[10];

	pKeyButton[0] = GCSGetChild(GetGBaseObject(), KEY_DURING_MACHINING);
	pKeyButton[1] = GCSGetChild(GetGBaseObject(), KEY_POST_MACHINING);
	pKeyButton[2] = GCSGetChild(GetGBaseObject(), KEY_PRE_MACHINING);
	pKeyButton[3] = GCSGetChild(GetGBaseObject(), KEY_DIAGNOSIS);
	pKeyButton[4] = GCSGetChild(GetGBaseObject(), KEY_CUT_O_METER);
	pKeyButton[5] = GCSGetChild(GetGBaseObject(), KEY_CALC_WINDOW);
	pKeyButton[6] = GCSGetChild(GetGBaseObject(), KEY_BACK);

	//ID_STRING00077 = KEY_PRE_MACHINING
	//ID_STRING00079 = KEY_DURING_MACHINING
	//ID_STRING00078 = KEY_POST_MACHINING
	//ID_STRING00090 = KEY_MAINTENANCE
	//ID_STRING00100 = KEY_CUT_O_METER
	//ID_STRING00176A = KEY_DIAGNOSIS
	//ID_STRING00165 = KEY_DOWNTIMEDATA
	//ID_STRING00023 = KEY_BACK

	GCSButtonSetStringID(pKeyButton[0], ID_STRING00079);
	GCSButtonSetStringID(pKeyButton[1], ID_STRING00078);
	GCSButtonSetStringID(pKeyButton[2], ID_STRING00077);
	GCSButtonSetStringID(pKeyButton[3], ID_STRING00176A);
	GCSButtonSetStringID(pKeyButton[4], ID_STRING00100);
	GCSButtonSetStringID(pKeyButton[5], ID_STRING00165);
	GCSButtonSetStringID(pKeyButton[6], ID_STRING00023);
}

//void GCHomeScreen1::ReadIconStatus(int i)
void GCMainte::ReadIconStatus()
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

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT(69),1, &sIconR69, T_SHORT); // To get the Data Protection StatusmelGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_X_1SHOT(3224),0, &sIconXC98, T_SHORT); // To get the Data Protection Status
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
		GCSPictureSetStatus(pIconPicture,1);
	}
	else if(sIconXC99!=0)
	{
		GCSPictureSetStatus(pIconPicture,1);
	}
	else if(sIconXC9A!=0)
	{
		GCSPictureSetStatus(pIconPicture,1);
	}
	else if(sIconXC9B!=0)
	{
		GCSPictureSetStatus(pIconPicture,1);
	}
	else if(sIconXC9C!=0)
	{
		GCSPictureSetStatus(pIconPicture,1);
	}
	else if(sIconX1886!=0)
	{
		GCSPictureSetStatus(pIconPicture,1);
	}
	else if(sIconM9101!=0)
	{
		GCSPictureSetStatus(pIconPicture,1);
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



/*******************************************************************************************/
/* Function - setWarningMessage														       */
/*																						   */
/* Purpose - To display warning message on screen				 						   */
/*******************************************************************************************/
void GCMainte::SetWarningMessage(int warnnum)
{
	GBaseObject *pLbl;
	GTCHAR szText[WARN_MSG_DATA_SIZE];

	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);	
	
	if(warnnum == UNDER_DEVELOPMENT_ERROR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "The Screen is Under Development",	sizeof(szText)/sizeof(GTCHAR));
	
	GCSTextboxSetString( pLbl, szText );
}
