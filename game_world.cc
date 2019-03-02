#include "game_world.h"
#include "asteroid.h"
#include "ship.h"
#include <glm/gtc/random.hpp>

using namespace std::chrono_literals;

GameWorld::GameWorld(Controller &controller) :
        mController(controller)
{
    SpawnObject<Ship>(ci::app::getWindowCenter(), glm::vec2{0.0, 1.0}, mController);
    RegisterCallback([this](){
        SpawnAsteroid();
    }, 5s);
}

void GameWorld::Update(const FrameDelta frameDelta)
{
    UpdateCollisions();
    mCallbacks.erase(std::remove_if(mCallbacks.begin(), mCallbacks.end(), [this](auto &callback){return Call(callback);}), mCallbacks.end());
    mChildren.erase(std::remove_if(mChildren.begin(), mChildren.end(), [](auto &child){return child->GetDestroyed();}), mChildren.end());
    std::for_each(mChildren.begin(), mChildren.end(), [frameDelta](auto child){child->Update(frameDelta);});
}

bool GameWorld::Call(Callback &callback)
{
    auto now = std::chrono::steady_clock::now();
    if(now > std::get<1>(callback))
    {
        std::get<0>(callback)();
        return true;
    }
    return false;
}

void GameWorld::Draw() {
    std::for_each(mChildren.begin(), mChildren.end(), [](auto child){child->Draw();});
}

void GameWorld::SpawnAsteroid()
{
    auto direction = glm::sphericalRand(1.0);
    CreateGameObject<Asteroid>(glm::vec2{1.0, 1.0}, glm::normalize(direction), 20, 30);
    RegisterCallback([this](){
        SpawnAsteroid();
    }, 10s);
}

void GameWorld::AddCollider(Collidable* collidable)
{
    mColliders.push_back(collidable);
}

void GameWorld::UpdateCollisions() {
    //FIXME: collection of references without ownership?
    for(auto it = mColliders.begin(); it != mColliders.end(); it++)
    {
        auto& a = *it;
        std::for_each(it, mColliders.end(), [&](auto& b){
            if(a != b and a->Overlaps(*b))
            {
                a->Collide(*b);
                b->Collide(*a);
            }
        });
    }

}

void GameWorld::RemoveCollider(Collidable *collidable) {
    mColliders.erase(std::remove_if(mColliders.begin(), mColliders.end(), [collidable](Collidable* collider){return collider == collidable;}), mColliders.end());
}

