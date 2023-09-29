#ifndef IMAGE_LOADER_HPP

#define IMAGE_LOADER_HPP

#include <string>

namespace Viewer
{
    struct ImageData 
    {
        size_t bytePerPixel;
        unsigned char* data;
        unsigned int width;
        unsigned int height;

        ~ImageData();
    };

    class ImageLoader final
    {
    public:
        static ImageData* LoadImage(std::string path);
    };
}

#endif