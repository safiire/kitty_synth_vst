#ifndef OBJECT_H
#define OBJECT_H

#include "midi_message.h"

class MidiManager;

//  This is my baseclass object that everything should derive from
//  this makes every object support receiving messages
class Object {
    protected:
    MidiManager *m_midi_manager;

    public:
    virtual void midi_callback(MidiMessage &msg);
    void callback_request(int type, int channel, int cc);
};

#endif
