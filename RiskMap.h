#ifndef RISK_RISKMAP_H
#define RISK_RISKMAP_H

#include <map>
#include <set>

#include <SDL2/SDL.h>
#include "RiskTerritory.h"

class RiskMap
{
public:
    static const SDL_Color OCEAN_COLOR;
    /**
     * Create the map using the given image and data file.
     *
     * @param map_image_path an image file where each territory has one unique color. OCEAN_COLOR is ignored (i.e.
     * reserve for the ocean)
     * @param map_data_path a comma-separated value file of the format "territory_id,name,r,g,b". Each territory must
     * have a unique integer id and unique RGB values. The RGB values should correspond to the map file.
     */
    RiskMap(const char *map_img_path, const char *map_data_path, const char *adjacencies_data_path);
    ~RiskMap();

    /**
     * Render the map to the screen.
     */
    void draw() const;

    std::set<RiskTerritory const*> const &getTerritoriesAdjacentTo(RiskTerritory const*) const;

    /**
     * Get a pointer to the RiskTerritory object which corresponds to the coordinates of the given coordinates.
     *
     * @param x the x coordinate
     * @param y the y coordinate
     * @return a pointer to the RiskTerritory object which corresponds to the coordinates of the given coordinates if
     * they are valid (e.g. within the bounds and not in the ocean), or null_ptr if they are invalid
     */
    RiskTerritory const *getTerritoryByCoordinates(int x, int y) const;

    RiskTerritory const *getTerritoryByID(int id) const;

private:
    // Map territory IDs to territories
    std::map<int, RiskTerritory *const> territories_;

    // Adjacency lists for territories on the map
    std::map<RiskTerritory const*, std::set<RiskTerritory const*>> territory_adjacencies_;

    SDL_Surface *image_surface_;
    SDL_Texture *image_texture_;
    SDL_Renderer *renderer_;
    SDL_Window *window_;

    RiskMap(const RiskMap&);

    void initAdjacencies(const char *adjacencies_data_path);
    void initMapImg(const char *map_img_path);
    void initTerritories(const char *map_data_path);
};


#endif //RISK_RISKMAP_H
