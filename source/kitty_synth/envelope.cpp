#include "envelope.h"

////
//  Constructor
Envelope::Envelope(MidiManager *mm){
  m_midi_manager = mm;
  m_target = 0.f;
  m_value  = 0.f;
  m_attack_rate = 0.001f;
  m_decay_rate  = 0.001f;
  m_sustain_level = 0.5f;
  m_release_rate = 0.01f;
  m_state = ATTACK;
}


////
//  Noteon has happened
void Envelope::note_on(){
    m_target = 1.f;
    m_rate = m_attack_rate;
    m_state = ATTACK;
}


////
//  Noteoff has happened
void Envelope::note_off(){
    m_target = 0.f;
    m_rate   = m_release_rate;
    m_state = RELEASE;
}


////
//  Set the rate of attack 
void Envelope::set_attack_rate(float rate){
    m_attack_rate = rate < 0.f ? -m_rate : m_rate;
}


////
//  Set the rate of decay 
void Envelope::set_decay_rate(float rate){
    m_decay_rate = rate < 0.f ? -m_rate : m_rate;
}


////
//  Set the sustain level
void Envelope::set_sustain_level(float level){
    m_sustain_level = level < 0.f ? 0.f : level;
}


////
//  Set the rate of release 
void Envelope::set_release_rate(float rate){
    m_release_rate = rate < 0.f ? -m_rate : m_rate;
}


////
//  Set the attack in time
void Envelope::set_attack_time(float time){
    m_attack_rate = time < 0.f ? (1.0 / (-time * 44100.0f)) : (1.0 / (time * 44100.0f));
}


////
//  Set the decay in time
void Envelope::set_decay_time(float time){
    m_decay_rate = time < 0.f ? (1.0 / (-time * 44100.0f)) : (1.0 / (time * 44100.0f));
}


////
//  Set the release in time
void Envelope::set_release_time(float time){
    m_release_rate = time < 0.f ? (m_sustain_level / (-time * 44100.0f)) : (m_sustain_level / (time * 44100.0f));
}


////
//  Set ADSR
void Envelope::set_adsr(float a, float d, float s, float r){
    set_attack_time(a);
    set_decay_time(d);
    set_sustain_level(s);
    set_release_time(r);
}


////
//  Set target
void Envelope::set_target(float target){
    m_target = target;
    if(m_value < m_target) {
        m_state = ATTACK;
        set_sustain_level(m_target);
        m_rate = m_attack_rate;
    }
    if(m_value > m_target){
        set_sustain_level(m_target);
        m_state = DECAY;
        m_rate  = m_decay_rate;
    }
}


////
//  Set the value
void Envelope::set_value(float value){
    m_state = SUSTAIN;
    m_target = value;
    m_value = value;
    set_sustain_level(m_value);
    m_rate = 0.f;
}


////
//  Get the state
int Envelope::get_state(){
    return m_state;
}

////
//  Midi callback 
void Envelope::midi_callback(MidiMessage &msg){
    switch(msg.status()){
    case MidiNoteOn:
        note_on();
        break;
    case MidiNoteOff:
        note_off();
        break;
    }
}


////
//  Value of envelope at n
float Envelope::value(){
    switch(m_state){
    case ATTACK:
      m_value += m_rate;
      if(m_value >= m_target){
        m_value = m_target;
        m_rate = m_decay_rate;
        m_target = m_sustain_level;
        m_state = DECAY;
      }
      break;
    case DECAY:
      m_value -= m_decay_rate;
      if(m_value <= m_sustain_level){
        m_value = m_sustain_level;
        m_rate  = 0.f;
        m_state = SUSTAIN;
      }
      break;
    case RELEASE:
      m_value -= m_release_rate;
      if(m_value <= 0.f){
        m_value = 0.f;
        m_state = CLOSED;
      }
    }
    m_last_output = m_value;
    return m_value;
    /*
    switch(m_state){
        case ATTACK:
          return 1.0f;
        case DECAY:
          return 1.0f;
        case SUSTAIN:
          return 1.0f;
        case RELEASE:
          return 0.0f;
        case CLOSED:
          return 0.0f;
    }
    */
}
