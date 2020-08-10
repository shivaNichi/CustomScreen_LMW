#if !defined _GCHELPWINDOW1HELPFRAME_HPP_
#define _GCHELPWINDOW1HELPFRAME_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCSVFrame.hpp"


class GCHelpWindow1HelpFrame : public GCSVFrame
{
public:

	//{{PANEL_ID
	enum {
		PANEL000 = 1,
		PANEL001 = 2,
		PANEL002 = 3,
	};
	//}}PANEL_ID

	//{{PUBLIC_METHOD
	GCHelpWindow1HelpFrame();
	virtual ~GCHelpWindow1HelpFrame();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP();
	//}}PROTECTED_METHOD
};

extern "C"
{
void GCIDeleteGCHelpWindow1HelpFrame( GBaseObject *pObject );
short GCINewGCHelpWindow1HelpFrame( GBaseObject *pObject );
}
#endif /* _GCHELPWINDOW1HELPFRAME_HPP_ */

