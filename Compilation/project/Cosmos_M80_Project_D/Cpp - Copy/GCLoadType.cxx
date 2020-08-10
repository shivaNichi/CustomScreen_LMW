#include "GCLoadType.hpp"
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

void GCIDeleteGCLoadType( GBaseObject *pObject )
{
	GCLoadType *pPanel = (GCLoadType*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCLoadType( GBaseObject *pObject )
{
	GCLoadType *pPanel = new GCLoadType;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCLoadType;
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
GCLoadType::GCLoadType()
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
GCLoadType::~GCLoadType()
{

}

#include "GCLoadType.prc"

short GCLoadType::CreateChildren( )
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

GPropertyInfo* GCLoadType::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCLoadType::KEYACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;

	pChild = GCSGetChild(GetGBaseObject(), KEYACTION);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}
	ReadIconStatus();
	ReadProgressBarStatus();
	return TRUE;
}

long GCLoadType::KEYACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	

	pChild = GCSGetChild(GetGBaseObject(), KEYACTION);

	switch(lLParam)
	{
		case GK_F5:
					GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), TREND_VIEW_SCREEN, 0), FALSE);
					break;
		case GK_F10:
					GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), PRE_MACHINING_SCREEN, 0), FALSE);
					break;
		default:
			break;
	}
	return TRUE;
}

long GCLoadType::KEY_BACKOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), PRE_MACHINING_SCREEN, 0), FALSE);
	return TRUE;
}

long GCLoadType::KEY_CANCEL_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCLoadType::KEY_HELP_WINDOWOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCLoadType::KEY_SET_BUTTONOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCLoadType::KEY_TEACHLOAD_SETOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCLoadType::KEY_TEACH_MODEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCLoadType::KEY_TOOL_SEARCHOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCLoadType::KEY_TREND_VIEWOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), TREND_VIEW_SCREEN, 0), FALSE);
	return TRUE;
}

long GCLoadType::MARGIN_INPUTOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCLoadType::MARGIN_INPUTOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCLoadType::MAX_LOAD_RECORDOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCLoadType::MAX_LOAD_RECORDOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCLoadType::P1XOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCLoadType::P1XOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCLoadType::TOOL_MANAGE_TABLEOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCLoadType::TOOL_MANAGE_TABLEOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{

	static int iRefreshIconTimer = 0;
	GBaseObject *pChild;

	pChild = GCSGetChild(GetGBaseObject(), KEYACTION);
	
	
		if(pChild != NULL)
		{
			GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
		}

		//iTableCounter++;
		//if(iTableCounter > 10)
		//{
		//	// Get Initial Pot Information Structure
		//	//GetPotInfo(&pt);																			// Get Screen parameters data structure
		//	//SetPotInfo(&pt);																			// Set Screen parameters data structure

		//	//FetchData();																				// Fetch Tool data
		//	//PrintToolData();																			// Printing tool data in to Table
		//			
		//	// Refresh Current Status of Spindle Tool and CLNT Type
		//	//ReadSpindleToolStatusClntType();																	
		//	iTableCounter = 0;
		//}

		iRefreshIconTimer++;
		if(iRefreshIconTimer >=100) {
			ReadIconStatus();
			ReadProgressBarStatus();
			iRefreshIconTimer = 0;
		}
	
	return TRUE;
}


void GCLoadType::ReadIconStatus()
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


void GCLoadType::ReadProgressBarStatus()
{
	GBaseObject *pProgressBar;

	double sXValue = 0;
	double sYValue = 0;
	double sZValue = 0;
	double sSPValue = 0;

	double sProgData;

	
	//for Updating the Progress of X value
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MON_SV, M_SSEC_MSV_CURRENT,1, &sXValue, T_SHORT); // To get the Data Protection Status
	sProgData = abs(sXValue);
	sXValue = sProgData;
	if(sXValue>=0 && sXValue<=60)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1X);
		GCSProgressbarSetValue(pProgressBar,sXValue);
	}
	else if(sXValue>=61 && sXValue<=80)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1X);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), P2X);
		GCSProgressbarSetValue(pProgressBar,sXValue);
	}
	else if(sXValue>=81 && sXValue<=120)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1X);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), P2X);
		GCSProgressbarSetValue(pProgressBar,80);

		pProgressBar = GCSGetChild(GetGBaseObject(), P3X);
		GCSProgressbarSetValue(pProgressBar,sXValue);
	}

	//for Updating the Progress of Y value
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MON_SV, M_SSEC_MSV_CURRENT,2, &sYValue, T_SHORT); // To get the Data Protection Status
	sProgData = abs(sYValue);
	sYValue = sProgData;
	if(sYValue>=0 && sYValue<=60)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1Y);
		GCSProgressbarSetValue(pProgressBar,sYValue);
	}
	else if(sYValue>=61 && sYValue<=80)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1Y);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), P2Y);
		GCSProgressbarSetValue(pProgressBar,sYValue);
	}
	else if(sYValue>=81 && sYValue<=120)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1Y);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), P2Y);
		GCSProgressbarSetValue(pProgressBar,80);

		pProgressBar = GCSGetChild(GetGBaseObject(), P3Y);
		GCSProgressbarSetValue(pProgressBar,sYValue);
	}

	//for Updating the Progress of Z value
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MON_SV, M_SSEC_MSV_CURRENT,3, &sZValue, T_SHORT); // To get the Data Protection Status
	sProgData = abs(sZValue);
	sZValue = sProgData;
	if(sZValue>=0 && sZValue<=60)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1Z);
		GCSProgressbarSetValue(pProgressBar,sZValue);
	}
	else if(sZValue>=61 && sZValue<=80)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1Z);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), P2Z);
		GCSProgressbarSetValue(pProgressBar,sZValue);
	}
	else if(sZValue>=81 && sZValue<=120)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1Z);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), P2Z);
		GCSProgressbarSetValue(pProgressBar,80);

		pProgressBar = GCSGetChild(GetGBaseObject(), P3Z);
		GCSProgressbarSetValue(pProgressBar,sZValue);
	}
	//for Updating the Progress of SP value
	//63/4/1
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_MON_SP, M_SSEC_MSP_LOAD,1, &sSPValue, T_SHORT); // To get the Data Protection Status
	sProgData = abs(sSPValue);
	sSPValue = sProgData;
	if(sSPValue>=0 && sSPValue<=60)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1SP);
		GCSProgressbarSetValue(pProgressBar,sSPValue);
	}
	else if(sSPValue>=61 && sSPValue<=80)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1SP);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), P2SP);
		GCSProgressbarSetValue(pProgressBar,sSPValue);
	}
	else if(sSPValue>=81 && sSPValue<=120)
	{
		pProgressBar = GCSGetChild(GetGBaseObject(), P1SP);
		GCSProgressbarSetValue(pProgressBar,60);

		pProgressBar = GCSGetChild(GetGBaseObject(), P2SP);
		GCSProgressbarSetValue(pProgressBar,80);

		pProgressBar = GCSGetChild(GetGBaseObject(), P3SP);
		GCSProgressbarSetValue(pProgressBar,sSPValue);
	}
}
