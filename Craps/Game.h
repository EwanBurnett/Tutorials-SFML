#pragma once
#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include<SFML/Graphics.hpp>

enum State {
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

private:
    int mClientWidth = 600;
    int mClientHeight = 400;
    
    sf::RenderWindow mWindow;
    sf::VideoMode mVideoMode;
    
    std::vector<sf::Drawable>mDrawqueue;
};