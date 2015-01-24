#ifndef SINE_OSCILLATOR
#define SINE_OSCILLATOR

#include "oscillator.h"

class Sine : public Oscillator {

    public:
    void bang(Message &msg);

    private:
    float **wavetable_data();
};

#endif

