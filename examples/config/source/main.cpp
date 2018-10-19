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

    // add a child group to demo group
    Group child("CHILD");
    child.addOption({"INTEGER", 11});
    group.addGroup(child);

    // add all that to the main config
    config->addGroup(group);
}

int main() {

    // create the main renderer
    auto *renderer = new C2DRenderer({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});
    renderer->setClearColor(Color::GrayLight);

    // create a configuration named "C2D_CFG" in a writable directory (getHomePath)
    Config *config = new Config("C2D_CFG", renderer->getIo()->getHomePath() + "config.cfg");
    // add a group to the configuration
    addConfigGroup(config);
    // load the configuration from file, overwriting default values (added in addConfigGroup)
    if (!config->load()) {
        // file doesn't exist or is malformed, (re)create it
        config->save();
    }

    // here the "INTEGER" option in group "DEMO" will be overwritten by the "config.cfg" file parameter, if any
    // note that you would normally check for a null pointer before "getInteger"
    printf("DEMO->INTEGER = %i\n", config->getOption("DEMO", "INTEGER")->getInteger());

    // create some text (width default font), for fun
    auto *text = new C2DText();
    std::ostringstream os;
    // loop through all groups and options
    for (auto &group : *config->getGroups()) {
        os << group.getName() << "\n";
        for (auto &option : *group.getOptions()) {
            if (option.getType() == Option::Type::Integer) {
                os << "\t" << option.getName() << ": " << option.getInteger() << "\n";
            } else if (option.getType() == Option::Type::Float) {
                os << "\t" << option.getName() << ": " << option.getFloat() << "\n";
            } else {
                os << "\t" << option.getName() << ": " << option.getString() << "\n";
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
