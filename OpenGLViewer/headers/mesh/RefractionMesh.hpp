#ifndef REFRACTION_MESH_HPP

#define REFRACTION_MESH_HPP

#include "buffer/PosNormalGeometryBuffer.hpp"
#include "geometry/Geometry.hpp"
#include "camera/Camera.hpp"
#include "scene/SceneLights.hpp"
#include "transform/Transform.hpp"
#include "material/RefractionMaterial.hpp"

namespace Viewer
{
    class RefractionMesh
    {
    private:
        Geometry &m_geometry;
        PosNormalGeometryBuffer m_geometryBuffer;

    public:
        RefractionMesh(Geometry &geometry);

        Transform Transform;
        RefractionMaterial Material;

        void Initialize();
        void Update();
        void Draw(Camera &camera);
    };
}

#endif