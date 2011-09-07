#include <Shaders/DevShaders.h>

#include <Kernel/DevLog.h>

using namespace dev;

Shader::Shader(const char* path, TypeShader type, const char* fuction) :
  _shader(NULL),
  _constantTable(NULL),
  _path(path),
  _type(type),
  _function(fuction)
{
  CompileShader();
}

Shader::~Shader()
{
  if (_shader)
    _shader->Release();
  if (_constantTable)
    _constantTable->Release();
}

void Shader::CompileShader()
{
  if (!supportTypeShader())
  {
    std::string buffer("Shader (");
    buffer += _path;
    buffer += "compilation error: this type of shaders not supported video card";
    Log::GetLog()->WriteToLog(buffer.c_str());
    return;
  }

  DWORD flags = D3DXSHADER_OPTIMIZATION_LEVEL3;
  #ifdef _DEBUG
    flags = D3DXSHADER_DEBUG;
  #endif

  ID3DXBuffer* _errorBuffer = NULL;
  const char* type = getCharType();
  if (type != NULL && FAILED(D3DXCompileShaderFromFile(_path.c_str(), 0, 0, _function.c_str(), type, flags, &_shader, &_errorBuffer, &_constantTable)))
  {
    std::string buffer("Shader (");
    buffer += _path;
    buffer += "compilation error: ";
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

bool Shader::supportTypeShader()
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
  return FALSE;
}
