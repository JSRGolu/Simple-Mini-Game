#pragma once
#include "../entities/StaticEntities.h"  

const int LOG_POOL_SIZE = 10;

class LogPool
{
public:
    LogPool();
    std::shared_ptr<Log> acquire();
    void update(Game* game, float elapsed);
    void draw(Window* window);

private:
    std::shared_ptr<Log> logs[LOG_POOL_SIZE];
};
