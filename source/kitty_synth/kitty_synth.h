/*
 *  kitty_synth - kitty_synth.h
 *  Created by saf on 10-12-09
 *  Copyright (c) 2010 None, All rights reserved
 */

#ifndef KITTY_SYNTH_H
#define KITTY_SYNTH_H

#include <stdio.h>
#include <math.h>
#include "audioeffectx.h"
#include "oscillator.h"
#include "envelope.h"
#include "midi_message.h"
#include "midi_manager.h"


// TODO: Add your parameters to this list
enum {
  // kFirstParameter = 0,
  kNumParameters
};


// TODO: Change these values to reflect your plugin's configuration
const int kNumPrograms = 0;
const int kNumInputs = 0;
const int kNumOutputs = 2;
const unsigned long kUniqueId = 'IKKS';


class kitty_synth : public AudioEffectX {
public:
  kitty_synth(audioMasterCallback audioMaster);
  ~kitty_synth();
  
  virtual VstInt32 canDo(char *text);
  virtual bool copyProgram(long destination);
  
  virtual VstInt32 getCurrentMidiProgram(VstInt32 channel, MidiProgramName *currentProgram);
  virtual bool getEffectName(char *name);
  virtual bool getMidiKeyName(VstInt32 channel, MidiKeyName *keyName);
  virtual VstInt32 getMidiProgramCategory(VstInt32 channel, MidiProgramCategory *category);
  virtual VstInt32 getMidiProgramName(VstInt32 channel, MidiProgramName *midiProgramName);
  virtual VstInt32 getNumMidiInputChannels();
  virtual VstInt32 getNumMidiOutputChannels();
  virtual bool getOutputProperties(VstInt32 index, VstPinProperties *properties);
  virtual float getParameter(VstInt32 index);
  virtual void getParameterDisplay(VstInt32 index, char *text);
  virtual void getParameterLabel(VstInt32 index, char *label);
  virtual void getParameterName(VstInt32 index, char *text);
  virtual VstPlugCategory getPlugCategory();
  virtual void getProgramName(char *name);
  virtual bool getProgramNameIndexed(VstInt32 category, VstInt32 index, char *text);
  virtual bool getProductString(char *text);
  virtual bool getVendorString(char *text);
  virtual VstInt32 getVendorVersion();
  
  virtual bool hasMidiProgramsChanged(VstInt32 channel);
  
  virtual VstInt32 processEvents(VstEvents *events);
  virtual void processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames);
  
  virtual void setSampleRate(float sampleRate);
  virtual void setParameter(VstInt32 index, float value);
  virtual void setProgram(VstInt32 index);
  virtual void setProgramName(char *name);  
  virtual void setBlockSize(VstInt32 blockSize);
  
private:
  MidiManager m_midi_manager;
  Oscillator *m_oscillators[NUM_OSCILLATORS];
  Oscillator *m_oscillator;
  Envelope   *m_amp_envelope;
};

#endif
