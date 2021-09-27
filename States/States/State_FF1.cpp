#include "State_FF1.h"
#include <assert.h>
#include <iostream>



State_FF1::State_FF1()
{
	//m_Window = nullptr;
}

void State_FF1::Update(sf::Time deltaTime)
{
	//std::cout << "Hi";
	//bgd.move(1, 0);
}

void State_FF1::Render(sf::RenderWindow& window)
{
	//m_Window = &window;
	window.setTitle("I'm a Final Fantasy addict");
	/*
	sf::Sprite bgd(ResourceManager::GetTexture("Background.png")); */
	window.draw(bgd);
	
}

void State_FF1::OnStateEntered()
{
	assert(music.openFromFile("Resources/Audio/BGM.ogg"));
	music.setLoop(true);
	music.play();

	bgd.setTexture(ResourceManager::GetTexture("Resources/Sprites/Background.png"));
}

void State_FF1::OnStateExit()
{
	music.stop();

	sf::Sound ExitSound(ResourceManager::GetSoundBuffer("Resources/Audio/SFX_Exit.ogg"));
	ExitSound.play();
	sf::sleep(sf::seconds(6));
	ExitSound.stop();
}

void State_FF1::EventHandler(sf::Event& event)
{
	switch (event.type) {
		case(sf::Event::EventType::KeyPressed):
			if (event.key.code == sf::Keyboard::Space)
				std::cout << "Fire 4!" << std::endl;
				Game::TryPop();
	}
}
