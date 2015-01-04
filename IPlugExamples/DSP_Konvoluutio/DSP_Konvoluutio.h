#ifndef __DSP_KONVOLUUTIO__
#define __DSP_KONVOLUUTIO__

#include "IPlug_include_in_plug_hdr.h"
#include "DSP_Konvo_grafiikka.h"

class DSP_Konvoluutio : public IPlug
{
public:
  DSP_Konvoluutio(IPlugInstanceInfo instanceInfo);
  ~DSP_Konvoluutio();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
  double mGain;
  DspKonvoGrafControl* dspKonvoGrafControl;
  ITextControl* irText;
};

#endif
