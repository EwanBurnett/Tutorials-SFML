#include "State_MainMenu.h"
#include <assert.h>
#include "State_FF1.h"

void State_MainMenu::Update(sf::Time deltaTime)
{
}

void State_MainMenu::Render(sf::RenderWindow& window)
{
	window.setTitle("MainMenu");
	window.draw(Bgd);

	Bgd.setPosition(window.getSize().x / 2, window.getSize().y / 2);
}

void State_MainMenu::OnStateEntered()
{
	assert(BGM_MainMenu.openFromFile("Resources/Audio/BGM_MainMenu.ogg"));
	BGM_MainMenu.setLoop(true);
	BGM_MainMenu.play();

	Bgd.setTexture(ResourceManager::GetTexture("Resources/Sprites/Background_MainMenu.png"));
	Bgd.setOrigin(Bgd.getTexture()->getSize().x / 2, Bgd.getTexture()->getSize().y / 2);
}

void State_MainMenu::OnStateExit()
{
	BGM_MainMenu.stop();
}

void State_MainMenu::EventHandler(sf::Event& event)
{
	switch (event.type) {
	case(sf::Event::EventType::KeyPressed):
		if (event.key.code == sf::Keyboard::Space) {
			Game::TryPush("FF1");
		}
	}
}
