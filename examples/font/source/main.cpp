//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

using namespace c2d;

int main() {

    // create the main renderer
    auto *renderer = new C2DRenderer({1280, 720});

    // load default font
    auto *font = new C2DFont();
    if (font->load()) {
        // some font have different offset..
        font->setOffset({0, -6});
        // create a text and add it to the renderer
        auto *text = new C2DText("Hello (GBAtemp) World", *font, 100);
        text->setPosition(renderer->getSize().x / 2, renderer->getSize().y / 2);
        text->setOrigin(Origin::Center);
        text->setFillColor(Color::Cyan);
        text->setOutlineColor(Color::Blue);
        text->setOutlineThickness(5);
        renderer->add(text);
    }

    // main loop
    while (renderer->getElapsedTime().asSeconds() < 10) {

        // draw everything
        renderer->flip();
    }

    // cleanup font resources
    delete (font);
    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}