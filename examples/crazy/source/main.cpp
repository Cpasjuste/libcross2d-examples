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

void addTweenRect(Renderer *renderer, int count) {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> x(0, renderer->getSize().x);
    std::uniform_real_distribution<float> y(0, renderer->getSize().y);
    std::uniform_real_distribution<float> w(10, 150);
    std::uniform_real_distribution<float> color(0, 255);
    std::uniform_real_distribution<float> scale(0.5f, 3.0f);

    for (int i = 0; i < count; i++) {

        auto rect = FloatRect(x(mt), y(mt), w(mt), w(mt));
        auto *r = new C2DRectangle(rect);
        r->setOrigin(Origin::Center);
        r->setOutlineColor({color(mt), color(mt), color(mt)});
        r->setOutlineThickness(2);

        auto *tweenPos = new TweenPosition(
                {r->getPosition().x, r->getPosition().y}, {x(mt), y(mt)},
                3.0f, TweenLoop::PingPong);
        r->add(tweenPos);
        auto *tweenRot = new TweenRotation(0, 360, 4.0f, TweenLoop::PingPong);
        r->add(tweenRot);
        auto *tweenScale = new TweenScale(
                {scale(mt), scale(mt)},
                {scale(mt), scale(mt)},
                scale(mt), TweenLoop::PingPong);
        r->add(tweenScale);
        auto *tweenColor = new TweenColor(
                {color(mt), color(mt), color(mt)},
                {color(mt), color(mt), color(mt)},
                scale(mt), TweenLoop::PingPong);
        r->add(tweenColor);

        renderer->add(r);
    }
}

int main() {

    char fps[64];
    int count = 100;

    // create the main renderer
    auto *renderer = new C2DRenderer({SCR_W, SCR_H});

    auto *input = new C2DInput();
    input->setRepeatEnable(true);
    input->setJoystickMapping(0, C2D_DEFAULT_JOY_KEYS);
    input->setKeyboardMapping(C2D_DEFAULT_KB_KEYS);

    // load default font
    auto *font = new C2DFont();
    font->load();

    addTweenRect(renderer, count);

    // create fps text and add it to the renderer
    auto *text = new C2DText("FPS: 60/60", *font);
    text->setOrigin(Origin::BottomRight);
    text->setPosition(renderer->getSize().x - 5, renderer->getSize().y - 45);
    text->setOutlineThickness(1);
    renderer->add(text);

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
                addTweenRect(renderer, 10);
                text->setLayer(2);
                count += 10;
            }
        }

        // update fps
        snprintf(fps, 63,
                 "press (UP) to add some stuff\nfps: %.2g/60, obj: %i",
                 renderer->getFps(), count);
        text->setString(fps);

        // draw everything
        renderer->flip();
    }

    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
