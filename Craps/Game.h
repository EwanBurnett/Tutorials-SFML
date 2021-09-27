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
    Dice();
    void Roll();
    int GetFace() const;

private:
    RNG rng;
    int mFace = 0;  //The dice's current face value [1 - faces]
    int mSides = 6; //How many faces the dice has. by default is a standard 6-sided die.
};


enum class State {
    START_SCREEN = 0,
    PLAYER_ROLL_1,
    PLAYER_ROLL_2,
    SCORE_CALC,
    WIN_SCREEN,
    LOSE_SCREEN
};

class Game {
    

public:
    Game();
    ~Game() = default;

    void Play();
    void Roll();
    void Update(float dt);

    void Win();
    void Lose();

    void SetState(State s);
    //Adds a sprite to the draw queue. 
    void AddSprite(std::string path, sf::Vector2f pos);
    void AddText(std::string Text, sf::Vector2f pos, int size);
    void DrawUI(float dt);

private:
    State mState;
    Dice mDice1;
    Dice mDice2;
    

    int mClientWidth = 750;
    int mClientHeight = 500;

    sf::RenderWindow mWindow;
    sf::VideoMode mVideoMode;

    std::vector<sf::Sprite>mDrawqueue;

private:
    int mWins;
    int mLosses;

    int mSum;
    int mPoint = 0;
    int mRolls;
};
