struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 color: COLOR;
    float3 fragWorldPos : VPOS;
    float3 viewDir : VIEWDIR;
};

struct AmbientLight
{
    float Intensity;
    float3 Color;
};

struct DirectionalLight
{
    float3 Direction;
    float Intensity;
    float3 Color;
    float _padding;
};

struct PointLight
{
    float3 Position;
    float Intensity;
    float3 Color;
    float Constant;
    float Linear;
    float Quadratic;
    float2 _padding;
};

struct Material
{
    float DiffuseCoefficient;
    float SpecularCoefficient;
    float Shininess;
};


sampler s_diffuseSampler : register(s0);
Texture2D<float4> s_diffuseTexture : register(t0);

sampler s_specularSampler : register(s1);
Texture2D<float4> s_specularTexture : register(t1);


cbuffer MaterialBuffer : register(b0)
{
    Material c_material;
}

cbuffer AmbientLightBuffer : register(b1)
{
    AmbientLight c_ambient;
}

cbuffer DirectionalLightBuffer : register(b2)
{
    DirectionalLight DirLights[3];
}

cbuffer PointLightBuffer : register(b3)
{
    PointLight PointLights[5];
}


float3 ambientLight(AmbientLight light, Material material)
{
    return light.Color * light.Intensity;
}

float3 directionalLight(DirectionalLight light, Material material, PS_INPUT input)
{
    float3 lightDirection = normalize(-light.Direction);
    return light.Color * light.Intensity * material.DiffuseCoefficient * max(dot(lightDirection, input.normal), 0.0f);
}

float3 directionalSpecularLight(DirectionalLight light, Material material, PS_INPUT input)
{
    float3 lightDirection = normalize(-light.Direction);
    float3 halfwayDir = normalize(lightDirection + input.viewDir);
    // find specular intensity
    float spec = max(dot(input.normal, halfwayDir), 0.0);
    spec = pow(spec, material.Shininess); 
    return light.Intensity * light.Color * material.SpecularCoefficient * spec;
}

float3 pointDiffuseLight(PointLight light, Material material,  PS_INPUT input)
{
    float3 lightDirection = normalize(light.Position - input.fragWorldPos);
    return light.Color * light.Intensity * material.DiffuseCoefficient * max(dot(lightDirection, input.normal), 0.0f);
}

float3 pointSpecularLight(PointLight light, Material material,  PS_INPUT input)
{
    float3 lightDir = normalize(light.Position - input.fragWorldPos);
    float3 halfwayDir = normalize(lightDir + input.viewDir);
    
    // find specular intensity
    float spec = max(dot(input.normal, halfwayDir), 0.0);
    spec = pow(spec, material.Shininess);
    
    // combine results
    float3 specular = light.Intensity * light.Color * material.SpecularCoefficient * spec;
    return specular;
}

float pointLightAttenuation(PointLight l, float3 fragPos)
{
    float distance = length(l.Position - fragPos);
    return 1.0 / (l.Constant + l.Linear * distance + l.Quadratic * (distance * distance));
}

float4 main(PS_INPUT input) : SV_TARGET
{

    // Ambient
    float3 ambient = ambientLight(c_ambient, c_material);
    
    // Directional
    float3 directional = float3(0.0, 0.0, 0.0);
    float3 directionalSpecular = float3(0.0, 0.0, 0.0);
    for (int i = 0; i < 3; i++)
    {
        DirectionalLight light = DirLights[i];
        directional += directionalLight(light, c_material, input);
        directionalSpecular += directionalSpecularLight(light, c_material, input);
    }
    
    // Point 
    float3 pointL = float3(0.0, 0.0, 0.0);
    float3 pointSpec = float3(0.0, 0.0, 0.0);
    for (int i = 0; i < 5; i++)
    {
        PointLight light = PointLights[i];
        float a = pointLightAttenuation(light, input.fragWorldPos);
        
        pointL += pointDiffuseLight(light, c_material, input) * a;
        pointSpec += pointSpecularLight(light, c_material, input) * a;
    }
    
    // total light    
    float3 lightAmount = ambient + directional + pointL;
    float3 specularAmount = directionalSpecular + pointSpec;
    
    float2 texCoords = float2(input.tex.x, 1.0 - input.tex.y);
    float3 diffuseColor = s_diffuseTexture.Sample(s_diffuseSampler, texCoords).xyz * lightAmount * input.color;
    float3 specularColor = s_specularTexture.Sample(s_specularSampler, texCoords).xyz * specularAmount * input.color;

    return float4(diffuseColor + specularColor, 1.0);
}