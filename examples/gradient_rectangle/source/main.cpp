//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

using namespace c2d;

int main(int argc, char **argv) {

    // create the main renderer
    auto *renderer = new C2DRenderer({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});
    renderer->setClearColor(Color::Red);

    // create a texture and add it to the main renderer
    auto *rect = new GradientRectangle({0, 0, renderer->getSize().x, renderer->getSize().y});
    rect->setColor(Color::Transparent, Color::Black);
    renderer->add(rect);

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
