//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

using namespace c2d;

int main() {

    // create the main renderer
    auto *renderer = new C2DRenderer({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});

    // create a font
    auto *font = new C2DFont();
    // load default (embedded) font
    if (font->load()) {
        // some font have different offset..
        font->setOffset({0, -6});
        // create a text and add it to the renderer
        auto *text = new C2DText("Hello (GBAtemp) World", *font);
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

    // cleanup
    delete (font);
    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
