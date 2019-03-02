#pragma once

#include <glm/vec2.hpp>
#include "collidable.h"

class Laser : public Collidable {
public:
    Laser(GameWorld& parent, glm::vec2 direction, glm::vec2 position);
    ~Laser() = default;
    void Update(FrameDelta frameDelta) override;
    void Draw() override;
    void Collide(Collidable& other) override;
private:
    const glm::vec2 mDirection;
    const float speed = 100;
};


