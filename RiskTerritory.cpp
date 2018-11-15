#include "RiskTerritory.h"

RiskTerritory::RiskTerritory(const SDL_Color &color, const std::string &name, std::pair<int, int> unit_position) :
color_(color),
//id_(id),
name_(name),
num_units_(0),
owner_(nullptr),
unit_position_(unit_position)
{ }

void RiskTerritory::addUnits(Uint16 num_units)
{
    num_units_ += num_units;
}

void RiskTerritory::changeOwnership(RiskPlayer const& new_owner, Uint16 num_units)
{
    owner_ = const_cast<RiskPlayer*>(&new_owner);
    num_units_ = num_units;
}

bool RiskTerritory::isRGBColor(const SDL_Color &color) const
{
    return color_.r == color.r
        && color_.g == color.g
        && color_.b == color.b;
}

bool RiskTerritory::isOwned() const
{
    return owner_ != nullptr;
}

const SDL_Color &RiskTerritory::getColor() const
{
    return color_;
}

const std::string &RiskTerritory::getName() const
{
    return name_;
}

Uint16 RiskTerritory::getNumUnits() const
{
    return num_units_;
}

const RiskPlayer *RiskTerritory::getOwner() const
{
    return owner_;
}

const std::pair<Uint32, Uint32> &RiskTerritory::getUnitPosition() const
{
    return unit_position_;
}

void RiskTerritory::removeUnits(int delta)
{
    assert(delta <= 0 && num_units_ >= delta);
    num_units_ -= delta;
}
