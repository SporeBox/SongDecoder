#include "../inc/Notes.h"
#include <math.h>
#include <stdio.h>

const Note* find_note(float frequency, float margin_cents) {
    const Note* closest = nullptr;
    float min_distance = 999999.0f;

    for (int i = 0; i < NOTE_COUNT; i++) {
        // distanta in cents (1 semitona = 100 cents)
        // formula: cents = 1200 * log2(f_masurata / f_nota)
        float cents = 1200.0f * log2f(frequency / NOTES[i].frequency);
        float abs_cents = cents < 0 ? -cents : cents;

        if (abs_cents < min_distance) {
            min_distance = abs_cents;
            closest = &NOTES[i];
        }
    }

    // returneaza nota doar daca e in marja acceptata
    if (min_distance <= margin_cents) {
        return closest;
    }
    return nullptr;
}

void printNote(const Note* note){
    printf("%s", note->name);
}