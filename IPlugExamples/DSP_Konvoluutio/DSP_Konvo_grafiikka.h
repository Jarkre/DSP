#ifndef __DSP_KONVO_GRAF__
#define __DSP_KONVO_GRAF__

#include "RandomNumber.h"

class DspKonvoGrafControl : public IControl
{
public:
	DspKonvoGrafControl(IPlugBase *pPlug, IRECT pR);
	//DspKonvoGrafControl(IPlugBase *pPlug, IRECT pR)
	//	: IControl(pPlug, pR)
	//{
	//	randomNumber.Seed();
	//	// mHandleColor = COLOR_RED;
	//}

	~DspKonvoGrafControl() {}

	bool Draw(IGraphics* pGraphics);
	void SetAmpValue(double *value) {ampValue = value;}
	
private:
    RandomNumber randomNumber;
	double*		 ampValue;
};

#endif