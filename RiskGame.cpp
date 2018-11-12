/**
 * Main game class.
 *
 * Created by Abhinav Patil on 11/11/2018. All Rights Reserved.
 */

#include <iostream>

#include <SDL2_image/SDL_image.h>
#include "RiskGame.h"

const char *RiskGame::MAP_DATA_PATH = "resources/map_data.csv";;
const char *RiskGame::MAP_IMG_PATH = "resources/game_map.bmp";;

RiskGame::RiskGame() :
map_(new RiskMap(MAP_IMG_PATH, MAP_DATA_PATH))
{ }

RiskGame::~RiskGame()
{
    delete map_;
}

void RiskGame::loop()
{
    do
    {
        draw();
    } while (getUserInput());
}

void RiskGame::draw()
{
    map_->draw();
}

bool RiskGame::getUserInput()
{
    SDL_Event e;

    if (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case SDL_KEYDOWN:
            {
                switch (e.key.keysym.sym)
                {

                }
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                RiskTerritory *territory = map_->getTerritoryByCoordinates(e.button.x, e.button.y);
                if (territory != nullptr)
                {
                    std::cout << territory->getName();
                }
                else
                {
                    std::cout << "NO SUCH TERRITORY!";
                }
                std::cout << std::endl;
                break;
            }
            case SDL_QUIT:
                return false;
        }
    }

    return true;
}
