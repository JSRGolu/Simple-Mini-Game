#pragma once
enum class ComponentID
{
	UNDEFINED = -1,
	INPUT = 0,
	POSITION = 1,
	VELOCITY = 2,
	COLLIDER = 3,
	GRAPHICS = 4,
	HEALTH = 5,
	PLAYERSTATE = 6,
	SPRITEGRAPHICS = 7,
	SPRITESHEETGRAPHICS = 8,
	TTL = 9,
	LOGIC = 10
};

class Component
{
public:

	virtual ~Component() = default;

	virtual ComponentID getID() const = 0;

};