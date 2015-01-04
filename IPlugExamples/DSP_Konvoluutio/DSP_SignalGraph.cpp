#include "DSP_SignalGraph.h"
#include "resource.h"

DSPsignalGraph::DSPsignalGraph(int x, int y)
{
		//barCoord.L = 60; 
	//barCoord.T = 100; 
	//barCoord.R = barCoord.L + barWidth;
	//barCoord.B = GUI_HEIGHT;


	coord.L = x;
	coord.T = y;
	coord.R = x+10;
	coord.B = GUI_HEIGHT;
}

void DSPsignalGraph::DrawGraph(IGraphics* pGraphics)
{

	int i = 0;
	// IRECT barCoord; 
	int barWidth = 10;
	
	IRECT filledBit;


	//barCoord.L = 60; 
	//barCoord.T = 100; 
	//barCoord.R = barCoord.L + barWidth;
	//barCoord.B = GUI_HEIGHT;

	for(i=0; i < dspBuffer->GetDspBufferSize() ; i++)
	{
		coord.T = dspBuffer->GetDspBbufferData(i);
		filledBit = IRECT(coord.L, GUI_HEIGHT - coord.T , coord.L + barWidth , GUI_HEIGHT);
		pGraphics->FillIRect(&(dspBuffer->GetDspBufferColor()), &filledBit);
		coord.L += barWidth;

	}

	//for(i=0; i < dspBuffer->GetDspBufferSize() ; i++)
	//{
	//	barCoord.T = dspBuffer->GetDspBbufferData(i);
	//	filledBit = IRECT(barCoord.L, GUI_HEIGHT - barCoord.T , barCoord.L + barWidth , GUI_HEIGHT);
	//	pGraphics->FillIRect(&(dspBuffer->GetDspBufferColor()), &filledBit);
	//	barCoord.L += barWidth;

	//}

}

void DSPsignalGraph::AttachBuffer(DspBuffer* buffer)
{
	dspBuffer = buffer;
}

void DSPsignalGraph::SetCoord(IRECT coordinates)
{
	IRECT coord(coordinates);
}