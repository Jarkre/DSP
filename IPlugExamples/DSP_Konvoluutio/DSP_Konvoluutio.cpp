
#include "DSP_Konvoluutio.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"
#include "DSP_Konvo_grafiikka.h"


const int kNumPrograms = 1;

enum EParams
{
  kGain = 0,
  kNumParams
};

enum ELayout
{
  kWidth = GUI_WIDTH,
  kHeight = GUI_HEIGHT,

  kGainX = 100,
  kGainY = 100,

  // kGainX = GUI_WIDTH - 50,
  // kGainY = GUI_HEIGHT - 50,
  kKnobFrames = 60
};

DSP_Konvoluutio::DSP_Konvoluutio(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo), mGain(1.)
{
  TRACE;

  time_t t;
  srand((unsigned) time(&t));

  //arguments are: name, defaultVal, minVal, maxVal, step, label
  GetParam(kGain)->InitDouble("Gain", 50., 0., 100.0, 0.01, "%");
  GetParam(kGain)->SetShape(1.);

  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
  // pGraphics->AttachPanelBackground(&COLOR_GRAY);
  pGraphics->AttachBackground(GRIDDISPLAY_ID, GRIDDISPLAY_FN);
  // pGraphics->AttachBackground(SAMPLE_ID, SAMPLE_FN);


  // IBitmap knob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, kKnobFrames);
  // pGraphics->AttachControl(new IKnobMultiControl(this, kGainX, kGainY, kGain, &knob));

  AttachGraphics(pGraphics);

/// Grafiikka testiä ->
  IRECT dspKonvoGrafArea;
  dspKonvoGrafArea.L = 0;
  dspKonvoGrafArea.T = 0;
  dspKonvoGrafArea.R = GUI_WIDTH;
  dspKonvoGrafArea.B = GUI_HEIGHT;

  dspKonvoGrafControl = new DspKonvoGrafControl(this, dspKonvoGrafArea); 
  pGraphics->AttachControl(dspKonvoGrafControl);

  IText textProps(18, &COLOR_WHITE, "Arial");
  IRECT tmpRect = IRECT(50, 30, 50, 170);
  irText = new ITextControl(this, tmpRect, &textProps, "Teksti"); 
  pGraphics->AttachControl(irText);

/// <- Grafiikkatestiä.

  //dspKonvoGrafControl->Draw(pGraphics);

  //MakePreset("preset 1", ... );
  MakeDefaultPreset((char *) "-", kNumPrograms);
}

DSP_Konvoluutio::~DSP_Konvoluutio() {}

void DSP_Konvoluutio::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
  // Mutex is already locked for us.

  IGraphics* pGraphics = GetGUI();

  double* in1 = inputs[0];
  double* in2 = inputs[1];
  double* out1 = outputs[0];
  double* out2 = outputs[1];

  for (int s = 0; s < nFrames; ++s, ++in1, ++in2, ++out1, ++out2)
  {
    *out1 = *in1 * mGain;
    *out2 = *in2 * mGain;


// Grafiikka testiä ->
	//static int counter = 0;
	//counter++;
	//if(counter < 100)  // Sample rate divided by frame rate
	//	goto out;

	//counter = 0;

	dspKonvoGrafControl->SetAmpValue(out1);
	dspKonvoGrafControl->SetDirty(true);
	dspKonvoGrafControl->Draw(pGraphics);

	// char textString[40] = {0};
	// double value = AmpToDB(*out1);
	// sprintf(textString, "%lf", ampValue);
	// irText->SetTextFromPlug(textString);

// Grafiikka testiä <-


  }

out:
  ;

}

void DSP_Konvoluutio::Reset()
{
  TRACE;
  IMutexLock lock(this);
  SetBlockSize(1); 
}

void DSP_Konvoluutio::OnParamChange(int paramIdx)
{



  IMutexLock lock(this);

  switch (paramIdx)
  {
    case kGain:
      mGain = GetParam(kGain)->Value() / 100.;
      break;

    default:
      break;
  }
}
