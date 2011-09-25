

//************ Shaders *************/

VS_OUTPUT VS( VS_IN In )
{

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
