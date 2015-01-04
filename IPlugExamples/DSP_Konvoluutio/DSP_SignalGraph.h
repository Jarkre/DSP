#ifndef __DSP_signalgraph__
#define __DSP_signalgraph__

#include "DSP_buffer.h"

class DSPsignalGraph
{
public:
	DSPsignalGraph(int x, int y);
	void DrawGraph(IGraphics* pGraphics);
	void AttachBuffer(DspBuffer* buffer);
	void SetCoord(IRECT coordinates);
private:
	DspBuffer* dspBuffer;
	IRECT   coord;
};
#endif