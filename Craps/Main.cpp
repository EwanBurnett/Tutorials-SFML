#include "Game.h"

int main() {
    Game game;

    //Prevent the program from terminating immediately
    //std::cin.get();
}

#pragma region Game

Game::Game() {
    mVideoMode.width = mClientWidth;
    mVideoMode.height = mClientHeight;

    mWindow.create(mVideoMode, "SFML Craps");
    mWindow.setFramerateLimit(60);
    mWindow.setVerticalSyncEnabled(false);

    DrawUI();

    Play();
}

void Game::Play()
{
    sf::Texture TEST;
    TEST.loadFromFile("Resources/UI/UI_Background.png");
    sf::Sprite s;
    s.setTexture(TEST);
    s.setPosition(sf::Vector2f(0, 0));

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
                mDice2.Roll();
            }
        }

        mDrawqueue.clear();
        mWindow.clear();

        //Update
        //Update();

        DrawUI();
        //Draw
        /*for (size_t i = 0; i < mDrawqueue.size(); i++) {
            mWindow.draw(mDrawqueue.at(i));
        }*/
       /* std::vector<sf::Sprite>::iterator it;
        for (it = mDrawqueue.begin(); it != mDrawqueue.end(); ++it) {
            mWindow.draw(*it);
        }*/
       /* for (auto spr : mDrawqueue) {
            mWindow.draw(spr);
        }*/

        mWindow.display();
        
       
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

void Game::AddSprite(std::string path, sf::Vector2f pos)
{
    sf::Texture texCache;
    texCache.loadFromFile(path);
    sf::Sprite sprCache;
    sprCache.setTexture(texCache);
    sprCache.setPosition(pos);
    mDrawqueue.push_back(sprCache);
    mWindow.draw(sprCache); //<-- Debug: Fix Stale References in Draw Queue Vector
}

void Game::AddText(std::string Text, sf::Vector2f pos, int size)
{
    sf::Font Lato;
    if (!Lato.loadFromFile("Resources/Fonts/Lato/Lato-Regular.ttf")){
        return;
    }

    sf::Text text;
    text.setFont(Lato);
    text.setCharacterSize(size);
    text.setStyle(sf::Text::Regular);

    text.setString(Text);
    text.setPosition(pos);
    mWindow.draw(text);
}

void Game::DrawUI()
{
    //Load Background
    AddSprite("Resources/UI/UI_Background.png", sf::Vector2f(0, 0));

    //Load UI Elements
    AddSprite("Resources/UI/UI_LogWindow.png", sf::Vector2f(8, 8));
    AddSprite("Resources/UI/UI_RulesWindow.png", sf::Vector2f(200, 8));
    AddSprite("Resources/UI/UI_Win-Loss.png", sf::Vector2f(570, 8));
    AddSprite("Resources/UI/UI_PointDisplay.png", sf::Vector2f(570, 93));
    AddSprite("Resources/UI/UI_PlayerView.png", sf::Vector2f(570, 157));
    AddSprite("Resources/UI/UI_DiceView.png", sf::Vector2f(200, 135));
    AddSprite("Resources/UI/UI_RollButton.png", sf::Vector2f(250, 382));
    AddSprite("Resources/UI/UI_ResetButton.png", sf::Vector2f(495, 450));
    AddSprite("Resources/UI/UI_ExitButton.png", sf::Vector2f(630, 450));
    
    //Load Text Elements

    //Win/Loss Display
    std::string lWins = std::to_string(mWins);
    std::string lLosses = std::to_string(mLosses);
    AddText("Wins", sf::Vector2f(590, 12), 24);
    AddText(lWins, sf::Vector2f(600, 30), 40);
    AddText(" - ", sf::Vector2f(650, 30), 40);
    AddText("Losses", sf::Vector2f(660, 12), 24);
    AddText(lLosses, sf::Vector2f(700, 30), 40);

    //Point Display
    if (mPoint == 0) {
        //First Turn, so display 7 or 12
        AddText("7 or 12", sf::Vector2f(590, 93), 40);
    }
    else {
        //Rerolling, so set equal to the player's point
        AddText("> ", sf::Vector2f(570, 103), 40);
        std::string lPoint = std::to_string(mPoint);
        AddText(lPoint, sf::Vector2f(600, 103), 40);
    }

    //Buttons
    AddText("Roll!", sf::Vector2f(250, 382), 40);
    AddText("Reset", sf::Vector2f(495, 450), 40);
    AddText("Exit", sf::Vector2f(630, 450), 40);

    //Dice Display
    std::string lDice1 = std::to_string(mDice1.GetFace());
    AddText(lDice1, sf::Vector2f(200, 135), 40);
    AddText("/", sf::Vector2f(230, 135), 40);
    std::string lDice2 = std::to_string(mDice2.GetFace());
    AddText(lDice2, sf::Vector2f(260, 135), 40);

    //Rules
    AddText("Craps Rules: Aim for your Point - the number(s) on the right.\nRoll until you hit the Point to win!\nIf you roll a 2, 3 or a 12, you lose.", sf::Vector2f(200, 8), 14);
}

#pragma endregion

#pragma region RNG

void RNG::Seed()
{
    srand(static_cast<unsigned>(time(0)));
}

int RNG::GetRand(int max) const
{
    return(rand() % max) + 1;
}
#pragma endregion

#pragma region Dice

void Dice::Roll()
{
    RNG rng;
    mFace = rng.GetRand(mSides);
}

int Dice::GetFace() const
{
    return mFace;
}

#pragma endregion
