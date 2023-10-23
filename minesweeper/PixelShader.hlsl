
cbuffer PerFrameConstantBuffer : register(b0)
{
	float2 screenSize;
	float2 unused;
}

SamplerState sampleObject : register(s0);
Texture2D textureObject :register(t0);

float4 main(float4 position : SV_POSITION, float4 color : COLOR0, float2 UV :TEXCOORD0 ) : SV_TARGET
{

	float4 tex = textureObject.Sample(sampleObject, UV);

	float4 outputColor = tex* color;
	return outputColor;
}