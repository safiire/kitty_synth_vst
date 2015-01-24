#include "kitty_synth.h"

extern int global_n;

int osc_index = 0;

VstInt32 kitty_synth::processEvents (VstEvents* ev) {
    int i;
    for(i = 0; i < ev->numEvents; i++){
        if(ev->events[i]->type == kVstMidiType){
            VstMidiEvent *midi_event = (VstMidiEvent*)ev->events[i]; 
            m_midi_manager.process_midi(midi_event->midiData);
            osc_index++;
        }
    }
    return 1;
}


void kitty_synth::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) {
    int i;
    float *left = outputs[0];
    float *right = outputs[1];

    for(i = 0; i < sampleFrames; i++){

      left[i]  = m_amp_envelope->value();
      right[i] = m_amp_envelope->value() * m_oscillator->value();
      

      //left[i] = right[i] = m_amp_envelope->value() * m_oscillators[osc_index % NUM_OSCILLATORS]->value();


      //left[i] = right[i] = m_amp_envelope->value() * m_oscillator->value();
      //left[i] = right[i] = m_oscillator->value();

      global_n++;
    }
}
