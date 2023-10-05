#ifndef TEXTURE_LOADER_HPP

#define TEXTURE_LOADER_HPP

#include "texture/Texture2D.hpp"
#include <string>

namespace Viewer
{
    class TextureLoader
    {
    public:
        Texture2D *LoadFromImg(std::string imgFilePath);
    };
}

#endif