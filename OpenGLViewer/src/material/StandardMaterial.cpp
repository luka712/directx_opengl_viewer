#include "material/StandardMaterial.hpp"

namespace Viewer
{
    StandardMaterial::StandardMaterial()
    {
        m_materialShader = new StandardMaterialShader();
        m_materialBuffer = new UniformBuffer<MaterialData>();
    }

    StandardMaterial::~StandardMaterial()
    {
        delete m_materialShader;
    }

    void StandardMaterial::Initialize()
    {
        m_materialShader->Initialize();
        MaterialData materialData;
        m_materialBuffer->Initialize(&materialData, 1);
    }

    void StandardMaterial::Use()
    {
        m_materialShader->Use();
    }

    void StandardMaterial::UpdateSelfProperties()
    {
        // Get currently assigned or empty.
        Texture2D *diffuseTexture = DiffuseTexture;
        Texture2D *specularTexture = SpecularTexture;
        if (diffuseTexture == nullptr)
        {
            diffuseTexture = Texture2D::GetEmptyTexture();
        }
        if (specularTexture == nullptr)
        {
            specularTexture = Texture2D::GetEmptyTexture();
        }

        // update textures.
        m_materialShader->SetDiffuseTexture(*diffuseTexture);
        m_materialShader->SetSpecularTexture(*specularTexture);

        // update non texture data.
        MaterialData data;
        data.DiffuseCoefficient = DiffuseCoefficient;
        data.SpecularCoefficient = SpecularCoefficient;
        data.Shininess = Shininess;
        m_materialBuffer->Update(&data);
        m_materialShader->SetMaterial(*m_materialBuffer);
    }

    void StandardMaterial::UpdateCameraProperties(glm::mat4x4 &projectionMatrix, glm::vec3 &cameraPosition)
    {
        m_materialShader->SetProjectionViewMatrix(projectionMatrix);
        m_materialShader->SetCameraPosition(cameraPosition);
    }

    void StandardMaterial::UpdateTranformProperties(glm::mat4x4 &modelMatrix, glm::mat3x3 &normalMatrix)
    {
        m_materialShader->SetModelMatrix(modelMatrix);
        m_materialShader->SetNormalMatrix(normalMatrix);
    }

    void StandardMaterial::UpdateLights(
        UniformBuffer<AmbientLight> &ambientLightBuffer,
        UniformBuffer<DirectionalLight> &directionalLightsBuffer,
        UniformBuffer<PointLight> &pointLightsBuffer)
    {
        m_materialShader->SetAmbientLight(ambientLightBuffer);
        m_materialShader->SetDirectionalLights(directionalLightsBuffer);
        m_materialShader->SetPointLights(pointLightsBuffer);
    }
}