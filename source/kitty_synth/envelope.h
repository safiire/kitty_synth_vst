#ifndef ENVELOPE_H
#define ENVELOPE_H

#include "object.h"
#include "midi_manager.h"


class Envelope : public Object {

    private:
    enum {ATTACK, DECAY, SUSTAIN, RELEASE, CLOSED};
    int m_state;
    float m_rate;
    float m_target;
    float m_value;
    float m_attack_rate;
    float m_decay_rate;
    float m_sustain_level;
    float m_release_rate;
    float m_last_output;

    public:
    Envelope(MidiManager *mm);
    virtual void midi_callback(MidiMessage &msg);
    float value();
    void note_on();
    void note_off();
    void set_attack_rate(float rate);
    void set_decay_rate(float rate);
    void set_sustain_level(float rate);
    void set_release_rate(float rate);
    void set_attack_time(float time);
    void set_decay_time(float time);
    void set_release_time(float time);
    void set_adsr(float a, float d, float s, float r);
    void set_target(float target);
    void write_state(int x);
    void set_value(float value);
    int  get_state();
};


#endif
