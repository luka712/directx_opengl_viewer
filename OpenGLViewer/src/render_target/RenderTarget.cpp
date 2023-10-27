#include "render_target/RenderTarget.hpp"
#include <exception>

namespace Viewer
{
    RenderTarget::RenderTarget(Renderer& renderer, unsigned int width, unsigned int height)
        : m_renderer(renderer), m_width(width), m_height(height)
    {
    }

    void RenderTarget::Initialize()
    {
        // create render buffer
        glGenFramebuffers(1, &m_frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

        // create texture
        m_texture = new Texture2D(nullptr, m_width, m_height, 3);
        m_texture->Initialize();
        m_texture->Bind();

        // attach texture to framebuffer
        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D,
            m_texture->GetHandle(),
            0);

        // create render buffer
        glGenRenderbuffers(1, &m_renderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);

        // allocate render buffer memory
        glRenderbufferStorage(
            GL_RENDERBUFFER,
            GL_DEPTH24_STENCIL8,
            m_width,
            m_height);

        // attach render buffer to framebuffer
        glFramebufferRenderbuffer(
            GL_FRAMEBUFFER,
            GL_DEPTH_STENCIL_ATTACHMENT,
            GL_RENDERBUFFER,
            m_renderBuffer);

        // check framebuffer status
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            throw std::exception("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
        }

        // unbind framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // unbind render buffer
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        // unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void RenderTarget::Use()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
        glViewport(0, 0, m_width, m_height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 0, 0, 1);
    }

    void RenderTarget::Stop()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, m_renderer.GetWidth(), m_renderer.GetHeight());
    }
}