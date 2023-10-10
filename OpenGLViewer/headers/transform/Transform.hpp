#ifndef TRANSFORM_HPP

#define TRANSFORM_HPP

#include "buffer/UniformBuffer.hpp"
#include <glm/glm.hpp>

namespace Viewer 
{
    class Transform
    {
        public:
            glm::vec3 Position;
            glm::vec3 Rotation;
            glm::vec3 Scale;

            Transform();

            /// @brief Initializes the transform.
            void Initialize();

            /// @brief Updates the transform.
            void Update();

            /// @brief Gets the transform buffer.
            /// @return The transform buffer.
            UniformBuffer<glm::mat4> &GetTransformBuffer() { return m_transformBuffer; }

        private:
            UniformBuffer<glm::mat4> m_transformBuffer;
    };
}

#endif 