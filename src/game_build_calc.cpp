#include "game_build_calc.h"
#include "input.h"
#include "renderer.h"
#include "rpg_generation.h"

namespace
{
    class SkillCounter : public UIContainer
    {

    public:
        SkillCounter( Point position, int width, std::string label )
            : UIContainer()
        {
            Style skillBarStyle;
            skillBarStyle.font = StandardFont::SMALL;
            skillBarStyle.textColor = StandardColor::WHITE;
            skillBarStyle.backgroundColor = StandardColor::DARK_GREY;
            skillBarStyle.borderColor = StandardColor::REALM_PRECISION;
            skillBarStyle.borderWidth = 2;
            skillBarStyle.borderRadius = 5;

            _items.push_back( std::make_shared<ProgressBar>( ProgressBar( { position._x, position._y, width, 31 }, 100, skillBarStyle ) ) );

            Style buttonStyle;
            buttonStyle.font = StandardFont::REGULAR;
            buttonStyle.textColor = StandardColor::WHITE;
            buttonStyle.backgroundColor = StandardColor::DARK_GREY;
            buttonStyle.borderColor = StandardColor::REALM_PRECISION;
            buttonStyle.borderWidth = 2;

            _items.push_back( std::make_shared<Button>( Button( { position._x + width + 5, position._y, 31, 31 }, "+", buttonStyle ) ) );
            _items.push_back( std::make_shared<Button>( Button( { position._x - 36, position._y, 31, 31 }, "-", buttonStyle ) ) );
            _items.push_back( std::make_shared<Label>( Label( position, label ) ) );

            updateRect();
        }

        void handleClickEvent(const Point& click) override {
            if ( _items[1]->getRect().contains( click ) ) {
                if ( ProgressBar * bar = dynamic_cast<ProgressBar *>( _items[0].get() ); bar != nullptr ) {
                    bar->setValue( bar->getValue() + 1 );
                }
            }
            else if ( _items[2]->getRect().contains( click ) ) {
                if ( ProgressBar * bar = dynamic_cast<ProgressBar *>( _items[0].get() ); bar != nullptr ) {
                    bar->setValue( bar->getValue() - 1 );
                }
            }
        }
    };
}

ModeBuildCalculator::ModeBuildCalculator()
    : _title( { 50, 10 }, "Character Builer" )
    , _bExit( 400, 800, 270, 80, "Return" )
    , _charName( { RenderEngine::GetScreenSize()._x / 2, 80 }, "Unknown" )
    , _bGenerateName( RenderEngine::GetScreenSize()._x / 2, 130, 100, 50, "Generate" )
{
    name = GameModeName::BUILD_CALCULATOR;

    Point p( 300, 500 );
    skills.push_back( std::make_shared<SkillCounter>( p, 200, "" ) );
    skills.push_back( std::make_shared<SkillCounter>( p.modAdd( 0, 40 ), 200, "" ) );
    skills.push_back( std::make_shared<SkillCounter>( p.modAdd( 0, 40 ), 200, "" ) );
    skills.push_back( std::make_shared<SkillCounter>( p.modAdd( 0, 40 ), 200, "" ) );
    skills.push_back( std::make_shared<SkillCounter>( p.modAdd( 0, 40 ), 200, "" ) );
    skills.push_back( std::make_shared<SkillCounter>( p.modAdd( 0, 40 ), 200, "" ) );
}

GameModeName ModeBuildCalculator::handleEvents()
{
    InputHandler & input = InputHandler::Get();

    if ( input.handleEvent() ) {
        if ( input.isSet( InputHandler::MOUSE_CLICKED ) ) {
            const Point & mouseClick = input.getClickPosition();
            if ( _bExit.getRect().contains( mouseClick ) ) {
                return GameModeName::CANCEL;
            }
            else if ( _bGenerateName.getRect().contains( mouseClick ) ) {
                _charName.setText( RPG::Generator::GetCharacterName() );
            }
            else if ( skills[0]->getRect().contains( mouseClick ) ) {
                skills[0]->handleClickEvent( mouseClick );
            }
        }
        // else if ( input.isSet( InputHandler::UP ) ) {
        //     skills[0].setValue( skills[0].getValue() + 1 );
        // }
        // else if ( input.isSet( InputHandler::DOWN ) ) {
        //     if ( skills[0].getValue() > 0 ) {
        //         skills[0].setValue( skills[0].getValue() - 1 );
        //     }
        // }
        return name;
    }
    return GameModeName::QUIT_GAME;
}

void ModeBuildCalculator::update( float deltaTime ) {}

void ModeBuildCalculator::render()
{
    _title.render();
    _bExit.render();

    RenderEngine::Draw( "assets/portaits/03087.png", { 10, 10, 256, 384 } );

    _charName.render();
    _bGenerateName.render();

    for ( auto & elem : skills ) {
        elem->render();
    }
}
