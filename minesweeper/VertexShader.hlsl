

cbuffer PerFrameConstantBuffer : register( b0 )
{
	float2 screenSize;
	float2 unused;
}

struct VSOUTPUT{
	float4 position : SV_POSITION;
	float4 color : COLOR0;
	float2 UV: TEXCOORD0;
};
SamplerState sampleObject : register(s0);
Texture2D textureObject :register(t0);




VSOUTPUT main( float4 pos : POSITION0,float4 color : COLOR0, float2 UV: TEXCOORD0 ) 
{
	VSOUTPUT OUT;
	OUT.position = pos;
	OUT.color = color; 
	OUT.UV = UV;



	OUT.position.xy = (OUT.position.xy / screenSize) * 2 - 1; 

	

	return OUT;
}