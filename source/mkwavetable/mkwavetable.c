#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "common.h"

//  Enums
enum {SAW, SQUARE, SINE};

//  The tables
float sinetable[WavetableSize];
float sawtable[WavetableSize];


void create_sinetable(void){
    int n;
    for(n = 0; n < WavetableSize; n++){
        sinetable[n] = sin(TwoPi * (float)n/WavetableSizeF);
    }
}


void create_sawtable(int midi_note, int shape){
    //  Figure out how many partials this midi note has.
    float frequency = Tuning * pow(2, (midi_note - 69) / 12.0f);
    int   num_harmonics = (int)(Fs * 0.5f / frequency);
    int   harmonic_step = shape == SQUARE ? 2 : 1;
    int   n, h;
    float m;

    //  Zero this table
    for(n = 0; n < WavetableSize; n++){ sawtable[n] = 0.0f; }

    //  Each harmonic
    for(h = 0; h < num_harmonics; h += harmonic_step){
        int partial = h + 1;
        m = cos((float)h * HalfPi / (float)num_harmonics); // Gibbs
        m *= m;                                            // Reduction
        m /= (float)partial;                               // <- Right here

        for(n = 0; n < WavetableSize; n++){
            //  This is really interesting
            sawtable[n] += m * sinetable[(n*partial) % WavetableSize];
        }
    }
}


void normalize(float *buffer){
    int n;
    float max_value = 0.0f;
    for(n = 0; n < WavetableSize; n++){
        if(buffer[n] > max_value){ max_value = buffer[n]; }
    }
    for(n = 0; n < WavetableSize; n++){
        buffer[n] *= (1.0f / max_value);
    }
}


////
//  Main, Usage is ./program <frequency>
int main(int argc, char **argv){
    int n;
    int midi_note;

    float *output_table;

    if(argc < 3){
      printf("Usage: %s <midi_note> <sine|saw|square>\n", argv[0]);
      exit(1);
    }

    //  Do up the arguments
    midi_note = atoi(argv[1]);

    //  Always need the sine table
    create_sinetable();

    if(!strcmp("sine", argv[2])){
        output_table = sinetable;

    } else if(!strcmp("square", argv[2])){
        create_sawtable(midi_note, SQUARE);
        output_table = sawtable;

    } else if(!strcmp("saw", argv[2])){
        create_sawtable(midi_note, SAW);
        output_table = sawtable;
    }else{
      printf("Usage: %s <midi_note> <sine|saw|square>\n", argv[0]);
      exit(1);
    }

    normalize(output_table);

    //  Output
    printf("[");
    for(n = 0; n < WavetableSize; n++){
        printf("%f", output_table[n]);
        if(n != WavetableSize - 1){ printf(", "); }
    }
    printf("]");

    return 0;
}
