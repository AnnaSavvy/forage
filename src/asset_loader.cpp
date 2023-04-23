#include "asset_loader.h"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

AssetLoader::~AssetLoader()
{
    clear();
}

void AssetLoader::initRenderer( SDL_Renderer * renderer )
{
    if ( renderer != _renderer ) {
        clear();
        _renderer = renderer;
    }
}

SDL_Texture * AssetLoader::loadTexture( const std::string & filePath )
{
    // Check if the texture has already been loaded
    auto it = _textureMap.find( filePath );
    if ( it != _textureMap.end() ) {
        // Texture has already been loaded
        return it->second;
    }

    if ( !_renderer ) {
        return nullptr;
    }

    // Load the texture from file
    SDL_Surface * surface = IMG_Load( filePath.c_str() );
    if ( !surface ) {
        std::cerr << "Failed to load texture from file: " << filePath << "\n";
        return nullptr;
    }

    // Convert the surface to a texture
    SDL_Texture * texture = SDL_CreateTextureFromSurface( _renderer, surface );
    SDL_FreeSurface( surface );
    if ( !texture ) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << "\n";
        return nullptr;
    }

    // Add the texture to the texture map
    _textureMap.emplace( filePath, texture );

    return texture;
}

void AssetLoader::freeTexture( const std::string & filePath )
{
    // Check if the texture has already been loaded
    auto it = _textureMap.find( filePath );
    if ( it == _textureMap.end() ) {
        // Texture not found
        return;
    }

    // Free the texture
    SDL_DestroyTexture( it->second );
    _textureMap.erase( it );
}

void AssetLoader::clear()
{
    // Free all textures and clear the map
    for ( auto & pair : _textureMap ) {
        SDL_DestroyTexture( pair.second );
    }
    _textureMap.clear();
}
