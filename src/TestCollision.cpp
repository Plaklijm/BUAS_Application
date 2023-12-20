#include "TestCollision.h"

#include "BoxCollider.h"
#include "template.h"

TestCollision::TestCollision()
{
    hitBox = new BoxCollider(vec2(0, 100), vec2(200, 64));
}
