#include <memory>  
#include <vector>
#include <SFML/Window/Keyboard.hpp> 

class Command;
class Game;

class InputHandler
{
public:
    InputHandler();  
    std::shared_ptr<Command> handleInput();  

private:
    std::shared_ptr<Command> pauseCommand;
	std::shared_ptr<Command> changeCommand;
    bool wasEscapePressed = false;
	bool wasChangePressed = false;
};


class PlayerInputHandler
{
public:
    PlayerInputHandler();
    std::vector<std::shared_ptr<Command>>& handlePlayerInput(Game& game);
    std::vector<std::shared_ptr<Command>> commands;

private:
    std::shared_ptr<Command> moveRight;
    std::shared_ptr<Command> moveLeft;
    std::shared_ptr<Command> moveUp;
    std::shared_ptr<Command> moveDown;
    std::shared_ptr<Command> attack;
    std::shared_ptr<Command> shout;
};