#pragma once
#include "game_object.h"

class Collidable : public GameObject {
public:
    Collidable(GameObject& parent, glm::vec2 position, float size);

    bool Overlaps(glm::vec2 other);

    glm::vec2& GetPosition() { return mPosition;}
    virtual void Collide(Collidable& other) = 0;

};
