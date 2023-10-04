
cbuffer CameraConstantBuffer : register(b0)
{
    matrix ProjectionViewMatrix;
    float3 EyePosition;
}

cbuffer ModelConstantBuffer : register(b1)
{
    matrix ModelMatrix;
}

cbuffer NormalConstantBuffer : register(b2)
{
    matrix NormalMatrix;
}

struct VS_INPUT
{
    float4 pos : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 color : COLOR;
};

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float3 color: COLOR;
    float3 fragWorldPos : VPOS;
    float3 eyePosition: EYEPOS;
};

PS_INPUT main(VS_INPUT input) 
{
    float4 worldPos = mul(float4(input.pos.xyz, 1.0), ModelMatrix);
    
    PS_INPUT output;
    output.pos = mul(worldPos, ProjectionViewMatrix);
    output.tex = input.tex;
    output.normal = mul(input.normal, (float3x3)NormalMatrix);
    output.color = input.color;
    output.fragWorldPos = worldPos.xyz;
    output.eyePosition = EyePosition;
    return output;
}