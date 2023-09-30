
cbuffer CameraConstantBuffer : register(b0)
{
    matrix ProjectionViewMatrix;
}

cbuffer ModelConstantBuffer : register(b1)
{
    matrix ModelMatrix;
}

struct VS_INPUT
{
    float4 pos : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

PS_INPUT main(VS_INPUT input) 
{
    float4 worldPos = mul(float4(input.pos.xyz, 1.0), ModelMatrix);
    
    PS_INPUT output;
    output.pos = mul(worldPos, ProjectionViewMatrix);
    output.tex = input.tex;
    output.normal = input.normal;
    return output;
}