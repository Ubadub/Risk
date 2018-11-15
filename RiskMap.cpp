#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>

#include <SDL2_image/SDL_image.h>

#include "RiskMap.h"

const SDL_Color RiskMap::OCEAN_COLOR = {255, 255, 255}; // white

const char* RiskMap::FONT_LOCATION = "resources/fonts/ostrich-sans/ostrich-regular.ttf";

RiskMap::RiskMap(const char &map_img_path, const char &map_data_path, const char &adjacencies_data_path) :
territories_()
{
    initTerritories(map_data_path);

    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        throw std::runtime_error("SDL_INIT_VIDEO failed!");
    }

    IMG_Init(0);

    if (TTF_Init() != 0)
        std::cout << "TTF failed to initialize! Error: " << TTF_GetError() << std::endl;

    font_ = TTF_OpenFont(FONT_LOCATION, 24);

    if(font_ == nullptr)
    {
        std::cout << "Failed to load game over font! SDL_ttf Error: " << TTF_GetError() << std::endl; }

    initMapImg(map_img_path);
    initAdjacencies(adjacencies_data_path);

    std::cout << "Map initialized with " << territories_.size() << " territories" << std::endl;
}

RiskMap::~RiskMap()
{
    SDL_FreeSurface(image_surface_);
    SDL_DestroyTexture(image_texture_);
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);

    SDL_Quit();
}

void RiskMap::draw() const
{
    SDL_Rect msg_rect = {0, 0, image_surface_->w, image_surface_->h};
    SDL_RenderCopy(renderer_, image_texture_, nullptr, &msg_rect);

    for (auto it = territories_.cbegin(); it != territories_.cend(); it++)
    {
        RiskTerritory *territory = it->second;

        if (territory->isOwned())
        {
            int w, h;
            std::pair<int, int> coords = territory->getUnitPosition();
            const char *num_units = std::to_string(territory->getNumUnits()).c_str();
            auto texture = SDL_CreateTextureFromSurface(renderer_,
                                                        TTF_RenderText_Blended(font_, num_units, {0, 0, 0, 255}));

            SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
            SDL_Rect unit_rect = {coords.first - w / 2, coords.second - h / 2, w, h};
            SDL_Color owner_color = territory->getOwner()->getDisplayColor();
            SDL_SetRenderDrawColor(renderer_, owner_color.r, owner_color.g, owner_color.b, owner_color.a);
            SDL_RenderFillRect(renderer_, &unit_rect);
            SDL_RenderCopy(renderer_, texture, nullptr, &unit_rect);
        }
    }

    SDL_RenderPresent(renderer_);
}

const std::set<RiskTerritory const*>& RiskMap::getTerritoriesAdjacentTo(RiskTerritory const *t) const
{
    return territory_adjacencies_.at(t);
}

RiskTerritory const *RiskMap::getTerritoryByCoordinates(int x, int y) const
{
    auto *pixels = (Uint32 *) image_surface_->pixels;
    auto pixel = pixels[(y * image_surface_->w) + x];
    auto format = image_surface_->format;
    Uint8 r = (pixel & format->Rmask) >> format->Rshift;
    Uint8 g = (pixel & format->Gmask) >> format->Gshift;
    Uint8 b = (pixel & format->Bmask) >> format->Bshift;

    SDL_Color rgb = {r, g, b, 255};

    for (const auto &t : territories_)
    {
        auto *territory = t.second;
        if (territory->isRGBColor(rgb))
            return territory;
    }

    // no valid RiskTerritory found at the given coordinates, so return nullptr
    return nullptr;
}

RiskTerritory const *RiskMap::getTerritoryByID(int id) const
{
    // TODO: Catch out of range exception if it happens
    return territories_.at(id);
}

void RiskMap::initAdjacencies(const char &adjacencies_data_path)
{
    std::fstream csv_stream;
    csv_stream.open(&adjacencies_data_path, std::fstream::in);

    int src_id;
    std::string s;
    std::getline(csv_stream, s); // ignore first line which just contains comments

    while (csv_stream >> src_id)
    {
        csv_stream.ignore();

        int temp_dest;
        std::set<RiskTerritory const*> *src_territory_dests = &territory_adjacencies_[getTerritoryByID(src_id)];

        while (csv_stream >> temp_dest)
        {
            src_territory_dests->insert(getTerritoryByID(temp_dest));

            csv_stream.ignore(1);
            if (csv_stream.peek() == '\n')
            {
                break;
            }
        }
    }

    csv_stream.close();
}

void RiskMap::initMapImg(const char &map_img_path)
{
    image_surface_ = IMG_Load(&map_img_path);

    if (!image_surface_)
    {
        throw std::runtime_error(std::string("Image Load failed! IMG Error: ") + IMG_GetError());
    }
    else
    {
        renderer_ = nullptr;
        window_ = nullptr;
        SDL_CreateWindowAndRenderer(image_surface_->w, image_surface_->h, 0, &window_, &renderer_);
        if(renderer_ == nullptr || window_ == nullptr)
        {
            throw std::runtime_error(
                    std::string("Renderer or window could not be created! SDL Error: ") + SDL_GetError());
        }
        else
        {
            image_texture_ = SDL_CreateTextureFromSurface(renderer_, image_surface_);
            SDL_LockSurface(image_surface_);
        }
    }

}

void RiskMap::initTerritories(const char &map_data_path)
{
    std::fstream csv_stream;
    csv_stream.open(&map_data_path, std::fstream::in);

    int id;
    int r, g, b, x, y;
    std::string name;
    std::getline(csv_stream, name); // ignore first line which just contains comments

    while (csv_stream >> id)
    {
        csv_stream.ignore();
        std::getline(csv_stream, name, ',');

        csv_stream >> r;
        csv_stream.ignore();

        csv_stream >> g;
        csv_stream.ignore();

        csv_stream >> b;
        csv_stream.ignore();

        csv_stream >> x;
        csv_stream.ignore();

        csv_stream >> y;
        csv_stream.ignore();

        SDL_Color rgb = {(Uint8) r, (Uint8) g, (Uint8) b, 255};

        territories_.insert(std::pair<int, RiskTerritory*>(id, new RiskTerritory(rgb, name, std::pair<int, int>(x, y))));
    }

    csv_stream.close();
}