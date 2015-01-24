#include <cstdlib>
#include "midi_manager.h"


////
// Contstructor
MidiManager::MidiManager(){
    //  Nothing  yet
}


////
//  Process a midi message
void MidiManager::process_midi(char *midi_data){
    //  There is a list of request objects which may
    //  indicate that an object is interested in this MidiMessage
    int i;
    MidiMessage midi(midi_data);

    for(i = 0; i < m_midi_message_requests.size(); i++){
        if(m_midi_message_requests[i]->match(midi)){
            m_midi_message_requests[i]->requestor()->midi_callback(midi);
        }
    }
}


////
//  Request to be called back
void MidiManager::callback_request(const MidiMessageRequest &request){
    // Make a copy of this the request
    MidiMessageRequest *copy = new MidiMessageRequest(request);
    m_midi_message_requests.push_back(copy);
}





