#ifndef TEXTURE_HPP

#define TEXTURE_HPP

#include "loaders/ImageLoader.hpp"

namespace Viewer 
{
    class Texture2D 
    {
        private:
            // gl texture id
            unsigned int m_textureID;

            size_t m_bytePerPixel;
            unsigned char* m_data;
            unsigned int m_width;
            unsigned int m_height;
        public:

            /// @brief Create the texture filled with data. 
            Texture2D(unsigned char* data, unsigned int width, unsigned int height, size_t bytePerPixel);

            /// @brief Create the texture filled with data.   
            Texture2D(ImageData& imgData);

            /// @brief Initialize the texture.
            void Initialize();

            /// @brief Bind the texture.
            void Bind();

            /// @brief Unbind the texture.
            void Unbind();

            /// @brief Gets the texture handle.
            unsigned int GetHandle() const { return m_textureID; }

            /// @brief Gets the empty texture.
            static Texture2D* GetEmptyTexture();

    };
}

#endif 