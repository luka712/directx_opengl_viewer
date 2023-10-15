
cbuffer CameraConstantBuffer : register(b0)
{
    matrix ProjectionViewMatrix;
}

struct VS_INPUT
{
    float4 pos : POSITION;
};

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float3 tex : TEXCOORD0;
};

PS_INPUT main(VS_INPUT input)
{
    
    PS_INPUT output;
    float4 pos = mul(float4(input.pos.xyz, 1.0), ProjectionViewMatrix);
    output.pos = pos.xyww;
    output.tex = input.pos.xyz;
    return output;
}