#pragma once

#include "utils.h"
#include "game_world.h"
#include <glm/vec2.hpp>
#include <vector>
#include <memory>
#include <functional>
#include <deque>
#include <chrono>
#include <algorithm>

class GameObject {

public:
    GameObject(GameWorld& root, Tag tag, glm::vec2 position, float size) : mRoot(root), mTag(tag), mPosition(position), mSize(size){};
    virtual void Update(FrameDelta frameDelta) = 0;
    virtual void Draw() = 0;

    Tag GetTag() { return mTag;}
    bool GetDestroyed() { return mDestroyed;}

    virtual void Destroy()
    {
        mDestroyed = true;
    }

protected:
    GameWorld& mRoot;
    bool mDestroyed = false;
    Tag mTag;
    glm::vec2 mPosition;
    float mSize;

};


