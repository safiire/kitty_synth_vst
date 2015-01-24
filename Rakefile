require 'rake/clean'
require 'rake/loaders/makefile'

####
##  Constants
KittySynthPackage = "dist/kitty_synth.vst"
KittySynthSrc     = FileList['source/kitty_synth/*.cpp', 'source/vst2.x/*.cpp']
KittySynthBin     = "dist/kitty_synth.vst/Contents/MacOS/kitty_synth"
MkWavetableBin    = 'bin/mkwavetable'
KittySynthObj     = KittySynthSrc.sub(/\.cpp$/, '.o')
Wavetables        = ['saw', 'square', 'sine']
WavetablesH       = ['source/kitty_synth/saw_table.h', 'source/kitty_synth/square_table.h', 'source/kitty_synth/sine_table.h']


#  Task to build my_vst
desc "Build Kitty Synth"
task :build_kitty_synth => [MkWavetableBin, 'source/kitty_synth/sine_table.h', 'source/kitty_synth/saw_table.h', 'source/kitty_synth/square_table.h', "dist/kitty_synth.vst/Contents/MacOS/kitty_synth"]


#  Generate the sine wavetable
file 'source/kitty_synth/sine_table.h' =>  MkWavetableBin do 
    sh "bin/mkwavetable.rb sine"
end

#  Generate the saw wavetable
file 'source/kitty_synth/saw_table.h' =>  MkWavetableBin do 
    sh "bin/mkwavetable.rb saw"
end

#  Generate the square wavetable
file 'source/kitty_synth/square_table.h' =>  MkWavetableBin do 
    sh "bin/mkwavetable.rb square"
end

####
##   Link object code together
ENV['OBJECTS'] = KittySynthObj.to_s
file KittySynthBin => KittySynthObj do |t|
      sh "clang++ -g -bundle $OBJECTS -o #{t.name}"
end


####
##   Rule to incrementally compile 
Flags = "-g -Wno-write-strings -I source/kitty_synth -I include/vst2.x -I include"
ENV['FLAGS'] = Flags
rule ".o" => [".cpp"] do |t|
    sh "clang++ $FLAGS -c -o #{t.name} #{t.source}"
end


####
##  Set the relation between the cpp files and o files
KittySynthSrc.each do |src|
      file src.ext(".o") => src
end

####
##  Install Kitty Synth
desc "Install Kitty Synth"
task :install_kitty_synth => KittySynthBin do
    sh "rm -rf /Library/Audio/Plug-Ins/VST/kitty_synth.vst"
    sh "cp -R #{KittySynthPackage} /Library/Audio/Plug-Ins/VST/"
end


####
##  The binary for mkwavetable
file MkWavetableBin => ["source/mkwavetable/mkwavetable.c"] do
    puts "Building mkwavetable..."
    sh "cc source/mkwavetable/mkwavetable.c -I include -o #{MkWavetableBin}"
end


####
##  Cleanup
CLEAN.include(['include/sine_table.h', 'include/saw_table.h', 'include/square_table.h', 'include/wavetables/*.h', KittySynthBin, MkWavetableBin])
CLEAN.include(['dist/kitty_synth.vst/Contents/MacOS/kitty_synth.dSYM/']);
CLEAN.include(["*/*/*.o"])

task :default => [:build_kitty_synth, :install_kitty_synth]

