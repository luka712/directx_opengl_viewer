#ifndef SHADER_HPP

#define SHADER_HPP

#include <string>
#include <glad/glad.h>
#include "texture/Texture2D.hpp"

namespace Viewer
{
    class Shader
    {
    public:
        Shader(std::string vertexPath, std::string);
        ~Shader();

        virtual bool Initialize();
        void Use();

    protected:
        std::string m_vertexPath;
        std::string m_fragmentPath;
        unsigned int m_programId;

        unsigned int CreateShader(std::string path, unsigned int type);

    };
}
#endif