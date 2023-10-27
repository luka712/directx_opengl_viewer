#ifndef MATERIAL_DATA_HPP

#define MATERIAL_DATA_HPP

#include <glm/glm.hpp>

namespace Viewer
{
    struct UnlitMaterialData
    {
        glm::vec3 DiffuseColor;
        float Intensity;
    };

    struct PhongMaterialData
    {
        float DiffuseCoefficient;
        float SpecularCoefficient;
        float Shininess;
    };

    struct RefractionMaterialData
    {
        float RefractionIndex;
    };
}

#endif