#pragma once
#include "ship.h"

class GameWorld : public GameObject {
public:
    explicit GameWorld(Controller& controller);
    void Update(float frameDelta) override;
    void Draw() override;

    void AddCollider(Collidable* collidable);
    void RemoveCollider(Collidable* collidable);

private:
    Controller& mController;
    std::vector<Collidable*> mColliders;
    void SpawnAsteroid();
    void UpdateCollisions();
};