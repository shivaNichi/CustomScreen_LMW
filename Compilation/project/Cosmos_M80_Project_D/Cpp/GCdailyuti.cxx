#include "GCdailyuti.hpp"
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

void GCIDeleteGCdailyuti( GBaseObject *pObject )
{
	GCdailyuti *pPanel = (GCdailyuti*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCdailyuti( GBaseObject *pObject )
{
	GCdailyuti *pPanel = new GCdailyuti;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCdailyuti;
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
GCdailyuti::GCdailyuti()
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
GCdailyuti::~GCdailyuti()
{

}

#include "GCdailyuti.prc"

short GCdailyuti::CreateChildren( )
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

GPropertyInfo* GCdailyuti::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCdailyuti::GNCTABLE00016OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailyuti::GNCTABLE00016OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailyuti::GNCTABLE00036OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailyuti::GNCTABLE00036OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

