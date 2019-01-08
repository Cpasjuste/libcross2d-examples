//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

using namespace c2d;

const IntRect getTextureRect(C2DTexture *texture, int direction) {

    int width = (int) texture->getSize().x / 4;
    int height = (int) texture->getSize().y / 4;
    IntRect rect = {0, 0, width, height};

    switch (direction) {
        case 1:
            rect.top = height;
            break;
        case 2:
            rect.top = height * 2;
            break;
        case 3:
            rect.top = height * 3;
            rect.left = width;
            break;
        default:
            break;
    }

    return rect;
}

int main(int argc, char **argv) {

    // create the main renderer
    auto *renderer = new C2DRenderer({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});
    renderer->setClearColor(Color::GrayLight);

    // create a texture for the sprite
    auto *texture = new C2DTexture(renderer->getIo()->getDataReadPath() + "sprite_sheet.png");
    // create a sprite
    auto *sprite = new Sprite(texture, getTextureRect(texture, 0));
    sprite->setOrigin(Origin::Center);
    sprite->setPosition(renderer->getSize().x / 2, renderer->getSize().y / 2);
    renderer->add(sprite);

    // main loop
    while (true) {

        unsigned int keys = renderer->getInput()->getKeys();

        if (keys & EV_QUIT) {
            break;
        }

        if (keys & Input::Key::Up) {
            sprite->setTextureRect(getTextureRect(texture, 1));
        } else if (keys & Input::Key::Down) {
            sprite->setTextureRect(getTextureRect(texture, 0));
        } else if (keys & Input::Key::Left) {
            sprite->setTextureRect(getTextureRect(texture, 2));
        } else if (keys & Input::Key::Right) {
            sprite->setTextureRect(getTextureRect(texture, 3));
        }

        // draw everything
        renderer->flip();
    }

    // as texture is not added to the renderer,
    // we need to manually clean it
    delete (texture);

    // cleanup
    // will delete child's (textures, sprites, shapes, text..)
    delete (renderer);

    return 0;
}
