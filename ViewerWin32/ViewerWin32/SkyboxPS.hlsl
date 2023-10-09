struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 tex : TEXCOORD0;
};

sampler s_sampler : register(s0);
TextureCube s_texture : register(t0);


float4 main(PS_INPUT input) : SV_TARGET
{
    return s_texture.Sample(s_sampler, normalize(input.tex));
}