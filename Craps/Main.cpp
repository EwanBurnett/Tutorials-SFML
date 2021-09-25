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
        }

        mWindow.clear();

        //Update


        //Draw
        for (int i = 0; i < mDrawqueue.size(); i++) {
            mWindow.draw(mDrawqueue.at(i));
        }
    }
}