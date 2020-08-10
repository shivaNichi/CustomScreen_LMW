#if !defined _GCCALCULATOR_HPP_
#define _GCCALCULATOR_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCCalculator : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		GSOFTKEY00001 = 1,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCCalculator();
	virtual ~GCCalculator();

	virtual short CreateChildren();
	virtual GPropertyInfo* GetPropertyInfo(const GBaseWindowProperty* pImport, unsigned short* pGPropertyInfoCnt);
	//}}PUBLIC_METHOD
	
	//{{CALLBACK_METHOD
	long GSOFTKEY00001OnCreate(unsigned short usMessage, long lLParam, long lUParam );
	long GSOFTKEY00001OnKeyRelease(unsigned short usMessage, long lLParam, long lUParam );
	//}}CALLBACK_METHOD

protected:
	//{{PROTECTED_METHOD
	GCDefCBMP()
	//}}PROTECTED_METHOD
};

extern "C"{
void GCIDeleteGCCalculator( GBaseObject *pObject );
short GCINewGCCalculator( GBaseObject *pObject );
}
#endif /* _GCCALCULATOR_HPP_ */

