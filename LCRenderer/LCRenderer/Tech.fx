

//************ Shaders *************/

struct vsInput

{

  // stream 0

  float4 position : POSITION;
  float3 normal   : NORMAL;

  // stream 1
  float4 model_matrix0 : TEXCOORD0;
  float4 model_matrix1 : TEXCOORD1;
  float4 model_matrix2 : TEXCOORD2;
  float4 model_matrix3 : TEXCOORD3;
  float4 instance_color : D3DCOLOR;

};


vsOutput GeometryInstancingVS(
  in vsInput input)

{
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
  output.position = mul(worldPosition, ViewProjectionMatrix);
  output.normal = mul(worldNormal, ViewProjectionMatrix);
  output.color = input.instance_color;
  // output other vertex data
}


float4 PS( VS_OUTPUT In ) : COLOR
{

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
