#ifndef TEXTURE_LOADER_HPP

#define TEXTURE_LOADER_HPP

#include "texture/Texture2D.hpp"
#include "texture/CubeTexture.hpp"
#include <string>

namespace Viewer
{
    class TextureLoader
    {
    public:
        Texture2D *LoadFromImg(std::string imgFilePath);

        CubeTexture* LoadFromImg(std::string rightImgFilePath,
                                 std::string leftImgFilePath,
                                 std::string topImgFilePath,
                                 std::string bottomImgFilePath,
                                 std::string backImgFilePath,
                                 std::string frontImgFilePath);
    };
}

#endif