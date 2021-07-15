// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "helpers.h"

/* GLOBAL VARIABLE DECLARATINS */

float freq; // inicialize frequency as a float

// Put all notes in a long array (version with sharp notation)
string keyboardSharp[84] =
{
    "C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "A#1", "B1",
    "C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2",
    "C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3",
    "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A#4", "B4",
    "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "B5",
    "C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "A#6", "B6",
    "C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "A#7", "B7"
};

// Put all notes in a long array (version with flat notation)
string keyboardFlat[84] =
{
    "C1", "Db1", "D1", "Eb1", "E1", "F1", "Gb1", "G1", "Ab1", "A1", "Bb1", "B1",
    "C2", "Db2", "D2", "Eb2", "E2", "F2", "Gb2", "G2", "Ab2", "A2", "Bb2", "B2",
    "C3", "Db3", "D3", "Eb3", "E3", "F3", "Gb3", "G3", "Ab3", "A3", "Bb3", "B3",
    "C4", "Db4", "D4", "Eb4", "E4", "F4", "Gb4", "G4", "Ab4", "A4", "Bb4", "B4",
    "C5", "Db5", "D5", "Eb5", "E5", "F5", "Gb5", "G5", "Ab5", "A5", "Bb5", "B5",
    "C6", "Db6", "D6", "Eb6", "E6", "F6", "Gb6", "G6", "Ab6", "A6", "Bb6", "B6",
    "C7", "Db7", "D7", "Eb7", "E7", "F7", "Gb7", "G7", "Ab7", "A7", "Bb7", "B7"
};

/* HELPER FUNCTIONS DECLARATIONS */

float getFrequencyWithSharps(string a);
float getFrequencyWithFlats(string a);
float getFrequencyRegular(string a);

/* MAIN FUNCTIONS DEFINITIONS */

// duration function: converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int x_int = (int) fraction[0];
    int y_int = (int) fraction[2];

    if (y_int == 52) // ASCII representation of denominator 4
    {
        x_int = (x_int - 48) * (8 / (y_int - 48)); // Convert ASCII of numerator as equivalent for denominator = 8
    }
    if (y_int == 50) // ASCII representation of denominator 2
    {
        x_int = (x_int - 48) * (8 / (y_int - 48)); // Convert ASCII of numerator as equivalent for denominator = 8
    }
    if (y_int == 49) // ASCII representation of denominator 1
    {
        x_int = (x_int - 48) * (8 / (y_int - 48)); // Convert ASCII of numerator as equivalent for denominator = 8
    }
    if (y_int == 56) // ASCII representation for denominator 8
    {
        x_int = (x_int - 48); //  Convert ASCII of numerator
    }
    return x_int;
}


// frequency function: calculates frequency (in Hz) of a note
int frequency(string note)
{
    if (strlen(note) == 3) // Determine if note has flat or sharps (length 3)
    {
        if (note[1] == '#')  // check if note has sharps
        {
            getFrequencyWithSharps(note);
        }

        if (note[1] == 'b') // check if note has flats
        {
            getFrequencyWithFlats(note);
        }
    }

    else // if note is a regular note (length 2)
    {
        getFrequencyRegular(note);
    }
    return round(freq); // round freq to the nearest integer
}


// is_rest function: determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


/* HELPER FUNCTIONS DEFINITIONS */

// getFrequencyWithSharps: gets frequency from array with sharps
float getFrequencyWithSharps(string a)
{
    int noteInx; // index of the note passed as argument
    for (int i = 0; i < 84; i++)
    {
        if (strcmp(keyboardSharp[i], a) == 0) // if note in array matches note passed as argument store index in noteInx
        {
            noteInx = i;
        }
    }

    float noteDiff = 45 - noteInx; // calculate the "distance" between note and A4

    if ((noteDiff) < 0) // if note is to the right of A4
    {
        noteDiff *= (-1); // get absolute value of "distance"
        freq = 440 * pow(2, noteDiff / 12); // calculate note's frequency

    }
    else // if note is to the left of A4

    {
        freq = 440 / pow(2, noteDiff / 12);
    }
    return freq;
}

// getFrequencyWithFlats: gets frequencies from array with flats
float getFrequencyWithFlats(string a)
{
    int noteInx; // index of the note passed as argument
    for (int i = 0; i < 84; i++)
    {
        if (strcmp(keyboardFlat[i], a) == 0) // if note in array matches note passed as argument store index in noteInx
        {
            noteInx = i;
        }
    }
    float noteDiff = 45 - noteInx; // calculate the "distance" between note and A4

    if ((noteDiff) < 0) // if note is to the right of A4
    {
        noteDiff = (-1) * noteDiff; // get absolute value of "distance"
        freq = 440 * pow(2, noteDiff / 12); // calculate note's frequency
    }
    else // if note is to the left of A4
    {
        freq = 440 / pow(2, noteDiff / 12);
    }
    return freq;
}

// getFrequencyRegular: gets frequencies from regular notes (using either array - no difference)
float getFrequencyRegular(string a)
{
    int noteInx; // index of the note passed as argument
    for (int i = 0; i < 84; i++)
    {
        if (strcmp(keyboardFlat[i], a) == 0) // if note in array matches note passed as argument store index in noteInx
        {
            noteInx = i;
        }
    }
    float noteDiff = 45 - noteInx; // calculate the "distance" between note and A4

    if ((noteDiff) < 0) // if note is to the right of A4
    {
        noteDiff = (-1) * noteDiff; // get absolute value of "distance"
        freq = 440 * pow(2, noteDiff / 12); // calculate note's frequency
    }
    else // if note is to the left of A4
    {
        freq = 440 / pow(2, noteDiff / 12);
    }
    return freq;
}
