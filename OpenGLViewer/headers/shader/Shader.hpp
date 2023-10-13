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
        Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath = "");
        ~Shader();

        virtual bool Initialize();
        void Use();

    protected:
        std::string m_vertexPath;
        std::string m_fragmentPath;
        std::string m_geometryPath;
        unsigned int m_programId;

        /**
         * @brief Create a shader from a file.
         * @param path The path to the shader file.
         * @param type The type of the shader.
        */
        unsigned int CreateShader(std::string path, unsigned int type);

        /**
         * @brief Get the location of a uniform variable.
         * @param name The name of the uniform variable.
        */
        int GetUniformLocation(const char* name);

    };
}
#endif