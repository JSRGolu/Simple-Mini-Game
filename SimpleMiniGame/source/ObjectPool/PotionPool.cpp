#include "../../include/ObjectPool/PotionPool.h"
#include "../../include/core/Game.h"

PotionPool::PotionPool()
{
    for (int i = 0; i < POTION_POOL_SIZE; ++i) {
        potions[i] = std::make_shared<Potion>();
    }
}

std::shared_ptr<Potion> PotionPool::acquire()
{
    for (int i = 0; i < POTION_POOL_SIZE; ++i) {
        if (!potions[i]->inUse()) {
            std::cout << "fanhuile: " << i << std::endl;
            potions[i]->ReverseToggle();
            return potions[i];
        }
    }
    return nullptr;
}

void PotionPool::update(Game* game, float elapsed)
{
    for (int i = 0; i < POTION_POOL_SIZE; ++i) {
        if (potions[i]->inUse()) {
            potions[i]->update(game, elapsed);
        }
    }
}

void PotionPool::draw(Window* window)
{
    for (int i = 0; i < POTION_POOL_SIZE; ++i) {
        if (potions[i]->inUse()) {
            potions[i]->draw(window);
        }
    }
}
