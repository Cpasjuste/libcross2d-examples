//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

using namespace c2d;
using namespace c2d::config;

void addConfigGroup(Config *config) {

    // add a main config group
    Group group("DEMO");
    group.addOption({"INTEGER", 10});
    group.addOption({"STRING", "Hello World"});
    group.addOption({"FLOAT", 9.99f});
    group.addOption({"VECTOR2F", Vector2f{10, 20}});
    group.addOption({"FLOATRECT", FloatRect{10, 20, 30, 40}});
    group.addOption({"COLOR", Color{255, 0, 0, 255}});
    group.addOption({"CHOICE", std::vector<std::string>{"ON", "OFF", "MAYBE"}, 2});

    // add a child group to demo group
    Group child("CHILD");
    child.addOption({"INTEGER", 11});
    group.addGroup(child);

    // add all that to the main config
    config->addGroup(group);
}

int main(int argc, char **argv) {

    // create the main renderer
    auto renderer = new C2DRenderer();
    renderer->setClearColor(Color::GrayLight);

    // add some delay to inputs
    renderer->getInput()->setRepeatDelay(250);

    // create a configuration named "C2D_CFG" in a writable directory (getHomePath)
    auto config = new Config("C2D_CFG", renderer->getIo()->getDataPath() + "config.cfg");

    // add a group to the configuration
    addConfigGroup(config);

    // load the configuration from file, overwriting default values (added in addConfigGroup)
    if (!config->load()) {
        // file doesn't exist or is malformed, (re)create it
        config->save();
    }

    FloatRect configRect = {128, 128, renderer->getSize().x - 256, renderer->getSize().y - 256};
    auto configBox = new ConfigBox(renderer->getFont(), C2D_DEFAULT_CHAR_SIZE, configRect);
    configBox->setLeftWidth(300);
    configBox->getListBoxLeft()->setFillColor(Color::White);
    configBox->getListBoxLeft()->getHighlight()->setFillColor(Color::Gray);
    configBox->getListBoxLeft()->getHighlight()->setAlpha(150);
    configBox->getListBoxRight()->setFillColor(Color::Gray);
    configBox->getListBoxRight()->getHighlight()->setOutlineColor(Color::Yellow);
    configBox->getListBoxRight()->getHighlight()->setOutlineThickness(1);
    configBox->getListBoxRight()->getHighlight()->add(
            new TweenAlpha(80, 150, 0.5f, TweenLoop::PingPong, TweenState::Playing));
    configBox->load(config->getGroup("DEMO"));
    renderer->add(configBox);

    // main loop
    while (true) {

        unsigned int keys = renderer->getInput()->getButtons();

        // stop if any key is pressed
        if (keys & Input::Button::Quit) {
            break;
        }

        if (keys & Input::Button::Up) {
            configBox->navigate(ConfigBox::Navigation::Up);
        } else if (keys & Input::Button::Down) {
            configBox->navigate(ConfigBox::Navigation::Down);
        } else if (keys & Input::Button::Left) {
            if (configBox->getSelection()) {
                //TODO: add multiple choice capability to Option?
            }
        } else if (keys & Input::Button::Right) {
            if (configBox->getSelection()) {
                //TODO: add multiple choice capability to Option?
            }
        } else if (keys & Input::Button::A) {
            Option *opt = configBox->navigate(ConfigBox::Navigation::Enter);
            if (opt) {
                //TODO: handle option
                printf("selection: %s -> %s\n", opt->getName().c_str(), opt->getString().c_str());
            }
        } else if (keys & Input::Button::B) {
            configBox->navigate(ConfigBox::Navigation::Exit);
        }

        // draw everything
        renderer->flip();
    }

    // cleanup
    delete (config);
    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
