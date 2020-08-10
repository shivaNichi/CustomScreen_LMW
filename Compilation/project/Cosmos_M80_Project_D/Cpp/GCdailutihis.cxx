#include "GCdailutihis.hpp"
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

void GCIDeleteGCdailutihis( GBaseObject *pObject )
{
	GCdailutihis *pPanel = (GCdailutihis*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCdailutihis( GBaseObject *pObject )
{
	GCdailutihis *pPanel = new GCdailutihis;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCdailutihis;
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
GCdailutihis::GCdailutihis()
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
GCdailutihis::~GCdailutihis()
{

}

#include "GCdailutihis.prc"

short GCdailutihis::CreateChildren( )
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

GPropertyInfo* GCdailutihis::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCdailutihis::GNCTABLE00016OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00016OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00036OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00036OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00037OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00037OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00038OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00038OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00039OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00039OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00040OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00040OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00054OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00054OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00055OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00055OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00056OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00056OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00057OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCdailutihis::GNCTABLE00057OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

