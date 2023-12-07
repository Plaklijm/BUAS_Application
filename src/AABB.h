#pragma once

struct AABB
{
public:
    vec2 pos;
    vec2 size;
    
    AABB(vec2 pos, vec2 size) : pos(pos), size(size) {}
};
