#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "inc/inmp441.h"
#include "inc/kiss_fft.h"
#include "inc/Notes.h"

#define PIN_START    10
#define SAMPLE_RATE  44100
#define FFT_SIZE     1024

void print_frequency(INMP441<int32_t>& mic, kiss_fft_cfg& cfg, kiss_fft_cpx* cx_in, kiss_fft_cpx* cx_out, int32_t* samples) {
    mic.read_audio_interleaved(samples, FFT_SIZE * 2);

        // fereastra Hanning + normalizare
        for (int i = 0; i < FFT_SIZE; i++) {
            float window = 0.5f * (1.0f - cosf(2.0f * M_PI * i / (FFT_SIZE - 1)));
            cx_in[i].r = (float)(samples[i * 2]) / 8388608.0f * window;
            cx_in[i].i = 0.0f;
        }

        kiss_fft(cfg, cx_in, cx_out);

        // cauta bin-ul cu amplitudine maxima
        float max_amp = 0.0f;
        int dominant_bin = 1;

        for (int k = 1; k < FFT_SIZE / 2; k++) {
            float amp = sqrtf(cx_out[k].r * cx_out[k].r + cx_out[k].i * cx_out[k].i);
            if (amp > max_amp) {
                max_amp = amp;
                dominant_bin = k;
            }
        }

        float frequency = (float)dominant_bin * SAMPLE_RATE / FFT_SIZE;

        if (max_amp > 0.01f && frequency > 43.1f) {
            const Note* note = find_note(frequency);
            if (note) {
                printNote(note);
                printf("\n");
            } else {
                printf("Unknown freq: %.2f Hz\n", frequency);
            }
        }
}

int main() {
    stdio_init_all();
    sleep_ms(2000);
    printf("Starting...\n");

    kiss_fft_cfg cfg = kiss_fft_alloc(FFT_SIZE, 0, 0, 0);
    if (cfg == NULL) {
        printf("ERROR: kiss_fft_alloc failed\n");
        return 1;
    }

    INMP441<int32_t> mic(PIN_START, FFT_SIZE * 2, SAMPLE_RATE);
    printf("Mic init done\n");

    int32_t samples[FFT_SIZE * 2];
    kiss_fft_cpx cx_in[FFT_SIZE];
    kiss_fft_cpx cx_out[FFT_SIZE];

    while (true) {
        print_frequency(mic, cfg, cx_in, cx_out, samples);
        
    }

    kiss_fft_free(cfg);
    return 0;
}