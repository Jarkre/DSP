//// Header ->
//
//#ifndef __SPECTRUMANALYZER__
//#define __SPECTRUMANALYZER__
//
//#include "IPlug_include_in_plug_hdr.h"
//#include "PeakEQ.h"
//#include "fft.h"
//#define WDL_FFT_REALSIZE 8
//#define FFT_BUFFERSIZE 1024
//
//class Graph : public IControl
//{
//public:
//    Graph(IPlugBase* pPlug, int x, int y, int width, int height, int paramIdx);
//    bool Draw(IGraphics* pGraphics);
//    bool IsDirty(){return true;};
//    void SetGraphVals(double* mag);
//   
//private:
//    IPlugBase *m_pPlug;
//    double * FFTmag;
//};
//
//
//class SpectrumAnalyzer : public IPlug
//{
//public:
//    SpectrumAnalyzer(IPlugInstanceInfo instanceInfo);
//    ~SpectrumAnalyzer();
//
//    void Reset();
//    void OnParamChange(int paramIdx);
//    void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);
//    double sinc(double x);
//    bool IsDirty(){return true;};
//    void FFT(double *in, int fftbuffersize);
//
//private:
//    void CreateParams();
//    void CreateGraphics();
//    void CreatePresets();
//    double *mFreqVek;
//    int mMaxIndex;
//    Graph *graph;
//    double *blackman;
//    const double a0 = (1-0.16)/2;
//    const double a1 = 1/2;
//    const double a2 = 0.16/2;
//    CPeakEQ	**peq;  
//    int bins;
//    WDL_FFT_COMPLEX *fftbuffer;
//    WDL_FFT_COMPLEX *sortedbuffer;
//    WDL_FFT_COMPLEX *unsortedbuffer;
//    double magFFT[FFT_BUFFERSIZE];
//    
//
//};
//
//#endif
//
//// <- Header end
//
//// cpp Start ->
//
//#define MAXCHNS 8
//
//const int kNumPrograms = 1;
//
//enum EParams
//{
//    kGain = 0,
//    kFreq,
//    kQ,
//    kGraphDummy,
//    kNumParams
//};
//
//enum ELayout
//{
//    kWidth  = GUI_WIDTH,
//    kHeight = GUI_HEIGHT,
//    
//    kGainX  = GUI_WIDTH/10,
//    kGainY  = GUI_HEIGHT-GUI_HEIGHT/6,
//    
//    kFreqX  = 2*GUI_WIDTH/10,
//    kFreqY  = GUI_HEIGHT-GUI_HEIGHT/6,
//    
//    kQX     = 3*GUI_WIDTH/10,
//    kQY     = GUI_HEIGHT-GUI_HEIGHT/6,
//    
//    kKnobFrames = 60,
//    
//    kGraph_X = 50,
//    kGraph_Y = 0,
//    kGraph_W = GUI_WIDTH -2*kGraph_X,
//    kGraph_H = GUI_HEIGHT/2,
//};
//
//typedef struct {
//    const char* name;
//    const int x;
//    const int y;
//    const double defaultVal;
//    const double minVal;
//    const double maxVal;
//    const double stepSize;
//} parameterProperties_struct;
//
//const parameterProperties_struct parameterProperties[kNumParams] =
//{
//    {.name = "Gain",        .x = kGainX, .y = kGainY, .defaultVal = 0.0,    .minVal = -24.0,    .maxVal = 24.0,     .stepSize = 0.25},
//    {.name = "Frequency",   .x = kFreqX, .y = kFreqY, .defaultVal = -57.0,  .minVal = 0.0,      .maxVal = 123.0                     },
//    {.name = "Q-Factor",    .x = kQX,    .y = kQY,    .defaultVal = 1.0,    .minVal = 0.25,     .maxVal = 4.0,      .stepSize = 0.125}
//};
//
//
//
//SpectrumAnalyzer::SpectrumAnalyzer(IPlugInstanceInfo instanceInfo)
//:	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo)
//{
//
//    TRACE;
//
//    CreateParams();
//    CreateGraphics();
//    CreatePresets();
//    WDL_fft_init();
//
//}
//
//SpectrumAnalyzer::~SpectrumAnalyzer() 
//{
//    for (int kk = 0; kk < MAXCHNS; kk++)
//    {
//        delete peq[kk]; // destroy the EQs
//        peq[kk] = 0;
//    }
//    delete[] peq; 
//    peq = 0;
//    delete[] mFreqVek;
//    mFreqVek = 0;
//    delete [] unsortedbuffer;
//    delete [] sortedbuffer;
//    delete [] fftbuffer;
//    delete [] blackman;
//}
//
//void SpectrumAnalyzer::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
//{
//    // Mutex is already locked for us.
//
//    bool bInputConnected;
//
//    for (int cc = 0; cc < MAXCHNS; cc++)
//    {
//        bInputConnected = IsInChannelConnected(cc);
//        if (bInputConnected) 
//        {
//            double *in = inputs[cc];
//            double *out = outputs[cc];
//
//            peq[cc]->processSamples(in, out, nFrames);
//            
//            FFT(in, FFT_BUFFERSIZE);
//            
//        }
//    }
//}
//
//void SpectrumAnalyzer::Reset()
//{
//    TRACE;
//    IMutexLock lock(this);
//    for (int cc = 0; cc < MAXCHNS;cc++)
//    {
//        peq[cc]->reset();
//    }
//
//}
//
//void SpectrumAnalyzer::OnParamChange(int paramIdx)
//{
//    IMutexLock lock(this);
//    //  double fs = GetSampleRate();
//
//    double Gain, Freq, Q;
//    int index;
//    switch (paramIdx)
//    {
//        case kGain:
//        Gain = GetParam(kGain)->Value();
//        for (int cc = 0; cc < MAXCHNS;cc++)
//        {
//            peq[cc]->setGain(Gain);
//        }
//        break;
//            
//        case kFreq:
//        index = GetParam(kFreq)->Value();
//        Freq = mFreqVek[index];
//        for (int cc = 0; cc < MAXCHNS;cc++)
//        {
//            peq[cc]->setFreq(Freq);
//        }
//        break;
//            
//        case kQ:
//        Q = GetParam(kQ)->Value();
//        for (int cc = 0; cc < MAXCHNS;cc++)
//        {
//            peq[cc]->setQFactor(Q);
//        }
//        break;
//
//        default:
//        break;
//    }
//}
//
//double SpectrumAnalyzer::sinc(double x)
//{
//    if(x == 0)
//    {
//        return 1;
//    }
//    return sin(PI*x)/(PI*x);
//}
//
//
//
//void SpectrumAnalyzer::FFT(double *in, int fftbuffersize)
//{
//    static int qq = 0;
//
//
//
//    if (qq==fftbuffersize)
//    {
//        WDL_fft(fftbuffer, fftbuffersize, false);
//
//        for (int i = 0; i < fftbuffersize; i++)
//        {
//            int j = WDL_fft_permute(fftbuffersize, i);
//            
//            blackman[i] =  (a0 - a1*cos((2*M_PI*i)/(fftbuffersize-1)) + a2*cos((4*M_PI*i)/(fftbuffersize-1)));
//            
//            sortedbuffer[i].re = fftbuffer[j].re ;
//            
//            sortedbuffer[i].im = fftbuffer[j].im ;
//            
//            magFFT[i] = ((sqrt(sortedbuffer[i].re*sortedbuffer[i].re + sortedbuffer[i].im*sortedbuffer[i].im)));
//            
//        }
//        
//        qq=0;
//        
//    }
//    
//    fftbuffer[qq].re = *in ;
//    
//    fftbuffer[qq].im = 0 ;
//
//    qq++;
//
//}
//
//
//Graph::Graph(IPlugBase *pPlug, int x, int y, int width, int height, int paramIdx)
//: IControl(pPlug, IRECT(x,y,width,height))
//{
//    mPlug = pPlug;
//}
//
//bool Graph::Draw(IGraphics *pGraphics)
//{
//    double mag = 0 ,x = kGraph_X;
//    int bins = FFT_BUFFERSIZE/2;
//
//    for (int i=0; i<bins; i++)
//    {
//        if (FFTmag[i] > double(kGraph_H)/2.)
//        {
//            mag = double(kGraph_H)/2.;
//        }
//        else
//        {
//            mag = FFTmag[i];
//        }
//
//        pGraphics->DrawLine(    &COLOR_BLACK,
//                                x,              //x1
//                                kGraph_Y+kGraph_H-FFTmag[i],       //y1
//                                x + double(kGraph_W)/double(bins) ,              //x2
//                                kGraph_Y+kGraph_H-FFTmag[i+1]   // y2
//                            );
//        x= x + double(kGraph_W)/double(bins);
//    }
//    return true;
//}
//
//void Graph::SetGraphVals(double* mag)
//{
//    FFTmag = mag;
//}
//
//
//void SpectrumAnalyzer::CreateParams()
//{
//    bins = FFT_BUFFERSIZE/2;
//    fftbuffer = new WDL_FFT_COMPLEX[FFT_BUFFERSIZE];
//    sortedbuffer = new WDL_FFT_COMPLEX[FFT_BUFFERSIZE];
//    unsortedbuffer = new WDL_FFT_COMPLEX[FFT_BUFFERSIZE];
//    blackman = new double[FFT_BUFFERSIZE];
//    
//    mMaxIndex = 124;
//    mFreqVek = new double[mMaxIndex];
//    int LowestSemitone = -57;
//    int HighestSemitone = 66;
//    double StandardPitchFreq = 440.;
//    
//    for (int kk = LowestSemitone; kk <= HighestSemitone ;kk++)
//    {
//        mFreqVek[kk-LowestSemitone] = StandardPitchFreq*pow(2,double(kk)/12.);
//    }
//    
//    for (int i=0;i<FFT_BUFFERSIZE;i++)  //initialize buffer
//    {
//        magFFT[i]=0;
//    }
//    
//    for (int i = 0; i<kNumParams; i++)
//    {
//        IParam *param = GetParam(i);
//        const parameterProperties_struct& properties = parameterProperties[i];
//        switch (i) {
//           
//            case kGain:
//                param->InitDouble(properties.name, properties.defaultVal, properties.minVal, properties.maxVal, properties.stepSize);
//                param->SetShape(1.);
//                break;
//           
//            case kFreq:
//                param->InitInt(properties.name, properties.defaultVal, properties.minVal, properties.maxVal);
//                break;
//            
//            case kQ:
//                param->InitDouble(properties.name, properties.defaultVal, properties.minVal, properties.maxVal, properties.stepSize);
//                param->SetShape(2.);
//                break;
//           
//            default:
//                break;
//        }
//        
//    }
//    for (int i; i<kNumParams; i++) {
//        OnParamChange(i);
//    }
//        
//    double Gain = 00;
//    double Freq = 1000;
//    double Q = 1;
//    double fs = GetSampleRate();
//    
//    // Multi-Channel EQ
//    peq = new CPeakEQ*[MAXCHNS];
//    
//    for (int kk = 0; kk < MAXCHNS; kk++)
//    {
//        peq[kk] = new CPeakEQ(Gain,Freq,fs,Q);
//    }
//    
//}
//
//void SpectrumAnalyzer::CreateGraphics()
//{
//    int fps =25;
//    IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight,fps);
//    
//    pGraphics->AttachPanelBackground(&COLOR_WHITE);
//
//    IBitmap knob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, kKnobFrames);
//    
//    graph = new Graph(this, kGraph_X, kGraph_Y, kGraph_W, kGraph_H, kGraphDummy);
//    
//    graph->SetGraphVals(magFFT);
//    
//    pGraphics->AttachControl(graph);
//    
//    pGraphics->AttachControl(new IKnobMultiControl(this, kGainX, kGainY, kGain, &knob));
//    
//    pGraphics->AttachControl(new IKnobMultiControl(this, kFreqX, kFreqY, kFreq, &knob));
//    
//    pGraphics->AttachControl(new IKnobMultiControl(this, kQX, kQY, kQ, &knob));
//
//    AttachGraphics(pGraphics);
//}
//
//void SpectrumAnalyzer::CreatePresets()
//{
//    //MakePreset("preset 1", ... );
//    MakeDefaultPreset((char *) "-", kNumPrograms);
//}
//
//// cpp end <-
