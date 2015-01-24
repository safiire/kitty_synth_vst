#ifndef SQUARE_OSCILLATOR
#define SQUARE_OSCILLATOR

#include "oscillator.h"

class Square : public Oscillator {

    public:
    void bang(Message &msg);

    private:
    float **wavetable_data();
};

#endif

