
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
    float4 color : COLOR0;
};

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float4 color : COLOR0;
};

PS_INPUT main(VS_INPUT input) 
{
    float4 worldPos = mul(float4(input.pos.xyz, 1.0), ModelMatrix);
    
    PS_INPUT output;
    output.pos = mul(worldPos, ProjectionViewMatrix);
    output.color = input.color;
    return output;
}