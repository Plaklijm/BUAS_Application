#include "TextureManager.h"

#include "game.h"
#include "surface.h"

bool TextureManager::Load(std::string id, std::string fileName)
{
    char* cstr = new char[fileName.length() + 1];
    strcpy(cstr, fileName.c_str());
    
    Tmpl8::Surface* surface = new Tmpl8::Surface(cstr);
    if (!surface)
    {
        printf("Failed to load texture: %s", fileName.c_str());
        return false;
    }

    Tmpl8::Sprite* sprite = new Tmpl8::Sprite(surface, 1);

    TextureMap[id] = sprite;
    return true;
}

void TextureManager::DrawTile(Tmpl8::Sprite* sprite, int x, int y, int row, int frame)
{
    sprite->Draw(targetSurface, x, y);
}

/*void TextureManager::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame,
                              SDL_RendererFlip flip)
{
    SDL_Rect dstRect = {x,y,tileSize,tileSize};
    SDL_Rect srcRect = {tileSize*frame, tileSize*(row-1), tileSize, tileSize};
    SDL_RenderCopyEx(Tmpl8::Game::renderer,TextureMap[tilesetID], &srcRect, &dstRect, 0,0, flip);
}*/
