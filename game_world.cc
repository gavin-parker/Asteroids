#include "game_world.h"
#include "asteroid.h"
#include "cinder/Rand.h"

GameWorld::GameWorld(Controller &controller) :
        GameObject(true),
        mController(controller),
        mShip(CreateGameObject<Ship>(ci::app::getWindowCenter(), glm::vec2{0.0, 1.0}, mController).get()){
    RegisterCallback([this](){
        SpawnAsteroid();
    }, std::chrono::steady_clock::now() + std::chrono::seconds(5));
}

void GameWorld::Update(const float frameDelta)
{
    GameObject::Update(frameDelta);
    UpdateCollisions();
}

void GameWorld::Draw()
{
    GameObject::Draw();
}

void GameWorld::SpawnAsteroid()
{
    auto dir =  glm::vec2{cinder::Rand::randFloat(0.0, 1.0), cinder::Rand::randFloat(0.0, 1.0)};
    CreateGameObject<Asteroid>(glm::vec2{1.0, 1.0}, glm::normalize(dir), 20, 30);
    RegisterCallback([this](){
        SpawnAsteroid();
    }, std::chrono::steady_clock::now() + std::chrono::seconds(10));
}

void GameWorld::AddCollider(Collidable* collidable)
{
    mColliders.push_back(collidable);
}

void GameWorld::UpdateCollisions() {
    mColliders.erase(std::remove_if(mColliders.begin(), mColliders.end(), [](const auto &collider){return not collider;}), mColliders.end());

    std::for_each(mColliders.begin(), mColliders.end(), [this](auto &a){
        std::for_each(mColliders.begin(), mColliders.end(), [this, a](auto &b){
            if(a != b and a->Overlaps(b->GetPosition()))
                a->Collide(*b);
        });
    });
}
