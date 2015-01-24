#ifndef MIDI_MANAGER_H
#define MIDI_MANAGER_H

#include "midi_message_request.h"
#include "midi_message.h"
#include "vector"

using namespace std;

class MidiManager{

    public:
    MidiManager();
    void callback_request(const MidiMessageRequest &request);
    void process_midi(char *midi_data);

    private:
    vector<MidiMessageRequest*> m_midi_message_requests;
};

#endif 
