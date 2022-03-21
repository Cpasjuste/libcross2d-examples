//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

using namespace c2d;

int main(int argc, char **argv) {

    // create the main renderer
    auto *renderer = new C2DRenderer({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});
    renderer->setClearColor(Color::GrayLight);

    // scaling is not (yet?) available in "PhysicsWorld" (box2d),
    // we can use a parent rectangle for this
    auto *view = new Rectangle(renderer->getSize());
    view->setOrigin(Origin::BottomLeft);
    view->setPosition(0, renderer->getSize().y);
    renderer->add(view);

    // Beware: PhysicsWorld (box2d) 0x0 coordinates are bottom left,
    // while cross2d use top left
    auto *world = new PhysicsWorld();
    view->add(world);

    auto shape = new C2DTexture(renderer->getIo()->getRomFsPath() + "icon.png");
    shape->setPosition(55, renderer->getSize().y - 100);
    shape->setSize(100, 100);
    shape->addPhysicsBody(world, b2_dynamicBody, 1.0f, 0.3f);
    world->add(shape);

    auto shape2 = new RectangleShape({0, 0, 100, 100});
    shape2->setFillColor(Color::Yellow);
    shape2->addPhysicsBody(world, b2_staticBody, 1.0f, 0.3f);
    world->add(shape2);

    auto shape3 = new RectangleShape({170, 0, 100, 100});
    shape3->setFillColor(Color::Yellow);
    shape3->addPhysicsBody(world, b2_staticBody, 1.0f, 0.3f);
    world->add(shape3);

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
