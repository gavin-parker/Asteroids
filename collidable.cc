#include <cmath>
#include "collidable.h"
#include "game_world.h"

Collidable::Collidable(GameObject& parent, glm::vec2 position, float size) : GameObject(parent, position, size)
{
    GameObject* p = &parent;
    while(not p->IsRoot())
        p = &p->GetParent();
    dynamic_cast<GameWorld*>(p)->AddCollider(this);
}

bool Collidable::Overlaps(glm::vec2 other) {
    const auto diff = mPosition - other;
    return std::sqrt(diff.x*diff.x + diff.y*diff.y) < mSize;
}
