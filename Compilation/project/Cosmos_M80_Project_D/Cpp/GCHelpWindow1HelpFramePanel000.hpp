#if !defined _GCHELPWINDOW1HELPFRAMEPANEL000_HPP_
#define _GCHELPWINDOW1HELPFRAMEPANEL000_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCHelpWindow1HelpFramePanel000 : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		GLABEL00003 = 3,
		GLABEL00004 = 4,
		GLABEL00005 = 5,
		GLABEL00006 = 6,
		GLABEL00007 = 7,
		GLABEL00008 = 8,
		GLABEL00009 = 9,
		GLABEL00010 = 10,
		GLABEL00011 = 11,
		GLABEL00012 = 12,
		GLABEL00013 = 13,
		GLABEL00048 = 48,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCHelpWindow1HelpFramePanel000();
	virtual ~GCHelpWindow1HelpFramePanel000();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	//}}CALLBACK_METHOD

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCHelpWindow1HelpFramePanel000( GBaseObject *pObject );
short GCINewGCHelpWindow1HelpFramePanel000( GBaseObject *pObject );
}
#endif /* _GCHELPWINDOW1HELPFRAMEPANEL000_HPP_ */

