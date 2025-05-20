#include "../../include/ObjectPool/FirePool.h"
#include "../../include/core/Game.h"

FirePool::FirePool()
{
    for (int i = 0; i < FIRE_POOL_SIZE; ++i) {
        fires[i] = std::make_shared<Fire>();
    }
}

std::shared_ptr<Fire> FirePool::acquire()
{
    for (int i = 0; i < FIRE_POOL_SIZE; ++i) {
        if (!fires[i]->inUse()) {
            fires[i]->setTTL(defaultTTL);
            return fires[i];
        }
    }
    return nullptr;
  
}

void FirePool::update(Game* game, float elapsed)
{
    for (int i = 0; i < FIRE_POOL_SIZE; ++i) {
        fires[i]->update(game, elapsed);
    }
}

void FirePool::draw(Window* window)
{
    for (int i = 0; i < FIRE_POOL_SIZE; ++i) {
        fires[i]->draw(window);
    }
}
