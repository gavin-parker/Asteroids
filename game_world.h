#pragma once
#include "ship.h"

class GameWorld {
public:
    explicit GameWorld(Controller& controller);
    void Update(float frameDelta);
    void Draw();
private:
    Controller& mController;
    Ship mShip;
};


