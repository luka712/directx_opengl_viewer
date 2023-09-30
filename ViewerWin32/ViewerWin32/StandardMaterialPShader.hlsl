struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct DirectionalLight
{
    float3 Direction;
    float Intensity;
    float3 Color;
    float _padding;
};

sampler Sampler;
Texture2D<float4> Texture;

cbuffer AmbientLightBuffer : register(b0)
{
    float AmbientIntensity;
    float3 AmbientColor;
}

cbuffer DirectionalLightBuffer : register(b1)
{
    DirectionalLight DirLights[3];
}

float4 main(PS_INPUT input) : SV_TARGET
{
    float4 matColor = Texture.Sample(Sampler, input.tex);
 
    // Ambient
    float3 ambient = AmbientColor * AmbientIntensity;
    
    // Directional
    float3 directional = float3(0.0, 0.0, 0.0);
    float3 n_normal = normalize(input.normal);
    for (int i = 0; i < 3; i++)
    {
        DirectionalLight light = DirLights[i];
        float3 n_direction = normalize(-light.Direction);
        
        directional += light.Intensity * light.Color * max(dot(n_normal, n_direction), 0.0f);
    }
    
    float3 lightAmount = ambient + directional;
    
    return float4(matColor.rgb * lightAmount, matColor.a);
}