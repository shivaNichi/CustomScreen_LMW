#include "GCDwntimehis.hpp"
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

void GCIDeleteGCDwntimehis( GBaseObject *pObject )
{
	GCDwntimehis *pPanel = (GCDwntimehis*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCDwntimehis( GBaseObject *pObject )
{
	GCDwntimehis *pPanel = new GCDwntimehis;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCDwntimehis;
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
GCDwntimehis::GCDwntimehis()
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
GCDwntimehis::~GCDwntimehis()
{

}

#include "GCDwntimehis.prc"

short GCDwntimehis::CreateChildren( )
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

GPropertyInfo* GCDwntimehis::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCDwntimehis::GNCTABLE00016OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00016OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00032OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00032OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00033OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00033OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00034OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00034OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00035OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00035OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00036OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00036OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00037OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00037OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00038OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00038OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00039OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00039OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00040OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCDwntimehis::GNCTABLE00040OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

