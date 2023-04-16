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
    FontPtr font = nullptr;
    ColorPtr textColor = nullptr;
    ColorPtr backgroundColor = nullptr;
    int padding;
    int borderWidth;
    int borderRadius;
};

namespace StandardStyles
{
    bool loadAssets();
    FontPtr getFont( StandardFont font );
    ColorPtr getColor( StandardColor color );
}
