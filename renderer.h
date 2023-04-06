#pragma once
#include <string>
#include "asset_loader.h"
#include <SDL.h>

class RenderEngine
{
    AssetLoader _assets;
    SDL_Window * _window = nullptr;
    SDL_Renderer * _renderer = nullptr;

public:
    bool Initialize();
    SDL_Renderer * GetRenderer();
    static RenderEngine & Get();
    static bool Draw( const std::string & image, const SDL_Rect & target );
};
