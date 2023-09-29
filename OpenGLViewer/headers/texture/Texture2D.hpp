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
            /**
             * @brief Create the texture filled with data. Initialize  
            */
            Texture2D(unsigned char* data, unsigned int width, unsigned int height, size_t bytePerPixel);

            /**
             * Initialize the texture.
            */
            void Initialize();

            void Bind();
            void Unbind();

    };
}

#endif 