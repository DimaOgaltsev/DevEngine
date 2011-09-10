float4x4 devWVPMatrix;

struct VS_INPUT
{
  float4 Position: POSITION0;
  float4 Color: COLOR0;
};

struct VS_OUTPUT
{
  float4 Position: POSITION0;
  float4 Color: COLOR0;
};

VS_OUTPUT main(VS_INPUT Input)
{
  VS_OUTPUT Output;
  
  Output.Position = mul(Input.Position, devWVPMatrix2);
  Output.Color = Color;
  
  return(Output);
}