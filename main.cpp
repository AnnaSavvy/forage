#include "logger.h"
#include "resource.h"
#include "unit_villager.h"
#include "village.h"
#include "wave_function.h"
#include "tournament.h"
#include <SDL.h>
#include <SDL_image.h>

#include <chrono>
#include <iostream>
#include <thread>

#define TILESIZE 64
#define MAPSIZE 16

int main(int argc, char* argv[]) {
    SDL_Init( SDL_INIT_EVERYTHING );
    SDL_Window * window = SDL_CreateWindow( "forage", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 1024, SDL_WINDOW_SHOWN );
    SDL_Renderer * renderer = SDL_CreateRenderer( window, -1, 0 );

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );

    SDL_RenderClear(renderer);

    SDL_Rect target;

    target.x = 0;
    target.y = 0;
    target.h = TILESIZE;
    target.w = TILESIZE;

    WaveMap ourMap( MAPSIZE );
    ourMap.updateMap();


    SDL_Surface * tmpSurface = IMG_Load( "assets/water.png" );
    SDL_Texture * water = SDL_CreateTextureFromSurface( renderer, tmpSurface );
    SDL_FreeSurface( tmpSurface );
    tmpSurface = IMG_Load( "assets/plains.png" );
    SDL_Texture * plains = SDL_CreateTextureFromSurface( renderer, tmpSurface );
    SDL_FreeSurface( tmpSurface );
    tmpSurface = IMG_Load( "assets/forest.png" );
    SDL_Texture * forest = SDL_CreateTextureFromSurface( renderer, tmpSurface );
    SDL_FreeSurface( tmpSurface );
    tmpSurface = IMG_Load( "assets/mountain.png" );
    SDL_Texture * mountain = SDL_CreateTextureFromSurface( renderer, tmpSurface );
    SDL_FreeSurface( tmpSurface );
    tmpSurface = IMG_Load( "assets/swamp.png" );
    SDL_Texture * swamp = SDL_CreateTextureFromSurface( renderer, tmpSurface );
    SDL_FreeSurface( tmpSurface );

    for ( int y = 0; y < MAPSIZE; y++ ) {
        for ( int x = 0; x < MAPSIZE; x++ ) {
            const int offset = ( x % 2 ) ? TILESIZE / 2 : 0;

            target.x = x * TILESIZE;
            target.y = y * TILESIZE + offset;

            auto & tile = ourMap.getTile( y * MAPSIZE + x );
            SDL_Texture * texture = water;
            switch ( tile.type ) {
            case FOREST:
                texture = mountain;
                break;
            case TREES:
                texture = forest;
                break;
            case GRASS:
                texture = plains;
                break;
            case SAND:
                texture = swamp;
                break;
            case LAKE:
                texture = water;
                break;
            default:
                texture = water;
                break;
            }
            SDL_RenderCopy( renderer, texture, NULL, &target );
        }
    }



    SDL_RenderPresent( renderer );

    while ( true ) {
        SDL_Delay( 3000 );
    }

    return 0;
}
    /*
namespace
{
    SDL_Renderer * renderer;
    SDL_Window * window;
}

void delay( uint32_t milliseconds )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( milliseconds ) );
}
//
//int main( int argc, char * args[] )
//{
//    runTournament();
//
//    // The window we'll be rendering to
//    SDL_Window * window = NULL;
//
//    // The surface contained by the window
//    SDL_Surface * screenSurface = NULL;
//
//    // Initialize SDL
//    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
//        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
//    }
//    else {
//        // Create window
//        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
//            1280, 720, SDL_WINDOW_SHOWN );
//        if ( window == NULL ) {
//            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
//        }
//        else {
//            // Get window surface
//            screenSurface = SDL_GetWindowSurface( window );
//
//            // Fill the surface white
//            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
//
//            // Update the surface
//            SDL_UpdateWindowSurface( window );
//
//            // Wait two seconds
//            SDL_Delay( 2000 );
//        }
//    }
//    // Destroy window
//    SDL_DestroyWindow( window );
//
//    // Quit SDL subsystems
//    SDL_Quit();
//
//    return 0;
//}

void gameLoop()
{
    bool gameIsRunning = true;

    printLine( "Generating the world." );
    Village mainVillage;

    while ( gameIsRunning ) {
        printLine( "" );
        mainVillage.printStatus();
        printLine( "" );
        mainVillage.update();

        delay( 2500 );
    }
}

int main()
{
    printIntroduction();

    bool menuIsRunning = true;

    while ( menuIsRunning ) {
        printMainMenu();

        int selection;
        std::cin >> selection;

        switch ( selection ) {
        case 1: {
            printLine( "Starting a new game, please wait..." );
            gameLoop();
        } break;
        case 2:
            printLine( "No saved games found, please start a new one!" );
            break;
        case 3: {
            WaveMap ourMap( 8 );
            ourMap.updateMap();

            WaveRenderer rnder;
            rnder.renderMap( ourMap );
        }
            // printLine( "No one beaten our game yet!" );
            break;
        case 4:
            menuIsRunning = false;
            break;
        default:
            break;
        }
    }
    return 0;
}
*/