#include "StateStack.h"
#include <iostream>

StateStack* StateStack::sInstance = nullptr;
std::vector<State*> StateStack::m_Stack;
std::unordered_map<std::string, State*> StateStack::m_States;
State* StateStack::m_CurrentState;

//Constructor initializes the states.
StateStack::StateStack()
{
	//Singleton management
	assert(sInstance == nullptr);
	sInstance = this;

	//Sets defaults
	m_CurrentState = nullptr;
	Push(new State_Empty); // <-- Assigns a new empty default state.
	
	//Pop();
}

StateStack::~StateStack()
{
}


void StateStack::InitState(std::string stateName, State* state)
{
	m_States.try_emplace(stateName, state);
}

void StateStack::InitStates(std::unordered_map<std::string, State*> l_States)
{
	if(l_States.size() > 0)
	{
		for (auto& j : l_States) {
			m_States.try_emplace(j.first, j.second);
		}
	}
}


void StateStack::Update(sf::Time deltaTime)
{
	if(m_Stack.size() > 0)
		m_CurrentState = m_Stack.back();
	m_CurrentState->Update(deltaTime);
}

void StateStack::Render(sf::RenderWindow& window)
{
	m_CurrentState->Render(window);
}

void StateStack::EventHandler(sf::Event& event)
{
	m_CurrentState->EventHandler(event);
}

void StateStack::Pop()
{
	if(m_Stack.size() > 1){
		m_CurrentState->OnStateExit();// <-- Calls OnStateExit() for the current state

		m_Stack.pop_back(); //<-- Pops the top state from the stack

		m_CurrentState = m_Stack.back(); // <-- Sets the current state to the top of the stack
		m_CurrentState->OnStateEntered();
	}
	
	else {
		std::cout << "uh oh" << std::endl;
	}
}

void StateStack::Push(State* state)
{
	//assert(ValidateState(state));
	assert(state); 

	if(m_CurrentState != nullptr)
		m_CurrentState->OnStateExit();

	m_Stack.push_back(state); //Adds the state to the stack. 

	m_CurrentState = m_Stack.back(); // <-- Sets the current state to the top of the stack

	m_CurrentState->OnStateEntered(); // <-- Calls OnStateEntered() for the current state
}

void StateStack::Push(std::string stateName)
{
	assert(stateName != "");
	assert(m_States.find(stateName) != m_States.end());
	State* cache = m_States.at(stateName);
	Push(cache);
}

void StateStack::Clear()
{
	//Free memory back up
	m_States.clear();
	m_Stack.clear();
}

/*
bool StateStack::ValidateState(State* state)
{
	std::cout << m_States.size();
	if(m_States.size() > 0){
		//return(std::find(m_States.begin(), m_States.end(), state) != m_States.end()); // <-- Ensures the state exists in the states list.
		for (int i = 0; i < m_States.size(); ++i) {
			m_States.
		}
	}

	else {
		m_States.emplace(new State_Empty); //Adds a new empty state if the states list is empty
		return false;
	}
}
*/

