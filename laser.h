#pragma once

#include <glm/vec2.hpp>
#include "game_object.h"

class Laser : public GameObject {
public:
    Laser(glm::vec2 direction, glm::vec2 position);
    ~Laser() = default;
    void Update(float frameDelta);
    void Draw();
private:
    const glm::vec2 mDirection;
    glm::vec2 mPosition;
    const float speed = 100;
};


