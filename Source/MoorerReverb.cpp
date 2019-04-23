/*
  ==============================================================================

    MoorerReverb.cpp
    Created: 4 Apr 2019 1:32:53pm
    Author:  Sean Newell, Rober Coomber

  ==============================================================================
*/

#ifndef MoorerReverb_cpp
#define MoorerReverb_cpp
#include "MoorerReverb.h"

MoorerReverb::MoorerReverb(){
    fbcf1.setDelaySamples(1426);
    fbcf2.setDelaySamples(1781);
    fbcf3.setDelaySamples(1973);
    fbcf4.setDelaySamples(2098);
    
    fbcf1.setGain(0.7f);
    fbcf2.setGain(0.7f);
    fbcf3.setGain(0.7f);
    fbcf4.setGain(0.7f);
    
    fbcf1.setDepth(.1);
    fbcf2.setDepth(.1);
    fbcf3.setDepth(.1);
    fbcf4.setDepth(.1);
    
    fbcf1.setRate(.99);
    fbcf2.setRate(.91);
    fbcf3.setRate(.93);
    fbcf4.setRate(.97);
    
    apf1.setModAmp(.1);
    apf2.setModAmp(.1);
    
    apf1.setFreqLFO(1.1);
    apf2.setFreqLFO(1.2);
    
    apf1.setGain(.7);
    apf2.setGain(.7);
    
    apf1.setDelaySamples(240);
    apf2.setDelaySamples(82);
    
};


float MoorerReverb::processSample(float x, int channel){
    
    // Send input into early reflections
    x = er1.processSample(x, channel);
    
    // Send input into each FBCF
    float x1 = fbcf1.processSample(x,channel);
    float x2 = fbcf2.processSample(x,channel);
    float x3 = fbcf3.processSample(x,channel);
    float x4 = fbcf4.processSample(x,channel);
    
    // Sum the FBCFs together
    x = x1 + x2 + x3 + x4;
    
    // Send processed input into APFs
    x = apf1.processSample(x, channel);
    x = apf2.processSample(x, channel);
    
    float y = x;
    
    return y;
};

void MoorerReverb::setReverbTime(float gain){
    fbcf1.setGain(gain + 0.06);
    fbcf2.setGain(gain - 0.07);
    fbcf3.setGain(gain);
    fbcf4.setGain(gain - .04);
    apf1.setGain(gain -.01);
    apf2.setGain(gain -.03);
}

void MoorerReverb::setDiffusion(float difValue){
    int delay = 60 + difValue*420;
    apf1.setDelaySamples(delay);
    apf2.setDelaySamples(delay/3);
};


void MoorerReverb::setModulation(float modValue){
    apf1.setModAmp(modValue);
    apf2.setModAmp(modValue);
    fbcf1.setDepth(modValue);
    fbcf2.setDepth(modValue);
    fbcf3.setDepth(modValue);
    fbcf4.setDepth(modValue);
};

#endif
