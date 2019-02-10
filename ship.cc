#include "ship.h"
#define PI 3.14159265
using namespace std::chrono_literals;

Ship::Ship(const glm::vec2& center, const glm::vec2& heading, Controller& controller) :
        mPosition(center),
        mHeading(heading),
        mController(controller){

}

void Ship::Update(float frameDelta)
{
    if(mController.held('w'))
        Accelerate(frameDelta);
    if(mController.held('a'))
        Rotate(frameDelta*60.0f);
    if(mController.held('d'))
        Rotate(-frameDelta*60.0f);
    if(mController.held('e') and ReadyToFire())
        Fire();
    mPosition += mSpeed;
    GameObject::Update(frameDelta);
}

void Ship::Draw()
{

    const auto front = mHeading*mSize;
    const auto left = glm::vec2(mHeading.y*(mSize/2.0), -mHeading.x*(mSize/2.0));
    ci::gl::drawSolidTriangle(mPosition + front, mPosition + left, mPosition - left);
    GameObject::Draw();
}

void Ship::Accelerate(float force)
{
    mSpeed += mHeading * force;
}

void Ship::Rotate(float degreesClockwise)
{
    const auto rads = degreesClockwise * PI / 180.0;
    glm::mat2x2 rotation(glm::vec2(cos(rads), sin(rads)), glm::vec2(-sin(rads), cos(rads)));
    auto new_heading = mHeading * rotation;
    mHeading = new_heading;

}

void Ship::Fire()
{
    auto laser = CreateGameObject<Laser>(normalize(mHeading), mPosition);
    RegisterCallback([this, laser](){DestroyGameObject(laser);}, std::chrono::steady_clock::now() + 1s);
    mLastFireTime = std::chrono::steady_clock::now();
}

bool Ship::ReadyToFire()
{
    return std::chrono::steady_clock::now() - mLastFireTime > 200ms;
}
