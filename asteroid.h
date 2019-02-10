#pragma once

#include <glm/vec2.hpp>
#include "game_object.h"

class Asteroid : public GameObject {
public:
    Asteroid(glm::vec2 direction, glm::vec2 position, float size);

    void Update(float frameDelta) override;
    void Draw() override;
private:
    glm::vec2 mDirection;
    glm::vec2 mPosition;
    float mSize;
    float mSpeed;
};


