#pragma once
#include <cinder/app/App.h>
#include <unordered_map>
using namespace ci::app;
class Controller {
public:
    Controller(std::initializer_list<char> bindings);
    void keyUp(KeyEvent &event);
    void keyDown(KeyEvent &event);
    bool held(char key) const;
private:
    std::unordered_map<char, bool> mKeyMap;
};


