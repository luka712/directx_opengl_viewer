#ifndef MESH_HPP

#define MESH_HPP

#include "buffer/GeometryBuffer.hpp"
#include "buffer/PosNormalGeometryBuffer.hpp"
#include "geometry/Geometry.hpp"
#include "camera/Camera.hpp"
#include "scene/SceneLights.hpp"
#include "transform/Transform.hpp"
#include "material/StandardMaterial.hpp"
#include "material/DebugNormalMaterial.hpp"

namespace Viewer
{
    class Mesh
    {
    private:
        Geometry &m_geometry;
        GeometryBuffer m_geometryBuffer;

        PosNormalGeometryBuffer m_posNormalGeometryBuffer; // for debug normals
        DebugNormalMaterial m_debugNormalMaterial;

    public:
        Mesh(Geometry &geometry);

        Transform Transform;
        StandardMaterial Material;

        bool DebugNormals = false;

        void Initialize();
        void Update();
        void Draw(Camera &camera, SceneLights &lights);
    };
}

#endif