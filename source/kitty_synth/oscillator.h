#ifndef OSCILLATOR
#define OSCILLATOR

#include <math.h>
#include <assert.h>
#include "common.h"
#include "object.h"
#include "midi_manager.h"

enum {SINE, SAW, SQUARE, NUM_OSCILLATORS};


//  Every Oscillator is an Object
class Oscillator : public Object {

    private:
    float  m_frequency;
    float  m_position;
    float  m_midi_note;
    float  m_last_value;
    float  **m_wavetable_data;

    public:
    Oscillator(MidiManager *mm, float **wavetable_data);
    float value();
    virtual void midi_callback(MidiMessage &msg);
    float *current_wavetable();
    static float interpolate_linear(float pt1, float pt2, float fract);
    static float midi_to_frequency(float midi_note);
};

#endif
