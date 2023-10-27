#ifndef RENDERER_HPP

#define RENDERER_HPP

#include <SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Viewer
{
    class Renderer final
    {
    public:
        Renderer(SDL_Window &window);
        ~Renderer();

        bool Initialize(unsigned int width, unsigned int height);

        unsigned int GetWidth() { return m_width;  }
        unsigned int GetHeight() { return m_height; }

        SDL_GLContext& GetGLContext() { return m_glContext; }

        void Begin();
        void End();
    private:
        unsigned int m_width;
        unsigned int m_height;
         
        SDL_Window &m_window;
        SDL_GLContext m_glContext;
        glm::vec4 m_clearColor = glm::vec4(1.0, 0.71, 0.76, 1.0f);
    };
}

#endif