#ifndef REFLECTIVE_MESH_HPP

#define REFLECTIVE_MESH_HPP

#include "buffer/PosNormalGeometryBuffer.hpp"
#include "geometry/Geometry.hpp"
#include "camera/Camera.hpp"
#include "scene/SceneLights.hpp"
#include "transform/Transform.hpp"
#include "material/ReflectiveMaterial.hpp"

namespace Viewer
{
    class ReflectiveMesh
    {
    private:
        Geometry &m_geometry;
        PosNormalGeometryBuffer m_geometryBuffer;

    public:
        ReflectiveMesh(Geometry &geometry);

        Transform Transform;
        ReflectiveMaterial Material;

        void Initialize();
        void Update();
        void Draw(Camera &camera);
    };
}

#endif