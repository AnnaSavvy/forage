#pragma once

using FontPtr = void *;
using ColorPtr = void *;

enum class StandardFont : int
{
    INVALID = 0,
    REGULAR,
    REGULAR_BOLD,
    END,
};

enum class StandardColor : int
{
    WHITE = 0,
    BLACK,
    DARK_RED,
    DARK_BLUE,
    HIGHLIGHT_RED,
    END,
};

struct Style
{
    StandardFont font = StandardFont::REGULAR;
    StandardColor textColor = StandardColor::WHITE;
    StandardColor backgroundColor = StandardColor::BLACK;
    int padding = 0;
    int borderWidth = 0;
    int borderRadius = 0;
};

namespace StandardStyles
{
    bool loadAssets();
    FontPtr getFont( StandardFont font );
    ColorPtr getColor( StandardColor color );
}
