#include "GCMAINSCREEN.hpp"
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

void GCIDeleteGCMAINSCREEN( GBaseObject *pObject )
{
	GCMAINSCREEN *pPanel = (GCMAINSCREEN*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCMAINSCREEN( GBaseObject *pObject )
{
	GCMAINSCREEN *pPanel = new GCMAINSCREEN;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCMAINSCREEN;
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
GCMAINSCREEN::GCMAINSCREEN()
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
GCMAINSCREEN::~GCMAINSCREEN()
{

}

#include "GCMAINSCREEN.prc"

short GCMAINSCREEN::CreateChildren( )
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

GPropertyInfo* GCMAINSCREEN::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCMAINSCREEN::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
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

long GCMAINSCREEN::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
		switch(lLParam)
	{
		case GK_F1:
				if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Monitor screen.
				ScreenTransition( HMI_SCREEN);
			}
				/*else
					CopyFiles("SAMPLINGCOMM.CSV");*/
				else
					ScreenTransition( PREV_SCREEN);
					
			break;
				case GK_F2:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Setup screen.
			ScreenTransition(SETUP_SCREEN);
			}
			else
				ScreenTransition( INOUTXY_SCREEN);
					
		break;
		case GK_F3:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Edit screen.
				ScreenTransition( HMI_EDIT_SCREEN);
			}
			else
				ScreenTransition( INOUTL_SCREEN);
					
		break;
		case GK_F4:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Diagnosis screen.
				ScreenTransition( DIAG_SCREEN);
			}
			else
			ScreenTransition( ALARM_SCREEN);
					
		break;
		case GK_F5:			
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Maintenance screen.
				ScreenTransition(  MAINTENANCE_SCREEN);
			}
		else
		ScreenTransition( MCODE_SCREEN);
				/*	sprintf(sDestFile, "%s", "M01:\\PRG\\MMACRO\\MCODE.CSV");
				melFSRemoveFile(0,(ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)),sDestFile);*/
			
		break;
		case GK_F6:			
		
		ScreenTransition( GCODE_SCREEN);
			break;
		case GK_F7:			
			
				
				// Changing the screen to home screen.
				ScreenTransition( INIT_SCREEN);
			
		break;
		case GK_F8:			
			
				
				// Changing the screen to MTB 
				ScreenTransition( MTB_PASSWORD);
			
		break;
		case GK_F9:			
			
				
				// Changing the screen to MTB 
				ScreenTransition( 14);
			
		break;
			default:
			break;
		}
	return TRUE;
}

long GCMAINSCREEN::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}
	return TRUE;
}

void GCMAINSCREEN::ScreenTransition(short ScreenNo)
{


	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
}

long GCMAINSCREEN::BUTTONALARMOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( ALARM_SCREEN);
	return TRUE;
}

long GCMAINSCREEN::BUTTONGCODEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( GCODE_SCREEN);
	return TRUE;
}

long GCMAINSCREEN::BUTTONINITIALOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( INIT_SCREEN);
	return TRUE;
}

long GCMAINSCREEN::BUTTONIOLISTOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( INOUTXY_SCREEN);
	return TRUE;
}

long GCMAINSCREEN::BUTTONLACHRELAYOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( INOUTL_SCREEN);
	return TRUE;
}

long GCMAINSCREEN::BUTTONMCODEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( MCODE_SCREEN);
	return TRUE;
}

long GCMAINSCREEN::BUTTONPREVNTOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( PREV_SCREEN);
	return TRUE;
}

long GCMAINSCREEN::MTB_SCREENOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( MTB_PASSWORD);
	return TRUE;
}
