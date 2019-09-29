//
// Created by cpasjuste on 12/04/18.
//

#ifndef FILER_FILER_H
#define FILER_FILER_H

#include "cross2d/c2d.h"

class Filer : public c2d::C2DRectangle {

public:

    Filer(c2d::Io *io, const std::string &path, c2d::Font *font,
          int fontSize, const c2d::FloatRect &rect);

    ~Filer();

    bool getDir(const std::string &path);

    std::string getPath();

    bool step(unsigned int keys);

    c2d::Io::File *getSelection();

private:

    void down();

    void up();

    void left();

    void right();

    void enter();

    void exit();

    std::string path;
    std::vector<c2d::Io::File> files;
    c2d::Io *io;
    c2d::ListBox *listBox;
    c2d::C2DRectangle *pathRect;
    c2d::Text *pathText;
};

#endif //FILER_FILER_H
