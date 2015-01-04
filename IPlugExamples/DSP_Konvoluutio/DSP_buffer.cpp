
#include "DSP_buffer.h"
#include "IControl.h"

#include "RandomNumber.h"

DspBuffer::~DspBuffer()
{
	delete [] dspBufferData;
}

void DspBuffer::Initialize(int* dspArray, int size, IColor color)
{
	RandomNumber randomNumber;
	// time_t t;
	// srand((unsigned) time(&t));

	int i = 0;
	dspBufferData = new int[size];
	for(i = 0; i < size; i++){
		// this->dspBufferData[i] = randomNumber.Get(0,200);
		this->dspBufferData[i] = dspArray[i];
	}
	this->size = size;
	this->color = color;
}
