#include "GCHelpWindow1HelpFramePanel001.hpp"
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

void GCIDeleteGCHelpWindow1HelpFramePanel001( GBaseObject *pObject )
{
	GCHelpWindow1HelpFramePanel001 *pPanel = (GCHelpWindow1HelpFramePanel001*)pObject->pSelf;
	delete pPanel;
	pObject->pSelf = NULL;
}	
short GCINewGCHelpWindow1HelpFramePanel001( GBaseObject *pObject )
{
	GCHelpWindow1HelpFramePanel001 *pPanel = new GCHelpWindow1HelpFramePanel001;
	if( pPanel == NULL ){
		return FALSE;
	}

	pObject->usType = 0;
	pObject->pSelf = pPanel;
	pObject->GCIMessageProcedure = &GCIBaseWindowMessageProcedure;
	pObject->GCICallBackMessageProcedure = &GCIBaseWindowCallBackMessageProcedure;
	pObject->GCIDeleteObject = &GCIDeleteGCHelpWindow1HelpFramePanel001;
	pPanel->SetGBaseObject( pObject );
	return TRUE;
}
}
/*
 *	<summary>		:	�R���X�g���N�^�B
 *
 *	<parameter>		:	�Ȃ�
 *
 *	<return>		:	�Ȃ�
 *
 *	<description>	:	�R���X�g���N�^
 */
GCHelpWindow1HelpFramePanel001::GCHelpWindow1HelpFramePanel001()
{
}

/*
 *	<summary>		:	�f�X�g���N�^�B
 *
 *	<parameter>		:	�Ȃ�
 *
 *	<return>		:	�Ȃ�
 *
 *	<description>	:	�f�X�g���N�^
 */
GCHelpWindow1HelpFramePanel001::~GCHelpWindow1HelpFramePanel001()
{

}

#include "GCHelpWindow1HelpFramePanel001.prc"

short GCHelpWindow1HelpFramePanel001::CreateChildren( )
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

GPropertyInfo* GCHelpWindow1HelpFramePanel001::GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt)
{
	if (pGPropertyInfoCnt != NULL)
	{
		*pGPropertyInfoCnt = sizeof(pGPropertyInfo) / sizeof(GPropertyInfo);
	}
	return pGPropertyInfo;
}


