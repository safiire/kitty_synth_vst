#include "midi_message.h"


//  Init and parse a midi message
MidiMessage::MidiMessage(char *midi_data){
    char status = midi_data[0];
    status &= 0x7f;  // Zero the most significant bit
    m_channel = status & 0x0f;
    m_status  = (status & 0xf0) >> 4;
    m_data1   = midi_data[1];
    m_data2   = midi_data[2];
}


//  What channel is this targetting?
char MidiMessage::channel(){
    return m_channel;
}


//  What is data1?
char MidiMessage::data1(){
    return m_data1;
}


//  What is data2?
char MidiMessage::data2(){
    return m_data2;
}


//  What is status?
int MidiMessage::status(){
    return m_status;
}


//  NoteOff  number
char NoteOff::note_number(){
}


//  NoteOff  velocity
char NoteOff::velocity(){

}


//  NoteOn 
char NoteOn::note_number(){
}


char NoteOn::velocity(){

}


//  PolyAftertouch  note number
char PolyAftertouch::note_number(){
}


//  PolyAftertouch  pressure
char PolyAftertouch::pressure(){
}


//  ControlChange  number
char ControlChange::control_number(){
}


//  ControlChange  data
char ControlChange::data(){
}


//  ProgramChange  number
char ProgramChange::program_number(){
}


//  ChannelAftertouch 
char ChannelAftertouch::pressure(){
}


//  PitchWheel 
int PitchWheel::value(){
    int v = m_data2;
    v = v << 8;
    v += m_data1;
    return v;
}

