#include "GCMCCond.hpp"
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

extern "C"
{

void GCIDeleteGCMCCond( GBaseObject *pObject )
{
	GCMCCond *pPanel = (GCMCCond*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCMCCond( GBaseObject *pObject )
{
	GCMCCond *pPanel = new GCMCCond;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCMCCond;
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
GCMCCond::GCMCCond()
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
GCMCCond::~GCMCCond()
{

}

#include "GCMCCond.prc"

short GCMCCond::CreateChildren( )
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

GPropertyInfo* GCMCCond::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCMCCond::GINPUTBOX00027OnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCMCCond::GINPUTBOX00027OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCMCCond::GINPUTBOX00027OnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCMCCond::GINPUTBOX00027OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCMCCond::GNCTABLE00016OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCMCCond::GNCTABLE00016OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

