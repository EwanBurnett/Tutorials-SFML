#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "States/State.h"

class Game {
public:
	Game();
	~Game();

	void Play(); //Starts the game

	static void TryPop();
	static void TryPush(std::string stateName);

	sf::RenderWindow& GetWindow();

private:
	sf::RenderWindow m_Window; //The Game Window.

	//Singleton of Game class
	static Game* sInstance;
};