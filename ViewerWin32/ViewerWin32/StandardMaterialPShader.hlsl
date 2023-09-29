
struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

sampler Sampler;
Texture2D<float4> Texture;

float4 main(PS_INPUT input) : SV_TARGET
{
    return Texture.Sample(Sampler, input.tex);
}