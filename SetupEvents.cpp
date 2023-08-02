#include "SetupEvents.h"

std::vector<std::shared_ptr<Event>> SetupEvents(std::shared_ptr<PlayerCharacter> player)
{
    std::vector<std::shared_ptr<Event>> events;

    // Create the "Find the Lost Sword" event
    auto findLostSwordEvent = std::make_shared<Event>(
        "Find the Lost Sword",                                   // Name
        1001,                                                    // EventID
        "Find the legendary lost sword in the\n"
        "Depths of Ancient Cave 1",                        // Description
        EventStatus::Inactive,                                   // Initial EventStatus

        // ActivationCondition
        [&player]() 
        {
            // Event triggers when player enters the Ancient Cave location
            return player->GetCurrentLocation()->GetName() == "Ancient Cave 1";
        },
        // CompletionCondition
        [&player]() 
        {
            // Event completes when player has item with ID 2314 (the lost sword)
            return player->HasItem(2314);
        },
        // FailureCondition
        []() 
        {
            // In this case, the event doesn't have a specific failure condition
            return false;
        }
    );
    events.push_back(findLostSwordEvent);

    // Create other events...

    return events;
}

// add events to player:
//