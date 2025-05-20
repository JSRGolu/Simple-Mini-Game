#include "../../include/core/Command.h"
#include "../../include/core/Game.h"
#include "../../include/Components/VelocityComponent.h"
#include <iostream>

void MoveRightCommand::execute(Game& game)
{
    if (game.getPlayer())
    {
        auto v = game.getPlayer()->getVelocity();
		v->setVelocity(1.0f, v->getVelocity().y);
    }
}

void MoveLeftCommand::execute(Game& game)
{
    if (game.getPlayer())
    {
        auto v = game.getPlayer()->getVelocity();
        v->setVelocity(-1.0f, v->getVelocity().y);
    }
}

void MoveUpCommand::execute(Game& game)
{
    if (game.getPlayer())
    {
        auto v = game.getPlayer()->getVelocity();
        v->setVelocity(v->getVelocity().x, -1.0f);
    }
}

void MoveDownCommand::execute(Game& game)
{
    if (game.getPlayer())
    {
        auto v = game.getPlayer()->getVelocity();
        v->setVelocity(v->getVelocity().x, 1.0f);
    }
}

void AttackCommand::execute(Game& game)
{
    if (game.getPlayer())
    {
        game.getPlayer()->setAttacking(true);
    }
}

void ShoutCommand::execute(Game& game)
{
    if (game.getPlayer())
    {
        game.getPlayer()->setShouting(true);
    }
}