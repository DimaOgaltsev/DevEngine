#include <Shaders/DevShaders.h>

#include <Kernel/DevLog.h>
#include <Math/DevMath.h>

using namespace dev;

Shader::Shader(const char* path, DWORD type, const char* fuction) :
  _shaderBuffer(NULL),
  _constantTable(NULL),
  _path(path),
  _type(type),
  _function(fuction)
{
}

Shader::~Shader()
{
  if (_shaderBuffer)
    _shaderBuffer->Release();
  if (_constantTable)
    _constantTable->Release();
}

void Shader::CompileShader()
{
  if (!supportTypeShader())
  {
    std::string buffer("Shader (");
    buffer += _path;
    buffer += ") compilation error: this type of shaders not supported video card";
    Log::GetLog()->WriteToLog(buffer.c_str());
    return;
  }

  DWORD flags = D3DXSHADER_NO_PRESHADER;
  #ifdef _DEBUG
    flags = D3DXSHADER_DEBUG;
  #endif

  ID3DXBuffer* _errorBuffer = NULL;
  const char* type = getCharType();
  if (type == NULL || 
      FAILED(D3DXCompileShaderFromFile(_path.c_str(), 0, 0, _function.c_str(), type, flags, &_shaderBuffer, &_errorBuffer, &_constantTable)))
  {
    std::string buffer("Shader (");
    buffer += _path;
    buffer += ") compilation error: ";
    if(_errorBuffer)
    {
      buffer += (char*)_errorBuffer->GetBufferPointer();
      Log::GetLog()->WriteToLog(buffer.c_str());
      _errorBuffer->Release();
      return;
    }
    
    if (type == NULL)
    {
      buffer += "Unknown shader type";
      Log::GetLog()->WriteToLog(buffer.c_str());
      return;
    }

     buffer += "Unknown error";
     Log::GetLog()->WriteToLog(buffer.c_str());
     return;
  }
}

const char* Shader::getCharType()
{
  return NULL;
}

bool Shader::supportTypeShader()
{
  return false;
}

void Shader::SetShader()
{

}

VertexShader::VertexShader(const char* path, TypeVertexShader type, const char* fuction) :
  Shader(path, (DWORD)type, fuction),
  _shader(NULL)
{

}

VertexShader::~VertexShader()
{
  if (_shader)
    _shader->Release();
}

const char* VertexShader::getCharType()
{
  switch(_type)
  {
  case VS_1_1:
    return "vs_1_1";
  case VS_2_0:
    return "vs_2_0";
  case VS_2_a:
    return "vs_2_a";
  case VS_2_SW:
    return "vs_2_sw";
  case VS_3_0:
    return "vs_3_0";
  case VS_3_SW:
    return "vs_3_sw";
  }
  return NULL;
}

bool VertexShader::supportTypeShader()
{
  D3DCAPS9 caps;
  _deviceDX->GetDeviceCaps(&caps);

  switch(_type)
  {
  case VS_1_1:
    return caps.VertexShaderVersion >= D3DVS_VERSION(1, 1);
  case VS_2_0:
  case VS_2_a:
  case VS_2_SW:
    return caps.VertexShaderVersion >= D3DVS_VERSION(2, 0);
  case VS_3_0:
  case VS_3_SW:
    return caps.VertexShaderVersion >= D3DVS_VERSION(3, 0);
  }
  return false;
}

void VertexShader::SetShader()
{
  if (_shader)
  {
    Matrix world, view, projection;
    _deviceDX->GetTransform(D3DTS_WORLD, (D3DMATRIX*)&world);
    _deviceDX->GetTransform(D3DTS_VIEW, (D3DMATRIX*)&view);
    _deviceDX->GetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&projection);
    _deviceDX->SetVertexShader(_shader);
    D3DXHANDLE hViewProjectionMatrix = _constantTable->GetConstantByName(0, "WorldViewProjection"); 
    _constantTable->SetMatrix(_deviceDX, hViewProjectionMatrix, (const D3DXMATRIX*)&(world * view * projection));
  }
}

void VertexShader::CompileShader()
{
  Shader::CompileShader();
  if (_shaderBuffer == NULL || 
    FAILED(_deviceDX->CreateVertexShader((DWORD*)_shaderBuffer->GetBufferPointer(), &_shader)))
  {
    std::string buffer("Shader (");
    buffer += _path;
    buffer += ") compilation error: create shader failed";
    Log::GetLog()->WriteToLog(buffer.c_str());
  }
}

PixelShader::PixelShader(const char* path, TypePixelShader type, const char* fuction) :
  Shader(path, (DWORD)type, fuction),
  _shader(NULL)
{
}

PixelShader::~PixelShader()
{
  if (_shader)
    _shader->Release();
}

const char* PixelShader::getCharType()
{
  switch(_type)
  {
  case PS_1_0:
    return "ps_1_0";
  case PS_1_1:
    return "ps_1_1";
  case PS_1_2:
    return "ps_1_2";
  case PS_1_3:
    return "ps_1_3";
  case PS_1_4:
    return "ps_1_4";
  case PS_2_0:
    return "ps_2_0";
  case PS_2_a:
    return "ps_2_a";
  case PS_2_b:
    return "ps_2_b";
  case PS_2_SW:
    return "ps_2_sw";
  case PS_3_0:
    return "ps_3_0";
  case PS_3_SW:
    return "ps_3_sw";
  }
  return NULL;
}

bool PixelShader::supportTypeShader()
{
  D3DCAPS9 caps;
  _deviceDX->GetDeviceCaps(&caps);

  switch(_type)
  {
  case PS_1_1:
    return caps.PixelShaderVersion >= D3DPS_VERSION(1, 1);
  case PS_1_2:
    return caps.PixelShaderVersion >= D3DPS_VERSION(1, 2);
  case PS_1_3:
    return caps.PixelShaderVersion >= D3DPS_VERSION(1, 3);
  case PS_1_4:
    return caps.PixelShaderVersion >= D3DPS_VERSION(1, 4);
  case PS_2_0:
  case PS_2_a:
  case PS_2_b:
  case PS_2_SW:
    return caps.PixelShaderVersion >= D3DPS_VERSION(2, 0);
  case PS_3_0:
  case PS_3_SW:
    return caps.PixelShaderVersion >= D3DPS_VERSION(3, 0);
  }
  return false;
}

void PixelShader::SetShader()
{
  if (_shader)
  {
    _deviceDX->SetPixelShader(_shader);
  }
}

void PixelShader::CompileShader()
{
  Shader::CompileShader();
  if (FAILED(_deviceDX->CreatePixelShader((DWORD*)_shaderBuffer->GetBufferPointer(), &_shader)))
  {
    std::string buffer("Shader (");
    buffer += _path;
    buffer += ") compilation error: create shader failed";
    Log::GetLog()->WriteToLog(buffer.c_str());
  }
}

