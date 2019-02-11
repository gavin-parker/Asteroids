#include <cinder/gl/gl.h>
#include "asteroid.h"
#include "utils.h"
#include <cinder/app/App.h>
Asteroid::Asteroid(GameObject& parent, glm::vec2 direction, glm::vec2 position, float size, float speed) :
                Collidable(parent, position, size),
                mDirection(direction),
                mSpeed(speed) {

}

void Asteroid::Update(float frameDelta) {
    auto dist = mDirection * mSpeed * frameDelta;
    mPosition += dist;
    auto bounds = ci::app::getWindowBounds();
    if(!bounds.contains(mPosition))
        ReturnToPlayArea(bounds, mPosition);
    GameObject::Update(frameDelta);
}

void Asteroid::Draw() {
    ci::gl::drawStrokedCircle(mPosition, mSize);
    GameObject::Draw();
}

void Asteroid::Collide(Collidable &other) {
    std::cout << "hit an asteroid" << std::endl;
}
