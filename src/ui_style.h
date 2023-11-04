#pragma once

using FontPtr = void *;
using ColorPtr = void *;

enum class StandardFont : int
{
    INVALID = 0,
    REGULAR,
    REGULAR_BOLD,
    MENU_HUGE_TITLE,
    END,
};

enum class StandardColor : int
{
    WHITE = 0,
    BLACK,
    DARK_GREY,
    DARK_RED,
    DARK_BLUE,
    HIGHLIGHT_RED,
    REALM_LIFE,
    REALM_ARCANE,
    REALM_NATURE,
    REALM_CHAOS,
    REALM_DEATH,
    REALM_POWER,
    REALM_DEFENSE,
    REALM_SPEED,
    REALM_PRECISION,
    END,
};

struct Style
{
    StandardFont font = StandardFont::REGULAR;
    StandardColor textColor = StandardColor::WHITE;
    StandardColor backgroundColor = StandardColor::BLACK;
    StandardColor borderColor = StandardColor::BLACK;
    int paddingX = 0;
    int paddingY = 0;
    int borderWidth = 0;
    int borderRadius = 0;
};

namespace StandardStyles
{
    bool loadAssets();
    FontPtr getFont( StandardFont font );
    ColorPtr getColor( StandardColor color );
}
