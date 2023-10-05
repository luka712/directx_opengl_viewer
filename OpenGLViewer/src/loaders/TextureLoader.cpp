#include "loaders/TextureLoader.hpp"
#include "loaders/ImageLoader.hpp"

namespace Viewer
{
    Texture2D *TextureLoader::LoadFromImg(std::string imgFilePath)
    {
        ImageLoader imageLoader;
        ImageData *imageData = imageLoader.LoadImage(imgFilePath);
        Texture2D *texture = new Texture2D(*imageData);
        texture->Initialize();

        delete imageData;
        
        return texture;
    }
}