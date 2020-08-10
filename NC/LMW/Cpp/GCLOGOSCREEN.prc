
GCClassCBMP(GCLOGOSCREEN)
	GCDefCBMsg(GM_CB_ONKEYPRESS, DATA, DATAOnKeyPress )
	GCDefCBMsg(GM_CB_ONTIMER, DATA, DATAOnTimer )
	GCDefCBMsg(GM_CB_ONCREATE, DATA, DATAOnCreate )
GCEndClassCBMP()

static const GFocusInformation pGPicture00000FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pGLabel00001FocusInformation =
{
	0,
	NULL
};

static const GFocusInformation pDATAFocusInformation =
{
	0,
	NULL
};


static const GBasicControlProperty pGBasicControlpProperty[1] =
{

	{{{GBASICCONTROL, GCLOGOSCREEN::DATA, 569, 426, 63, 34, GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pDATAFocusInformation}}}
};
static const GLabelProperty pGLabelpProperty[1] =
{

	{{{GLABEL, GCLOGOSCREEN::GLABEL00001, 50, 345, 540, 36, GW_STYLE_CAPTION | GW_STYLE_VISIBLE, (GFocusInformation*)&pGLabel00001FocusInformation}}, ID_STRING00103,{RGB32(0,0,147), GCAPTION_POS_RIGHT, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00102,{GCSCROLL_SCROLL_ENABLE, GCSCROLL_REPEAT_SCROLL, 0, 10, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}}
};
static const GDesign pGPicture00000Design[1] = {
	{{ FILL_BACK_COLOR , RGB32(192,192,192), RGB32(192,192,192)} , ID_IMAGE00002}
};

static const GVector pGPicture00000Vector[1] = {
	{0 , 0, 1, 10000, 100}
};

static const GPicturePropertyEx pGPicturepProperty[1] =
{

	{{{{GPICTURE, GCLOGOSCREEN::GPICTURE00000, 0, 0, 640, 480, GW_STYLE_CAPTION | GW_STYLE_VISIBLE, (GFocusInformation*)&pGPicture00000FocusInformation}}, 0,{RGB32(0,0,0), GCAPTION_POS_CENTER, GCAPTION_POS_CENTER, 0, 0, 0, 0}, ID_FONT00000, 0, GPCTR_DISP_IMAGE, 1, (GDesign*)pGPicture00000Design,{GCSCROLL_SCROLL_DISABLE, GCSCROLL_ONE_SCROLL, 0, 100, 1, GCSCROLL_START_NOW},{GCBLINK_BLINK_DISABLE, GCBLINK_CHANGE_VISIBLE_STRING, RGB32(255,255,255)}}, (GVector*)pGPicture00000Vector, GPCTR_EFFECT_NONE, GPCTR_EFFECT_NONE, 100, 0}
};

static GPropertyInfo pGPropertyInfo[4] =
{
	{NULL, {0, 0}},
	{(void *)&pGPicturepProperty[0], {4, 90}},
	{(void *)&pGLabelpProperty[0], {4, 68}},
	{(void *)&pGBasicControlpProperty[0], {4, 20}},
};

static const GBaseWindowProperty *pProperty[4] =
{
	(const GBaseWindowProperty*) NULL,
	(const GBaseWindowProperty*) &pGPicturepProperty[0],
	(const GBaseWindowProperty*) &pGLabelpProperty[0],
	(const GBaseWindowProperty*) &pGBasicControlpProperty[0]
};

