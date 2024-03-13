#include "input.h"
#include "ui_rpg.h"

namespace
{
    const Style skillBarStyle{ StandardFont::SMALL, StandardColor::WHITE, StandardColor::DARK_GREY, StandardColor::REALM_PRECISION, 2 };
}

SkillCounter::SkillCounter( Point position, int width, std::string description, ValueBinding binding )
    : UIContainer( { position._x, position._y, 0, 0 } )
    , _binding( binding )
{
    addElement( std::make_shared<Label>( Label( position, description ) ) );
    position.modAdd( 150, 0 );

    addElement( std::make_shared<ProgressBar>( ProgressBar( { position._x, position._y, width, 31 }, binding, skillBarStyle ) ) );

    const Style buttonStyle{ StandardFont::REGULAR, StandardColor::WHITE, StandardColor::DARK_GREY, StandardColor::REALM_PRECISION, 2 };

    addElement( std::make_shared<Button>( Button( { position._x + width + 5, position._y, 31, 31 }, "+", buttonStyle ) ) );
    addElement( std::make_shared<Button>( Button( { position._x - 36, position._y, 31, 31 }, "-", buttonStyle ) ) );

    updateRect();
}

void SkillCounter::handleClickEvent( const Point & click, int modes )
{
    const ValueBinding & binding = _binding.get();
    if ( _items[2]->getRect().contains( click ) ) {
        const int change = modes & InputHandler::MOUSE_RIGHT_CLICKED ? 10 : 1;
        binding.value = std::min( binding.value + change, binding.maximum );
    }
    else if ( _items[3]->getRect().contains( click ) ) {
        const int change = modes & InputHandler::MOUSE_RIGHT_CLICKED ? 10 : 1;
        binding.value = std::min( binding.value - change, binding.maximum );
    }
}
