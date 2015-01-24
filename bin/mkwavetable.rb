#!/usr/bin/env ruby 

##
script_dir = File.expand_path(File.dirname(__FILE__))
require "#{script_dir}/../lib/audio"

wavename = ARGV.first

puts "Generating #{wavename} Wavetables using Maths!"
File.open("source/kitty_synth/#{wavename}_table.h", 'w') do |fp|
    names = []
    fp.puts "#ifndef #{wavename.upcase}_H"
    fp.puts "#define #{wavename.upcase}_H"
    ##  Followed by 128 literal array assignments, or 1 for sine
    if wavename == 'sine'
        midi = 1
        ary = `bin/mkwavetable #{midi} #{wavename}`
        name = "#{wavename}_midi#{midi}"
        fp.puts "float #{name}[4096] = #{ary.tr('[]','{}')};"
        names = [name] * 128
    else
        (0..127).to_a.map do |midi|
            hash = midi_to_hash(midi)
            print "\n" if midi % 12 == 0 and (not midi.zero?)
            print "#{hash[:name]} "
            ary = `bin/mkwavetable #{midi} #{wavename}`
            name = "#{wavename}_midi#{midi}"
            fp.puts "float #{name}[4096] = #{ary.tr('[]','{}')};"
            names << name
        end
    end
    print "\n"
    ##  Followed by a mass assignment of those 128 values to saw_table
    fp.puts "float *#{wavename}_table[128] = #{names.to_s.tr('[]"', '{} ') };"
    fp.puts "#endif"
end
