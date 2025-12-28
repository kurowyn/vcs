#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "data/enums.hpp"

struct Vector2D {
    float x;
    float y;
};

class BuildingMetaData {
   public:
    Vector2D size;
    EBuildingClass className;

    BuildingMetaData(EBuildingClass className, Vector2D size)
        : className(className), size(size) {};

    ~BuildingMetaData() {};
};

namespace BuildingMetaDict {
extern BuildingMetaData* HOUSE  ;
extern BuildingMetaData* FACTORY;
extern BuildingMetaData* PARK;
BuildingMetaData getMetaFromEnum(EBuildingClass className);

}  // namespace BuildingMetaDict

/**
 * Simple axis-alignment bounding boxes (AA`BB) object collision detection
 * between two rectangles. Each rectangle is defined by its position (top-left
 * corner) and size (x: width and y:height)
 *
 * needed for building placement validation, buildings should not overlap
 * (in case a building takes more than one tile).
 *
 * @returns true if the rectangles are colliding, false otherwise.
 *  __________
 * |         |
 * |     ____|______    ---> areColliding = true
 * |____|____|      |
 *      |___________|
 *
 */
static bool areColliding(Vector2D xPos, Vector2D xSize, Vector2D yPos,
                         Vector2D ySize) {
    bool collidingX = xPos.x < yPos.x + ySize.x && xPos.x + xSize.x > yPos.x;
    if (!collidingX) return false;  //* micro optimization :P

    bool collidingY = xPos.y < yPos.y + ySize.y && xPos.y + xSize.y > yPos.y;
    return collidingY;
}
