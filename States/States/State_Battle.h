#pragma once
#include "State.h"
#include <string>
#include <list>

struct Action {
public:
    std::string mName;
    float mATBTime;
};

class Entity {
public:
    std::string mName;
    std::list<Action> mActions;
    float mATB = 2.0f;
};

class State_Battle {
public:
    void Update(sf::Time deltaTime);
    void Render(sf::RenderWindow& window);
    void OnStateEntered();
    void OnStateExit();
    void EventHandler(sf::Event& event);

private:
    void SortActionQueue();
    void SortEntityQueue();
    //A queue for executed actions. Actions with the shortest time remaining will be first in the queue.
    std::list<Action> mActionQueue;
    //A queue for entities in the battle. Enemies and players are all pooled together, with the one with the lowest ATB taking its turn.
    std::list<Entity> mEntityQueue;

};