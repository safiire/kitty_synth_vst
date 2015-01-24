#include "kitty_synth.h"
#include "sine_table.h"
#include "saw_table.h"
#include "square_table.h"


//// 
//  Returns an instance of this VSTi
AudioEffect* createEffectInstance(audioMasterCallback audioMaster) {
	return new kitty_synth(audioMaster);
}


////
//  Constructor for this VSTi synth
kitty_synth::kitty_synth(audioMasterCallback audioMaster) : AudioEffectX(audioMaster, kNumPrograms, kNumParameters) {
  if(audioMaster != NULL) {
    setNumInputs(kNumInputs);
    setNumOutputs(kNumOutputs);
    setUniqueID(kUniqueId);
    canProcessReplacing();
    isSynth();
  }

  m_oscillators[SINE]   = new Oscillator(&m_midi_manager, sine_table);
  m_oscillators[SAW]    = new Oscillator(&m_midi_manager, saw_table );
  m_oscillators[SQUARE] = new Oscillator(&m_midi_manager, square_table);

  //  Set the starting oscillator to square
  m_oscillator = m_oscillators[SQUARE];

  //  Set up messaging for each oscillator
  int i;
  for(i = 0; i < NUM_OSCILLATORS; i++){
      //                                 Type         Channel       CC#
      m_oscillators[i]->callback_request(MidiNoteOn,  MidiWildcard, MidiWildcard);
      m_oscillators[i]->callback_request(MidiNoteOff, MidiWildcard, MidiWildcard);
  }

  //  Set up messaging for my volume envelope
  m_amp_envelope = new Envelope(&m_midi_manager);
  //                               Type         Channel       CC#
  m_amp_envelope->callback_request(MidiNoteOn,  MidiWildcard, MidiWildcard);
  m_amp_envelope->callback_request(MidiNoteOff, MidiWildcard, MidiWildcard);

  //  Set the initial ADSR values
  m_amp_envelope->set_adsr(1.f, 0.5f, 0.5f, 1.f);

  suspend();
}


////
//  Destructor for the synth
kitty_synth::~kitty_synth() {
}




VstInt32 kitty_synth::canDo(char *text) {
  // TODO: Fill in according to your plugin's capabilities
  if(!strcmp(text, "receiveVstEvents")) {
		return 1;
  }
  else if(!strcmp(text, "receiveVstMidiEvent")) {
		return 1;
  }
	else if(!strcmp(text, "midiProgramNames")) {
		return 1;
  }
  
  // -1 => explicitly can't do; 0 => don't know
	return 0;
}

bool kitty_synth::copyProgram(long destination) {
  // TODO: Copy program to destination
  return false;
}

VstInt32 kitty_synth::getCurrentMidiProgram(VstInt32 channel, MidiProgramName *mpn) {
	VstInt32 prg = 0;
  // TODO: Look up your current MIDI program and fill the MidiProgramName with it
	return prg;
}

bool kitty_synth::getEffectName(char* name) {
  strncpy(name, "kitty_synth", kVstMaxProductStrLen);
  return true;
}

bool kitty_synth::getMidiKeyName(VstInt32 channel, MidiKeyName *key) {
	// TODO: Fill in this information
  // key->thisProgramIndex;		// >= 0. fill struct for this program index.
	// key->thisKeyNumber;			// 0 - 127. fill struct for this key number.
	key->keyName[0] = 0;
	key->reserved = 0;				// zero
	key->flags = 0;					// reserved, none defined yet, zero.
	return true;
}

VstInt32 kitty_synth::getMidiProgramCategory(VstInt32 channel, MidiProgramCategory *category) {
  // TODO: Get the MIDI program category
	return 0;
}

VstInt32 kitty_synth::getMidiProgramName(VstInt32 channel, MidiProgramName *mpn) {
  // TODO: Return the MIDI program name
  return 0;
}

VstInt32 kitty_synth::getNumMidiInputChannels() {
  // TODO: Change this value for polyphonic synths
  return 1;
}

VstInt32 kitty_synth::getNumMidiOutputChannels() {
  // TODO: Change this value if you are sending MIDI output back to the host
  return 0;
}

bool kitty_synth::getOutputProperties(VstInt32 index, VstPinProperties *properties) {
  if(index < kNumOutputs) {
    sprintf(properties->label, "%1ld Out", (long)index + 1);
		properties->flags = kVstPinIsActive;
		if(index < 2) {
			properties->flags |= kVstPinIsStereo;
    }
    return true;
  }
  return false;
}

float kitty_synth::getParameter(VstInt32 index) {
  // TODO: Get parameter value for index
  return 0.0;
}

void kitty_synth::getParameterDisplay(VstInt32 index, char *text) {
  // TODO: Get parameter display for index
}

void kitty_synth::getParameterLabel(VstInt32 index, char *text) {
  // TODO: Get parameter label for index
}

void kitty_synth::getParameterName(VstInt32 index, char *text) {
  // TODO: Get parameter name for index
}

VstPlugCategory kitty_synth::getPlugCategory() { 
  return kPlugCategSynth;
}

bool kitty_synth::getProductString(char* text) {
  // TODO: Replace with actual description of your synth
  strncpy(text, "kitty_synth", kVstMaxProductStrLen);
  return true;
}

void kitty_synth::getProgramName(char *name) {
  // TODO: Copy active program name into "name" string
}

bool kitty_synth::getProgramNameIndexed(VstInt32 category, VstInt32 index, char *text) {
  // TODO: Return program name for index
  return false;
}

bool kitty_synth::getVendorString(char* text) {
  strncpy(text, "None", kVstMaxVendorStrLen);
  return true;
}

VstInt32 kitty_synth::getVendorVersion() {
  // TODO: Return actual version of this plugin
  return 1000;
}

bool kitty_synth::hasMidiProgramsChanged(VstInt32 channel) {
  // TODO: Return true/false if the MIDI programs have changed
  return false;
}

void kitty_synth::setBlockSize(VstInt32 blockSize) {
  // TODO: Handle this call if necessary
	AudioEffectX::setBlockSize(blockSize);
}

void kitty_synth::setParameter(VstInt32 index, float value) {
  // TODO: Set parameter value for index
}

void kitty_synth::setProgram(VstInt32 index) {
  // TOOD: Set local variables based on program parameters
}

void kitty_synth::setProgramName(char *name) {
  // TODO: Set program name
}

void kitty_synth::setSampleRate(float sampleRate) {
  // TODO: Handle this call if necessary
	AudioEffectX::setSampleRate(sampleRate);
}
