struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float3 fragWorldPos : VPOS;
    float3 viewDir : VIEWDIR;
};

sampler s_sampler : register(s0);
TextureCube s_texture : register(t0);

float4 main(PS_INPUT input) : SV_TARGET
{
    PS_INPUT output;
    
    float3 eyeToFrag = -input.viewDir;
    float3 reflection = reflect(eyeToFrag, input.normal);
    
    return float4(s_texture.Sample(s_sampler, normalize(reflection)).rgb, 1.0);

}