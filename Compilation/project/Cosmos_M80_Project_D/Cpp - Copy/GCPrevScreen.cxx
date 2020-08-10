#include "GCPrevScreen.hpp"
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

void GCIDeleteGCPrevScreen( GBaseObject *pObject )
{
	GCPrevScreen *pPanel = (GCPrevScreen*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCPrevScreen( GBaseObject *pObject )
{
	GCPrevScreen *pPanel = new GCPrevScreen;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCPrevScreen;
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
GCPrevScreen::GCPrevScreen()
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
GCPrevScreen::~GCPrevScreen()
{

}

#include "GCPrevScreen.prc"

short GCPrevScreen::CreateChildren( )
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

GPropertyInfo* GCPrevScreen::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCPrevScreen::DATAOnClick(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCPrevScreen::DATAOnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCPrevScreen::DATAOnKeyPress(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCPrevScreen::DATAOnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

