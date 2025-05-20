#pragma once
#include "../entities/Fire.h"

const int FIRE_POOL_SIZE = 10;
const int defaultTTL = 150;

class FirePool
{
public:
    FirePool();
    std::shared_ptr<Fire> acquire();
    void update(Game* game, float elapsed);
    void draw(Window* window);

private:
    std::shared_ptr<Fire> fires[FIRE_POOL_SIZE];
};
