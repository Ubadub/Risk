/**
 * Main entry point for Risk game.
 *
 * Created by Abhinav Patil on 11/11/2018. All Rights Reserved.
 */

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "RiskGame.h"

int main()
{
    RiskGame game;
    game.loop();

    return 0;
}