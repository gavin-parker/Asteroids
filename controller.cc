//
// Created by gavinparker on 29/12/18.
//

#include "controller.h"
using namespace ci::app;

Controller::Controller(std::initializer_list<char> bindings)
{
    for(const auto &c : bindings)
        mKeyMap[c] = false;
}

void Controller::keyUp(KeyEvent &event)
{
    auto key = event.getChar();
    mKeyMap[key] = false;
}

void Controller::keyDown(KeyEvent &event)
{
    auto key = event.getChar();
    mKeyMap[key] = true;
}

bool Controller::held(char key) const
{
    return mKeyMap.at(key);
}

