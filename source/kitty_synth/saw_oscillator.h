#ifndef SAW_OSCILLATOR
#define SAW_OSCILLATOR

#include "oscillator.h"

class Saw : public Oscillator {

    public:
    void bang(Message &msg);

    private:
    float **wavetable_data();
};

#endif

