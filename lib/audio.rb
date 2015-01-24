##  A little Ruby audio library
require 'json'


##  Convert from midi to frequency
def midi_to_f(midi)
    440 * 2**((midi-69)/12.0)
end

##  Frequency to midi
def f_to_midi(frequency)
    69 + 12 * Math.log(frequency/440.0) / Math.log(2.0)
end


##  Midi to note name
def midi_to_note(midi)
    notes = [:c, :'c#', :d, :'d#', :e, :f, :'f#', :g, :'g#', :a, :'a#', :b]
    notes[midi.to_i % 12.0]
end


##  Midi to octave number
def midi_to_octave(midi)
    (midi / 12) - 2
end


##  Number of harmonics a frequency has when bandlimited
def num_harmonics(f0, fs = 44100)
    (fs / 2.0 / f0.to_f).to_i
end


##  Midi note info as a hash
def midi_to_hash(midi, fs = 44100)
    {:frequency => midi_to_f(midi),
     :name      => midi_to_note(midi),
     :harmonics => num_harmonics(midi_to_f(midi), fs),
     :octave    => midi_to_octave(midi),
     :midi      => midi
    }     
end


##  Pretty version of my equal tempered midi map
def midi_map_equal_tempered
    JSON.pretty_generate((0..127).to_a.map{|midi| midi_to_hash(midi)})
end


##  A function to preform linear interpolation
def linear_interpolation(index, table)
    index_whole = index.to_i
    index_fract = index - index_whole
    pt1 = table[index_whole]
    pt2 = table[index_whole + 1]
    slope = (pt2 - pt1) / 1.0
    slope * index_fract + 1
end





