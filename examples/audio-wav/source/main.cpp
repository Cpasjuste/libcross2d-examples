//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

using namespace c2d;

int main(int argc, char **argv) {

    // create the main renderer
    auto *renderer = new C2DRenderer({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});

    // create audio interface
    auto *audio = new C2DAudio(44100, 1024);

    auto *wav = new Audio::Wav(renderer->getIo()->getDataPath() + "sample.wav");
    auto *audio_buffer = (unsigned char *) malloc(audio->getSamplesSize());
    audio->pause(0);

    // main loop
    while (true) {

        unsigned int keys = renderer->getInput()->getKeys();

        if (keys & Input::Key::Start || keys & EV_QUIT) {
            break;
        }

        // play audio buffer
        int samples = wav->read(audio_buffer, audio->getSamples());
        if (samples > 0) {
            audio->play(audio_buffer, samples);
        }

        // draw everything
        renderer->flip();
    }

    // delete audio interface
    delete (audio);

    // cleanup, will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
