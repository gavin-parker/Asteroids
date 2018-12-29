//

#include "application.h"

//
// Created by gavinparker on 27/12/18.
Application::Application() : player(getWindowCenter(), glm::vec2{0.0, 1.0}, 10),
                            mLastFrameTime(getElapsedSeconds()),
                            mThisFrameTime(getElapsedSeconds()){

}

void Application::draw()
{
    mThisFrameTime = getElapsedSeconds();
    auto delta = mThisFrameTime - mLastFrameTime;
    if(keyController.held('w'))
        player.accelerate(delta);
    if(keyController.held('a'))
        player.rotate(-delta*60.0);
    if(keyController.held('d'))
        player.rotate(delta*60.0);
    ci::gl::clear();
    player.draw();

    mLastFrameTime = mThisFrameTime;
}

void Application::keyDown(KeyEvent event) {
    keyController.keyDown(event);
}

void Application::keyUp(KeyEvent event) {
    keyController.keyUp(event);
}

