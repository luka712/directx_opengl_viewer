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

        void Begin();
        void End();
    private:
        SDL_Window &m_window;
        SDL_GLContext m_glContext;
        glm::vec4 m_clearColor = glm::vec4(1.0, 0.71, 0.76, 1.0f);
    };
}

#endif