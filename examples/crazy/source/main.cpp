//
// Created by cpasjuste on 08/12/16.
//

#include <random>
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

void addTweenShape(C2DRectangle *rect, int count) {

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
                    {scale(mt), scale(mt)},
                    scale(mt), TweenLoop::PingPong);
            shape->add(tweenScale);
        } else {
            shape = new C2DTexture(TEX_PATH);
            ((C2DTexture *) shape)->setPosition(r.left, r.top);
            float from = scale(mt) / 2;
            float to = scale(mt) / 2;
            auto *tweenScale = new TweenScale(
                    {from, from}, {to, to},
                    scale(mt), TweenLoop::PingPong);
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

int main() {

    char info[128];

    // create the main renderer
    auto *renderer = new C2DRenderer({SCR_W, SCR_H});

    auto *input = new C2DInput();
    input->setRepeatEnable(true);
    input->setJoystickMapping(0, C2D_DEFAULT_JOY_KEYS);
    input->setKeyboardMapping(C2D_DEFAULT_KB_KEYS);

    // load default font
    auto *font = new C2DFont();
    font->load();
    // create fps text and add it to the renderer
    auto *text = new C2DText("FPS: 60/60", *font);
    text->setOrigin(Origin::BottomRight);
    text->setPosition(renderer->getSize().x - 5, renderer->getSize().y - 80);
    text->setOutlineThickness(1);
    renderer->add(text);

    // create a rectangle shape holding our childs
    C2DRectangle *rect = new C2DRectangle({renderer->getSize().x, renderer->getSize().y});
    rect->setFillColor(Color::Transparent);
    renderer->add(rect);

    // add some shapes to the rect
    addTweenShape(rect, 100);

    text->setLayer(2);

    // main loop
    while (true) {

        unsigned int keys = input->update()[0].state;
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
                addTweenShape(rect, 10);
                text->setLayer(2);
            } else if (keys & Input::Key::KEY_DOWN) {
                removeTweenShape(rect, 10);
                text->setLayer(2);
            } else if (keys & Input::Key::KEY_LEFT) {
                removeTweenShape(rect, 100);
                text->setLayer(2);
            } else if (keys & Input::Key::KEY_RIGHT) {
                addTweenShape(rect, 100);
                text->setLayer(2);
            }
        }

        // update fps
        snprintf(info, 128,
                 "libcross2d \"crazy example\"\n"
                 "press dpad to do some stuff\nfps: %.2g/60, obj: %i",
                 renderer->getFps(), (int) rect->getChilds().size());
        text->setString(info);

        // draw everything
        renderer->flip();
    }

    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
