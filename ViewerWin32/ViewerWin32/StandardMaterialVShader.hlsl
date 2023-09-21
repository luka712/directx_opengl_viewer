
cbuffer CameraConstantBuffer : register(b0)
{
    matrix ProjectionViewMatrix;
}

cbuffer ModelConstantBuffer : register(b1)
{
    matrix ModelMatrix;
}

float4 main(float4 pos : POSITION) : SV_POSITION
{
    float4 worldPos = mul(float4(pos.xyz, 1.0), ModelMatrix);
    return mul(worldPos, ProjectionViewMatrix);
}