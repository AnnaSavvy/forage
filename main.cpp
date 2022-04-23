#include "logger.h"
#include "resource.h"
#include "unit_villager.h"
#include "village.h"
#include "wave_function.h"

#include <chrono>
#include <iostream>
#include <thread>

void delay( uint32_t milliseconds )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( milliseconds ) );
}

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
    WaveRenderer render;
    WaveMap waveMap( 5 );
    render.renderMap( waveMap );

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
            printLine( "No one beaten our game yet!" );
            waveMap.waveIterate();
            render.renderMap( waveMap );
        } break;
        case 4:
            menuIsRunning = false;
            break;
        default:
            break;
        }
    }
    return 0;
}