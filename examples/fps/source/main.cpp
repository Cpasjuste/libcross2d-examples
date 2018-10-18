//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

using namespace c2d;

int main() {

    char fps[64];

    // create the main renderer
    auto *renderer = new C2DRenderer({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});

    // load default font
    auto *font = new C2DFont();
    if (!font->load()) {
        delete (renderer);
        return -1;
    }

    // create a text and add it to the renderer
    auto *text = new C2DText("FPS: 60/60", *font);
    renderer->add(text);

    // main loop
    while (true) {

        // stop if any key is pressed
        if (renderer->getInput()->getKeys()) {
            break;
        }

        snprintf(fps, 63, "FPS: %.2g/60\nDELTA: %f\nTIME: %f",
                 renderer->getFps(),
                 renderer->getDeltaTime().asSeconds(),
                 renderer->getElapsedTime().asSeconds());
        text->setString(fps);

        // draw everything
        renderer->flip();
    }

    // cleanup
    delete (font);
    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
