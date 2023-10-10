#ifndef UNLIT_MESH_HPP

#define UNLIT_MESH_HPP

#include "buffer/GeometryBuffer.hpp"
#include "geometry/Geometry.hpp"
#include "camera/Camera.hpp"
#include "scene/SceneLights.hpp"
#include "transform/Transform.hpp"
#include "material/UnlitMaterial.hpp"

namespace Viewer
{
    class UnlitMesh
    {
    private:
        Geometry &m_geometry;
        GeometryBuffer m_geometryBuffer;

    public:
        UnlitMesh(Geometry &geometry);

        Transform Transform;
        UnlitMaterial Material;

        void Initialize();
        void Update();
        void Draw(Camera &camera);
    };
}

#endif