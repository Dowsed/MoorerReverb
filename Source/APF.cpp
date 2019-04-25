/*
  ==============================================================================

    APF.cpp
    Created: 4 Apr 2019 1:32:14pm
    Author:  Justin Zemgulys

  ==============================================================================
*/

#include "APF.h"
#include <math.h>

float APF::processSample(float x, int channel){
    
    float delayIn = x + (-gain * delaySig);
    delaySig = delay.processSample(delayIn, channel);

    float y = delaySig + (gain * delayIn);
    
    return y;
};

void APF::setFs(float Fs){
    if (Fs == 44100 || Fs == 48000 || Fs == 88200 || Fs == 96000 || Fs == 192000){
        this->Fs = Fs;
        delay.setFs(Fs);
    }
};

float APF::getFs(){
    return Fs;
};

void APF::setDelaySamples(int delaySamples){
    this->delaySamples = delaySamples;
    delay.setDelaySamples(delaySamples);
};

float APF::getDelaySamples(){
    return delaySamples;
};

void APF::setDelayMs(float delayMs){
    this->delayMs = delayMs;
    delay.setDelaySamples(delayMs * .001 * Fs);
};

float APF::getDelayMs(){
    return delayMs;
};

void APF::setGain(float gain){
    this->gain = gain;
};

float APF::getGain(){
    return gain;
};

void APF::setModAmp(float m){
    delay.setModAmp(m);
};

void APF::setFreqLFO(float f){
    delay.setFreqLFO(f);
};

