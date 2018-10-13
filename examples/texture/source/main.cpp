//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

using namespace c2d;

int main() {

    // create the main renderer
    auto *renderer = new C2DRenderer({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});
    renderer->setClearColor(Color::GrayLight);

    // create io helper
    auto *io = new C2DIo();

    // create a texture and add it to the main renderer
    auto *texture = new C2DTexture(io->getDataPath() + "gbatemp.png");
    texture->setOrigin(Origin::Center);
    texture->setPosition(renderer->getSize().x / 2, renderer->getSize().y / 2);
    renderer->add(texture);

    // main loop
    while (renderer->getElapsedTime().asSeconds() < 10) {

        // draw everything
        renderer->flip();
    }

    // cleanup
    delete (io);
    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
