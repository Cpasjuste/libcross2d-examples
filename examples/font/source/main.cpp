//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

#ifdef __PSP2__
#define SCR_W 960
#define SCR_H 544
#elif __3DS__
#define SCR_W 400
#define SCR_H 240
#else
#define SCR_W 1280
#define SCR_H 720
#endif

using namespace c2d;

int main() {

    // create the main renderer
    auto *renderer = new C2DRenderer({SCR_W, SCR_H});

    // create a font
    auto *font = new C2DFont();
    // load default (embedded) font
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
