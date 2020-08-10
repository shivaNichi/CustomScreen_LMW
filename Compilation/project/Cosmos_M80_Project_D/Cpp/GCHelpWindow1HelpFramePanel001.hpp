#if !defined _GCHELPWINDOW1HELPFRAMEPANEL001_HPP_
#define _GCHELPWINDOW1HELPFRAMEPANEL001_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCHelpWindow1HelpFramePanel001 : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		GLABEL00015 = 15,
		GLABEL00016 = 16,
		GLABEL00017 = 17,
		GLABEL00018 = 18,
		GLABEL00019 = 19,
		GLABEL00020 = 20,
		GLABEL00021 = 21,
		GLABEL00022 = 22,
		GLABEL00024 = 24,
		GLABEL00049 = 49,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCHelpWindow1HelpFramePanel001();
	virtual ~GCHelpWindow1HelpFramePanel001();

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
void GCIDeleteGCHelpWindow1HelpFramePanel001( GBaseObject *pObject );
short GCINewGCHelpWindow1HelpFramePanel001( GBaseObject *pObject );
}
#endif /* _GCHELPWINDOW1HELPFRAMEPANEL001_HPP_ */

