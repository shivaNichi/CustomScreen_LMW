#if !defined _GCHELPWINDOW1HELPFRAMEPANEL002_HPP_
#define _GCHELPWINDOW1HELPFRAMEPANEL002_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCHelpWindow1HelpFramePanel002 : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		GLABEL00025 = 25,
		GLABEL00026 = 26,
		GLABEL00027 = 27,
		GLABEL00028 = 28,
		GLABEL00029 = 29,
		GLABEL00030 = 30,
		GLABEL00031 = 31,
		GLABEL00032 = 32,
		GLABEL00033 = 33,
		GLABEL00034 = 34,
		GLABEL00035 = 35,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCHelpWindow1HelpFramePanel002();
	virtual ~GCHelpWindow1HelpFramePanel002();

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
void GCIDeleteGCHelpWindow1HelpFramePanel002( GBaseObject *pObject );
short GCINewGCHelpWindow1HelpFramePanel002( GBaseObject *pObject );
}
#endif /* _GCHELPWINDOW1HELPFRAMEPANEL002_HPP_ */

