//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

#define SCR_W 1280
#define SCR_H 720

using namespace c2d;

int main() {

    // create the main renderer
    auto *renderer = new C2DRenderer({SCR_W, SCR_H});
    // set "clear" color
    renderer->setClearColor(Color::Black);

    // load default font
    auto *font = new C2DFont();
    if (font->load()) {
        // some font have different offset..
        font->setOffset({0, -10});
        // create a text and add it to the renderer
        auto *text = new C2DText("Hello (GBAtemp) World", *font, 100);
        text->setPosition(renderer->getSize().x / 2, renderer->getSize().y / 2);
        text->setOrigin(Origin::Center);
        text->setOutlineColor(Color::Blue);
        text->setOutlineThickness(5);
        renderer->add(text);
    }

    // main loop
    while (renderer->getElapsedTime().asSeconds() < 10) {

        // draw everything
        renderer->flip();
    }

    delete (font);
    // will delete widgets (if any) recursively
    delete (renderer);

    return 0;
}
