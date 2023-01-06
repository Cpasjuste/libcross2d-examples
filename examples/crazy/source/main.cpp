//
// Created by cpasjuste on 08/12/16.
//

#include <random>
#include "cross2d/c2d.h"

using namespace c2d;

void addTweenShape(Texture *tex, C2DRectangle *rect, int count) {

    std::mt19937 mt((unsigned long) time(nullptr));
    std::uniform_real_distribution<float> x(0, rect->getSize().x);
    std::uniform_real_distribution<float> y(0, rect->getSize().y);
    std::uniform_real_distribution<float> w(10, 150);
    std::uniform_real_distribution<float> color(0, 255);
    std::uniform_real_distribution<float> scale(0.2f, 1.0f);

    for (int i = 0; i < count; i++) {
        auto r = FloatRect(x(mt), y(mt), w(mt), w(mt));
        // create a "gbatemp" texture every 10 shapes
        if (!tex || !tex->available || rect->getChilds().size() % 10 != 0) {
            auto shape = new C2DRectangle(r);
            shape->setOrigin(Origin::Center);
            shape->setOutlineColor({color(mt), color(mt), color(mt)});
            shape->setOutlineThickness(2);
            auto *tweenColor = new TweenColor(
                    {color(mt), color(mt), color(mt)},
                    {color(mt), color(mt), color(mt)},
                    scale(mt), TweenLoop::PingPong);
            shape->add(tweenColor);
            tweenColor->play();
            auto *tweenScale = new TweenScale(
                    {1.0f, 1.0f},
                    {scale(mt), scale(mt)}, scale(mt), TweenLoop::PingPong);
            tweenScale->play();
            shape->add(tweenScale);
            shape->setOrigin(Origin::Center);
            auto *tweenPos = new TweenPosition(
                    {shape->getPosition().x, shape->getPosition().y}, {x(mt), y(mt)},
                    3.0f, TweenLoop::PingPong);
            shape->add(tweenPos);
            auto *tweenRot = new TweenRotation(0, 360, 4.0f, TweenLoop::PingPong);
            tweenRot->play();
            shape->add(tweenRot);
            rect->add(shape);
        } else {
            auto shape = new Sprite(tex);
            shape->setOrigin(Origin::Center);
            shape->setOutlineColor({color(mt), color(mt), color(mt)});
            shape->setOutlineThickness(2);
            ((C2DTexture *) shape)->setPosition(r.left, r.top);
            float from = scale(mt) / 2;
            float to = scale(mt) / 2;
            auto *tweenScale = new TweenScale(
                    {from, from}, {to, to}, scale(mt), TweenLoop::PingPong);
            tweenScale->play();
            shape->add(tweenScale);
            auto *tweenPos = new TweenPosition(
                    {shape->getPosition().x, shape->getPosition().y}, {x(mt), y(mt)},
                    3.0f, TweenLoop::PingPong);
            shape->add(tweenPos);
            auto *tweenRot = new TweenRotation(0, 360, 4.0f, TweenLoop::PingPong);
            tweenRot->play();
            shape->add(tweenRot);
            rect->add(shape);
        }
    }
}

void removeTweenShape(C2DObject *obj, int count) {

    for (int i = 0; i < count; i++) {
        if (obj->getChilds().empty()) {
            break;
        }
        C2DObject *child = obj->getChilds().at(0);
        if (child) {
            delete (child);
        }
    }
}

int main(int argc, char **argv) {

    char info[128];

    // create the main renderer
    auto *renderer = new C2DRenderer();

    // set key repeat to 1 sec
    renderer->getInput()->setRepeatDelay(1000);

    // create fps text and add it to the renderer
    auto *text = new C2DText("FPS: 60/60");
    text->setOrigin(Origin::BottomRight);
    text->setPosition(renderer->getSize().x - 5, renderer->getSize().y - 80);
    text->setOutlineThickness(1);
    renderer->add(text);

    // create a rectangle shape holding our childs
    auto rect = new C2DRectangle({renderer->getSize().x, renderer->getSize().y});
    rect->setFillColor(Color::Transparent);
    renderer->add(rect);

    // load texture
    auto texture = new C2DTexture(renderer->getIo()->getRomFsPath() + "icon.png");

    // add some shapes to the rect
    addTweenShape(texture, rect, 100);

    // set text in front of everything
    text->setLayer(2);

    // main loop
    while (true) {

        unsigned int keys = renderer->getInput()->getButtons();
        if (keys) {
            // "special" close/quit event send by sdl2 windows (linux platform)
            if (keys & Input::Button::Quit) {
                break;
            }
            // exit if START or SELECT is pressed (+/- on switch)
            if (keys & Input::Button::Start || keys & Input::Button::Select) {
                break;
            }

            if (keys & Input::Button::Up) {
                addTweenShape(texture, rect, 10);
                text->setLayer(2);
            } else if (keys & Input::Button::Down) {
                removeTweenShape(rect, 10);
                text->setLayer(2);
            } else if (keys & Input::Button::Left) {
                removeTweenShape(rect, 100);
                text->setLayer(2);
            } else if (keys & Input::Button::Right) {
                addTweenShape(texture, rect, 100);
                text->setLayer(2);
            }
        }

        // update fps
        snprintf(info, 128,
                 "libcross2d \"crazy example\"\n"
                 "press dpad to do some stuff\nfps: %.2g/60, objects: %i",
                 renderer->getFps(), (int) rect->getChilds().size());
        text->setString(info);

        // draw everything
        renderer->flip();
    }

    // cleanup
    delete (texture);
    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
