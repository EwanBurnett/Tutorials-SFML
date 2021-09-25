#pragma once
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include<SFML/Graphics.hpp>

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

    int mClientWidth = 600;
    int mClientHeight = 400;

    sf::RenderWindow mWindow;
    sf::VideoMode mVideoMode;

    std::vector<sf::Drawable>mDrawqueue;

private:
    int mScore_p1;
    int mScore_p2;
};
