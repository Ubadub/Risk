#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>

#include <SDL2_image/SDL_image.h>

#include "RiskMap.h"

const SDL_Color RiskMap::OCEAN_COLOR = {255, 255, 255}; // white

RiskMap::RiskMap(const char* map_img_path, const char* map_data_path):
territories_()
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

        territories_.push_back(new RiskTerritory(rgb, id, name));
    }

    csv_stream.close();


    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        throw std::runtime_error("SDL_INIT_VIDEO failed!");
    }

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
        SDL_SetWindowBordered(window_, SDL_TRUE);
        if(renderer_ == nullptr || window_ == nullptr)
        {
            throw std::runtime_error(std::string("Renderer or window could not be created! SDL Error: ") + SDL_GetError());
        }
        else
        {
            //Initialize PNG loading
            int imgFlags = IMG_INIT_JPG;
            if(!(IMG_Init(imgFlags) &imgFlags))
            {
                throw std::runtime_error(std::string("IMG_Init failed! IMG Error: ") + IMG_GetError());
            }

            image_texture_ = SDL_CreateTextureFromSurface(renderer_, image_surface_);
            SDL_LockSurface(image_surface_);
        }
    }

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

void RiskMap::draw()
{
    SDL_Rect msg_rect = {0, 0, image_surface_->w, image_surface_->h};
    SDL_RenderCopy(renderer_, image_texture_, nullptr, &msg_rect);
    SDL_RenderPresent(renderer_);
}

RiskTerritory* RiskMap::getTerritoryByCoordinates(int x, int y)
{
    Uint32 *pixels = (Uint32 *) image_surface_->pixels;
    Uint32 pixel = pixels[(y * image_surface_->w) + x];
    Uint8 r, g, b;

    SDL_GetRGB(pixel, image_surface_->format, &r, &g, &b);

    SDL_Color rgb = {r, g, b, 255};

    for (RiskTerritory *territory : territories_)
    {
        if (territory->isRGBColor(rgb))
            return territory;
    }

    std::cout << "(" << (int) r << ", " << (int) g << ", " << (int) b << ")" << std::endl;

    return nullptr;
}