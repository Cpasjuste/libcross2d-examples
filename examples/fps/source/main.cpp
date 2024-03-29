//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

using namespace c2d;

int main(int argc, char **argv) {

    char fps[64];

    // create the main renderer
    auto *renderer = new C2DRenderer();

    // create a text and add it to the renderer
    auto *text = new Text("FPS: 60/60");
    renderer->add(text);

    // main loop
    while (true) {

        // stop if any key is pressed
        if (renderer->getInput()->getButtons()) {
            break;
        }

        snprintf(fps, 63, "FPS: %.2g/60\nDELTA: %f",
                 renderer->getFps(),
                 renderer->getDeltaTime().asSeconds());
        text->setString(fps);

        // draw everything
        renderer->flip();
    }

    // cleanup
    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
