float4x4 g_mViewProjection;
float3   g_vEyePos;

float3 g_vLightPos = float3(0, 10, 0);
float4 g_vLightColor = float4(1.0,1.0,1.0,1.0);

//************ Shaders *************/

struct VS_INPUT 

{
  // stream 0

  float4 position : POSITION;
  float3 normal   : NORMAL;

  // stream 1
  float4 model_matrix0 : TEXCOORD0;
  float4 model_matrix1 : TEXCOORD1;
  float4 model_matrix2 : TEXCOORD2;
  float4 model_matrix3 : TEXCOORD3;
  float4 instance_color : COLOR;

};

struct VS_OUTPUT
{
  float4 position : POSITION;
  float3 normal   : NORMAL;
  float4 color    : COLOR;
};


VS_OUTPUT VS(
  in VS_INPUT input)

{
  VS_OUTPUT output = (VS_OUTPUT)0;
  // construct the model matrix
  float4x4 modelMatrix =
  {
    input.model_matrix0,
    input.model_matrix1,
    input.model_matrix2,
    input.model_matrix3
  };

  // transform input position and normal to world space
  // with the instance model matrix

  float4 worldPosition = mul(input.position, modelMatrix);
  float3 worldNormal = mul(input.normal, modelMatrix);

  // output position, normal, and color
  output.position = mul(worldPosition, g_mViewProjection);
  output.normal = mul(worldNormal, g_mViewProjection);
  output.color = input.instance_color;
  // output other vertex data
  return output;
}


float4 PS( VS_OUTPUT In ) : COLOR
{
  return float4(0.0f, 1.0f, 0.0f, 1.0f);
}




//--------------------------------------------------------------------------------------
// Renders scene 
//--------------------------------------------------------------------------------------
technique RenderScene
{
  pass P0
  {   
    CullMode = NONE;
    VertexShader = compile vs_3_0 VS();
    PixelShader  = compile ps_3_0 PS(); 
  }
}
