#ifndef CAMERA_HPP

#define CAMERA_HPP

#include <glm/glm.hpp>
#include <buffer/UniformBuffer.hpp>
#include <input/MouseState.hpp>

namespace Viewer
{
    struct CameraData 
    {
        glm::mat4x4 ProjectionViewMatrix;
        glm::vec3 EyePosition;
    };

    class Camera
    {
    protected:
        glm::vec3 m_eyePosition;
        glm::vec3 m_lookAtPosition;
        glm::vec3 m_upVector;

        glm::mat4x4 m_projectionMatrix;
        glm::mat4x4 m_viewMatrix;
        glm::mat4x4 m_projectionViewMatrix;

        UniformBuffer<CameraData> m_cameraBuffer;

        // @brief This camera buffer does not contain translation, only scale/rotation
        UniformBuffer<glm::mat4x4> m_skyboxCameraBuffer;

    public:

        Camera(float aspectRatio);

        virtual void Initialize();

        // @brief Gets the eye position of the camera.    
        inline glm::vec3 GetEyePosition() const { return m_eyePosition; }

        // @brief Gets the look at position of the camera.
        inline glm::vec3 GetLookAtPosition() const { return m_lookAtPosition; }

        // @brief Gets the up vector of the camera.
        inline glm::vec3 GetUpVector() const { return m_upVector; }

        // @brief Gets the projection view matrix of the camera.
        inline glm::mat4x4 GetProjectionViewMatrix() const { return m_projectionViewMatrix; }

        // @brief Gets the camera buffer.
        inline UniformBuffer<CameraData> &GetCameraBuffer() { return m_cameraBuffer; }

        inline UniformBuffer<glm::mat4x4> &GetSkyboxCameraBuffer() { return m_skyboxCameraBuffer; }

        // @brief Updates the camera.
        virtual void Update(MouseState& event);
    };
}

#endif