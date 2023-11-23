#pragma once
#include "template.h"

using namespace Tmpl8;
struct AABB
{
private:
    vec2 center;
    vec2 halfSize;

public:
    AABB(vec2 center, vec2 halfSize) : center(center), halfSize(halfSize) {}

    auto GetCenter() const { return center; }
    auto GetHalfSize() const { return halfSize; }

    void SetCenter(vec2 center) { this->center = center; }
    void SetHalfSize(vec2 halfSize) { this->halfSize = halfSize; }
};
