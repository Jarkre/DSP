#include "IControl.h"
#include "DSP_Konvo_grafiikka.h"
#include "resource.h"
#include "DSP_ImpulseResponse.h"
#include "DSP_buffer.h"
#include "DSP_SignalGraph.h"

DspKonvoGrafControl::DspKonvoGrafControl(IPlugBase *pPlug, IRECT pR) : IControl(pPlug, pR)
{
		//DspKonvoGrafControl(IPlugBase *pPlug, IRECT pR)
	//	: IControl(pPlug, pR)

	randomNumber.Seed();
}

bool DspKonvoGrafControl::Draw(IGraphics* pGraphics)
{

/// Amp value koodi ->

	// Pylvään korkeus riippuu signaaliarvosta.

	//int i = 0;
	//IRECT barCoord; 
	//int barWidth = 10;
	//IRECT filledBit;

	//barCoord.L = 60; 
	//barCoord.T = 100; 
	//barCoord.R = barCoord.L + barWidth;
	//barCoord.B = GUI_HEIGHT;

	//barCoord.T = (*ampValue) * 1000;
	//filledBit = IRECT(barCoord.L, GUI_HEIGHT - barCoord.T , barCoord.L + barWidth , GUI_HEIGHT);
	//pGraphics->FillIRect(&COLOR_BLUE, &filledBit);

/// Amp value koodi <-

/// Alkuper koodi ->
	int impulseResponse[] = {140, 130, 120, 110, 100};
	int inputSignal[] = {20,30,40,50,60,70,80,90,100,110};
	int convolution[] = {60,70,80,90,100,100,90,80,70,60,50,40,30,20};


	IColor irColor(255,45,56,76);
	IColor inpColor(255,78,35,64);
	IColor convColor(255,98,95,34);

	DspBuffer irBuffer;
	irBuffer.Initialize(impulseResponse, DSP_IMPULSE_RESPOSE_SIZE, irColor);

	DspBuffer inpSignalBuffer;
	inpSignalBuffer.Initialize(inputSignal, DSP_INPUT_BUFFER_SIZE, inpColor);

	DspBuffer convolBuffer;
	convolBuffer.Initialize(convolution, DSP_CONVOL_SIZE, convColor);

	DSPsignalGraph ir(60, 100);
	DSPsignalGraph inpSignal( 200, 100);
	DSPsignalGraph convolGraph( 400, 100);

	ir.AttachBuffer(&irBuffer);
	inpSignal.AttachBuffer(&inpSignalBuffer);
	convolGraph.AttachBuffer(&convolBuffer);	

	ir.DrawGraph(pGraphics);
	inpSignal.DrawGraph(pGraphics);
	convolGraph.DrawGraph(pGraphics);


/// Alkuper koodi <-

	return true;

}

