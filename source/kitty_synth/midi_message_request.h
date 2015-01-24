#ifndef MIDI_MESSAGE_REQUEST_H
#define MIDI_MESSAGE_REQUEST_H

#include "object.h"
#include "midi_message.h"

#define MidiWildcard -1

//  This structure represents a request for a certain stream of midi messsages
class MidiMessageRequest{
    public:
    MidiMessageRequest(Object *requestor, int message_types, int channel, int control_change);
    bool match(MidiMessage &message);
    Object *requestor();

    private:
    Object *m_requestor;
    int m_message_types;
    int m_channel;
    int m_control_change;
};

#endif
