#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../ResourceManager.h"
#include "../Game.h"

class State
{

public:

	//virtual ~State();

	virtual void Update(sf::Time deltaTime) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;
	virtual void OnStateEntered() = 0;
	virtual void OnStateExit() = 0;
	virtual void EventHandler(sf::Event& event) = 0;

};

