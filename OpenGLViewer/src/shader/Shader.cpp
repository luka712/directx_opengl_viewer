#include "shader/shader.hpp"
#include "loaders/FileLoader.hpp"
#include <iostream>
#include <SDL.h>

namespace Viewer
{
    Shader::Shader(std::string vertexPath, std::string fragmentPath)
        : m_vertexPath(vertexPath), m_fragmentPath(fragmentPath)
    {
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_ID);
    }

    bool Shader::Initialize()
    {
        FileLoader fileLoader;
        std::string vertexCode = fileLoader.LoadFile(m_vertexPath);
        std::string fragmentCode = fileLoader.LoadFile(m_fragmentPath);

        if (vertexCode == "")
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OpenGL error", "Failed to load vertex shader.", nullptr);
            return false;
        }
        else if (fragmentCode == "")
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OpenGL error", "Failed to load fragment shader.", nullptr);
            return false;
        }

        unsigned int vertexShader = CreateShader(vertexCode, GL_VERTEX_SHADER);
        unsigned int fragmentShader = CreateShader(fragmentCode, GL_FRAGMENT_SHADER);

        if (vertexShader == 0)
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OpenGL error", "Failed to create vertex shader.", nullptr);
            return false;
        }

        if (fragmentShader == 0)
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OpenGL error", "Failed to create fragment shader.", nullptr);
            return false;
        }

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertexShader);
        glAttachShader(m_ID, fragmentShader);
        glLinkProgram(m_ID);

        int success;
        char infoLog[512];
        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
            std::string error = "Failed to link shader program: " + std::string(infoLog);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OpenGL error", error.c_str(), nullptr);
            return false;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return true;
    }

    void Shader::Use()
    {
        glUseProgram(m_ID);
    }

    unsigned int Shader::CreateShader(std::string filePath, unsigned int type)
    {
        unsigned int shader = glCreateShader(type);
        const char *shaderCode = filePath.c_str();
        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);

        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::string error = "Failed to compile shader: " + std::string(infoLog);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OpenGL error", error.c_str(), nullptr);
        }

        return shader;
    }
}
