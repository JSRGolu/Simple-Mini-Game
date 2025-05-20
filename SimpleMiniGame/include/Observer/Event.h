#pragma once

enum class EventType
{
    PotionCollected,
    PlayerShouted
};

class Event
{
private:
    EventType type;

public:
    Event(EventType t) : type(t) {}
    EventType getType() const { return type; }
};
