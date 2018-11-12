#ifndef RISK_RISKTERRITORY_H
#define RISK_RISKTERRITORY_H

#include <string>
#include <utility>

#include <SDL2/SDL.h>

class RiskTerritory
{
public:
    RiskTerritory(const SDL_Color &color, int id, const std::string &name);

    bool isRGBColor(const SDL_Color&) const;

    const SDL_Color &getColor() const;

    const std::string &getName() const;

private:
    const SDL_Color color_;
    int id_;
    std::string name_;
    std::pair<int, int> unit_position_;
};


#endif //RISK_RISKTERRITORY_H
