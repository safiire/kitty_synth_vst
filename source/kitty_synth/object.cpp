#include "object.h"
#include "midi_message_request.h"
#include "midi_manager.h"

////
//   Every object has a callback for midi
void Object::midi_callback(MidiMessage &msg){
  //  Nothing by default
}


////
//   Every object can request a callback for a MIDI message
void Object::callback_request(int type, int channel, int cc){
  MidiMessageRequest request(this, type, channel, cc);
  m_midi_manager->callback_request(request);
}
