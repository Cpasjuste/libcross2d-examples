//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

using namespace c2d;

#define SAMPLE_RATE 48000
#define FRAME_RATE (1000 / 60)
#define SAMPLE_COUNT (SAMPLE_RATE / FRAME_RATE)

void fill_audio_buffer(void *audio_buffer, size_t audio_size, int frequency) {
    if (audio_buffer == nullptr) return;

    auto *dest = (short *) audio_buffer;
    for (size_t i = 0; i < audio_size / 2; i++) {
        short sample = 0.3 * 0x7FFF * sin(frequency * (2 * M_PI) * i / SAMPLE_RATE);
        dest[i] = (sample << 16) | (sample & 0xffff);
    }
}

int main(int argc, char **argv) {

    // create the main renderer
    auto *renderer = new C2DRenderer({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});

    // create audio interface
    auto *audio = new C2DAudio(SAMPLE_RATE, SAMPLE_COUNT);

    // sine wave
    int notes[] = {440, 880, 1760};
    auto *audio_buffer = (unsigned char *) malloc(audio->getSamplesSize());
    fill_audio_buffer(audio_buffer, audio->getSamplesSize(), notes[0]);
    audio->pause(0);

    // main loop
    while (true) {

        unsigned int keys = renderer->getInput()->getKeys();

        if (keys & Input::Key::Start || keys & EV_QUIT) {
            break;
        }

        if (keys & Input::Key::Fire1) {
            fill_audio_buffer(audio_buffer, audio->getSamplesSize(), notes[0]);
        } else if (keys & Input::Key::Fire2) {
            fill_audio_buffer(audio_buffer, audio->getSamplesSize(), notes[1]);
        } else if (keys & Input::Key::Fire3) {
            fill_audio_buffer(audio_buffer, audio->getSamplesSize(), notes[2]);
        }

        // play audio buffer
        audio->play(audio_buffer, audio->getSamples());

        // draw everything
        renderer->flip();
    }

    // delete audio interface
    delete (audio);

    // cleanup, will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
