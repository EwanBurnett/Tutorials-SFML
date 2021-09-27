#pragma once
#include <SFML/Graphics.hpp>
#include <assert.h>
#include <vector>
#include <unordered_map>
#include "States/State.h"
#include "States/State_Empty.h"

class StateStack : sf::NonCopyable
{
public:

	StateStack();
	~StateStack();

	static void InitStates(std::unordered_map<std::string, State*> l_States);
	static void Update(sf::Time deltaTime);
	static void Render(sf::RenderWindow& window);
	static void EventHandler(sf::Event& event);
	static void Pop();
	static void Push(State* state);
	static void Push(std::string stateName);
	static void Clear();

private:
	//static bool ValidateState(State* state);

	static std::vector<State*> m_Stack;
	//static std::vector<State*> m_States;
	static std::unordered_map<std::string, State*>m_States;
	
	static State* m_CurrentState;

	static StateStack* sInstance; //Singleton for the state stack
};
