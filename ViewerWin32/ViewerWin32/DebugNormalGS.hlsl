
struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
};

struct GSOutput
{
    float4 pos : SV_POSITION;
};


cbuffer CameraBuffer : register(b0)
{
    float4x4 ProjectionMatrix;
};

cbuffer ModelConstantBuffer : register(b1)
{
    matrix ViewModelMatrix;
    matrix NormalViewModelMatrix;
}


[maxvertexcount(6)]
void main(
	triangle VS_OUTPUT input[3] : INPUT,
	inout LineStream<GSOutput> output
)
{
    float MAGNITUDE = 0.5f;
    
    for (int i = 0; i < 3; i++)
    {
        GSOutput start;
        float4 viewSpacePos = mul(input[i].pos, ViewModelMatrix);
        float4 pos = mul(viewSpacePos, ProjectionMatrix);
        start.pos = pos;
       
        
        GSOutput end;
        float4 normal = mul(float4(input[i].normal, 0.0), NormalViewModelMatrix);
        float4 normalViewSpacePos = viewSpacePos + normalize(normal) * MAGNITUDE;
        end.pos = mul(normalViewSpacePos, ProjectionMatrix);

        output.Append(start);
        output.Append(end);
   
    
        output.RestartStrip();
    }
}