#include "Game.h"
#include "StateStack.h"	
#include "States/State_FF1.h"
#include "States/State_MainMenu.h"

Game* Game::sInstance = nullptr;

Game::Game()
{
	assert(sInstance == nullptr);
	sInstance = this;
}

Game::~Game()
{
}

void Game::Play()
{
	//Singleton Declarations
	ResourceManager rManager;
	StateStack sStack;
	//Game game;

	//Add game states

	State_FF1* ff1 = new State_FF1(); {};
	State_MainMenu* mainMenu = new State_MainMenu(); {};

	//Using InitStates
	/*std::unordered_map<std::string, State*> StateInit;
	StateInit.try_emplace("FF1", ff1);
	StateInit.try_emplace("MainMenu", mainMenu);

	StateStack::InitStates(StateInit);
	StateStack::Push(mainMenu);*/

	//using InitState
	StateStack::InitState("Battle", ff1);
	StateStack::InitState("Main Menu", mainMenu);
	
	StateStack::Push("Main Menu");
	//Timing
	sf::Time deltaTime;
	sf::Clock clock;

	//Window Declaration
	sf::VideoMode videoMode(480, 320, 16U);
	m_Window.create(videoMode, "SFML States");

	m_Window.setFramerateLimit(60);

	//Game Loop
	while (m_Window.isOpen()) {

		//Calculate timing
		sf::Time elapsedTime = clock.restart(); // <-- Elapsed time between frames
		deltaTime += elapsedTime;
		float dtAsSeconds = deltaTime.asSeconds();

		//1. Poll Events
		sf::Event event;
		while (m_Window.pollEvent(event)) {
			
			switch (event.type) {
			case(sf::Event::EventType::Closed):
				StateStack::Clear();
				m_Window.close();
				break;

			default:
				StateStack::EventHandler(event);
				break;
			}
		}

		//2. Update
		StateStack::Update(deltaTime);

		//3. Render
		StateStack::Render(m_Window);

		m_Window.display();
		m_Window.clear();

	}

}

void Game::TryPop()
{
	StateStack::Pop();
}

void Game::TryPush(std::string stateName)
{
	StateStack::Push(stateName);
}

/*
void Game::TryPush(State* state)
{
	StateStack::Push(state);
}
*/

sf::RenderWindow& Game::GetWindow()
{
	return m_Window;
}
