#pragma once
#include "State.h"
class State_Empty :
    public State
{
public:
    State_Empty();

    /*
    // Inherited via State
    virtual void Update(sf::Time deltaTime) override;
    virtual void Render(sf::RenderWindow& window) override;
    virtual void OnStateEntered() override;
    virtual void OnStateExit() override;
    */

    void Update(sf::Time deltaTime) ;
    void Render(sf::RenderWindow& window);
    void OnStateEntered() ;
    void OnStateExit() ;
    void EventHandler(sf::Event& event);
};

