struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float3 fragWorldPos : VPOS;
    float3 viewDir : VIEWDIR;
};

struct Material
{
    float RefractionIndex;
};


sampler s_diffuseSampler : register(s0);
Texture2D<float4> s_diffuseTexture : register(t0);


cbuffer MaterialBuffer : register(b0)
{
    Material c_material;
}


sampler s_sampler : register(s0);
TextureCube s_texture : register(t0);

float4 main(PS_INPUT input) : SV_TARGET
{
    PS_INPUT output;
    
    float3 eyeToFrag = -input.viewDir;
    float3 refraction = refract(eyeToFrag, input.normal, c_material.RefractionIndex);
    
    return float4(s_texture.Sample(s_sampler, normalize(refraction)).rgb, 1.0);

}