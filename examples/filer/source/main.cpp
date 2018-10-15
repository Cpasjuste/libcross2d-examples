//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"
#include "filer.h"

using namespace c2d;

int main() {

    // create the main renderer
    auto *renderer = new C2DRenderer({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});
    renderer->setClearColor(Color::White);

    // init inputs
    auto *input = new C2DInput();
    input->setJoystickMapping(0, C2D_DEFAULT_JOY_KEYS);
    input->setKeyboardMapping(C2D_DEFAULT_KB_KEYS);
    // set auto-repeat delay
    input->setRepeatEnable(true);
    input->setRepeatDelay(1000);

    // create and load default font
    auto *font = new C2DFont();
    font->load();

    // create io wrapper and the filer
    auto *io = new C2DIo();
    auto *filer = new Filer(io, "/", *font, 22,
                            {16, 16, (renderer->getSize().x / 2) - 16, renderer->getSize().y - 32});
    renderer->add(filer);

    // main loop
    while (true) {

        // update inputs and get player 0 keys
        unsigned int keys = input->update()[0].state;
        if (((keys & c2d::Input::Key::KEY_START) || (keys & c2d::Input::Key::KEY_COIN)
             || (keys & EV_QUIT))) {
            break;
        }

        // update filer input
        Io::File file = filer->step(keys);
        if (keys & Input::Key::KEY_FIRE1 && file.type == Io::Type::File) {
            if (Utility::endsWith(file.name, ".mkv")) {
                // do somethine with this mkv file...
                printf("mkv file selected: %s\n", file.path.c_str());
            }
        }


        // draw everything
        renderer->flip();
    }

    // cleanup
    delete (io);
    delete (font);
    delete (input);
    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
