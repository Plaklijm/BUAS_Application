#include "Object.h"
#include "surface.h"

Object::Object(Tmpl8::vec2 position, Tmpl8::vec2 size, World* world, Type type) : Actor(position, size, world), type(type)
{
    sprite = nullptr;
    
}

float frame = 0;
void Object::Render(Tmpl8::Surface* screen) const
{
    if (sprite != nullptr)
    {
        // To animate an object (implemented it like this because a whole animation system would be a lil too clunky)
        // !!!Disclaimer when the game is paused this will keep on running, bit of an oversight!!! 
        if (sprite->Frames() > 1)
        {
            sprite->SetFrame(frame);
            frame += .15f;
            if (frame >= sprite->Frames() -1) frame = 0;
        }
        sprite->Draw(screen, GetPosition().x, GetPosition().y);
    }
}

void Object::Collect() const
{
    delete this;
}

void Object::SetSprite(Tmpl8::Sprite* sprite)
{
    this->sprite = sprite;
}
