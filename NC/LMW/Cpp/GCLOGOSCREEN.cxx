#include "GCLOGOSCREEN.hpp"
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

static  bool bPowerOnFlag=0;


extern "C"
{

void GCIDeleteGCLOGOSCREEN( GBaseObject *pObject )
{
	GCLOGOSCREEN *pPanel = (GCLOGOSCREEN*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCLOGOSCREEN( GBaseObject *pObject )
{
	GCLOGOSCREEN *pPanel = new GCLOGOSCREEN;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCLOGOSCREEN;
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
GCLOGOSCREEN::GCLOGOSCREEN()
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
GCLOGOSCREEN::~GCLOGOSCREEN()
{

}

#include "GCLOGOSCREEN.prc"

short GCLOGOSCREEN::CreateChildren( )
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

GPropertyInfo* GCLOGOSCREEN::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCLOGOSCREEN::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	

	pChild = GCSGetChild(GetGBaseObject(), DATA);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}
	if(bPowerOnFlag==1)
	{
		ScreenTransition(EOS_SCREEN);
	}
	else
	{
	lSettime=0;
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_RUNTIME, 
		M_SSEC_RTIME_TIME, 0,(void *)&lSettime, T_LONG); 
	lSettime=lSettime+5;
	}
	
	
	return TRUE;
}

long GCLOGOSCREEN::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCLOGOSCREEN::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	GBaseObject *pChild;
	pChild = GCSGetChild(GetGBaseObject(), DATA);
	
	if(pChild != NULL)
	{
		GCSChangeActiveFocus(GetGBaseObject(), pChild);							// Setting active focus to Data object
	}

	TimeCalculation();
	return TRUE;
}

void GCLOGOSCREEN::ScreenTransition(short ScreenNo)
{


	GESetEvent(GECreateEventMessage(GM_SHOWPANEL, GCSGetScreen(GetGBaseObject()), ScreenNo, 0), FALSE);
}
void GCLOGOSCREEN::TimeCalculation()
{
	if(bPowerOnFlag==0)
	{
	long lCuurenttime=0;
	melGetData(0, (ADR_MACHINE(1)|ADR_BASE_SYSTEM|ADR_SYSTEM(1)|ADR_GROUND(0)), M_SEC_RUNTIME, 
		M_SSEC_RTIME_TIME, 0,(void *)&lCuurenttime, T_LONG); 
	if(lSettime<lCuurenttime)
	{
	bPowerOnFlag=1;
	ScreenTransition(CAUTION_SCREEN);
	}
	}
	else
	ScreenTransition(EOS_SCREEN);

	
}
