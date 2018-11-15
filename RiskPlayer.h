#ifndef RISK_RISKPLAYER_H
#define RISK_RISKPLAYER_H


#include <SDL2/SDL_pixels.h>

class RiskPlayer
{
public:
    RiskPlayer();
    ~RiskPlayer();

    const SDL_Color &getDisplayColor() const;
private:
    RiskPlayer(const RiskPlayer&);

    SDL_Color display_color_;
};


#endif //RISK_RISKPLAYER_H
