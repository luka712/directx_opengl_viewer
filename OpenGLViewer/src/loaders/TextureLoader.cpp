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

    CubeTexture *TextureLoader::LoadFromImg(std::string rightImgFilePath,
                             std::string leftImgFilePath,
                             std::string topImgFilePath,
                             std::string bottomImgFilePath,
                             std::string backImgFilePath,
                             std::string frontImgFilePath)
    {
        ImageLoader imageLoader;

        ImageData *rightImgData = imageLoader.LoadImage(rightImgFilePath);
        ImageData *leftImgData = imageLoader.LoadImage(leftImgFilePath);
        ImageData *topImgData = imageLoader.LoadImage(topImgFilePath);
        ImageData *bottomImgData = imageLoader.LoadImage(bottomImgFilePath);
        ImageData *backImgData = imageLoader.LoadImage(backImgFilePath);
        ImageData *frontImgData = imageLoader.LoadImage(frontImgFilePath);

        CubeTexture *texture = new CubeTexture(*rightImgData,
                                               *leftImgData,
                                               *topImgData,
                                               *bottomImgData,
                                               *backImgData,
                                               *frontImgData);
        texture->Initialize();

        delete rightImgData;
        delete leftImgData;
        delete topImgData;
        delete bottomImgData;
        delete backImgData;
        delete frontImgData;

        return texture;
    }
}