#include "State_Empty.h"
#include <iostream>

State_Empty::State_Empty()
{
	std::cout << "New State_Empty constructed" << std::endl;
}

void State_Empty::Update(sf::Time deltaTime)
{
	std::cout << "Update Called" << std::endl;
}

void State_Empty::Render(sf::RenderWindow& window)
{
	std::cout << "Render Called" << std::endl;
	window.setTitle("Empty State");
}

void State_Empty::OnStateEntered()
{
	std::cout << "OnStateEntered Called" << std::endl;
}

void State_Empty::OnStateExit()
{
	std::cout << "OnStateExit Called" << std::endl;
}

void State_Empty::EventHandler(sf::Event& event)
{
	std::cout << "EventHandler Called" << std::endl;
}
