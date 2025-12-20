#pragma once

#include <string>
#include <unordered_map>

enum BuildingClass { UNKNOWN = 1, HOUSE, FACTORY, PARK };

struct Vector2D {
    float x;
    float y;
};

class BuildingMetaData {
   public:
    Vector2D size;
    BuildingClass className;

    BuildingMetaData(BuildingClass className, Vector2D size)
        : className(className), size(size) {};

    ~BuildingMetaData() {};
};

static unordered_map<BuildingClass, BuildingMetaData> BuildingMetaDatabase = {
    {BuildingClass::HOUSE, BuildingMetaData(HOUSE, {1.0f, 1.0f})},
    {BuildingClass::FACTORY, BuildingMetaData(FACTORY, {2.0f, 2.0f})},
    {BuildingClass::PARK, BuildingMetaData(PARK, {1.5f, 1.5f})},
};

/**
 * Simple axis-alignement bounding boxes (AABB) object collision detection
 * between two rectangles. Each rectangle is defined by its position (top-left
 * corner) and size (x: width and y:height)
 *
 * needed for building placement validation, buildings should not overlap.
 *
 * @returns true if the rectangles are colliding, false otherwise.
 *  __________
 * |         |
 * |     ____|______
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
