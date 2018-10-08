//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

using namespace c2d;

int main() {

    char fps[32];

    // create the main renderer
    auto *renderer = new C2DRenderer({1280, 720});

    // load default font
    auto *font = new C2DFont();
    if (!font->load()) {
        delete (renderer);
        return -1;
    }

    // create a text and add it to the renderer
    auto *text = new C2DText("FPS: 60/60", *font, 100);
    text->setPosition(renderer->getSize().x / 2, renderer->getSize().y / 2);
    text->setOrigin(Origin::Center);
    renderer->add(text);

    // main loop
    while (renderer->getElapsedTime().asSeconds() < 10) {

        snprintf(fps, 31, "FPS: %.2g/60", renderer->getFps());
        text->setString(fps);

        // draw everything
        renderer->flip();
    }

    // cleanup font resources
    delete (font);
    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
