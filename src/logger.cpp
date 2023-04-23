#include "logger.h"
#include <iostream>

void printLine( const std::string & content )
{
    std::cout << content << std::endl;
}

void printIntroduction()
{
    printLine( "===============================================" );
    printLine( "=         WORLD OF FORAGE AND HUNTING         =" );
    printLine( "===============================================" );
    printLine( "=               ADVENTURE AWAITS!             =" );
    printLine( "===============================================" );
}

void printMainMenu()
{
    printLine( "" );
    printLine( "1. New Game" );
    printLine( "2. Load Game" );
    printLine( "3. Highscores" );
    printLine( "4. Quit" );
    printLine( "" );
    std::cout << "Select an option: ";
}
