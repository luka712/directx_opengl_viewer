#include "texture/Texture2D.hpp"
#include "glad/glad.h"

namespace Viewer
{
    Texture2D::Texture2D(unsigned char *data, unsigned int width, unsigned int height, size_t bytePerPixel)
        : m_data(data), m_width(width), m_height(height), m_bytePerPixel(bytePerPixel)
    {
        m_textureID = 0;
    }

    Texture2D::Texture2D(ImageData& imgData)
    {
        m_data = imgData.data;
		m_width = imgData.width;
		m_height = imgData.height;
		m_bytePerPixel = imgData.bytePerPixel;
		m_textureID = 0;
    }

    void Texture2D::Initialize()
    {
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        unsigned int format = GL_RGBA;
        if (m_bytePerPixel == 3)
        {
            format = GL_RGB;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data);

        // Filter and wrap settings.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // unbind texture.
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture2D::Bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_textureID);
    }

    void Texture2D::Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture2D* Texture2D::GetEmptyTexture()
    {
        static Texture2D* sm_emptyTexture = nullptr;
        if (sm_emptyTexture == nullptr)
        {
            unsigned char data[] = { 255, 255, 255, 255 };
            sm_emptyTexture = new Texture2D(data, 1, 1, 4);
            sm_emptyTexture->Initialize();
        }

        return sm_emptyTexture;
    }

}