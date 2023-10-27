#ifndef RENDER_TARGET_HPP

#define RENDER_TARGET_HPP

#include <glad/glad.h>
#include "texture/Texture2D.hpp"
#include "renderer\Renderer.hpp"

namespace Viewer
{
    /// @brief The render target class.
    class RenderTarget
    {
    public:
        RenderTarget(Renderer& renderer, unsigned int width, unsigned int height);

        Texture2D& GetTexture() const { return *m_texture; }

        void Initialize();

        void Use();
        void Stop();

    private:
        Renderer& m_renderer;

        GLuint m_frameBuffer;
        GLuint m_renderBuffer;
        Texture2D* m_texture;

        unsigned int m_width;
        unsigned int m_height;
    };
}

#endif