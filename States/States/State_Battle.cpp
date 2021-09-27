#include "State_Battle.h"

void State_Battle::OnStateEntered()
{
	Entity* p1 = new Entity();
	Entity* p2 = new Entity();
	Entity* e1 = new Entity();
}

void State_Battle::OnStateExit()
{
	//Clean up entities before we exit
	for (Entity e : mEntityQueue) {
		delete(&e);
	}

	mActionQueue.clear();
	mEntityQueue.clear();
}
