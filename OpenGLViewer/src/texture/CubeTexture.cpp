#include "texture/CubeTexture.hpp"
#include <glad/glad.h>

namespace Viewer
{
    CubeTexture::CubeTexture(ImageData &imgDataRight,
                             ImageData &imgDataLeft,
                             ImageData &imgDataTop,
                             ImageData &imgDataBottom,
                             ImageData &imgDataBack,
                             ImageData &imgDataFront)
        : m_imgDataRight(imgDataRight),
          m_imgDataLeft(imgDataLeft),
          m_imgDataTop(imgDataTop),
          m_imgDataBottom(imgDataBottom),
          m_imgDataBack(imgDataBack),
          m_imgDataFront(imgDataFront)
    {
    }

    void CubeTexture::Initialize()
    {
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, m_imgDataRight.width, m_imgDataRight.height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imgDataRight.data);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, m_imgDataLeft.width, m_imgDataLeft.height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imgDataLeft.data);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, m_imgDataTop.width, m_imgDataTop.height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imgDataTop.data);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, m_imgDataBottom.width, m_imgDataBottom.height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imgDataBottom.data);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, m_imgDataBack.width, m_imgDataBack.height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imgDataBack.data);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, m_imgDataFront.width, m_imgDataFront.height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_imgDataFront.data);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void CubeTexture::Bind()
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
    }

    void CubeTexture::Unbind()
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
}