#include "laser.h"
#include <cinder/gl/gl.h>

Laser::Laser(GameWorld& root, glm::vec2 direction, glm::vec2 position) : Collidable(root, Tag::Laser, position, 1), mDirection(direction){}

void Laser::Update(const FrameDelta frameDelta)
{
    auto dist = mDirection * speed * frameDelta.count();
    mPosition += dist;
}

void Laser::Draw()
{
    ci::gl::drawSolidCircle(mPosition, mSize);
}

void Laser::Collide(Collidable &other) {
    if(other.GetTag() == Tag::Asteroid)
        Destroy();

}