#pragma once
#include "State_Empty.h"
class State_FF1 :
    public State_Empty
{
public:

    State_FF1();

    void Update(sf::Time deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    void OnStateEntered() override;
    void OnStateExit() override;
    void EventHandler(sf::Event& event);

private:
    //sf::RenderWindow* m_Window;

    //State member variables
    sf::Music music;
    sf::Sprite bgd;
    
};

