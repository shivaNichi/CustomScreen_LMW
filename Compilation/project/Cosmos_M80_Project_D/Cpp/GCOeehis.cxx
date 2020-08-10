#include "GCOeehis.hpp"
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

void GCIDeleteGCOeehis( GBaseObject *pObject )
{
	GCOeehis *pPanel = (GCOeehis*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCOeehis( GBaseObject *pObject )
{
	GCOeehis *pPanel = new GCOeehis;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCOeehis;
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
GCOeehis::GCOeehis()
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
GCOeehis::~GCOeehis()
{

}

#include "GCOeehis.prc"

short GCOeehis::CreateChildren( )
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

GPropertyInfo* GCOeehis::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


long GCOeehis::GNCTABLE00016OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00016OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00036OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00036OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00037OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00037OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00038OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00038OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00039OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00039OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00040OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00040OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00075OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00075OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00076OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00076OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00077OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00077OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00078OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00078OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00102OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00102OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00103OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00103OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00104OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00104OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00105OnCreate(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

long GCOeehis::GNCTABLE00105OnTimer(unsigned short usMessage, long lLParam, long lUParam)
{
	return TRUE;
}

