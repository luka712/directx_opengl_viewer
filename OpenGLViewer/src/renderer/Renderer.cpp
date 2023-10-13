#include "renderer/Renderer.hpp"

namespace Viewer
{
    Renderer::Renderer(SDL_Window &window)
        : m_window(window)
    {
    }

    Renderer::~Renderer()
    {
        SDL_GL_DeleteContext(m_glContext);
    }

    bool Renderer::Initialize(unsigned int width, unsigned int height)
    {
        m_glContext = SDL_GL_CreateContext(&m_window);

        // Initialize Glad (after creating an OpenGL context)
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "OpenGL error", "Failed to initialize Glad.", nullptr);
            return false;
        }

        glViewport(0, 0, width, height);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        return true;
    }

    void Renderer::Begin()
    {
        glClearColor(
            m_clearColor.r,
			m_clearColor.g,
			m_clearColor.b,
			m_clearColor.a
        );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
      
    }

    void Renderer::End()
    {
        SDL_GL_SwapWindow(&m_window);
    }
}