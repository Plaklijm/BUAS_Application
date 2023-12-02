#pragma once
#include "template.h"

using namespace Tmpl8;
struct AABB
{
public:
    vec2 pos;
    vec2 size;

    vec2 vel;
    AABB(vec2 pos, vec2 size) : pos(pos), size(size) {}
};
