//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

#ifdef __PSP2__
#define SCR_W 960
#define SCR_H 544
#define TEX_PATH "app0:/data/gbatemp.png"
#elif __3DS__
#define SCR_W 400
#define SCR_H 240
#define TEX_PATH "data/gbatemp.png"
#else
#define SCR_W 1280
#define SCR_H 720
#define TEX_PATH "data/gbatemp.png"
#endif

#define SPEED 500

using namespace c2d;

int main() {

    // create the main renderer
    auto *renderer = new C2DRenderer({1280, 720});

    auto *texture = new C2DTexture(TEX_PATH);
    texture->setOrigin(Origin::Center);
    texture->setPosition(renderer->getSize().x / 2, renderer->getSize().y / 2);
    renderer->add(texture);

    auto *input = new C2DInput();
    input->setJoystickMapping(0, C2D_DEFAULT_JOY_KEYS);
    input->setKeyboardMapping(C2D_DEFAULT_KB_KEYS);

    // main loop
    while (true) {

        // update inputs and get player 1 keys state
        unsigned int keys = input->update()[0].state;
        if (keys) {

            // "special" close/quit event send by sdl2 windows (linux platform)
            if (keys & EV_QUIT) {
                break;
            }

            // exit if START or SELECT is pressed (+/- on switch)
            if (keys & Input::Key::KEY_START || keys & Input::Key::KEY_COIN) {
                break;
            }

            // move the texture
            if (keys & Input::Key::KEY_LEFT) {
                // move with delta time for smooth movement
                texture->move({-(renderer->getDeltaTime().asSeconds() * SPEED), 0});
            }
            if (keys & Input::Key::KEY_RIGHT) {
                texture->move({renderer->getDeltaTime().asSeconds() * SPEED, 0});
            }
            if (keys & Input::Key::KEY_UP) {
                texture->move({0, -(renderer->getDeltaTime().asSeconds() * SPEED)});
            }
            if (keys & Input::Key::KEY_DOWN) {
                texture->move({0, renderer->getDeltaTime().asSeconds() * SPEED});
            }
        }

        // draw everything
        renderer->flip();
    }

    delete (input);
    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
