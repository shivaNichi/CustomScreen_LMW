#include "GCHelpWindow1HelpFrame.hpp"
#include "GCButton.hpp"
#include "GCPicture.hpp"
#include "GCSampleScreen.hpp"
#include "GEvent.h"
#include "GResource.h"

extern "C"
{

void GCIDeleteGCHelpWindow1HelpFrame( GBaseObject *pObject )
{
	GCHelpWindow1HelpFrame *pFrame = (GCHelpWindow1HelpFrame*)pObject->pSelf;
	delete pFrame;
	pObject->pSelf = NULL;
}	
short GCINewGCHelpWindow1HelpFrame( GBaseObject *pObject )
{
	GCHelpWindow1HelpFrame *pFrame = new GCHelpWindow1HelpFrame;
	if( pFrame == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pFrame;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCHelpWindow1HelpFrame;
	pFrame->SetGBaseObject( pObject );
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
GCHelpWindow1HelpFrame::GCHelpWindow1HelpFrame()
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
GCHelpWindow1HelpFrame::~GCHelpWindow1HelpFrame()
{

}

GCClassCBMP(GCHelpWindow1HelpFrame)
GCEndClassCBMP()

#include "GCHelpWindow1HelpFrame.prc"

short GCHelpWindow1HelpFrame::CreateChildren( )
{
	GBaseObject *pChild;

	unsigned int i;
	for( i = 1; i < sizeof(pProperty)/sizeof(GBaseWindowProperty*); i++ ){
		pChild = GCSCreateInstance( GCSGetScreen( m_pSelf ),
							pProperty[i]->usType, pProperty[i], GetGBaseObject() );
		AddChild( pChild );
		GCSCreate( pChild, GetGBaseObject() );
	}
	return TRUE;
}

GPropertyInfo* GCHelpWindow1HelpFrame::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPanelPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPanelPropertyInfo;
}

