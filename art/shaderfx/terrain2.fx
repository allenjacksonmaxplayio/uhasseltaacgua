
/*** Generated through Lumonix shaderFX  by: Arutha in 3dsmax at: 12-4-2010 22:30:15  ***/ 

// This FX shader was built to support 3ds Max's standard shader compiler. 


texture Layer0_TS
<
	string Name = "grass.jpg";
	string UIName = "Layer0_TS";
	string ResourceType = "2D";
>;
 
sampler2D Layer0_TSSampler = sampler_state
{
	Texture = <Layer0_TS>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};
 
texture AlphaMap0_TS : DiffuseMap
<
	string Name = "Sphere011_alpha.png";
	string UIName = "AlphaMap0_TS";
	string ResourceType = "2D";
>;
 
sampler2D AlphaMap0_TSSampler = sampler_state
{
	Texture = <AlphaMap0_TS>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};
 
texture Layer1_TS
<
	string Name = "sand.jpg";
	string UIName = "Layer1_TS";
	string ResourceType = "2D";
>;
 
sampler2D Layer1_TSSampler = sampler_state
{
	Texture = <Layer1_TS>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};
 
texture Layer2_TS
<
	string Name = "dirt.jpg";
	string UIName = "Layer2_TS";
	string ResourceType = "2D";
>;
 
sampler2D Layer2_TSSampler = sampler_state
{
	Texture = <Layer2_TS>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};
 
texture TextureSampler_5611
<
	string Name = "grass.jpg";
	string UIName = "Layer3_TS";
	string ResourceType = "2D";
>;
 
sampler2D TextureSampler_5611Sampler = sampler_state
{
	Texture = <TextureSampler_5611>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};
 
texture AlphaMap1_TS : DiffuseMap
<
	string Name = "";
	string UIName = "AlphaMap1_TS";
	string ResourceType = "2D";
>;
 
sampler2D AlphaMap1_TSSampler = sampler_state
{
	Texture = <AlphaMap1_TS>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};
 
texture TextureSampler_5339
<
	string Name = "sand.jpg";
	string UIName = "Layer4_TS";
	string ResourceType = "2D";
>;
 
sampler2D TextureSampler_5339Sampler = sampler_state
{
	Texture = <TextureSampler_5339>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};
 
texture TextureSampler_2594
<
	string Name = "dirt.jpg";
	string UIName = "Layer5_TS";
	string ResourceType = "2D";
>;
 
sampler2D TextureSampler_2594Sampler = sampler_state
{
	Texture = <TextureSampler_2594>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};
 

// this function does the different types of light attenuation 
float attenuation_func(int lightattenType, float4 lightAttenuation, float3 lightVec) 
{ 
	float att = 1.0; 
	return att; 
} 
	 
// this function does the different types of cone angle 
float coneangle_func(int lightconeType, float lightHotspot, float lightFalloff, float3 lightVec, float3 lightDir) 
{ 
	float cone = 1.0; 
	return cone; 
} 

/************** light info **************/ 

float3 light1Dir : Direction 
< 
	string UIName = "Light 1 Direction"; 
	string Object = "TargetLight"; 
	string Space = "World"; 
		int refID = 1; 
> = {100.0f, 100.0f, 100.0f}; 

float3 light1Pos : POSITION 
< 
	string UIName = "Light 1 Position"; 
	string Object = "PointLight"; 
	string Space = "World"; 
		int refID = 1; 
> = {100.0f, 100.0f, 100.0f}; 

float4 light1Color : LIGHTCOLOR <int LightRef = 1; string UIWidget = "None"; > = { 1.0f, 1.0f, 1.0f, 1.0f}; 
float4 light1Attenuation : LightAttenuation <int LightRef = 1; string UIWidget = "None"; > = { 20.0f, 30.0f, 0.0f, 100.0f}; 
float light1Hotspot : LightHotSpot <int LightRef = 1; string UIWidget = "None"; > = { 43.0f }; 
float light1Falloff : LightFallOff <int LightRef = 1; string UIWidget = "None"; > = { 45.0f }; 

#define light1Type 1
#define light1attenType 0
#define light1coneType 0
#define light1CastShadows false

//---------------------------------- 

float4x4 wvp : WorldViewProjection < string UIType = "None"; >;  
float4x4 worldI : WorldInverse < string UIType = "None"; >;  
// create the light vector 
float3 lightVec_func(float3 worldSpacePos, float3 lightVector, float3x3 objTangentXf, int lightType) 
{ 
	float3 lightVec = mul(objTangentXf, (mul((lightVector - worldSpacePos), worldI).xyz)); 
	return lightVec; 
} 

// input from application 
	struct a2v { 
	float4 position		: POSITION; 

	float2 texCoord		: TEXCOORD0; 

}; 

// output to fragment program 
struct v2f { 
        float4 position    		: POSITION; 

	float2 texCoord			: TEXCOORD0; 

}; 

// Ambient Pass Vertex Shader: 
v2f av(a2v In, uniform float3 lightPos, uniform int lightType, uniform float3 lightDir) 
{ 
	v2f Out = (v2f)0; 
	Out.position = mul(In.position, wvp);				//transform vert position to homogeneous clip space 

	Out.texCoord = In.texCoord;						//pass through texture coordinates from channel 1 

	return Out; 
} 

// Ambient Pass Pixel Shader: 
float4 af(v2f In, uniform float3 lightDir, uniform float4 lightColor, uniform float4 lightAttenuation, uniform float lightHotspot, uniform float lightFalloff, uniform int lightType, uniform int lightattenType, uniform int lightconeType, uniform bool lightCastShadows, uniform int shadowPassCount) : COLOR 
{ 

	float4 Layer0_TU = tex2D(Layer0_TSSampler, In.texCoord.xy);
	float4 Alpha0_TU = tex2D(AlphaMap0_TSSampler, In.texCoord.xy);
	float4 Layer1_TU = tex2D(Layer1_TSSampler, In.texCoord.xy);
	float4 Layer2_TU = tex2D(Layer2_TSSampler, In.texCoord.xy);
	float4 TextureMap_4055 = tex2D(TextureSampler_5611Sampler, In.texCoord.xy);
	float4 Alpha1_TU = tex2D(AlphaMap1_TSSampler, In.texCoord.xy);
	float4 TextureMap_4640 = tex2D(TextureSampler_5339Sampler, In.texCoord.xy);
	float4 TextureMap_342 = tex2D(TextureSampler_2594Sampler, In.texCoord.xy);
	float3 input1 = ((((Layer0_TU.rgb * Alpha0_TU.r) + (Layer1_TU.rgb * Alpha0_TU.g)) + (Layer2_TU.rgb * Alpha0_TU.b)) + (((TextureMap_4055.rgb * Alpha1_TU.r) + (TextureMap_4640.rgb * Alpha1_TU.g)) + (TextureMap_342.rgb * Alpha1_TU.a))); 

	float4 ret =  float4(input1, 1); 
	return ret; 
} 

technique Complete  
{  
	pass ambient  
    {		 
		VertexShader = compile vs_2_0 av(light1Pos,  light1Type, light1Dir); 
		ZEnable = true; 
		ZWriteEnable = true; 
		CullMode = cw; 
		ShadeMode = Gouraud;
		AlphaBlendEnable = false; 
		AlphaTestEnable = FALSE; 
		PixelShader = compile ps_2_0 af(light1Dir, light1Color, light1Attenuation, light1Hotspot, light1Falloff, light1Type, light1attenType, light1coneType, light1CastShadows, 1); 
	}  

}    