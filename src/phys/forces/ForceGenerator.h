#pragma once

namespace Tmpl8
{
    class Rigidbody2D;
    
    class ForceGenerator
    {
    public:
        virtual void UpdateForce(Rigidbody2D rb, float dt);

    private:
        virtual ~ForceGenerator() = default;
    };
}
