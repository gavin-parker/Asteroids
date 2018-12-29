//
// Created by gavinparker on 29/12/18.
//

#ifndef HOMEWORK_CONTROLLER_H
#define HOMEWORK_CONTROLLER_H
#include <cinder/app/App.h>
#include <unordered_map>
using namespace ci::app;
class Controller {
public:
    Controller(std::initializer_list<char> bindings);
    void keyUp(KeyEvent event);
    void keyDown(KeyEvent event);
    bool held(char key) const;
private:
    std::unordered_map<char, bool> mKeyMap;
};


#endif //HOMEWORK_CONTROLLER_H
