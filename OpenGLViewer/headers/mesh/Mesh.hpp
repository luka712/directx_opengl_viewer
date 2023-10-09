#ifndef MESH_HPP

#define MESH_HPP

#include "buffer/GeometryBuffer.hpp"
#include "geometry/Geometry.hpp"
#include "camera/Camera.hpp"
#include "scene/SceneLights.hpp"
#include "transform/Transform.hpp"
#include "material/StandardMaterial.hpp"

namespace Viewer
{
    class Mesh
    {
    private:
        Geometry &m_geometry;
        GeometryBuffer m_geometryBuffer;

    public:
        Mesh(Geometry &geometry);

        Transform Transform;
        StandardMaterial Material;

        void Initialize();
        void Update();
        void Draw(Camera &camera, SceneLights &lights);
    };
}

#endif