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

    // add a child group
    Group child("CHILD");
    child.addOption({"INTEGER", 777});
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


    // loop through all groups and options
    for (auto &group : *config->getGroups()) {
        printf("\n%s:\n", group.getName().c_str());
        for (auto &option : *group.getOptions()) {
            if (option.getType() == Option::Type::Integer) {
                printf("\t%s: %i\n", option.getName().c_str(), option.getInteger());
            } else if (option.getType() == Option::Type::Float) {
                printf("\t%s: %f\n", option.getName().c_str(), option.getFloat());
            } else {
                printf("\t%s: %s\n", option.getName().c_str(), option.getString().c_str());
            }
        }
    }

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
