//
// Created by cpasjuste on 08/12/16.
//

#include "cross2d/c2d.h"

using namespace c2d;
using namespace c2d::config;

int main() {

    // create the main renderer
    auto *renderer = new C2DRenderer({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});
    renderer->setClearColor(Color::GrayLight);

    // create io helper
    auto *io = new C2DIo();

    // TODO
    Config *config = new Config("C2D_CFG", io->getHomePath() + "config.cfg");

    Section section("DEMO");
    section.add({"INTEGER", 10});
    section.add({"STRING", "Hello World"});
    section.add({"FLOAT", 9.99f});
    config->add(section);

    if(!config->load()) {
        // file doesn't exist or is not well formed, (re)create it
        config->save();
    }

    printf("%i\n", section.getOptions().at(0).getInteger());
    printf("%i\n", config->getSection("DEMO").getOption("INTEGER").getInteger());

    // main loop
    while (renderer->getElapsedTime().asSeconds() < 10) {

        // draw everything
        renderer->flip();
    }

    // cleanup
    delete (config);
    delete (io);
    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
