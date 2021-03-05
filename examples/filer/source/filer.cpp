//
// Created by cpasjuste on 12/04/18.
//

#include "filer.h"

using namespace c2d;

Filer::Filer(c2d::Io *io, const std::string &path, c2d::Font *font,
             int fontSize, const c2d::FloatRect &rect) : RectangleShape(rect) {

    this->io = io;
    this->path = path;
    this->setFillColor(Color::Transparent);

    // create current path box
    pathRect = new RectangleShape({rect.width, fontSize + 10});
    pathRect->setFillColor(Color::GrayLight);
    pathRect->setOutlineColor(Color::Gray);
    pathRect->setOutlineThickness(2);
    pathText = new Text("/", (unsigned int) fontSize, font);
    pathText->setOutlineThickness(2);
    pathText->setOrigin(Origin::Left);
    pathText->setPosition(4, (pathRect->getSize().y / 2));
    pathText->setSizeMax(rect.width - 8, 0);
    pathRect->add(pathText);
    RectangleShape::add(pathRect);

    float y = pathRect->getGlobalBounds().top + pathRect->getGlobalBounds().height;
    FloatRect r = {0, y + 8, rect.width, rect.height - y - 8};
    listBox = new ListBox(font, fontSize, r, std::vector<Io::File>());
    listBox->setFillColor(Color::GrayLight);
    listBox->setOutlineColor(Color::Gray);
    listBox->setOutlineThickness(2);
    listBox->setTextColor(Color::White, Color::Yellow);
    listBox->setTextOutlineThickness(2);
    listBox->getHighlight()->setOutlineThickness(2);
    listBox->getHighlight()->setFillColor(Color::White);
    listBox->getHighlight()->setOutlineColor(Color::Black);
    listBox->getHighlight()->add(new TweenAlpha(50, 100, 0.6f, TweenLoop::PingPong));
    RectangleShape::add(listBox);

    if (!getDir(path)) {
        getDir("/");
    }
}

bool Filer::getDir(const std::string &p) {

    if (io->getType(p) != Io::Type::Directory) {
        return false;
    }

    printf("getDir(%s)\n", p.c_str());

    path = p;
    files = io->getDirList(path, true);
    if (files.empty()) {
        // add up/back ("..")
        files.emplace_back("..", "..", Io::Type::Directory, 0);
        return false;
    }

    listBox->setFiles(files);
    listBox->setSelection(0);
    pathText->setString(this->path);

    return true;
}

bool Filer::step(unsigned int keys) {

    if (keys & Input::Key::Up) {
        up();
    } else if (keys & Input::Key::Down) {
        down();
    } else if (keys & Input::Key::Right) {
        right();
    } else if (keys & Input::Key::Left) {
        left();
    } else if (keys & Input::Key::Fire1) {
        if (getSelection()->type == Io::Type::File) {
            return true;
        }
        enter();
    } else if (keys & Input::Key::Fire2) {
        exit();
    }

    return false;
}

void Filer::down() {
    listBox->down();
}

void Filer::up() {
    listBox->up();
}

void Filer::left() {
    int index = listBox->getIndex() - listBox->getMaxLines();
    if (index < 0)
        index = 0;
    listBox->getIndex();
    listBox->setSelection(index);
}

void Filer::right() {
    int index = listBox->getIndex() + listBox->getMaxLines();
    if (index >= (int) listBox->getFiles().size())
        index = (int) (listBox->getFiles().size() - 1);
    listBox->setSelection(index);
}

void Filer::enter() {

    Io::File *file = listBox->getSelection();

    if (file->name == "..") {
        exit();
        return;
    }

    if (path == "/") {
        getDir(path + file->name);
    } else {
        getDir(path + "/" + file->name);
    }
}

void Filer::exit() {

    if (path == "/" || path.find('/') == std::string::npos) {
        return;
    }

    while (path.back() != '/') {
        path.erase(path.size() - 1);
    }

    if (path.size() > 1 && Utility::endsWith(path, "/")) {
        path.erase(path.size() - 1);
    }

    getDir(path);
}

std::string Filer::getPath() {
    return path;
}

c2d::Io::File *Filer::getSelection() {
    return listBox->getSelection();
}

Filer::~Filer() {
    files.clear();
}
