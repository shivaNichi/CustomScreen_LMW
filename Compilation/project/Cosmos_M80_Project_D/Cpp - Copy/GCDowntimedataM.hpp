#if !defined _GCDOWNTIMEDATAM_HPP_
#define _GCDOWNTIMEDATAM_HPP_
#include "genifa.h"
#include "GWin.h"
#include "GCPanel.hpp"


class GCDowntimedataM : public GCPanel
{
public:

	//{{CONTROL_ID
	enum {
		GBUTTON00072 = 72,
		GLABEL00000 = 0,
		GLABEL00016 = 16,
		GLABEL00018 = 18,
		GLABEL00020 = 20,
		GLABEL00023 = 23,
		GLABEL00030 = 30,
		GLABEL00034 = 34,
		GLABEL00038 = 38,
		GLABEL00042 = 42,
		GLABEL00046 = 46,
		GLABEL00050 = 50,
		GLABEL00054 = 54,
		GLABEL00058 = 58,
		GLABEL00062 = 62,
		GLABEL00066 = 66,
		GLABEL00070 = 70,
		GNCDATATEXTBOX00015 = 15,
		GNCDATATEXTBOX00017 = 17,
		GNCDATATEXTBOX00019 = 19,
		GNCDATATEXTBOX00024 = 24,
		GNCDATATEXTBOX00026 = 26,
		GNCDATATEXTBOX00028 = 28,
		GNCDATATEXTBOX00031 = 31,
		GNCDATATEXTBOX00032 = 32,
		GNCDATATEXTBOX00033 = 33,
		GNCDATATEXTBOX00035 = 35,
		GNCDATATEXTBOX00036 = 36,
		GNCDATATEXTBOX00037 = 37,
		GNCDATATEXTBOX00039 = 39,
		GNCDATATEXTBOX00040 = 40,
		GNCDATATEXTBOX00041 = 41,
		GNCDATATEXTBOX00043 = 43,
		GNCDATATEXTBOX00044 = 44,
		GNCDATATEXTBOX00045 = 45,
		GNCDATATEXTBOX00047 = 47,
		GNCDATATEXTBOX00048 = 48,
		GNCDATATEXTBOX00049 = 49,
		GNCDATATEXTBOX00051 = 51,
		GNCDATATEXTBOX00052 = 52,
		GNCDATATEXTBOX00053 = 53,
		GNCDATATEXTBOX00055 = 55,
		GNCDATATEXTBOX00056 = 56,
		GNCDATATEXTBOX00057 = 57,
		GNCDATATEXTBOX00059 = 59,
		GNCDATATEXTBOX00060 = 60,
		GNCDATATEXTBOX00061 = 61,
		GNCDATATEXTBOX00063 = 63,
		GNCDATATEXTBOX00064 = 64,
		GNCDATATEXTBOX00065 = 65,
		GNCDATATEXTBOX00067 = 67,
		GNCDATATEXTBOX00068 = 68,
		GNCDATATEXTBOX00069 = 69,
		GSRECT00001 = 1,
	};
	//}}CONTROL_ID

	//{{PUBLIC_METHOD
	GCDowntimedataM();
	virtual ~GCDowntimedataM();

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
void GCIDeleteGCDowntimedataM( GBaseObject *pObject );
short GCINewGCDowntimedataM( GBaseObject *pObject );
}
#endif /* _GCDOWNTIMEDATAM_HPP_ */

