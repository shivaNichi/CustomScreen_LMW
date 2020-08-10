#if !defined _GCDOWNTIMEDATA_HPP_
#define _GCDOWNTIMEDATA_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCDowntimedata : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		KEY_ACTION = 16,
		GBUTTON00002 = 2,
		GBUTTON00003 = 3,
		GBUTTON00004 = 4,
		GBUTTON00005 = 5,
		GBUTTON00006 = 6,
		GBUTTON00007 = 7,
		GBUTTON00008 = 8,
		GBUTTON00009 = 9,
		GBUTTON00010 = 10,
		GBUTTON00011 = 11,
		GBUTTON00012 = 12,
		GBUTTON00013 = 13,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCDowntimedata();
	virtual ~GCDowntimedata();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long KEY_ACTIONOnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnKeyPress(unsigned short usMessage, long lLParam, long lUParam );
	long KEY_ACTIONOnTimer(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCDowntimedata( GBaseObject *pObject );
short GCINewGCDowntimedata( GBaseObject *pObject );
}
#endif /* _GCDOWNTIMEDATA_HPP_ */

