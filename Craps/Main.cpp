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
    
    //DrawUI();

    Play();
}

void Game::Play()
{
    sf::Time deltaTime;
    sf::Clock clock;

    while (mWindow.isOpen()) {
        //Calculate Timing
        sf::Time elapsedTime = clock.restart();
        deltaTime = elapsedTime;
        float dtAsMs = deltaTime.asSeconds();

        //Event Polling
        sf::Event event;
        while (mWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mWindow.close();
            }

            else if (event.type == sf::Event::KeyPressed) {
                Roll();
            }
                
        }

        //Clear
        mDrawqueue.clear();
        mWindow.clear();

        //Update
        Update(dtAsMs);

        //Draw
        mWindow.display(); 
    }
}

void Game::Roll()
{
    mDice1.Roll();
    mDice2.Roll();
    mRolls++;

    mSum = (mDice1.GetFace() + mDice2.GetFace());

    //First Turn
    if (mPoint <= 0) {
        std::cout << "Start: Aiming for either a 7 or 12" << std::endl;
        if ((mSum == 7) || (mSum == 12)) {
            Win();
        }

        else if ((mSum == 2) || (mSum == 3) || (mSum == 12) ){
            Lose();
        } 

        else {
            std::cout << "Player aiming for: " << mSum << std::endl;
            mPoint = mSum;
        }
    }

    //Rerolls
    else {
        if ((mSum == 2) || (mSum == 3) || (mSum == 12)) {
            Lose();
        }
        else if (mSum == mPoint) {
            Win();
        }
    }

    std::cout << "Turn " << mRolls << " - Player rolled a " << mDice1.GetFace() << " / " << mDice2.GetFace() << ": Sum = " << mSum << std::endl;
}


void Game::Update(float dt)
{
    DrawUI(dt);

    switch (mState){
    case(State::START_SCREEN):
        //Display start screen
        //std::cout << "Start Screen state entered" << std::endl;
        
        //Await First Roll before switching state
        if (mRolls > 0) {
            SetState(State::PLAYER_ROLL_1);
        }
        
        break;

    case(State::WIN_SCREEN):
        //Display win screen
        static float animTime;
        animTime += dt;
        if (animTime <= 1.5f) {  //After 1.5s, stop display
            AddSprite("Resources/UI/UI_WinBanner.png", sf::Vector2f(0, 170));
            AddText("You Win!", sf::Vector2f(220, 210), 72);
        }
        else {
            animTime = 0;
            SetState(State::PLAYER_ROLL_1);
        }
        break;

    case(State::LOSE_SCREEN):
        //Display lose screen
        //std::cout << "Lose Screen state entered" << std::endl;
        break;

    case(State::PLAYER_ROLL_1):
        //Process player's dice roll
        //std::cout << "Player Turn state entered" << std::endl;
        
        break;

    case(State::PLAYER_ROLL_2):
        //Process computer's dice roll
        //std::cout << "CPU Turn state entered" << std::endl;
        break;

    case(State::SCORE_CALC):
        //Display scores
        //std::cout << "Score Calculation state entered" << std::endl;
        break;
    }
}

void Game::Win()
{
    std::cout << "Win" << std::endl;
    mWins++;
    mPoint = 0;
    SetState(State::WIN_SCREEN);
}

void Game::Lose()
{
    std::cout << "Loss" << std::endl;
    mLosses++;
    mPoint = 0;
    SetState(State::LOSE_SCREEN);
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

void Game::DrawUI(float dt)
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
    AddText("Wins", sf::Vector2f(585, 12), 24);
    AddText(lWins, sf::Vector2f(600, 30), 40);
    AddText(" - ", sf::Vector2f(638, 30), 40);
    AddText("Losses", sf::Vector2f(660, 12), 24);
    AddText(lLosses, sf::Vector2f(680, 30), 40);

    //Point Display
    if (mPoint == 0) {
        //First Turn, so display 7 or 12
        AddText("7 or 12", sf::Vector2f(594, 93), 40);
    }
    else {
        //Rerolling, so set equal to the player's point
        AddText("Aim For: ", sf::Vector2f(582, 103), 30);
        std::string lPoint = std::to_string(mPoint);
        AddText(lPoint, sf::Vector2f(700, 100), 34);
    }

    //Buttons
    AddText("Roll!", sf::Vector2f(325, 390), 40);
    AddText("Reset", sf::Vector2f(515, 450), 24);
    AddText("Exit", sf::Vector2f(650, 450), 24);

    //Dice Display
    std::string lDice1 = std::to_string(mDice1.GetFace());
    AddText(lDice1, sf::Vector2f(210, 135), 40);
    AddText("/", sf::Vector2f(240, 135), 40);
    std::string lDice2 = std::to_string(mDice2.GetFace());
    AddText(lDice2, sf::Vector2f(270, 135), 40);

    //Dice Sum Display
    std::string lSum = std::to_string(mSum);
    AddText(lSum, sf::Vector2f(492, 309), 40);

    //Rules
    AddText("Craps Rules: Aim for your Point - the number(s) on the \nright.\nRoll until you hit the Point to win!\nIf you roll a 2, 3 or a 12, you lose.", sf::Vector2f(210, 10), 14);
}

#pragma endregion

#pragma region RNG

void RNG::Seed()
{
    //std::cout << "Seeded to " << time(0) << std::endl;
    srand((unsigned int)time(0));
}

int RNG::GetRand(int max) const
{
    return(rand() % max) + 1;
}
#pragma endregion

#pragma region Dice


Dice::Dice()
{
    rng.Seed();
}

void Dice::Roll()
{
    mFace = rng.GetRand(mSides);
}

int Dice::GetFace() const
{
    return mFace;
}

#pragma endregion
