#pragma once
class Game;

class Command
{
public:
    virtual ~Command() = default;  
    virtual void execute(Game& game) = 0; 
};

class PauseCommand : public Command
{
public:
    void execute(Game& game) override; 
};

class ChangeCommand : public Command
{
public:
	void execute(Game& game) override;
};

class MoveRightCommand : public Command
{
public:
    void execute(Game& game) override;
};

class MoveLeftCommand : public Command
{
public:
    void execute(Game& game) override;
};

class MoveUpCommand : public Command
{
public:
    void execute(Game& game) override;
};

class MoveDownCommand : public Command
{
public:
    void execute(Game& game) override;
};

class AttackCommand : public Command
{
public:
    void execute(Game& game) override;
};

class ShoutCommand : public Command
{
public:
    void execute(Game& game) override;
};