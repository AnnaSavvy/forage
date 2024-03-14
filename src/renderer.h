#pragma once
#include <string>
#include "asset_loader.h"
#include "point.h"
#include "ui_style.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

enum class AnchorPoint
{
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    CENTER_LEFT,
    CENTER,
    CENTER_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT,
};

class RenderEngine
{
    AssetLoader _assets;
    SDL_Window * _window = nullptr;
    SDL_Renderer * _renderer = nullptr;
    Point _logicalSize = { 1024, 1024 };

public:
    bool Initialize( Point logicalSize, double scaling );
    SDL_Renderer * GetRenderer();
    static Point GetScreenSize();
    static Point GetAnchorPoint( AnchorPoint anchor );
    static RenderEngine & Get();

    static bool Draw( const std::string & image, const Rect & target, bool flipped = false );
    static bool DrawRect( const Rect & target, StandardColor color );
    static bool DrawStyledRect( const Rect & target, const Style & style );

    static int DrawText( const std::string & text, const Point & target );
    static int DrawText( const std::string & text, const Point & target, StandardFont font );
    static int DrawText( const std::string & text, const Point & target, StandardFont font, StandardColor color );
    static SDL_Surface * GetTextSurface( const std::string & text, StandardFont font, StandardColor color );
    static bool DrawDestroySurface( SDL_Surface * surface, const Rect & target );
    static bool DrawPieSlice( const Rect & target, double startAngle, double size, StandardColor color );

    static int GetTextWidth( const std::string & text, StandardFont font = StandardFont::REGULAR );
};
