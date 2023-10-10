struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 color : COLOR;
};


struct Material
{
    float3 DiffuseColor;
    float Intensity;
};


sampler s_diffuseSampler : register(s0);
Texture2D<float4> s_diffuseTexture : register(t0);


cbuffer MaterialBuffer : register(b0)
{
    Material c_material;
}



float4 main(PS_INPUT input) : SV_TARGET
{ 
    float3 diffuseColor = s_diffuseTexture.Sample(s_diffuseSampler, input.tex).xyz * input.color * c_material.DiffuseColor * c_material.Intensity;

    return float4(diffuseColor, 1.0);
}