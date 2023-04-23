#pragma once

#include <string>
#include <unordered_map>

struct SDL_Texture;
struct SDL_Renderer;

class AssetLoader
{
public:
    AssetLoader(){};
    ~AssetLoader();
    void initRenderer( SDL_Renderer * renderer );
    SDL_Texture * loadTexture( const std::string & filePath );
    void freeTexture( const std::string & filePath );
    void clear();

private:
    std::unordered_map<std::string, SDL_Texture *> _textureMap;
    SDL_Renderer * _renderer = nullptr;
};
