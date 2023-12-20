#pragma once
#include "template.h"

using namespace Tmpl8;

/**
 * \brief This class is based on the implementation seen in Celeste
 * Following this article of the celeste Dev: https://www.mattmakesgames.com/articles/celeste_and_towerfall_physics/index.html
 * Some elements are directly copied like the way movement is handled in the MoveX and MoveY functions
 * This was also a handy guideline because the plan from the beginning was to make something inspired by the celeste Movement
 */

class Actor
{
public:
    struct BoxCollider* hitBox;

    void MoveX(float amount);
    void MoveY(float amount);

    vec2 GetPosition() const { return position; }
private:
    float xRemainder{};
    float yRemainder{};
    
    vec2 position = vec2::Zero();
};
