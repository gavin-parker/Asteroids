//
// Created by gavinparker on 10-2-19.
//

#include <cinder/gl/gl.h>
#include "laser.h"

Laser::Laser(glm::vec2 direction, glm::vec2 position) : mDirection(direction), mPosition(position) {}

void Laser::Update(const float frameDelta)
{
    auto dist = mDirection * speed * frameDelta;
    mPosition += dist;
}

void Laser::Draw()
{
    ci::gl::drawSolidCircle(mPosition, 1);
}
