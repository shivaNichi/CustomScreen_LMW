#include "GCDrillSel.hpp"
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

void GCIDeleteGCDrillSel( GBaseObject *pObject )
{
	GCDrillSel *pPanel = (GCDrillSel*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCDrillSel( GBaseObject *pObject )
{
	GCDrillSel *pPanel = new GCDrillSel;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCDrillSel;
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
GCDrillSel::GCDrillSel()
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
GCDrillSel::~GCDrillSel()
{

}

#include "GCDrillSel.prc"

short GCDrillSel::CreateChildren( )
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

GPropertyInfo* GCDrillSel::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCDrillSel::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild, *nctextbox1;
	unsigned char iPicStatus;

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}
	WarningBit =0;
	Cursor_Pos = 1;
	SetCursor(Cursor_Pos);
	Tab_Pos = -1;
	bCalcWindowOpened = false;
	//ReadIconStatus(0);
	ReadIconStatus();
	return TRUE;
}

long GCDrillSel::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	GTCHAR inpBuff[10];
	char sData[10];
	int Scount = 0;
	short sEditPermit = 0;			// To store the edit permition y708

	pChild = GCSGetChild(GetGBaseObject(), DATA);

	switch(lLParam)
	{
		case GK_F1:
					ScreenTransition(GCODE_SCREEN);
					break;
		case GK_F2:
					ScreenTransition(DRILL_SELECTION_SCREEN);
					break;
		case GK_F3:
					ScreenTransition(MAGAZINE_LIST_SCREEN);
					break;
		case GK_F4:
					SetWarningMessage(UNDER_DEVELOPMENT_ERROR);
					break;
		case GK_F5:
					ScreenTransition(MACHINE_COND_SELECTION_SCREEN);
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
					ScreenTransition(PRE_MACHINING_SCREEN);
					break;
		case GK_DOWN:
					ClearWarningMessage();
					if(Cursor_Pos < 2){
							Cursor_Pos++;
					}
					else if(Cursor_Pos==2)
						Cursor_Pos = 1;
					SetCursor(Cursor_Pos);
					break;
		case GK_UP:ClearWarningMessage();
					if(Cursor_Pos > 1){
							Cursor_Pos--;
					}
					else if(Cursor_Pos==1)
						Cursor_Pos = 2;
					SetCursor(Cursor_Pos);
					break;
		case GK_RETURN:ClearWarningMessage();
						melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(1800),0, &sEditPermit, T_SHORT); // To get the Data Protection Status
						if(sEditPermit != 0)
							MainFunction();
						else
						{
							GCSTextboxSetString(pChild, (GTCHAR *)"");
							SetWarningMessage(9);
						}
						break;
		default:
			break;
	}
	return TRUE;
}

long GCDrillSel::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	
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

long GCDrillSel::KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam)
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

long GCDrillSel::KEY_CALC_WINDOWOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	if(!bCalcWindowOpened){
		DisableButtonName();
		bCalcWindowOpened = true;
		GCSCreateGWindow(GCSGetScreen(GetGBaseObject()),CALCULATOR_WINDOW);
	}
	return TRUE;
}

long GCDrillSel::KEY_CODESOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(GCODE_SCREEN);
	return TRUE;
}

long GCDrillSel::KEY_CUTTING_PARAOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(CUTTING_PARAMETERS_SCREEN);
	return TRUE;
}

long GCDrillSel::KEY_CUT_O_METEROnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(CUT_O_METER_SCREEN);
	return TRUE;
}

long GCDrillSel::KEY_CYCLESOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	SetWarningMessage(UNDER_DEVELOPMENT_ERROR);
	return TRUE;
}

long GCDrillSel::KEY_MACHINING_CONDOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(MACHINE_COND_SELECTION_SCREEN);
	return TRUE;
}

long GCDrillSel::KEY_TOOLDATAOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(MAGAZINE_LIST_SCREEN);
	return TRUE;
}



void GCDrillSel::SetCursor(short cur_pos)
{
	GBaseObject *pTouchButton[4];
	//short position ;

	pTouchButton[0] = GCSGetChild(GetGBaseObject(), TAP_SIZE);
	pTouchButton[1] = GCSGetChild(GetGBaseObject(), PITCH_THREAD);


	if(cur_pos==0)
	{
		for(int i=1;i<=2;i++)
		{
			GCSNCPLCTextboxSetNormalColor(pTouchButton[i-1],DEFAULT_COLOR);
		}
	}
	for(int i=1;i<=2;i++)
	{
		if(i==cur_pos)
		{
			GCSNCPLCTextboxSetNormalColor(pTouchButton[i-1],CURSOR_COLOR);
		}
		else
		{
			GCSNCPLCTextboxSetNormalColor(pTouchButton[i-1],DEFAULT_COLOR);
		}

	}
}


void GCDrillSel::ClearWarningMessage()
{
	GBaseObject *pLbl;
	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);
	GCSTextboxSetString(pLbl, (GTCHAR *)"");
}


void GCDrillSel::ScreenTransition(short ScreenNo)
{
	if(!bCalcWindowOpened){
		GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
	}
}


void GCDrillSel::DisableButtonName()
{
	GBaseObject *pKeyButton[10];

	pKeyButton[0] = GCSGetChild(GetGBaseObject(), KEY_CODES);
	pKeyButton[1] = GCSGetChild(GetGBaseObject(), KEY_CUTTING_PARA);
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
long GCDrillSel::User(long lLParam, long lUParam)
{
	switch(lLParam)
	{
		case 0:	bCalcWindowOpened = false;
				EnableButtonName();
				break;	
	}
	return TRUE;
}


void GCDrillSel::EnableButtonName()
{
	GBaseObject *pKeyButton[10];

	pKeyButton[0] = GCSGetChild(GetGBaseObject(), KEY_CODES);
	pKeyButton[1] = GCSGetChild(GetGBaseObject(), KEY_CUTTING_PARA);
	pKeyButton[2] = GCSGetChild(GetGBaseObject(), KEY_TOOLDATA);
	pKeyButton[3] = GCSGetChild(GetGBaseObject(), KEY_CYCLES);
	pKeyButton[4] = GCSGetChild(GetGBaseObject(), KEY_MACHINING_COND);
	pKeyButton[5] = GCSGetChild(GetGBaseObject(), KEY_CUT_O_METER);
	pKeyButton[6] = GCSGetChild(GetGBaseObject(), KEY_CALC_WINDOW);
	pKeyButton[7] = GCSGetChild(GetGBaseObject(), KEY_BACK);

	//KEY_CODES = ID_STRING00233 
	//KEY_CUTTING_PARA=ID_STRING00147
	//KEY_TOOLDATA=ID_STRING00680
	//KEY_CYCLES=ID_STRING00681
	//KEY_MACHINING_COND=ID_STRING00231
	//KEY_CUT_O_METER=ID_STRING00100
	//KEY_CALC_WINDOW=ID_STRING00165
	//KEY_BACK=ID_STRING00023

	GCSButtonSetStringID(pKeyButton[0], ID_STRING00233);
	GCSButtonSetStringID(pKeyButton[1], ID_STRING00147);
	GCSButtonSetStringID(pKeyButton[2], ID_STRING00680);
	GCSButtonSetStringID(pKeyButton[3], ID_STRING00681);
	GCSButtonSetStringID(pKeyButton[4], ID_STRING00231);
	GCSButtonSetStringID(pKeyButton[5], ID_STRING00100);
	GCSButtonSetStringID(pKeyButton[6], ID_STRING00165);
	GCSButtonSetStringID(pKeyButton[7], ID_STRING00023);
}

//void GCHomeScreen1::ReadIconStatus(int i)
void GCDrillSel::ReadIconStatus()
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
/* Function - SetWarningMessage														       */
/*																						   */
/* Purpose - To display warning message on screen				 						   */
/*******************************************************************************************/
void GCDrillSel::SetWarningMessage(int warnnum)
{
	GBaseObject *pLbl;
	GTCHAR szText[WARN_MSG_DATA_SIZE];

	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);	
	
	if(warnnum == UNDER_DEVELOPMENT_ERROR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "The Screen is Under Development",	sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 1)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Value must be 0 to 99.99", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 2)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Drill Size value must be 0 to 999.99", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 4)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Alphanumeric Error", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 5)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Please enter the data", sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 9)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Data is Protected!!!", sizeof(szText)/sizeof(GTCHAR));


	GCSTextboxSetString( pLbl, szText );
}


void GCDrillSel::MainFunction()
{
	GBaseObject *pChild, *pTxtB[2];
//	GTCHAR inpBuff[10];
	char sData[10];
	long lErrFlag;
	float iValue;

	pChild = GCSGetChild(GetGBaseObject(), DATA);

	pTxtB[0] = GCSGetChild(GetGBaseObject(), TAP_SIZE);
	pTxtB[1] = GCSGetChild(GetGBaseObject(), PITCH_THREAD);

	GCSTextboxGetString(pChild, inpBuff, sizeof(inpBuff)/sizeof(GTCHAR));
	GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), sData,inpBuff, sizeof(sData));
	if(strlen(sData) == 0)
	{
		SetWarningMessage(5);
		return;
	}
	else
	{
		iValue = atof(sData);
	}

	if(Cursor_Pos == 1 || Cursor_Pos == 2)
	{
		lErrFlag = CheckRange(sData, 0);
		if(lErrFlag == 1)
		{
			SetWarningMessage(4);
		}
		else
		{
			if(iValue>=0 && iValue<=99.99)
			{
				Calcuations();
				if(WarningBit != 1)
				{
					GCSNCPLCTextboxSetString(pTxtB[Cursor_Pos-1],inpBuff);			
					WarningBit = 0;
					if(Cursor_Pos == 1)
					{
						Cursor_Pos+=1;
						SetCursor(Cursor_Pos);
					}
				}
			}
			else
			{
				SetWarningMessage(1);
			}
		}
	}
	GCSTextboxSetString(pChild, (GTCHAR *)"");
}

void GCDrillSel::Calcuations()
{
	GBaseObject *pTapSize, *pPitchThread, *pDrillSize;
	GTCHAR inpBuff0[10], inpBuff1[10], inpBuff2[10];
	char sTapSizeData[10], sPitchThreadData[10], sDrillSizeData[10];
	float iTapSizeValue, iPitchThreadValue;

	pTapSize = GCSGetChild(GetGBaseObject(), TAP_SIZE);
	pPitchThread = GCSGetChild(GetGBaseObject(), PITCH_THREAD);

	pDrillSize = GCSGetChild(GetGBaseObject(), DRILL_SIZE);

	//Get pTapSize Value
	if(Cursor_Pos == 1)
	{
		GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), sTapSizeData,inpBuff, sizeof(sTapSizeData));
		iTapSizeValue = atof(sTapSizeData);
	}
	else
	{
		GCSNCPLCTextboxGetString(pTapSize, inpBuff0, sizeof(inpBuff0)/sizeof(GTCHAR));
		GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), sTapSizeData,inpBuff0, sizeof(sTapSizeData));
		iTapSizeValue = atof(sTapSizeData);
	}

	//Get pPitchThread Value
	if(Cursor_Pos == 2)
	{
		GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), sPitchThreadData,inpBuff, sizeof(sPitchThreadData));
		iPitchThreadValue = atof(sPitchThreadData);
	}
	else
	{
		GCSNCPLCTextboxGetString(pPitchThread, inpBuff1, sizeof(inpBuff1)/sizeof(GTCHAR));
		GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), sPitchThreadData,inpBuff1, sizeof(sPitchThreadData));
		iPitchThreadValue = atof(sPitchThreadData);
	}

	//DRILLSIZE Calculation...
	float iDrillSize = iTapSizeValue-iPitchThreadValue;
	sprintf(sDrillSizeData, "%.2f", iDrillSize);

	//Set Calculated DRILL SIZE
	if(iDrillSize>=0 && iDrillSize<=999.99)
	{
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(),inpBuff2, sDrillSizeData, sizeof(sDrillSizeData));
		GCSNCPLCTextboxSetString(pDrillSize,inpBuff2);
	}
	else
	{
		SetWarningMessage(2);
	}
}

long GCDrillSel::CheckRange(char *dat, int cellpos)
{
	GTCHAR szText[MAX_PARAM];
	float ddata;
	short lErr = 0;
	short lAlpha = 0;
	short i;
	short len = strlen(dat);

	switch(cellpos)
	{
		
		case 1:
			 for(i = 0; i < len; i++){
					if(! ( ( (dat[i] >= '0') && (dat[i] <= '9') ) ) ){
						lAlpha = 1;
						break;
					}				
					if( (dat[i] == '-') || (dat[i] == '+') || (dat[i] == '.') ){
						if (i != 0){
							lAlpha = 1;
							break;
						}
					}
				}
		case 0:
		case 2: for(i = 0; i < len; i++){
					if(! ( ( (dat[i] >= '0') && (dat[i] <= '9') ) || (dat[i] == '.') ) ){
						lAlpha = 1;
						break;
					}				
					if( (dat[i] == '-') || (dat[i] == '+') ){
						if (i != 0){
							lAlpha = 1;
							break;
						}
					}
				}
		break;
		default:for(i = 0; i < len; i++){
					if(! ( ( (dat[i] >= '0') && (dat[i] <= '9') ) || (dat[i] == '.') || (dat[i] == '-') || (dat[i] == '+') ) ){
						lAlpha = 1;
						break;
					}
				
					if( (dat[i] == '-') || (dat[i] == '+') ){
						if (i != 0){
							lAlpha = 1;
							break;
						}
					}
				}
		break;
	}
	
	// Set Error Flag
	if( (lErr == 1) || (lAlpha == 1) ){
		return 1;
	}
	else{
		return 0;
	}
}

long GCDrillSel::PITCH_THREADOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	Cursor_Pos = 2;
	SetCursor(Cursor_Pos);
	return TRUE;
}

long GCDrillSel::TAP_SIZEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	Cursor_Pos = 1;
	SetCursor(Cursor_Pos);
	return TRUE;
}
