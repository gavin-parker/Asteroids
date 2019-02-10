#pragma once
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>
#include "controller.h"
#include "game_object.h"
#include "laser.h"

class Ship : public GameObject {
public:
    Ship(const glm::vec2 &center, const glm::vec2& heading, Controller& controller);
    void Update(float frameDelta);
    void Draw();
    void Accelerate(float force);
    void Rotate(float degreesClockwise);
    void Fire();
private:
    glm::vec2 mPosition;
    glm::vec2 mHeading;
    const float mSize = 10;
    Controller& mController;
    glm::vec2 mSpeed{0,0};
    std::vector<std::shared_ptr<Laser>> mLasers;

    std::chrono::steady_clock::time_point mLastFireTime = std::chrono::steady_clock::now();
    bool ReadyToFire();
};


