#pragma once
#include "Observer.h"
#include "Event.h"
#include <iostream>

class AchievementManager : public Observer
{
private:
    int shoutCount = 0;
    int totalPotions = 0;
    int collectedPotions = 0;
    bool potionAchievementUnlocked = false;
    bool shoutAchievementUnlocked = false;

public:
    AchievementManager() {}

    void setTotalPotions(int total) { totalPotions = total; }

    bool onNotify(const Event& event) override
    {
        switch (event.getType())
        {
        case EventType::PotionCollected:
            collectedPotions++;
            if (!potionAchievementUnlocked && collectedPotions >= totalPotions)
            {
                potionAchievementUnlocked = true;
                unlockAchievement("Collected all potions!");
            }
            return true;

        case EventType::PlayerShouted:
            shoutCount++;
            if (!shoutAchievementUnlocked && shoutCount >= 5)
            {
                shoutAchievementUnlocked = true;
                unlockAchievement("Shouted 5 times!");
            }
            return true;
        }

        return false;
    }

private:
    void unlockAchievement(const std::string& achievementName)
    {
        std::cout << "Achievement Unlocked: " << achievementName << std::endl;
    }
};
