#include "Game.h"

int main() {
    Game game;

    //Prevent the program from terminating immediately
    std::cin.get();
}

Game::Game() {
    mVideoMode.width = mClientWidth;
    mVideoMode.height = mClientHeight;

    mWindow.create(mVideoMode, "SFML Craps");
    mWindow.setFramerateLimit(60);
    mWindow.setVerticalSyncEnabled(false);

    Play();
}

void Game::Play()
{
    while (mWindow.isOpen()) {
        //Event Polling
        sf::Event event;
        while (mWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mWindow.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                mDice1.Roll();
                std::cout << mDice1.GetFace() << std::endl;
            }
        }

        mWindow.clear();

        //Update
        //Update();

        //Draw
        for (size_t i = 0; i < mDrawqueue.size(); i++) {
            mWindow.draw(mDrawqueue.at(i));
        }
    }
}

void Game::Update()
{
    switch (mState){
    case(State::START_SCREEN):
        //Display start screen
        std::cout << "Start Screen state entered" << std::endl;
        break;

    case(State::WIN_SCREEN):
        //Display win screen
        std::cout << "Win Screen state entered" << std::endl;
        break;

    case(State::LOSE_SCREEN):
        //Display lose screen
        std::cout << "Lose Screen state entered" << std::endl;
        break;

    case(State::PLAYER_TURN):
        //Process player's dice roll
        std::cout << "Player Turn state entered" << std::endl;
        break;

    case(State::CPU_TURN):
        //Process computer's dice roll
        std::cout << "CPU Turn state entered" << std::endl;
        break;

    case(State::SCORE_CALC):
        //Display scores
        std::cout << "Score Calculation state entered" << std::endl;
        break;
    }
}

void Game::SetState(State s)
{
    mState = s;
    return;
}


void RNG::Seed()
{
    srand(static_cast<unsigned>(time(0)));
}

int RNG::GetRand(int max) const
{
    return(rand() % max) + 1;
}



void Dice::Roll()
{
    RNG rng;
    mFace = rng.GetRand(mSides);
}

int Dice::GetFace() const
{
    return mFace;
}
