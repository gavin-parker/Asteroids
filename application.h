//
// Created by gavinparker on 27/12/18.
//

#ifndef HOMEWORK_APPLICATION_H
#define HOMEWORK_APPLICATION_H

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>
#include "ship.h"
#include "controller.h"

using namespace ci::app;

class Application : public App {
public:
    Application();
    void draw() override;
    void keyDown(KeyEvent event) override;
    void keyUp(KeyEvent event) override;
private:
    Ship player;
    double mLastFrameTime;
    double mThisFrameTime;
    Controller keyController{'w', 'a', 's', 'd'};
};


#endif //HOMEWORK_APPLICATION_H
CINDER_APP( Application, RendererGl )