
cbuffer CameraConstantBuffer : register(b0)
{
    matrix ProjectionViewMatrix;
    float3 EyePosition;
}

cbuffer ModelConstantBuffer : register(b1)
{
    matrix ModelMatrix;
    matrix NormalMatrix;
}


struct VS_INPUT
{
    float4 pos : POSITION;
    float3 normal : NORMAL;
};

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float3 fragWorldPos : VPOS;
    float3 viewDir : VIEWDIR;
};

PS_INPUT main(VS_INPUT input)
{
    float4 worldPos = mul(float4(input.pos.xyz, 1.0), ModelMatrix);
    
    PS_INPUT output;
    output.pos = mul(worldPos, ProjectionViewMatrix);
    output.normal = normalize(mul(input.normal, (float3x3) NormalMatrix));
    output.fragWorldPos = worldPos.xyz;
    output.viewDir = normalize(EyePosition - worldPos.xyz);
    return output;
}