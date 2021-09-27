#pragma once
#include "State_Empty.h"
class State_MainMenu :
    public State_Empty
{
    void Update(sf::Time deltaTime);
    void Render(sf::RenderWindow& window);
    void OnStateEntered();
    void OnStateExit();
    void EventHandler(sf::Event& event);

private:
    sf::Sprite Bgd;
    sf::Music BGM_MainMenu;
};

