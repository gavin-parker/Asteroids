//
// Created by gavinparker on 27/12/18.
//

#include "ship.h"
#define PI 3.14159265
Ship::Ship(const glm::vec2 &center, const glm::vec2 &heading, float size) : mPosition(center), mHeading(heading), mSize(size){

}

void Ship::draw() {
    mPosition += mSpeed;

    const auto front = mHeading*mSize;
    const auto left = glm::vec2(mHeading.y*(mSize/2.0), -mHeading.x*(mSize/2.0));
    ci::gl::drawSolidTriangle(mPosition + front, mPosition + left, mPosition - left);
}

void Ship::accelerate(float force) {
    mSpeed += mHeading * force;
}

void Ship::rotate(float degreesClockwise) {
    const auto rads = degreesClockwise * PI / 180.0;
    glm::mat2x2 rotation(glm::vec2(cos(rads), sin(rads)), glm::vec2(-sin(rads), cos(rads)));
    auto new_heading = mHeading * rotation;
    mHeading = new_heading;
}
