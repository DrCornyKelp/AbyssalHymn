#ifndef MAP1_H
#define MAP1_H

#include "map.h"

class Map1 : public Map
{
private:
    int checkpoint_x = 3;
    int checkpoint_y = 3;

    std::vector<const char*> grass_decor = {
        "res/BlockTile/x64/Nature/GrassDecor0.png",
        "res/BlockTile/x64/Nature/GrassDecor1.png",
        "res/BlockTile/x64/Nature/GrassDecor2.png",
        "res/BlockTile/x64/Nature/GrassDecor3.png",
        "res/BlockTile/x64/Nature/GrassDecor4.png",
        "res/BlockTile/x64/Nature/GrassDecor5.png"
    };

    std::vector<const char*> nature_block = {
        // 0 - 8
        "res/BlockTile/x64/Nature/Dirt1.png",
        "res/BlockTile/x64/Nature/Dirt1Under.png",
        "res/BlockTile/x64/Nature/Dirt1Under1.png",
        "res/BlockTile/x64/Nature/Dirt1Under2.png",
        "res/BlockTile/x64/Nature/Dirt1Upper.png",
        "res/BlockTile/x64/Nature/Dirt1Upper1.png",
        "res/BlockTile/x64/Nature/Dirt1Upper2.png",
        "res/BlockTile/x64/Nature/Dirt1Wall1.png",
        "res/BlockTile/x64/Nature/Dirt1Wall2.png",

        // 9 - 17
        "res/BlockTile/x64/Nature/Dirt2.png",
        "res/BlockTile/x64/Nature/Dirt2Under.png",
        "res/BlockTile/x64/Nature/Dirt2Under1.png",
        "res/BlockTile/x64/Nature/Dirt2Under2.png",
        "res/BlockTile/x64/Nature/Dirt2Upper.png",
        "res/BlockTile/x64/Nature/Dirt2Upper1.png",
        "res/BlockTile/x64/Nature/Dirt2Upper2.png",
        "res/BlockTile/x64/Nature/Dirt2Wall1.png",
        "res/BlockTile/x64/Nature/Dirt2Wall2.png",
        
        // 18 - 20
        "res/BlockTile/x64/Nature/Grass1.png",
        "res/BlockTile/x64/Nature/Grass1Upper1.png",
        "res/BlockTile/x64/Nature/Grass1Upper2.png",

        // 21 - 26
        "res/BlockTile/x64/Nature/Bridge1.png",
        "res/BlockTile/x64/Nature/Bridge1Hold1.png",
        "res/BlockTile/x64/Nature/Bridge1Hold2.png",
        "res/BlockTile/x64/Nature/Bridge1Upper.png",
        "res/BlockTile/x64/Nature/Bridge1Upper1.png",
        "res/BlockTile/x64/Nature/Bridge1Upper2.png",

        // The last index possible
        "nothing :))"
    };
    int nb = nature_block.size() - 1;

public:
    // Player
    void initMapPlayer(Player *player) override;

    // NPC
    void initEnemies(SDL_Renderer *renderer) override;
    void initNpcDialogues(SDL_Renderer *renderer) override;

    // Items
    void initItems(SDL_Renderer *renderer) override;
    
    // Blocks
    void initBlocks(SDL_Renderer *renderer) override;

    // Cosmetic
    void initBackground(SDL_Renderer *renderer) override;
    void initBackDecors(SDL_Renderer *renderer) override;
    void initBlocksBack(SDL_Renderer *renderer) override;
    void initFrontDecors(SDL_Renderer *renderer) override;

    void updateMapExclusive(SDL_Renderer *renderer, Player *player, Input *input, Collision *collision) override;

};

#endif