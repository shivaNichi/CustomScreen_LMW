#include "GCMaint_Home.hpp"
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

void GCIDeleteGCMaint_Home( GBaseObject *pObject )
{
	GCMaint_Home *pPanel = (GCMaint_Home*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCMaint_Home( GBaseObject *pObject )
{
	GCMaint_Home *pPanel = new GCMaint_Home;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCMaint_Home;
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
GCMaint_Home::GCMaint_Home()
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
GCMaint_Home::~GCMaint_Home()
{

}

#include "GCMaint_Home.prc"

short GCMaint_Home::CreateChildren( )
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

GPropertyInfo* GCMaint_Home::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}



long GCMaint_Home::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCMaint_Home::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
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
				ScreenTransition( INOUTXY_SCREEN);
					
		break;
		case GK_F4:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Diagnosis screen.
				ScreenTransition( DIAG_SCREEN);
			}
			else
				ScreenTransition( POWER_SCREEN);
					
		break;
		case GK_F5:			
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Maintenance screen.
				ScreenTransition(  MAINTENANCE_SCREEN);
			}
		else
			ScreenTransition( ALARM_SCREEN);
		
			
		break;
		case GK_F6:			
		
			ScreenTransition( PREV_SCREEN);
			break;
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
				
			ScreenTransition(EOS_SCREEN);
			
		break;
		case GK_F10:			
		
			ScreenTransition( HMI_SCREEN);
			
		break;
			default:
			break;
		}
	return TRUE;
}

long GCMaint_Home::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
		GBaseObject *pChild;
		
	pChild = GCSGetChild(GetGBaseObject(), DATA);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);	
	}


	
	
	return TRUE;
}

void GCMaint_Home::ScreenTransition(short ScreenNo)
{


	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
}

long GCMaint_Home::BTNALARMOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( ALARM_SCREEN);
	return TRUE;
}

long GCMaint_Home::BTNEOSOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(EOS_SCREEN);
	return TRUE;
}

long GCMaint_Home::BTNEXITOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( HMI_SCREEN);
	return TRUE;
}

long GCMaint_Home::BTNGMOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(GCODE_SCREEN);
	return TRUE;
}

long GCMaint_Home::BTNIOOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		ScreenTransition( INOUTXY_SCREEN);
	return TRUE;
}

long GCMaint_Home::BTNPOWEROnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( POWER_SCREEN);
	return TRUE;
}

long GCMaint_Home::BTNPREVOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( PREV_SCREEN);
	return TRUE;
}
