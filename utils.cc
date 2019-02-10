//
// Created by gavinparker on 10-2-19.
//


#include <cinder/Area.h>
#include <glm/vec2.hpp>

void ReturnToPlayArea(cinder::Area &bounds, glm::vec2 &pos){
    if(pos.x > bounds.x2)
        pos.x = pos.x - bounds.x2;
    if(pos.x < bounds.x1)
        pos.x = pos.x - bounds.x1;
    if(pos.y > bounds.y2)
        pos.y = pos.y - bounds.y2;
    if(pos.y < bounds.y1)
        pos.y = pos.y - bounds.y1;
}
