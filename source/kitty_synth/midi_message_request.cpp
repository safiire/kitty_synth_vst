#include "midi_message_request.h"

//// 
//  Constructor
MidiMessageRequest::MidiMessageRequest(Object *requestor, int message_types, int channel, int control_change){
    m_requestor = requestor;
    m_message_types = message_types;
    m_channel = channel;
    m_control_change = control_change;
}


////
//  Does this Midi Message match this request?
bool MidiMessageRequest::match(MidiMessage &message){
    // For now yes
    return true;
}


////
//  Who requested this midi message?
Object *MidiMessageRequest::requestor(){
    return m_requestor;
}
