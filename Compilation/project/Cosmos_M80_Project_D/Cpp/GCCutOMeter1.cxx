#include "GCCutOMeter1.hpp"
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

void GCIDeleteGCCutOMeter1( GBaseObject *pObject )
{
	GCCutOMeter1 *pPanel = (GCCutOMeter1*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCCutOMeter1( GBaseObject *pObject )
{
	GCCutOMeter1 *pPanel = new GCCutOMeter1;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCCutOMeter1;
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
GCCutOMeter1::GCCutOMeter1()
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
GCCutOMeter1::~GCCutOMeter1()
{

}

#include "GCCutOMeter1.prc"

short GCCutOMeter1::CreateChildren( )
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

GPropertyInfo* GCCutOMeter1::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCCutOMeter1::KEY_ACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	switch(lLParam)
	{
		case GK_F10:
					if( (lUParam & KEY_BITALL) != 0){
						break;
					}
					GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), sParentScreen, 0), FALSE);;
					break;
	}
	return TRUE;
}

long GCCutOMeter1::KEY_ACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	pChild = GCSGetChild(GetGBaseObject(), KEY_ACTION);
		
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}
	static int nCounter;
	//static int i = 0;
	nCounter++;
	if(nCounter >=10) {
		ReadStatus();
		nCounter = 0;
	}
	return TRUE;
}

long GCCutOMeter1::KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), sParentScreen, 0), FALSE);;
	return TRUE;
}

long GCCutOMeter1::KEY_ACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;

	pChild = GCSGetChild(GetGBaseObject(), KEY_ACTION);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}

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

	ReadStatus();

	return TRUE;
}



/****************************************************************************************************/
/* Function - ReadStatus																			*/
/*																									*/
/* Purpose - Reads and Updates the status															*/
/*			 Operation Mode,Lube Icon, and Tool Type																			*/
/****************************************************************************************************/
void GCCutOMeter1::ReadStatus()
{
	char cInputData[PARAM_DATA_SIZE];
	GTCHAR inpBuff[PARAM_DATA_SIZE];

	//ICON 1
	GBaseObject *pOpMode;
	GBaseObject *pLubeIcon;
	short sJogMode = 0;
	short sHandleMode = 0;
	short sIncMode = 0;
	short sZrnMode = 0;
	short sMemMode = 0;
	short sMdiMode = 0;
	short sRpdMode = 0;

	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3072),0, &sJogMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3073),0, &sHandleMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3074),0, &sIncMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3076),0, &sZrnMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3080),0, &sMemMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(3083),0, &sMdiMode, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(30110),0, &sRpdMode, T_SHORT); // To get the Data Protection Status
	
	pOpMode = GCSGetChild(GetGBaseObject(), OP_MODE);

	if(sJogMode !=0)
	{	
		if(sRpdMode!=0)
		{
			sprintf(cInputData, "%s", "RAPID");
			GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, cInputData, OUTPUT_BUFFER_SIZE);
			GCSTextboxSetString(pOpMode, inpBuff);
		}
		else
		{
			sprintf(cInputData, "%s", "JOG");
			GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, cInputData, OUTPUT_BUFFER_SIZE);
			GCSTextboxSetString(pOpMode, inpBuff);
		}
	}	
	else if(sHandleMode !=0)
	{	
		sprintf(cInputData, "%s", "HANDLE");
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, cInputData, OUTPUT_BUFFER_SIZE);
		GCSTextboxSetString(pOpMode, inpBuff);
	}	
	else if(sIncMode !=0)
	{	
		sprintf(cInputData, "%s", "INC");
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, cInputData, OUTPUT_BUFFER_SIZE);
		GCSTextboxSetString(pOpMode, inpBuff);	
	}
	else if(sZrnMode !=0)
	{	
		sprintf(cInputData, "%s", "ZRN");
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, cInputData, OUTPUT_BUFFER_SIZE);
		GCSTextboxSetString(pOpMode, inpBuff);	
	}	
	else if(sMemMode !=0)
	{	
		sprintf(cInputData, "%s", "MEM");
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, cInputData, OUTPUT_BUFFER_SIZE);
		GCSTextboxSetString(pOpMode, inpBuff);
	}
	else if(sMdiMode !=0)
	{	
		sprintf(cInputData, "%s", "MDI");
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, cInputData, OUTPUT_BUFFER_SIZE);
		GCSTextboxSetString(pOpMode, inpBuff);
	}	
	else if(sRpdMode !=0)
	{	
		sprintf(cInputData, "%s", "RAPID");
		GRCMultiByteToUnicode(GRCLoadNowLanguageStr(), inpBuff, cInputData, OUTPUT_BUFFER_SIZE);
		GCSTextboxSetString(pOpMode, inpBuff);
	}
	/*else
	{	
			GCSPictureSetStatus( pIconPicture,i);
	}	*/

	//need to Add for T and DRILL
	short sToolType = 0;
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT(10620),1, &sToolType, T_SHORT); // To get the Data Protection Status
	if(sToolType!=0 && sToolType<=14 && sToolType>0)
	{
		GBaseObject *pToolType;
		pToolType = GCSGetChild(GetGBaseObject(), TOOL_TYPE);
		GCSLabelSetStringID(pToolType, sToolTypeArray[sToolType-1]);
	}
	else
	{
		GBaseObject *pToolType;
		pToolType = GCSGetChild(GetGBaseObject(), TOOL_TYPE);
		GCSLabelSetStringID(pToolType, ID_STRING01300);
	}

	//Change Lube ICON;
	short sIconLube = 0;
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_Y_1SHOT(592),0, &sIconLube, T_SHORT); // To get the Data Protection Status
	pLubeIcon = GCSGetChild(GetGBaseObject(), LUBE_ICON);
	if(sIconLube !=0)
	{	
		GCSPictureSetStatus( pLubeIcon,0);	
	}
	else
	{
		GCSPictureSetStatus(pLubeIcon,1);
	}

}

