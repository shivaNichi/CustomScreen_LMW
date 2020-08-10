#include "GCEOS.hpp"
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

void GCIDeleteGCEOS( GBaseObject *pObject )
{
	GCEOS *pPanel = (GCEOS*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCEOS( GBaseObject *pObject )
{
	GCEOS *pPanel = new GCEOS;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCEOS;
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
GCEOS::GCEOS()
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
GCEOS::~GCEOS()
{

}

#include "GCEOS.prc"

short GCEOS::CreateChildren( )
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

GPropertyInfo* GCEOS::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCEOS::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	short sAlramFlg = 0;
	short i;

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}
	
	for(i = 0; i <= 2000; i++)
	{
		melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)),
			  M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_F_1SHOT(i) ,0, (void *)&sAlramFlg, T_SHORT);
		if(sAlramFlg == 1)
			ScreenTransition( ALARM_SCREEN);

	}
	
	return TRUE;
}

long GCEOS::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	switch(lLParam)
	{
		case GK_F1:
				if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Monitor screen.
				ScreenTransition( HMI_SCREEN);
			}
			
				else
					ScreenTransition(GCODE_SCREEN);
					
			break;
		case GK_F2:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Setup screen.
			ScreenTransition(SETUP_SCREEN);
			}
		/*	else
				ScreenTransition( INOUTXY_SCREEN);*/
					
		break;
		case GK_F3:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Edit screen.
				ScreenTransition( HMI_EDIT_SCREEN);
			}
			else
				ScreenTransition( INIT_SCREEN);
					
		break;
		case GK_F4:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Diagnosis screen.
				ScreenTransition( DIAG_SCREEN);
			}
			else
				ScreenTransition( MTB_PASSWORD);
					
		break;
		case GK_F5:			
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Maintenance screen.
				ScreenTransition(  MAINTENANCE_SCREEN);
			}
		else
			ScreenTransition( MAINTAIN_HOME_SCREEN);
		
			
		break;
		//case GK_F6:			
		//
		//ScreenTransition( GCODE_SCREEN);
		//	break;
		//case GK_F7:			
		//	
		//		
		//		// Changing the screen to home screen.
		//		ScreenTransition( INIT_SCREEN);
		//	
		//break;
		//case GK_F8:			
		//	
		//		
		//		// Changing the screen to MTB 
		//		ScreenTransition( MTB_PASSWORD);
		//	
		//break;
		case GK_F9:			
				
			ScreenTransition(SUBSYS_SCREEN);
			
		break;
		case GK_F10:			
		
			ScreenTransition( HMI_SCREEN);
			
		break;
			default:
			break;
		}
	return TRUE;
}

long GCEOS::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
		GBaseObject *pChild;
		GBaseObject *pIconPicture1,*pIconPicture2;

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);	
	}

	long lR610=0,lR620=0;
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT(10620),0, &lR610, T_LONG); // To get the Data Protection StatusmelGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_BIT, M_SSEC_PLBIT_X_1SHOT(3224),0, &sIconXC98, T_SHORT); // To get the Data Protection Status
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_PLC_DEV_WORD, M_SSEC_PLWRD_R_1SHOT(10621),0, &lR620, T_LONG); // To get the Data Protection Status
	

	pIconPicture1 = GCSGetChild(GetGBaseObject(), ICON1);
	pIconPicture2 = GCSGetChild(GetGBaseObject(), ICON2);
	
	if(lR610 !=0)
	{	
		GCSSetVisibleStatus(pIconPicture1,1);
	}
	else
		GCSSetVisibleStatus(pIconPicture1,0);
	if(lR620 !=0)
	{	
		GCSSetVisibleStatus(pIconPicture2,1);
	}
	else
		GCSSetVisibleStatus(pIconPicture2,0);
	return TRUE;
}

void GCEOS::ScreenTransition(short ScreenNo)
{


	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
}

long GCEOS::BTNEXITOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( HMI_SCREEN);
	return TRUE;
}

long GCEOS::BTNGMOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(GCODE_SCREEN);
	return TRUE;
}

long GCEOS::BTNMAINTEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( MAINTAIN_HOME_SCREEN);
	return TRUE;
}

long GCEOS::BTNMCOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(SUBSYS_SCREEN);
	return TRUE;
}

long GCEOS::BTNTOOLOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( MTB_PASSWORD);
	return TRUE;
}



long GCEOS::BTNINITOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( INIT_SCREEN);
	return TRUE;
}

