#include "GCSUB_SysInfo.hpp"
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

void GCIDeleteGCSUB_SysInfo( GBaseObject *pObject )
{
	GCSUB_SysInfo *pPanel = (GCSUB_SysInfo*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCSUB_SysInfo( GBaseObject *pObject )
{
	GCSUB_SysInfo *pPanel = new GCSUB_SysInfo;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCSUB_SysInfo;
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
GCSUB_SysInfo::GCSUB_SysInfo()
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
GCSUB_SysInfo::~GCSUB_SysInfo()
{

}

#include "GCSUB_SysInfo.prc"

short GCSUB_SysInfo::CreateChildren( )
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

GPropertyInfo* GCSUB_SysInfo::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCSUB_SysInfo::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCSUB_SysInfo::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
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
					ScreenTransition( LUBRICATION_SCREEN);
					
			break;
				case GK_F2:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Setup screen.
			ScreenTransition(SETUP_SCREEN);
			}
			else
				ScreenTransition( COOLANT_SCREEN);
					
		break;
		case GK_F3:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Edit screen.
				ScreenTransition( HMI_EDIT_SCREEN);
			}
			else
				ScreenTransition( ATC_ARM_SCREEN);
					
		break;
		case GK_F4:
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Diagnosis screen.
				ScreenTransition( DIAG_SCREEN);
			}
			/*else
			ScreenTransition( ALARM_SCREEN);*/
					
		break;
		case GK_F5:			
			if((lUParam & KEY_SHIFT) == KEY_SHIFT){
				
				// Changing the screen to Maintenance screen.
				ScreenTransition(  MAINTENANCE_SCREEN);
			}
		else
			ScreenTransition( CHIPCONVEY_SCREEN);
				
			
		break;
		case GK_F6:			
		
	//	ScreenTransition( GCODE_SCREEN);
			break;
		case GK_F7:			
			
				
				// Changing the screen to home screen.
				ScreenTransition( HYDROLIC_SCREEN);
			
		break;
		case GK_F8:			
			
				
				// Changing the screen to MTB 
				ScreenTransition( SPINDLE_SCREEN);
			
		break;
		case GK_F9:			
			
				
				// Changing the screen to MTB 
				ScreenTransition( EOS_SCREEN);
			
		break;
		case GK_F10:			
		
			ScreenTransition( HMI_SCREEN);
			
		break;
			default:
			break;
		}
	return TRUE;
}

long GCSUB_SysInfo::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
		GBaseObject *pChild;

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);	
	}
	return TRUE;
}



void GCSUB_SysInfo::ScreenTransition(short ScreenNo)
{


	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
}

long GCSUB_SysInfo::DBTNATCOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( ATC_ARM_SCREEN);
	return TRUE;
}

long GCSUB_SysInfo::DBTNCHIPOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( CHIPCONVEY_SCREEN);
	return TRUE;
}

long GCSUB_SysInfo::DBTNCOOLOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		ScreenTransition( COOLANT_SCREEN);
	return TRUE;
}

long GCSUB_SysInfo::DBTNHYDOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		ScreenTransition( HYDROLIC_SCREEN);
	return TRUE;
}

long GCSUB_SysInfo::DBTNLUBEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( LUBRICATION_SCREEN);
	return TRUE;
}

long GCSUB_SysInfo::DBTNSPINDLEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( SPINDLE_SCREEN);
	return TRUE;
}

long GCSUB_SysInfo::BTNSPINDLEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( SPINDLE_SCREEN);
	return TRUE;
}

long GCSUB_SysInfo::BTNATCOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( ATC_ARM_SCREEN);
	return TRUE;
}

long GCSUB_SysInfo::BTNCHIPOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( CHIPCONVEY_SCREEN);
	return TRUE;
}

long GCSUB_SysInfo::BTNCOOLOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( COOLANT_SCREEN);
	return TRUE;
}

long GCSUB_SysInfo::BTNEOSOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition(EOS_SCREEN);
	return TRUE;
}

long GCSUB_SysInfo::BTNEXITOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
		ScreenTransition( HMI_SCREEN);
	return TRUE;
}

long GCSUB_SysInfo::BTNHYDOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( HYDROLIC_SCREEN);
	return TRUE;
}

long GCSUB_SysInfo::BTNLUBEOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	ScreenTransition( LUBRICATION_SCREEN);
	return TRUE;
}

