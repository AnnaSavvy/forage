#pragma once
#include <string>
#include "asset_loader.h"
#include "point.h"
#include "ui_style.h"

struct SDL_Window;
struct SDL_Renderer;

class RenderEngine
{
    AssetLoader _assets;
    SDL_Window * _window = nullptr;
    SDL_Renderer * _renderer = nullptr;

public:
    bool Initialize();
    SDL_Renderer * GetRenderer();
    static RenderEngine & Get();
    static bool Draw( const std::string & image, const Rect & target );
    static bool DrawRect( const Rect & target, ColorPtr color );
    static bool DrawText( const std::string & text, const Rect & target );
};
