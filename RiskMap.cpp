#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>

#include <SDL2_image/SDL_image.h>

#include "RiskMap.h"

const SDL_Color RiskMap::OCEAN_COLOR = {255, 255, 255}; // white

RiskMap::RiskMap(const char *map_img_path, const char *map_data_path, const char *adjacencies_data_path) :
territories_()
{
    initTerritories(map_data_path);

    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        throw std::runtime_error("SDL_INIT_VIDEO failed!");
    }

    IMG_Init(0);

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
    SDL_RenderPresent(renderer_);
}

std::set<RiskTerritory const*> const &RiskMap::getTerritoriesAdjacentTo(RiskTerritory const *t) const
{
    return territory_adjacencies_.at(t);
}

RiskTerritory const *RiskMap::getTerritoryByCoordinates(int x, int y) const
{
    auto *pixels = (Uint32 *) image_surface_->pixels;
    Uint32 pixel = pixels[(y * image_surface_->w) + x];
    Uint8 r, g, b;

    SDL_GetRGB(pixel, image_surface_->format, &r, &g, &b);

    SDL_Color rgb = {r, g, b, 255};

    for (const auto &t : territories_)
    {
        auto *territory = t.second;
        if (territory->isRGBColor(rgb))
            return territory;
    }

    return nullptr;
}

RiskTerritory const *RiskMap::getTerritoryByID(int id) const
{
    // TODO: Catch out of range exception if it happens
    return territories_.at(id);
}

void RiskMap::initAdjacencies(const char *adjacencies_data_path)
{
    std::cout << "Initializing adjacencies" << std::endl;
    std::fstream csv_stream;
    csv_stream.open(adjacencies_data_path, std::fstream::in);

    int src_id;
    std::string s;
    std::getline(csv_stream, s); // ignore first line which just contains comments

    while (csv_stream >> src_id)
    {
        csv_stream.ignore();

        std::cout << "Source: " << src_id << std::endl;

        std::set<RiskTerritory const*> *src_territory_dests = &territory_adjacencies_[getTerritoryByID(src_id)];

        int temp_dest;

        while (csv_stream >> temp_dest)
        {
            std::cout << temp_dest << std::endl;
            src_territory_dests->insert(getTerritoryByID(temp_dest));

            csv_stream.ignore(1);
            if (csv_stream.peek() == '\n')
            {
                break;
            }
        }

        std::cout << "Added " << src_territory_dests->size() << " territories as adjacent to src (ID) " << src_id << std::endl;

    }

    csv_stream.close();
}

void RiskMap::initMapImg(const char *map_img_path)
{
    image_surface_ = IMG_Load(map_img_path);

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
            throw std::runtime_error(std::string("Renderer or window could not be created! SDL Error: ") + SDL_GetError());
        }
        else
        {
            image_texture_ = SDL_CreateTextureFromSurface(renderer_, image_surface_);
            SDL_LockSurface(image_surface_);
        }
    }

}

void RiskMap::initTerritories(const char *map_data_path)
{
    std::fstream csv_stream;
    csv_stream.open(map_data_path, std::fstream::in);

    int id;
    int r, g, b;
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

        SDL_Color rgb = {(Uint8) r, (Uint8) g, (Uint8) b, 255};

        territories_.insert(std::pair<int, RiskTerritory*>(id, new RiskTerritory(rgb, name)));
    }

    csv_stream.close();
}