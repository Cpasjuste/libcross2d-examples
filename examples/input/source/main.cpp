//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

#define SPEED 500

using namespace c2d;

int main(int argc, char **argv) {

    // create the main renderer
    auto *renderer = new C2DRenderer({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});

    // create a texture
    auto *texture = new C2DTexture(renderer->getIo()->getRomFsPath() + "icon.png");
    texture->setOrigin(Origin::Center);
    texture->setPosition(renderer->getSize().x / 2, renderer->getSize().y / 2);
    auto *tween = new TweenRotation(0, 360, 1);
    texture->add(tween);
    renderer->add(texture);

    // main loop
    while (true) {

        // get player 1 keys state
        unsigned int keys = renderer->getInput()->getKeys();
        if (keys > 0 && keys != Input::Key::Delay) {

            // "special" close/quit event send by sdl2 windows (linux platform)
            if (keys & EV_QUIT) {
                break;
            }

            // exit if START or SELECT is pressed (+/- on switch)
            if (keys & Input::Key::Start || keys & Input::Key::Select) {
                break;
            }

            // move the texture
            if (keys & Input::Key::Left) {
                // move with delta time for smooth movement
                texture->move({-(renderer->getDeltaTime().asSeconds() * SPEED), 0});
            }
            if (keys & Input::Key::Right) {
                texture->move({renderer->getDeltaTime().asSeconds() * SPEED, 0});
            }
            if (keys & Input::Key::Up) {
                texture->move({0, -(renderer->getDeltaTime().asSeconds() * SPEED)});
            }
            if (keys & Input::Key::Down) {
                texture->move({0, renderer->getDeltaTime().asSeconds() * SPEED});
            }

            // basic touch support
            if (keys & Input::Key::Touch) {
                Vector2f touch = renderer->getInput()->getPlayer(0)->touch;
                if (texture->getGlobalBounds().contains(touch)) {
                    tween->play(TweenDirection::Forward, true);
                }
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
