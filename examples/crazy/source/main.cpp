//
// Created by cpasjuste on 08/12/16.
//

#include <random>
#include "cross2d/c2d.h"

using namespace c2d;

void addTweenShape(Io *io, C2DRectangle *rect, int count) {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> x(0, rect->getSize().x);
    std::uniform_real_distribution<float> y(0, rect->getSize().y);
    std::uniform_real_distribution<float> w(10, 150);
    std::uniform_real_distribution<float> color(0, 255);
    std::uniform_real_distribution<float> scale(0.2f, 1.0f);

    for (int i = 0; i < count; i++) {

        auto r = FloatRect(x(mt), y(mt), w(mt), w(mt));
        Shape *shape;
        // create a "gbatemp" texture every 10 shapes
        if (rect->getChilds().size() % 10 != 0) {
            shape = new C2DRectangle(r);
            shape->setOutlineColor({color(mt), color(mt), color(mt)});
            shape->setOutlineThickness(2);
            auto *tweenColor = new TweenColor(
                    {color(mt), color(mt), color(mt)},
                    {color(mt), color(mt), color(mt)},
                    scale(mt), TweenLoop::PingPong);
            shape->add(tweenColor);
            auto *tweenScale = new TweenScale(
                    {1.0f, 1.0f},
                    {scale(mt), scale(mt)}, scale(mt), TweenLoop::PingPong);
            shape->add(tweenScale);
        } else {
            shape = new C2DTexture(io->getDataPath() + "gbatemp.png");
            shape->setOutlineColor({color(mt), color(mt), color(mt)});
            shape->setOutlineThickness(2);
            ((C2DTexture *) shape)->setPosition(r.left, r.top);
            float from = scale(mt) / 2;
            float to = scale(mt) / 2;
            auto *tweenScale = new TweenScale(
                    {from, from}, {to, to}, scale(mt), TweenLoop::PingPong);
            shape->add(tweenScale);
        }
        shape->setOrigin(Origin::Center);

        auto *tweenPos = new TweenPosition(
                {shape->getPosition().x, shape->getPosition().y}, {x(mt), y(mt)},
                3.0f, TweenLoop::PingPong);
        shape->add(tweenPos);
        auto *tweenRot = new TweenRotation(0, 360, 4.0f, TweenLoop::PingPong);
        shape->add(tweenRot);

        rect->add(shape);
    }
}

void removeTweenShape(C2DRectangle *rect, int count) {

    for (int i = 0; i < count; i++) {
        if (rect->getChilds().empty()) {
            break;
        }
        C2DObject *child = rect->getChilds().at(0);
        if (child) {
            delete (child);
            rect->remove(child);
        }
    }
}

int main(int argc, char **argv) {

    char info[128];

    // create the main renderer
    auto *renderer = new C2DRenderer({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});

    // set key repeat to 1 sec
    renderer->getInput()->setRepeatEnable(true);
    renderer->getInput()->setRepeatDelay(1000);

    // create fps text and add it to the renderer
    auto *text = new C2DText("FPS: 60/60");
    text->setOrigin(Origin::BottomRight);
    text->setPosition(renderer->getSize().x - 5, renderer->getSize().y - 80);
    text->setOutlineThickness(1);
    renderer->add(text);

    // create a rectangle shape holding our childs
    C2DRectangle *rect = new C2DRectangle({renderer->getSize().x, renderer->getSize().y});
    rect->setFillColor(Color::Transparent);
    renderer->add(rect);

    // add some shapes to the rect
    addTweenShape(renderer->getIo(), rect, 100);

    // set text in front of everything
    text->setLayer(2);

    // main loop
    while (true) {

        unsigned int keys = renderer->getInput()->getKeys();
        if (keys) {
            // "special" close/quit event send by sdl2 windows (linux platform)
            if (keys & EV_QUIT) {
                break;
            }
            // exit if START or SELECT is pressed (+/- on switch)
            if (keys & Input::Key::KEY_START || keys & Input::Key::KEY_COIN) {
                break;
            }

            if (keys & Input::Key::KEY_UP) {
                addTweenShape(renderer->getIo(), rect, 10);
                text->setLayer(2);
            } else if (keys & Input::Key::KEY_DOWN) {
                removeTweenShape(rect, 10);
                text->setLayer(2);
            } else if (keys & Input::Key::KEY_LEFT) {
                removeTweenShape(rect, 100);
                text->setLayer(2);
            } else if (keys & Input::Key::KEY_RIGHT) {
                addTweenShape(renderer->getIo(), rect, 100);
                text->setLayer(2);
            }
        }

        // update fps
        snprintf(info, 128,
                 "libcross2d \"crazy example\"\n"
                 "press dpad to do some stuff\nfps: %.2g/60, tris: %i",
                 renderer->getFps(), (int) rect->getChilds().size() * 10);
        text->setString(info);

        // draw everything
        renderer->flip();
    }

    // cleanup
    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
