#pragma once
#pragma once

class Event; 

class Observer
{
public:
    virtual ~Observer() {}
    virtual bool onNotify(const Event& event) = 0;
};
