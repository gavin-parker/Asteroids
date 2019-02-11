#pragma once
#include "ship.h"

class GameWorld : public GameObject {
public:
    explicit GameWorld(Controller& controller);
    void Update(float frameDelta) override;
    void Draw() override;

    void AddCollider(Collidable* collidable);
private:
    Controller& mController;
    std::unique_ptr<Ship> mShip;
    std::vector<Collidable*> mColliders;
    void SpawnAsteroid();
    void UpdateCollisions();
};