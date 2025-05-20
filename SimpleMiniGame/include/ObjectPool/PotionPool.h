#pragma once
#include "../entities/StaticEntities.h"  

const int POTION_POOL_SIZE = 10;

class PotionPool
{
public:
    PotionPool();
    std::shared_ptr<Potion> acquire();
    void update(Game* game, float elapsed);
    void draw(Window* window);

private:
    std::shared_ptr<Potion> potions[POTION_POOL_SIZE];
};
