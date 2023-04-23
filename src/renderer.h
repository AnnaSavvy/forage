#pragma once
#include <string>
#include "asset_loader.h"
#include "point.h"
#include "ui_style.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

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
    static bool DrawRect( const Rect & target, StandardColor color );
    static bool DrawStyledRect( const Rect & target, const Style & style );

    static bool DrawText( const std::string & text, const Point & target );
    static bool DrawText( const std::string & text, const Point & target, StandardFont font );
    static bool DrawText( const std::string & text, const Point & target, StandardFont font, StandardColor color );
    static SDL_Surface * GetTextSurface( const std::string & text, StandardFont font, StandardColor color );
    static bool DrawDestroySurface( SDL_Surface * surface, const Rect & target );
};
