/**
 * Main game class.
 *
 * Created by Abhinav Patil on 11/11/2018. All Rights Reserved.
 */

#ifndef RISK_RISKGAME_H
#define RISK_RISKGAME_H

#include <string>

#include <SDL2/SDL.h>
#include "RiskPlayer.h"
#include "RiskTerritory.h"
#include "RiskMap.h"

class RiskGame
{
public:
    RiskGame();
    ~RiskGame();
    void loop();

private:
    static const char *MAP_IMG_PATH;
    static const char *MAP_DATA_PATH;
    static const int numPlayers_ = 4;

    RiskMap *const map_;
    RiskPlayer *players;

    void draw();

    bool getUserInput();
};


#endif //RISK_RISKGAME_H
