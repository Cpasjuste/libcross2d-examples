//
// Created by cpasjuste on 08/12/16.
//

#include <sstream>
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
    auto *renderer = new C2DRenderer({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});
    renderer->setClearColor(Color::GrayLight);

    // create a configuration named "C2D_CFG" in a writable directory (getHomePath)
    auto config = new Config("C2D_CFG", renderer->getIo()->getDataPath() + "config.cfg");

    // add a "config group"
    addConfigGroup(config);

    // load the configuration from file, overwriting default values (added in addConfigGroup)
    if (!config->load()) {
        // file doesn't exist or is malformed, (re)create it
        config->save();
    }

    // here the "INTEGER" option in group "DEMO" will be overwritten by the "config.cfg" file parameter, if any
    // note that you would normally check for a null pointer before "getInteger"
    printf("DEMO->INTEGER = %i\n", config->getOption("DEMO", "INTEGER")->getInteger());

    // create some text (width default font)
    auto *text = new Text();
    std::ostringstream os;
    // loop through all groups and options
    for (auto &group : *config->getGroups()) {
        os << group.getName() << "\n";
        for (auto &option : *group.getOptions()) {
            if (option.getType() == Option::Type::String
                || option.getType() == Option::Type::Choice) {
                os << "\t" << option.getName() << ": " << option.getString() << "\n";
            } else if (option.getType() == Option::Type::Integer) {
                os << "\t" << option.getName() << ": " << option.getInteger() << "\n";
            } else if (option.getType() == Option::Type::Float) {
                os << "\t" << option.getName() << ": " << option.getFloat() << "\n";
            } else if (option.getType() == Option::Type::Vector2f) {
                os << "\t" << option.getName() << ": [" <<
                   option.getVector2f().x << ", " << option.getVector2f().y << "]\n";
            } else if (option.getType() == Option::Type::FloatRect) {
                os << "\t" << option.getName() << ": [" <<
                   option.getFloatRect().left << ", " << option.getFloatRect().top << ", " <<
                   option.getFloatRect().width << ", " << option.getFloatRect().height << "]\n";
            } else if (option.getType() == Option::Type::Color) {
                os << "\t" << option.getName() << ": [" <<
                   (int) option.getColor().r << ", " << (int) option.getColor().g << ", " <<
                   (int) option.getColor().b << ", " << (int) option.getColor().a << "]\n";
            }
        }
    }
    text->setString(os.str());
    renderer->add(text);

    // change an option and save the new configuration, next time we load this example
    // the "INTEGER" option from "DEMO" group will return "20"
    // note that you would normally check for a null pointer before "getInteger"
    config->getOption("DEMO", "INTEGER")->setInteger(20);
    config->save();

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
    delete (config);

    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
