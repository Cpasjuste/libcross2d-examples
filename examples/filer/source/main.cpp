//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"
#include "filer.h"

using namespace c2d;

int main(int argc, char **argv) {

    // create the main renderer
    auto *renderer = new C2DRenderer();
    renderer->setClearColor(Color::White);

    // set auto-repeat delay
    renderer->getInput()->setRepeatDelay(250);

    // create the filer
    auto *filer = new Filer(renderer->getIo(), "/", renderer->getFont(), 36,
                            {16, 16, (renderer->getSize().x / 2) - 16, renderer->getSize().y - 32});
    renderer->add(filer);

    // main loop
    while (true) {

        // update inputs and get player 0 keys
        unsigned int keys = renderer->getInput()->getButtons();
        if (((keys & Input::Button::Start)
             || (keys & Input::Button::Select)
             || (keys & Input::Button::Quit))) {
            break;
        }

        // update filer input
        if (filer->step(keys)) {
            Io::File *file = filer->getSelection();
            if (Utility::endsWith(file->name, ".mkv")) {
                // do somethine with this mkv file ;)
                printf("mkv file selected: %s\n", file->path.c_str());
            }
        }

        // draw everything
        renderer->flip();
    }

    // cleanup
    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
