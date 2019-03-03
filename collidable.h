#pragma once
#include "game_object.h"


class Collidable : public GameObject {
public:
    Collidable(GameWorld* root, uint64_t id, glm::vec2 position, float size);

    ~Collidable();
    bool Overlaps(Collidable& other);

    float GetSize(){return mSize;}
    glm::vec2& GetPosition() { return mPosition;}

    virtual void Collide(Collidable& other) = 0;

};
