#pragma once

#include <cinder/Area.h>
#include <glm/vec2.hpp>
#include <chrono>

enum class Tag {
    None,
    Player,
    Laser,
    Asteroid
};

using FrameDelta = std::chrono::duration<float>;


void ReturnToPlayArea(const cinder::Area &bounds, glm::vec2 &pos);