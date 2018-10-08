//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

#ifdef __PSP2__
#define SCR_W 960
#define SCR_H 544
#define TEX_PATH "app0:/data/gbatemp.png"
#elif __3DS__
#define SCR_W 400
#define SCR_H 240
#define TEX_PATH "data/gbatemp.png"
#else
#define SCR_W 1280
#define SCR_H 720
#define TEX_PATH "data/gbatemp.png"
#endif

using namespace c2d;

int main() {

    // create the main renderer
    auto *renderer = new C2DRenderer({1280, 720});

    auto *texture = new C2DTexture(TEX_PATH);
    texture->setOrigin(Origin::Center);
    texture->setPosition(renderer->getSize().x / 2, renderer->getSize().y / 2);
    renderer->add(texture);

    // main loop
    while (renderer->getElapsedTime().asSeconds() < 10) {

        // draw everything
        renderer->flip();
    }

    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
