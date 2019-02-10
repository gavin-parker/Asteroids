#include "game_world.h"


GameWorld::GameWorld(Controller &controller) :
        mController(controller),
        mShip(getWindowCenter(), glm::vec2{0.0, 1.0}, mController){}

void GameWorld::Update(const float frameDelta)
{
    mShip.Update(frameDelta);
}

void GameWorld::Draw()
{
    mShip.Draw();
}