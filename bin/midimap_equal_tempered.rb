#!/usr/bin/env ruby

script_dir = File.expand_path(File.dirname(__FILE__))
require "#{script_dir}/../lib/audio"

puts midi_map_equal_tempered
