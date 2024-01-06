#pragma once
#include "Layer.h"

class Object;


class ObjectLayer : public Layer
{
public:
    ObjectLayer();
    
    void Render(Tmpl8::Surface* screen) override;
    void Update() override;

    void AddObject(Object* obj);

private:
};
