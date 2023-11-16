#pragma once
#include <list>

#include "ForceRegistration.h"

namespace Tmpl8
{
    
    class ForceRegistry
    {
    public:
        friend ForceRegistration;
        
        ForceRegistry() = default;

        void Add(const Rigidbody2D& rb, const ForceGenerator& fg);
        void Remove(const Rigidbody2D& rb, const ForceGenerator& fg);
        void Clear();

        void UpdateForces(float dt) const;
        void ZeroForces() const;
    private:
        std::list<ForceRegistration*> registry;
    };
    
}

