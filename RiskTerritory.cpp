#include "RiskTerritory.h"

RiskTerritory::RiskTerritory(const SDL_Color &color, int id, const std::string &name) :
color_(color),
id_(id),
name_(name)
{ }

bool RiskTerritory::isRGBColor(const SDL_Color &color) const
{
    return color_.r == color.r
        && color_.g == color.g
        && color_.b == color.b;
}

const SDL_Color &RiskTerritory::getColor() const
{
    return color_;
}

const std::string &RiskTerritory::getName() const
{
    return name_;
}
