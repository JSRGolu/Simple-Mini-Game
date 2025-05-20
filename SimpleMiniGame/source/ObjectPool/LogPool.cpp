#include "../../include/ObjectPool/LogPool.h"
#include "../../include/core/Game.h"

LogPool::LogPool()
{
    for (int i = 0; i < LOG_POOL_SIZE; ++i) {
        logs[i] = std::make_shared<Log>();
        std::cout << logs[i] << std::endl;
    }
}

std::shared_ptr<Log> LogPool::acquire()
{
    for (int i = 0; i < LOG_POOL_SIZE; ++i) {
        if (!logs[i]->inUse()) {
            logs[i]->ReverseToggle();
            return logs[i];
        }
    }
    return nullptr;
}

void LogPool::update(Game* game, float elapsed)
{
    for (int i = 0; i < LOG_POOL_SIZE; ++i) {
        logs[i]->update(game, elapsed);
    }
}

void LogPool::draw(Window* window)
{
    for (int i = 0; i < LOG_POOL_SIZE; ++i) {
        logs[i]->draw(window);
    }
}
