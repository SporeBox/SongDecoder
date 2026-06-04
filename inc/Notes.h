#pragma once

struct Note {
    const char* name;  // ex: "A4", "C#3"
    float frequency;   // Hz
};

// toate notele de la octava 2 la 6 (range chitara)
const Note NOTES[] = {
    {"C2",   65.41f},
    {"C#2",  69.30f},
    {"D2",   73.42f},
    {"D#2",  77.78f},
    {"E2",   82.41f},
    {"F2",   87.31f},
    {"F#2",  92.50f},
    {"G2",   98.00f},
    {"G#2", 103.83f},
    {"A2",  110.00f},
    {"A#2", 116.54f},
    {"B2",  123.47f},

    {"C3",  130.81f},
    {"C#3", 138.59f},
    {"D3",  146.83f},
    {"D#3", 155.56f},
    {"E3",  164.81f},
    {"F3",  174.61f},
    {"F#3", 185.00f},
    {"G3",  196.00f},
    {"G#3", 207.65f},
    {"A3",  220.00f},
    {"A#3", 233.08f},
    {"B3",  246.94f},

    {"C4",  261.63f},
    {"C#4", 277.18f},
    {"D4",  293.66f},
    {"D#4", 311.13f},
    {"E4",  329.63f},
    {"F4",  349.23f},
    {"F#4", 369.99f},
    {"G4",  392.00f},
    {"G#4", 415.30f},
    {"A4",  440.00f},
    {"A#4", 466.16f},
    {"B4",  493.88f},

    {"C5",  523.25f},
    {"C#5", 554.37f},
    {"D5",  587.33f},
    {"D#5", 622.25f},
    {"E5",  659.25f},
    {"F5",  698.46f},
    {"F#5", 739.99f},
    {"G5",  783.99f},
    {"G#5", 830.61f},
    {"A5",  880.00f},
    {"A#5", 932.33f},
    {"B5",  987.77f},

    {"C6",  1046.50f},
    {"C#6", 1108.73f},
    {"D6",  1174.66f},
    {"D#6", 1244.51f},
    {"E6",  1318.51f},
};

const int NOTE_COUNT = sizeof(NOTES) / sizeof(NOTES[0]);

// cauta nota cea mai apropiata de frecventa data
// returneaza nullptr daca frecventa e in afara marjei
const Note* find_note(float frequency, float margin_cents = 50.0f);
void printNote(const Note* note);