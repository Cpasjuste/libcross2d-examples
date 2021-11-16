//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

using namespace c2d;

int main(int argc, char **argv) {

    // create the main renderer
    auto *renderer = new C2DRenderer({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});
    renderer->setClearColor(Color::Red);

    // freetype font support, using cross2d default one
    auto *text = new Text("Hello World");
    text->setPosition(renderer->getSize().x / 2, renderer->getSize().y / 2);
    text->setOrigin(Origin::Center);
    text->setFillColor(Color::Yellow);
    text->setOutlineColor(Color::Black);
    text->setOutlineThickness(2);
    renderer->add(text);

    // bmfont font support (basic, binary)
    // https://www.angelcode.com/products/bmfont/
    auto bmFont = new BMFont();
    if (bmFont->loadFromFile(renderer->getIo()->getRomFsPath() + "future.fnt")) {
        auto *bmfText = new Text("Hello World", 18, bmFont);
        bmfText->setPosition(text->getPosition().x, text->getPosition().y + text->getLocalBounds().height);
        bmfText->setOrigin(Origin::Center);
        bmfText->setFillColor(Color::Cyan);
        renderer->add(bmfText);
    }

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
