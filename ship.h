//
// Created by gavinparker on 27/12/18.
//

#ifndef HOMEWORK_SHIP_H
#define HOMEWORK_SHIP_H
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>


class Ship {
public:
    Ship(const glm::vec2 &center, const glm::vec2 &heading, float size=10);
    void draw();
    void accelerate(float force);
    void rotate(float degreesClockwise);
private:
    glm::vec2 mPosition;
    glm::vec2 mHeading;
    float mSize;
    glm::vec2 mSpeed{0,0};
};


#endif //HOMEWORK_SHIP_H
