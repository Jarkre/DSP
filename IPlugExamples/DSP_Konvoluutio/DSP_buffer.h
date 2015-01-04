#ifndef __DSP_buffer__
#define __DSP_buffer__

#include "IControl.h"

class DspBuffer
{
public:
	DspBuffer() {};
	// DspBuffer(int* array, int size);
	~DspBuffer();
	void Initialize(int* dspArray, int size, IColor color);
	int GetDspBbufferData(int i) {return dspBufferData[i];}
	int GetDspBufferSize() {return size;}
	IColor GetDspBufferColor() {return color;}

private:
	IColor color;
	int* dspBufferData;
	int size;
};

#endif