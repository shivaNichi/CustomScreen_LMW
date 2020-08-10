#include "GCMcode.hpp"
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

void GCIDeleteGCMcode( GBaseObject *pObject )
{
	GCMcode *pPanel = (GCMcode*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCMcode( GBaseObject *pObject )
{
	GCMcode *pPanel = new GCMcode;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCMcode;
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
GCMcode::GCMcode()
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
GCMcode::~GCMcode()
{

}

#include "GCMcode.prc"

short GCMcode::CreateChildren( )
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

GPropertyInfo* GCMcode::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}



long GCMcode::KEY_ACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam)
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
	ReadIconStatus();
	return TRUE;
}

long GCMcode::KEY_ACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	GTCHAR inpBuff[10];
	char sData[10];
	int Scount = 0;
	short sEditPermit = 0;			// To store the edit permition y708

	pChild = GCSGetChild(GetGBaseObject(), KEY_ACTION);

	GBaseObject *pChildHTML;
	pChildHTML = GCSGetChild(GetGBaseObject(), HTML_OBJECT);

	short value = 0;

	switch(lLParam)
	{
		case GK_F1:
					if(!(((lUParam & KEY_SHIFT) != KEY_SHIFT) && ((lUParam & KEY_SEC) != KEY_SEC))){
							break;
					}
					ScreenTransition(GCODE_SCREEN);
					break;
		case GK_F2:
					if(!(((lUParam & KEY_SHIFT) != KEY_SHIFT) && ((lUParam & KEY_SEC) != KEY_SEC)))
					{
					   break;
					}
					ScreenTransition(CUTTING_PARAMETERS_SCREEN);
					break;
		case GK_F3:
					if(!(((lUParam & KEY_SHIFT) != KEY_SHIFT) && ((lUParam & KEY_SEC) != KEY_SEC)))
					{
						break;
					}
					ScreenTransition(MAGAZINE_LIST_SCREEN);
					break;
		case GK_F4:
					if(!(((lUParam & KEY_SHIFT) != KEY_SHIFT) && ((lUParam & KEY_SEC) != KEY_SEC)))
					{
						break;
					}
					SetWarningMessage(UNDER_DEVELOPMENT_ERROR);
					break;
		case GK_F5:
					if(!(((lUParam & KEY_SHIFT) != KEY_SHIFT) && ((lUParam & KEY_SEC) != KEY_SEC)))
					{
						break;
					}
					//ScreenTransition(MACHINE_COND_SELECTION_SCREEN);
					break;
		case GK_F6:
					sParentScreen = MCODE_SCREEN;
					ScreenTransition(CUT_O_METER_SCREEN);
					break;
		case GK_F7:
					DisableButtonName();
					bCalcWindowOpened = true;
					GCSCreateGWindow(GCSGetScreen(GetGBaseObject()),CALCULATOR_WINDOW);
					break;
		case GK_F10:
					if( (lUParam & KEY_BITALL) != 0){
						break;
					}
					ScreenTransition(PRE_MACHINING_SCREEN);
					break;
		case GK_DOWN:
					value = GCSHtmlbrowserGetVScrollPosition(pChildHTML);
					value = value+80;
					GCSHtmlbrowserSetVScrollPosition(pChildHTML,value);
					GCSUpdateScroll(pChildHTML);
					break;
		case GK_UP:ClearWarningMessage();
					value = GCSHtmlbrowserGetVScrollPosition(pChildHTML);
					value = value-80;
					GCSHtmlbrowserSetVScrollPosition(pChildHTML,value);
					GCSUpdateScroll(pChildHTML);
					break;
		default:
			break;
	}
	return TRUE;
}

long GCMcode::KEY_ACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	pChild = GCSGetChild(GetGBaseObject(), KEY_ACTION);
		
	if(pChild != NULL && !bCalcWindowOpened)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}
	

	static int nCounter;
	nCounter++;
	if(nCounter >=10) {
		ReadIconStatus();
		nCounter = 0;
	}
	return TRUE;
}

long GCMcode::KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(!bCalcWindowOpened)
		ScreenTransition(PRE_MACHINING_SCREEN);
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

long GCMcode::KEY_CALC_WINDOWOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(!bCalcWindowOpened){
		DisableButtonName();
		bCalcWindowOpened = true;
		GCSCreateGWindow(GCSGetScreen(GetGBaseObject()),CALCULATOR_WINDOW);
	}
	return TRUE;
}

long GCMcode::KEY_CUT_O_METEROnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	sParentScreen = MCODE_SCREEN;
	ScreenTransition(CUT_O_METER_SCREEN);
	return TRUE;
}

long GCMcode::KEY_CYCLESOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	SetWarningMessage(UNDER_DEVELOPMENT_ERROR);
	return TRUE;
}

long GCMcode::KEY_GCODEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(GCODE_SCREEN);
	return TRUE;
}

long GCMcode::KEY_MACHINING_CONDOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	//ScreenTransition(MACHINE_COND_SELECTION_SCREEN);
	return TRUE;
}

long GCMcode::KEY_PARAMETEROnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(CUTTING_PARAMETERS_SCREEN);
	return TRUE;
}

long GCMcode::KEY_TOOLDATAOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(MAGAZINE_LIST_SCREEN);
	return TRUE;
}


/****************************************************************************************************/
/* Function - SetCursor																				*/
/*																									*/
/* Purpose - Sets the cursor position to given Cursor Position										*/
/****************************************************************************************************/
void GCMcode::SetCursor(short cur_pos)
{
	GBaseObject *pTouchButton[13];
	//short position ;

	/*pTouchButton[0] = GCSGetChild(GetGBaseObject(), IP_LIST_BUTTON);
	pTouchButton[1] = GCSGetChild(GetGBaseObject(), ELECTRICAL_BUTTON);
	pTouchButton[2] = GCSGetChild(GetGBaseObject(), PLC_BITS_BUTTON);
	pTouchButton[3] = GCSGetChild(GetGBaseObject(), KEY_HISTORY_BUTTON);
	pTouchButton[4] = GCSGetChild(GetGBaseObject(), HW_SW_VERSION_BUTTON);
	pTouchButton[5] = GCSGetChild(GetGBaseObject(), OP_LIST_BUTTON);
	pTouchButton[6] = GCSGetChild(GetGBaseObject(), PNEUMATICS_BUTTON);
	pTouchButton[7] = GCSGetChild(GetGBaseObject(), LATCH_RELAY_BUTTON);
	pTouchButton[8] = GCSGetChild(GetGBaseObject(), TOUCH_HISTORY_BUTTON);
	pTouchButton[9] = GCSGetChild(GetGBaseObject(), HYDRAULICS_BUTTON);
	pTouchButton[10] = GCSGetChild(GetGBaseObject(), REGISTERS_BUTTON);
	pTouchButton[11] = GCSGetChild(GetGBaseObject(), WORK_OFFSET_BUTTON);
	pTouchButton[12] = GCSGetChild(GetGBaseObject(), TOOL_OFFSET_BUTTON);*/

	/*if(cur_pos==0)
	{
		for(int i=1;i<=13;i++)
		{
			GCSButtonSetStatus(pTouchButton[i-1],GBTN_STATE_OFF);
		}
	}
	for(int i=1;i<=13;i++)
	{
		if(i==cur_pos)
		{
			GCSButtonSetStatus(pTouchButton[i-1],GBTN_STATE_ON);
		}
		else
		{
			GCSButtonSetStatus(pTouchButton[i-1],GBTN_STATE_OFF);
		}

	}*/
}


/****************************************************************************************************/
/* Function - ClearWarningMessage																	*/
/*																									*/
/* Purpose - Clears the Warning Message.															*/
/****************************************************************************************************/
void GCMcode::ClearWarningMessage()
{
	GBaseObject *pLbl;
	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);
	GCSTextboxSetString(pLbl, (GTCHAR *)"");
}



/****************************************************************************************************/
/* Function - ScreenTransition																		*/
/*																									*/
/* Purpose - Used for Screen Trasition. opens the Given Screen No.									*/
/****************************************************************************************************/
void GCMcode::ScreenTransition(short ScreenNo)
{
	if(!bCalcWindowOpened){
		GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
	}
}



/****************************************************************************************************/
/* Function - DisableButtonName																		*/
/*																									*/
/* Purpose - Hides Button Name for each button in the screen Show Button Name Only For Close Button	*/
/****************************************************************************************************/
void GCMcode::DisableButtonName()
{
	GBaseObject *pKeyButton[10];

	pKeyButton[0] = GCSGetChild(GetGBaseObject(), KEY_GCODE);
	pKeyButton[1] = GCSGetChild(GetGBaseObject(), KEY_PARAMETER);
	pKeyButton[2] = GCSGetChild(GetGBaseObject(), KEY_TOOLDATA);
	pKeyButton[3] = GCSGetChild(GetGBaseObject(), KEY_CYCLES);
	pKeyButton[4] = GCSGetChild(GetGBaseObject(), KEY_MACHINING_COND);
	pKeyButton[5] = GCSGetChild(GetGBaseObject(), KEY_CUT_O_METER);
	pKeyButton[6] = GCSGetChild(GetGBaseObject(), KEY_CALC_WINDOW);
	pKeyButton[7] = GCSGetChild(GetGBaseObject(), KEY_BACK);

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
long GCMcode::User(long lLParam, long lUParam)
{
	switch(lLParam)
	{
		case 0:	bCalcWindowOpened = false;
				EnableButtonName();
				break;	
	}
	return TRUE;
}



/************************************************************************************/
/* Function - EnableButtonName														*/
/*																					*/
/* Purpose - Shows Button Name for each button in the screen						*/
/************************************************************************************/
void GCMcode::EnableButtonName()
{
	GBaseObject *pKeyButton[10];

	pKeyButton[0] = GCSGetChild(GetGBaseObject(), KEY_GCODE);
	pKeyButton[1] = GCSGetChild(GetGBaseObject(), KEY_PARAMETER);
	pKeyButton[2] = GCSGetChild(GetGBaseObject(), KEY_TOOLDATA);
	pKeyButton[3] = GCSGetChild(GetGBaseObject(), KEY_CYCLES);
	pKeyButton[4] = GCSGetChild(GetGBaseObject(), KEY_MACHINING_COND);
	pKeyButton[5] = GCSGetChild(GetGBaseObject(), KEY_CUT_O_METER);
	pKeyButton[6] = GCSGetChild(GetGBaseObject(), KEY_CALC_WINDOW);
	pKeyButton[7] = GCSGetChild(GetGBaseObject(), KEY_BACK);

	//ID_STRING00145 = KEY_GCODE //ID_STRING00228 = g codes
	//ID_STRING00146 = KEY_MCODE //ID_STRING00229 = M-codes

	//ID_STRING00148 = KEY_PARAMETER
	//ID_STRING00680 = KEY_TOOLDATA
	//ID_STRING00231 = KEY_MACHINING_COND
	//ID_STRING00455 = KEY_CUT_O_METER
	//ID_STRING00681 = KEY_CYCLES
	//ID_STRING00165 = KEY_CALC_WINDOW
	//ID_STRING00023 = KEY_BACK

	GCSButtonSetStringID(pKeyButton[0], ID_STRING00228);
	GCSButtonSetStringID(pKeyButton[1], ID_STRING00148);
	GCSButtonSetStringID(pKeyButton[2], ID_STRING00680);
	GCSButtonSetStringID(pKeyButton[3], ID_STRING00681);
	GCSButtonSetStringID(pKeyButton[4], ID_STRING00231);
	GCSButtonSetStringID(pKeyButton[5], ID_STRING00455);
	GCSButtonSetStringID(pKeyButton[6], ID_STRING00165);
	GCSButtonSetStringID(pKeyButton[7], ID_STRING00023);
}


/****************************************************************************************************/
/* Function - ReadIconStatus																		*/
/*																									*/
/* Purpose - Reads and Updates the Icon Status	for													*/
/*			 Mode,Key,Lube,Manuual/Auto,Caution,SP Icon, & Tool Change Icon							*/
/****************************************************************************************************/
void GCMcode::ReadIconStatus()
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
	unsigned short sIconR69 = 0;
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
	
	if(sIconR69 !=65535)
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



/*******************************************************************************************/
/* Function - setWarningMessage														       */
/*																						   */
/* Purpose - To display warning message on screen				 						   */
/*******************************************************************************************/
void GCMcode::SetWarningMessage(int warnnum)
{
	GBaseObject *pLbl;
	GTCHAR szText[WARN_MSG_DATA_SIZE];

	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);	
	
	if(warnnum == UNDER_DEVELOPMENT_ERROR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "The Screen is Under Development",	sizeof(szText)/sizeof(GTCHAR));
	
	GCSTextboxSetString( pLbl, szText );
}
