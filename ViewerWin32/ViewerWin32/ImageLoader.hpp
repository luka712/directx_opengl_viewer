#pragma once

#include <string>

namespace Viewer
{
    struct ImageData
    {
        size_t bytePerPixel;
        unsigned char* Data;
        unsigned int Width;
        unsigned int Height;

        ~ImageData();
    };

    class ImageLoader final
    {
    public:
        static ImageData* Load(std::string path);
    };

}