#ifndef CUBE_TEXTURE_HPP

#define CUBE_TEXTURE_HPP

#include "loaders/ImageLoader.hpp"

namespace Viewer
{
    class CubeTexture
    {
    private:
        // gl texture id
        unsigned int m_textureID;

        ImageData &m_imgDataRight;
        ImageData &m_imgDataLeft;
        ImageData &m_imgDataTop;
        ImageData &m_imgDataBottom;
        ImageData &m_imgDataBack;
        ImageData &m_imgDataFront;

    public:
        /// @brief Create the texture filled with data.
        CubeTexture(ImageData &imgDataRight,
                    ImageData &imgDataLeft,
                    ImageData &imgDataTop,
                    ImageData &imgDataBottom,
                    ImageData &imgDataBack,
                    ImageData &imgDataFront);

        /// @brief Initialize the texture.
        void Initialize();

        void Bind();
        void Unbind();
    };
}

#endif