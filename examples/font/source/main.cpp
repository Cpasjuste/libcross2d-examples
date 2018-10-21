//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

using namespace c2d;

int main() {

    // create the main renderer
    auto *renderer = new C2DRenderer({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});

    auto *text = new C2DText("Hello (GBAtemp) World");
    text->setPosition(renderer->getSize().x / 2, renderer->getSize().y / 2);
    text->setOrigin(Origin::Center);
    text->setFillColor(Color::Cyan);
    text->setOutlineColor(Color::Blue);
    text->setOutlineThickness(2);
    renderer->add(text);

    // main loop
    while (true) {

        // stop if any key is pressed
        if (renderer->getInput()->getKeys()) {
            break;
        }

        // draw everything
        renderer->flip();
    }

    // cleanup
    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
