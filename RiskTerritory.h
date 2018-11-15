#ifndef RISK_RISKTERRITORY_H
#define RISK_RISKTERRITORY_H

#include <string>
#include <utility>

#include <SDL2/SDL.h>
#include "RiskPlayer.h"

class RiskTerritory
{
public:
    RiskTerritory(const SDL_Color &color, const std::string &name, std::pair<int, int> unit_position);

    void addUnits(Uint16);

    void changeOwnership(const RiskPlayer &new_owner, Uint16 num_new_units);

    bool isRGBColor(const SDL_Color&) const;

    bool isOwned() const;

    const SDL_Color &getColor() const;

    const std::string &getName() const;

    Uint16 getNumUnits() const;

    const RiskPlayer *getOwner() const;

    const std::pair<Uint32, Uint32> &getUnitPosition() const;

    void removeUnits(int);

private:
    RiskTerritory(const RiskTerritory&);

    const SDL_Color color_;
    std::string name_;
    Uint16 num_units_;
    RiskPlayer *owner_;
    std::pair<Uint32, Uint32> unit_position_;

    void doCombat(RiskTerritory &attacker);
};


#endif //RISK_RISKTERRITORY_H
