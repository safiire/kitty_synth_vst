#include "oscillator.h"

extern int global_n;

//  Constructor
Oscillator::Oscillator(MidiManager *mm, float **wavetable_data){
    m_midi_manager = mm;
    m_wavetable_data = wavetable_data;
    m_midi_note = 69;

    ////Message msg = {MsgMidiNote, 69};
    //bang(msg);
}



//  Get the value at global_n
float Oscillator::value(){
    float *wavetable = current_wavetable();
    float  rate      = WavetableSizeF * m_frequency / Fs;

    //  TODO: This only works if it is a free running oscillator
    //  This will need to be modified by m_position somehow
    float  index  = fmod(global_n * rate, WavetableSizeF);

    //  index is now between 0 - 4096.0 (or whatever WavetableSizeF is)
    int   index_whole = (int)index;
    float index_fract = index - index_whole;

    float pt1 = wavetable[index_whole];
    float pt2 = wavetable[index_whole + 1];
    if(index_whole == WavetableSize - 1){
        pt2 = wavetable[0];  //  Wrap
    }

    float v = interpolate_linear(pt1, pt2, index_fract);

    assert(v <= 1.0f);

    return v;
}


//  Get the current wavetable we're rending from,
//  this is based on the current frequency and should 
//  ensure we get a wavetable that has exactly the right 
//  number of harmonics or less.
float *Oscillator::current_wavetable(){
    float **wt;
    int int_midi_note = (int)m_midi_note;
    return m_wavetable_data[int_midi_note];
}


////
//  Here we accpet external MIDI control
void Oscillator::midi_callback(MidiMessage &msg){
    if(msg.status() == MidiNoteOn){
        m_midi_note = msg.data1();
        m_frequency = midi_to_frequency(m_midi_note);
        //  Maybe also reset the position in wavetable
    }
}

//  Linear interpolate between two values
float Oscillator::interpolate_linear(float pt1, float pt2, float fract){
    float slope = (pt2 - pt1) / 1.0f;
    return slope * fract + pt1;
}


//  Class function to change Midi to Frequency
float Oscillator::midi_to_frequency(float midi_note){
    return Tuning * pow(2, (midi_note - 69) / 12.0f);
}
