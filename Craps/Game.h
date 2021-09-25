#pragma once
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include<SFML/Graphics.hpp>

//A Simple Random Number Generator class. Seeded by Time. 
class RNG {
public:
    //Seed our RNG to the system's current time.
    void Seed();

    //Returns a random number in range [1..max]
    int GetRand(int max) const;
};

class Dice {
public:
    void Roll();
    int GetFace() const;

private:
    int mFace = 0;  //The dice's current face value [1 - faces]
    int mSides = 6; //How many faces the dice has. by default is a standard 6-sided die.
};


enum class State {
    START_SCREEN = 0,
    PLAYER_TURN,
    CPU_TURN,
    SCORE_CALC,
    WIN_SCREEN,
    LOSE_SCREEN
};

class Game {
    

public:
    Game();
    ~Game() = default;

    void Play();
    void Update();

    void SetState(State s);

private:
    State mState;
    Dice mDice1;
    Dice mDice2;
    

    int mClientWidth = 600;
    int mClientHeight = 400;

    sf::RenderWindow mWindow;
    sf::VideoMode mVideoMode;

    std::vector<sf::Drawable>mDrawqueue;

private:
    int mScore_p1;
    int mScore_p2;
};
