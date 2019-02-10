#include "game_world.h"


GameWorld::GameWorld(Controller &controller) :
        mController(controller),
        mShip(CreateGameObject<Ship>(ci::app::getWindowCenter(), glm::vec2{0.0, 1.0}, mController).get()){}

void GameWorld::Update(const float frameDelta)
{
    GameObject::Update(frameDelta);
}

void GameWorld::Draw()
{
    GameObject::Draw();
}