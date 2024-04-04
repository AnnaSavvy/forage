#pragma once
#include "binding.h"
#include "character.h"
#include "input.h"
#include "ui_base.h"

namespace UIC
{
    constexpr int HEIGHT = 31;
}

class ProgressBar : public UIComponent
{
    Style _style;

public:
    ValueComponent _binding;

    ProgressBar( const Rect & dimensions, ValueBinding binding );
    ProgressBar( const Rect & dimensions, ValueBinding binding, const Style & style );

    void setStyle( const Style & style );
    virtual void update( float deltaTime ) override {}
    virtual void render() override;
};

template <typename Lambda>
class SkillCounter : public UIContainer
{
    Lambda _callback;
    CharacterAttributes::Enum _skill;

public:
    SkillCounter( Point position, int width, CharacterAttributes::Enum skill, ValueBinding binding, Lambda & callback )
        : UIContainer( { position.x, position.y, 0, 0 } )
        , _callback( callback )
        , _skill( skill )
    {
        addElement( std::make_shared<CenteringLabel>( CenteringLabel( { position.x, position.y, 0, 31 }, RPG::Character::GetSkillName( skill ) ) ) );
        position.modAdd( 150, 0 );

        const Style buttonStyle{ StandardFont::REGULAR, StandardColor::WHITE, StandardColor::DARK_GREY, StandardColor::REALM_PRECISION, 2 };
        addElement( std::make_shared<Button>( Button( { position.x - UIC::HEIGHT - 5, position.y, UIC::HEIGHT, UIC::HEIGHT }, "-", buttonStyle ) ) );

        addElement(
            std::make_shared<ProgressBar>( ProgressBar( { position.x, position.y, width, 31 }, binding,
                                                        { StandardFont::SMALL, StandardColor::WHITE, StandardColor::DARK_GREY, StandardColor::REALM_PRECISION, 2 } ) ) );

        addElement( std::make_shared<Button>( Button( { position.x + width + 5, position.y, 31, 31 }, "+", buttonStyle ) ) );
    }

    int handleEvent( const Point & click, int event ) override
    {
        if ( _items[1]->getRect().contains( click ) ) {
            const int change = event & InputHandler::MOUSE_RIGHT_CLICKED ? -10 : -1;
            _callback( _skill, change );
            return UIComponent::BASIC_EVENT;
        }
        else if ( _items[3]->getRect().contains( click ) ) {
            const int change = event & InputHandler::MOUSE_RIGHT_CLICKED ? 10 : 1;
            _callback( _skill, change );
            return UIComponent::BASIC_EVENT;
        }
        return UIComponent::NO_EVENT;
    }
};

template <typename Lambda>
class AttributeCounter : public UIContainer
{
    CenteringLabel * _display;
    Lambda _callback;
    CharacterAttributes::Enum _attribute;

public:
    ValueComponent _binding;

    AttributeCounter( Point position, CharacterAttributes::Enum attribute, ValueBinding binding, Lambda & callback )
        : UIContainer( { position.x, position.y, 0, 0 } )
        , _binding( binding )
        , _callback( callback )
        , _attribute( attribute )
    {
        addElement( std::make_shared<CenteringLabel>( CenteringLabel( { position.x, position.y, 90, UIC::HEIGHT }, RPG::Character::GetSkillName( _attribute ) ) ) );
        position.modAdd( 90, 0 );

        const Style buttonStyle{ StandardFont::REGULAR, StandardColor::WHITE, StandardColor::DARK_GREY, StandardColor::REALM_PRECISION, 2 };
        addElement( std::make_shared<Button>( Button( { position.x, position.y, UIC::HEIGHT, UIC::HEIGHT }, "-", buttonStyle ) ) );

        position.modAdd( 35, 0 );
        addElement( std::make_shared<CenteringLabel>( CenteringLabel( { position.x, position.y, 60, UIC::HEIGHT }, std::to_string( binding.value ) ) ) );
        _display = dynamic_cast<CenteringLabel *>( _items.back().get() );

        position.modAdd( 60, 0 );
        addElement( std::make_shared<Button>( Button( { position.x, position.y, UIC::HEIGHT, UIC::HEIGHT }, "+", buttonStyle ) ) );
    }

    int handleEvent( const Point & click, int event ) override
    {
        if ( _items[1]->getRect().contains( click ) ) {
            const int change = event & InputHandler::MOUSE_RIGHT_CLICKED ? -10 : -1;
            _callback( _attribute, change );
            return UIComponent::BASIC_EVENT;
        }
        else if ( _items[3]->getRect().contains( click ) ) {
            const int change = event & InputHandler::MOUSE_RIGHT_CLICKED ? 10 : 1;
            _callback( _attribute, change );
            return UIComponent::BASIC_EVENT;
        }
        return UIComponent::NO_EVENT;
    }

    virtual void render() override
    {
        _display->setText( std::to_string( _binding.get().value ) );
        for ( auto & component : _items ) {
            component.get()->render();
        }
    }
};
