
GCClassCBMP(GCCalculator)
	GCDefCBMsg(GM_CB_ONKEYRELEASE, GSOFTKEY00001, GSOFTKEY00001OnKeyRelease )
	GCDefCBMsg(GM_CB_ONCREATE, GSOFTKEY00001, GSOFTKEY00001OnCreate )
GCEndClassCBMP()

static const GFocusInformation pGSoftKey00001FocusInformation =
{
	0,
	NULL
};


static const GSoftKeyProperty pGSoftKeypProperty[1] =
{

	{{{GSOFTKEY, GCCalculator::GSOFTKEY00001, 0, 0, 271, 198, GW_STYLE_CAPTION | GW_STYLE_VISIBLE | GW_STYLE_ENABLE, (GFocusInformation*)&pGSoftKey00001FocusInformation}}, ID_STRING00164, 0, 0, 0, 1, 0, RGB32(192,192,192), RGB32(0,0,0), RGB32(255,255,255), RGB32(0,0,0), RGB32(192,192,192), 256, 0, 1, GFOCUS_EFFECT_CURSOR, GCURSOR_TYPE_NORMAL, RGB32(99,107,222), RGB32(255,255,255), 0, 0, 0, RGB32(99,107,222), RGB32(255,255,255), 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

static GPropertyInfo pGPropertyInfo[2] =
{
	{NULL, {0, 0}},
	{(void *)&pGSoftKeypProperty[0], {4, 116}},
};

static const GBaseWindowProperty *pProperty[2] =
{
	(const GBaseWindowProperty*) NULL,
	(const GBaseWindowProperty*) &pGSoftKeypProperty[0]
};

