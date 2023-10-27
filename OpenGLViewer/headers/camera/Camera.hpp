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
        glm::vec3 m_upVector;

        glm::mat4x4 m_projectionMatrix;
        glm::mat4x4 m_projectionViewMatrix;

        UniformBuffer<CameraData> m_cameraBuffer;

        /// @brief This camera buffer does not contain translation, only scale/rotation
        UniformBuffer<glm::mat4x4> m_skyboxCameraBuffer;

        /// @brief The projection camera buffer.
        UniformBuffer<glm::mat4x4> m_projectionBuffer;

    public:

        Camera(float aspectRatio);

        /// @brief The eye position of the camera.
        glm::vec3 EyePosition;

        /// @brief The look at position of the camera.
        glm::vec3 LootAtPosition;

        /// @brief The view matrix of the camera.
        glm::mat4x4 ViewMatrix;

        virtual void Initialize();

        // @brief Gets the eye position of the camera.    
        inline glm::vec3 GetEyePosition() const { return EyePosition; }

        // @brief Gets the look at position of the camera.
        inline glm::vec3 GetLookAtPosition() const { return LootAtPosition; }

        // @brief Gets the up vector of the camera.
        inline glm::vec3 GetUpVector() const { return m_upVector; }

        // @brief Gets the projection view matrix of the camera.
        inline glm::mat4x4 GetProjectionViewMatrix() const { return m_projectionViewMatrix; }

        // @brief Gets the camera buffer.
        inline UniformBuffer<CameraData> &GetCameraBuffer() { return m_cameraBuffer; }

        inline UniformBuffer<glm::mat4x4> &GetSkyboxCameraBuffer() { return m_skyboxCameraBuffer; }

        /// @brief Gets the projection camera buffer.
        inline UniformBuffer<glm::mat4x4> &GetProjectionBuffer() { return m_projectionBuffer; }

        // @brief Updates the camera.
        virtual void Update(MouseState& event);
    };
}

#endif
