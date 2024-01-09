#include "TileLayer.h"

#include "../Engine/Solid.h"
#include "../Engine/BoxCollider.h"
#include "../Engine/surface.h"


TileLayer::TileLayer(bool collidable, int tileSize, int rowCount, int colCount, TileMap tileMap, const TileSetList& tileSetList)
    : tileSize(tileSize), rowCount(rowCount), colCount(colCount), tileMap(std::move(tileMap)), tileSets(tileSetList)
{
    this->collidable = collidable;

    // Load the map
    for (const auto& tileSet : tileSetList)
    {
        std::string temp = "assets/Map/" + tileSet.source;
        char* cTemp = new char[temp.length() + 1];
        strcpy(cTemp, temp.c_str());
        textures.emplace_back(new Tmpl8::Sprite(new Tmpl8::Surface(cTemp), tileSet.tileCount));
    }

    // initialize this layer
    SetupCollisionLayer();
    CalculateSpriteData();
}


void TileLayer::Render(Tmpl8::Surface* screen)
{
    for (const auto tile : tiles)
    {
        // If i created a new sprite for each one it was a lot more costly on performance, so this way only 1 sprite is loaded
        // and the frame is set to whichever tile needs to be rendered
        tile.sprite->SetFrame(static_cast<float>(tile.frameID));
        tile.sprite->Draw(screen, tile.posX, tile.posY);

        // Disclaimer, I made this and only after I did I came across the cpp fast track 11 for the Tiles so I didn't know about
        // the way they did it there, so the solution I came up with was putting the tileset as an sprite (but dumb but yeah)
        // it maybe isn't the most elegant of solutions but it works good enough to get the job done
        // https://www.3dgep.com/cpp-fast-track-11-tiles/
    }
}

/*
 * This function will setup a collision layer where the player can interact with. It will calculate the neighbours of each
 * tile, and only add the tiles without 4 neighbours, ive done it this way because it isn't necessary to have collidables
 * where you can't reach anyway. So it only gives a "shell" as a collider. Bit of optimization :)
 * ---------------------------------------------------------------------------------------------------------------------
 * Maybe a further improvement can be that if we are at an edge with 3 neighbours we can also skip it
 * and the same goes for corners but then with 2 neighbours.
 * But I looked into this for a bit and it seemed a bit too much for not enough in return. (The bigger the grid, the less it saves)
 * I did some testing with a pretty big world but at most it saved around 2 fps
 * (the biggest performance hit comes from drawing all the sprites, and not the amount of collidable tiles)
 */

void TileLayer::SetupCollisionLayer()
{
    // Create collidable layer from layer if its a collision layer
    if (collidable)
    {
        for (int i = 0; i < colCount; i++)
        {
            //if (i > 3) continue;
            for (int j = 0; j < rowCount; j++)
            {
                const auto tileID = tileMap[i][j];
                // continue if there is a non collidable tile

                // Check if the tile isn't empty and if the neighbour check isn't out of bounds
                // (When we are at an edge its always less than 4 neighbours so we always add them)
                if (tileID == 0) continue;
                if (i == 0 || i == colCount - 1 || j == 0 || j == rowCount - 1)
                {
                    collisionTiles.emplace_back(new Solid(Tmpl8::vec2(j * 32.f, i * 32.f), Tmpl8::vec2(tileSize,tileSize)));
                }
                else
                {
                    // Calculate neighbours
                    int neighbourCount = 0;
                    if (tileMap[i-1][j] != 0) neighbourCount++;
                    if (tileMap[i+1][j] != 0) neighbourCount++;
                    if (tileMap[i][j-1] != 0) neighbourCount++;
                    if (tileMap[i][j+1] != 0) neighbourCount++;

                    // Dont add tile if it has 4 neighbours (>= for safety)
                    if (neighbourCount >= 4) continue;
                    // Create a new solid at the position of the tile
                    collisionTiles.emplace_back(new Solid(Tmpl8::vec2(j * 32.f, i * 32.f), Tmpl8::vec2(tileSize,tileSize)));
                }
            }
        }
    }
}

/*
 * This function creates a vector with all the tiles that needs to be rendered and their position + frame
 * Previously this was in the Render function but I wanted to make that smaller
 * Also it needed to be a bit better without the nested for loop iteration through each frame, so a bit of performance was gained
 */
void TileLayer::CalculateSpriteData()
{
    for (int i = 0; i < colCount; i++)
    {
        for (int j = 0; j < rowCount; j++)
        {
            int tileID = tileMap[i][j];
            // continue if there is an empty tile
            if (tileID == 0) continue;

            // Check from which tileset the sprite needs to be loaded from
            int index = 0;
            if (tileSets.size() > 1)
            {
                for (int k = 1; k < tileSets.size(); k++)
                {
                    if (tileID >= tileSets[k].firstID && tileID <= tileSets[k].lastID)
                    {
                        // Calculate the correct tile ID
                        // Explained: 100 is the last of the first set, then the first of the second set is 101
                        // but we need 1 as the id to display it correctly
                        // So this formula calculates the actual ID needed from the correct set
                        tileID = tileID + tileSets[k].tileCount - tileSets[k].lastID;
                        index = k;
                        break;
                    }
                }
            }

            // Subtract 1 from the tileID to make sure the correct Frame from the source is loaded
            tileID--;

            // Create a new tile and set its data
            tile tile;
            tile.sprite = textures[index];
            tile.frameID = tileID;
            tile.posX = j * 32;
            tile.posY = i * 32;
            // Add it to a vector so the vector can be rendered instead of doing nested for loops each frame
            tiles.emplace_back(tile);
        }
    }
}
