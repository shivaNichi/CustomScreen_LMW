#include "GCBITS3.hpp"
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

void GCIDeleteGCBITS3( GBaseObject *pObject )
{
	GCBITS3 *pPanel = (GCBITS3*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCBITS3( GBaseObject *pObject )
{
	GCBITS3 *pPanel = new GCBITS3;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCBITS3;
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
GCBITS3::GCBITS3()
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
GCBITS3::~GCBITS3()
{

}

#include "GCBITS3.prc"

short GCBITS3::CreateChildren( )
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

GPropertyInfo* GCBITS3::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}



long GCBITS3::KEYACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;

	pChild = GCSGetChild(GetGBaseObject(), KEYACTION);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}


	Cursor_Pos = 1;
	SetCursor(Cursor_Pos);
	ReadIconStatus();

	DisplayBits();
	return TRUE;
}

long GCBITS3::KEYACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	GTCHAR inpBuff[10];
	char sData[10];
	int Scount = 0;
	short sEditPermit = 0;			// To store the edit permition y708

	pChild = GCSGetChild(GetGBaseObject(), KEYACTION);

	switch(lLParam)
	{
	
		case GK_F2:
				    if(!(((lUParam & KEY_SHIFT) != KEY_SHIFT) && ((lUParam & KEY_SEC) != KEY_SEC)))
				    {
					   break;
				    }
					SetValueZero();
					break;
		case GK_F3:
					if(!(((lUParam & KEY_SHIFT) != KEY_SHIFT) && ((lUParam & KEY_SEC) != KEY_SEC)))
					{
						break;
					}
					SetValueOne();
					break;
		case GK_F8:
					GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), BITS_4_SCREEN, 0), FALSE);
					break;
		case GK_F9:
					GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), DIAGNOSIS_SCREEN, 0), FALSE);
					break;
		case GK_F10:
					if( (lUParam & KEY_BITALL) != 0){
						break;
					}
					GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), BITS_2_SCREEN, 0), FALSE);
					break;
		case GK_DOWN:	ClearWarningMessage();
					
						if(Cursor_Pos < 8){
							Cursor_Pos++;
						}
						else if(Cursor_Pos == 8){
								Cursor_Pos = 1;
						}
						SetCursor(Cursor_Pos);
						break;

		case GK_UP:ClearWarningMessage();
					if(Cursor_Pos > 1){
							Cursor_Pos--;
					}
					else if(Cursor_Pos == 1){
							Cursor_Pos = 8;
					}
					SetCursor(Cursor_Pos);
					break;
		case GK_ESCAPE:
			Cursor_Pos = 0;
			SetCursor(Cursor_Pos);
		default:
			break;
	}
	return TRUE;
}

long GCBITS3::KEYACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	static int iRefreshIconTimer = 0;
	GBaseObject *pChild;
	GBaseObject *pMaxLoadRecord;
	GTCHAR szText[PARAM_DATA_SIZE];
	char *cInputData;


	pChild = GCSGetChild(GetGBaseObject(), KEYACTION);
	
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}


	iRefreshIconTimer++;
	if(iRefreshIconTimer >=100) {
		ReadIconStatus();
		iRefreshIconTimer = 0;
	}
	return TRUE;
}

long GCBITS3::KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), BITS_2_SCREEN, 0), FALSE);
	return TRUE;
}

long GCBITS3::KEY_DIAG_SCREENOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), DIAGNOSIS_SCREEN, 0), FALSE);
	return TRUE;
}

long GCBITS3::KEY_NEXTOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), BITS_4_SCREEN, 0), FALSE);
	return TRUE;
}

long GCBITS3::KEY_SET_0OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	SetValueZero();
	return TRUE;
}

long GCBITS3::KEY_SET_1OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	SetValueOne();
	return TRUE;
}

long GCBITS3::T1OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	Cursor_Pos = 1;
	SetCursor(Cursor_Pos);
	return TRUE;
}

long GCBITS3::T2OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	Cursor_Pos = 2;
	SetCursor(Cursor_Pos);
	return TRUE;
}

long GCBITS3::T3OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	Cursor_Pos = 3;
	SetCursor(Cursor_Pos);
	return TRUE;
}

long GCBITS3::T4OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	Cursor_Pos = 4;
	SetCursor(Cursor_Pos);
	return TRUE;
}

long GCBITS3::T5OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	Cursor_Pos = 5;
	SetCursor(Cursor_Pos);
	return TRUE;
}

long GCBITS3::T6OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	Cursor_Pos = 6;
	SetCursor(Cursor_Pos);
	return TRUE;
}

long GCBITS3::T7OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	Cursor_Pos = 7;
	SetCursor(Cursor_Pos);
	return TRUE;
}

long GCBITS3::T8OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	Cursor_Pos = 8;
	SetCursor(Cursor_Pos);
	return TRUE;
}

/****************************************************************************************************/
/* Function - ReadIconStatus																		*/
/*																									*/
/* Purpose - Reads and Updates the Icon Status	for													*/
/*			 Mode,Key,Lube,Manuual/Auto,Caution,SP Icon, & Tool Change Icon							*/
/****************************************************************************************************/
void GCBITS3::ReadIconStatus()
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
void GCBITS3::SetWarningMessage(int warnnum)
{
	GBaseObject *pLbl;
	GTCHAR szText[WARN_MSG_DATA_SIZE];

	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);	
	
	if(warnnum == UNDER_DEVELOPMENT_ERROR)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "The Screen is Under Development",	sizeof(szText)/sizeof(GTCHAR));
	else if(warnnum == 1)
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), szText, "Incorrect Password",	sizeof(szText)/sizeof(GTCHAR));
	
	GCSTextboxSetString( pLbl, szText );
}

/****************************************************************************************************/
/* Function - ClearWarningMessage																	*/
/*																									*/
/* Purpose - Clears the Warning Message.															*/
/****************************************************************************************************/
void GCBITS3::ClearWarningMessage()
{
	GBaseObject *pLbl;
	pLbl = GCSGetChild(GetGBaseObject(), MSGBOX);
	GCSTextboxSetString(pLbl, (GTCHAR *)"");
}


void GCBITS3::DisplayBits()
{

	GBaseObject *pTouchButton[13];
	//short position ;

	pTouchButton[0] = GCSGetChild(GetGBaseObject(), T1);
	pTouchButton[1] = GCSGetChild(GetGBaseObject(), T2);
	pTouchButton[2] = GCSGetChild(GetGBaseObject(), T3);
	pTouchButton[3] = GCSGetChild(GetGBaseObject(), T4);
	pTouchButton[4] = GCSGetChild(GetGBaseObject(), T5);
	pTouchButton[5] = GCSGetChild(GetGBaseObject(), T6);
	pTouchButton[6] = GCSGetChild(GetGBaseObject(), T7);
	pTouchButton[7] = GCSGetChild(GetGBaseObject(), T8);


	long sRead6401Bits;

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MPRM_SELECT_BIT, 
						M_SSEC_MP_SELECT_BIT(2), 0, &sRead6401Bits, T_LONG);

	tData.num = sRead6401Bits;


	if(tData.bits.b0 == 1)
		GCSButtonSetStringID(pTouchButton[0],ID_STRING01317);
	else
		GCSButtonSetStringID(pTouchButton[0],ID_STRING01318);

	if(tData.bits.b1 == 1)
		GCSButtonSetStringID(pTouchButton[1],ID_STRING01317);
	else
		GCSButtonSetStringID(pTouchButton[1],ID_STRING01318);

	if(tData.bits.b2 == 1)
		GCSButtonSetStringID(pTouchButton[2],ID_STRING01317);
	else
		GCSButtonSetStringID(pTouchButton[2],ID_STRING01318);

	if(tData.bits.b3 == 1)
		GCSButtonSetStringID(pTouchButton[3],ID_STRING01317);
	else
		GCSButtonSetStringID(pTouchButton[3],ID_STRING01318);


	if(tData.bits.b4 == 1)
		GCSButtonSetStringID(pTouchButton[4],ID_STRING01317);
	else
		GCSButtonSetStringID(pTouchButton[4],ID_STRING01318);

	if(tData.bits.b5 == 1)
		GCSButtonSetStringID(pTouchButton[5],ID_STRING01317);
	else
		GCSButtonSetStringID(pTouchButton[5],ID_STRING01318);

	if(tData.bits.b6 == 1)
		GCSButtonSetStringID(pTouchButton[6],ID_STRING01317);
	else
		GCSButtonSetStringID(pTouchButton[6],ID_STRING01318);

	if(tData.bits.b7 == 1)
		GCSButtonSetStringID(pTouchButton[7],ID_STRING01317);
	else
		GCSButtonSetStringID(pTouchButton[7],ID_STRING01318);

}

/****************************************************************************************************/
/* Function - SetValueZero																			*/
/*																									*/
/* Purpose - Set the value to Zero for the Given Bit(Cur_pos)										*/
/****************************************************************************************************/
void GCBITS3::SetValueZero()
{
	GBaseObject *pTouchButton[13];
	//short position ;

	pTouchButton[0] = GCSGetChild(GetGBaseObject(), T1);
	pTouchButton[1] = GCSGetChild(GetGBaseObject(), T2);
	pTouchButton[2] = GCSGetChild(GetGBaseObject(), T3);
	pTouchButton[3] = GCSGetChild(GetGBaseObject(), T4);
	pTouchButton[4] = GCSGetChild(GetGBaseObject(), T5);
	pTouchButton[5] = GCSGetChild(GetGBaseObject(), T6);
	pTouchButton[6] = GCSGetChild(GetGBaseObject(), T7);
	pTouchButton[7] = GCSGetChild(GetGBaseObject(), T8);


	long sRead6401Bits;

	bool bCorrectPwd = CheckPassword();

	if(bCorrectPwd)
	{

		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MPRM_SELECT_BIT, 
							M_SSEC_MP_SELECT_BIT(2), 0, &sRead6401Bits, T_LONG);

		tData.num = sRead6401Bits;

		switch(Cursor_Pos)
		{
		case 1: tData.bits.b0 = 0;
			break;
		case 2: tData.bits.b1 = 0;
			break;
		case 3: tData.bits.b2 = 0;
			break;
		case 4: tData.bits.b3 = 0;
			break;
		case 5: tData.bits.b4 = 0;
			break;
		case 6: tData.bits.b5 = 0;
			break;
		case 7: tData.bits.b6 = 0;
			break;
		case 8: tData.bits.b7 = 0;
			break;
		}
		GCSButtonSetStringID(pTouchButton[Cursor_Pos-1],ID_STRING01318);

		

		sRead6401Bits = tData.num;

		melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MPRM_SELECT_BIT, 
							M_SSEC_MP_SELECT_BIT(2), 0, &sRead6401Bits, T_LONG);
	}
}

/****************************************************************************************************/
/* Function - CheckPassword																			*/
/*																									*/
/* Purpose - Check for password constant 107/130													*/
/****************************************************************************************************/
bool GCBITS3::CheckPassword()
{	
	GBaseObject *pChild;
	char operData[WARN_MSG_DATA_SIZE];
	GTCHAR inpBuffPwd[WARN_MSG_DATA_SIZE];

	GTCHAR ReadBuffPwd[WARN_MSG_DATA_SIZE];
	long ReadPwdData;

	pChild = GCSGetChild(GetGBaseObject(), KEYACTION);
	


	GCSTextboxGetString( pChild, inpBuffPwd, sizeof(inpBuffPwd)/sizeof(GTCHAR) );
	GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), operData, inpBuffPwd, sizeof(operData));

	//107/130
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)),M_SEC_MPRM_PLC_CONST, M_SSEC_MP_PLC_CONST(129), 0, &ReadPwdData, T_LONG);
	//GRCUnicodeToMultiByte(GRCLoadNowLanguageStr(), ReadPwdData, ReadBuffPwd, sizeof(ReadPwdData));

	if( atoi(operData) == ReadPwdData)
	{
		return TRUE;
	}
	else
	{
		SetWarningMessage(1);
		return FALSE;
	}
}

/****************************************************************************************************/
/* Function - SetValueOne																			*/
/*																									*/
/* Purpose - Set the value to One for the Given Bit(Cur_pos)										*/
/****************************************************************************************************/
void GCBITS3::SetValueOne()
{
	GBaseObject *pTouchButton[13];
	//short position ;

	pTouchButton[0] = GCSGetChild(GetGBaseObject(), T1);
	pTouchButton[1] = GCSGetChild(GetGBaseObject(), T2);
	pTouchButton[2] = GCSGetChild(GetGBaseObject(), T3);
	pTouchButton[3] = GCSGetChild(GetGBaseObject(), T4);
	pTouchButton[4] = GCSGetChild(GetGBaseObject(), T5);
	pTouchButton[5] = GCSGetChild(GetGBaseObject(), T6);
	pTouchButton[6] = GCSGetChild(GetGBaseObject(), T7);
	pTouchButton[7] = GCSGetChild(GetGBaseObject(), T8);


	long sRead6401Bits;

	bool bCorrectPwd = CheckPassword();

	if(bCorrectPwd)
	{

		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MPRM_SELECT_BIT, 
							M_SSEC_MP_SELECT_BIT(2), 0, &sRead6401Bits, T_LONG);

		tData.num = sRead6401Bits;

		switch(Cursor_Pos)
		{
		case 1: tData.bits.b0 = 1;
			break;
		case 2: tData.bits.b1 = 1;
			break;
		case 3: tData.bits.b2 = 1;
			break;
		case 4: tData.bits.b3 = 1;
			break;
		case 5: tData.bits.b4 = 1;
			break;
		case 6: tData.bits.b5 = 1;
			break;
		case 7: tData.bits.b6 = 1;
			break;
		case 8: tData.bits.b7 = 1;
			break;
		}
		GCSButtonSetStringID(pTouchButton[Cursor_Pos-1],ID_STRING01317);
	
		sRead6401Bits = tData.num;

		melSetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MPRM_SELECT_BIT, 
							M_SSEC_MP_SELECT_BIT(2), 0, &sRead6401Bits, T_LONG);
	}
}


/****************************************************************************************************/
/* Function - SetCursor																				*/
/*																									*/
/* Purpose - Sets the cursor position to given Cursor Position										*/
/****************************************************************************************************/
void GCBITS3::SetCursor(short cur_pos)
{
	GBaseObject *pTouchButton[13];
	//short position ;

	pTouchButton[0] = GCSGetChild(GetGBaseObject(), T1);
	pTouchButton[1] = GCSGetChild(GetGBaseObject(), T2);
	pTouchButton[2] = GCSGetChild(GetGBaseObject(), T3);
	pTouchButton[3] = GCSGetChild(GetGBaseObject(), T4);
	pTouchButton[4] = GCSGetChild(GetGBaseObject(), T5);
	pTouchButton[5] = GCSGetChild(GetGBaseObject(), T6);
	pTouchButton[6] = GCSGetChild(GetGBaseObject(), T7);
	pTouchButton[7] = GCSGetChild(GetGBaseObject(), T8);

	if(cur_pos==0)
	{
		for(int i=1;i<=8;i++)
		{
			GCSButtonSetStatus(pTouchButton[i-1],GBTN_STATE_OFF);
		}
	}
	for(int i=1;i<=8;i++)
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
