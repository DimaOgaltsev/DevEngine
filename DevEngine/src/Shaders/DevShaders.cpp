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

bool Shader::CompileShader()
{
  if (!supportTypeShader())
  {
    std::string buffer("Shader (");
    buffer += _path;
    buffer += ") compilation error: this type of shaders not supported video card";
    Log::GetLog()->WriteToLog(buffer.c_str());
    return false;
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
      return false;
    }
    
    if (type == NULL)
    {
      buffer += "Unknown shader type";
      Log::GetLog()->WriteToLog(buffer.c_str());
      return false;
    }

     buffer += "Unknown error";
     Log::GetLog()->WriteToLog(buffer.c_str());
     return false;
  }

  return true;
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

const D3DXHANDLE Shader::CreateParametr(const char* name)
{
  if (!_constantTable)
    return NULL;
   
  D3DXHANDLE parametr = _constantTable->GetConstantByName(0, name);

  if (parametr == NULL)
  {
    std::string buffer("Shader (");
    buffer += _path;
    buffer += ") parametr not found: ";
    buffer += name;
    Log::GetLog()->WriteToLog(buffer.c_str());
  }

  return parametr;
}

void Shader::SetBool(const D3DXHANDLE& parametr, bool Bool)
{
  if (_constantTable && parametr)
    _constantTable->SetBool(_deviceDX, parametr, Bool);
}

void Shader::SetBoolArray(const D3DXHANDLE& parametr, const bool* Bool, UINT num)
{
  if (_constantTable && parametr)
    _constantTable->SetBoolArray(_deviceDX, parametr, (CONST BOOL*)Bool, num);
}

void Shader::SetInt(const D3DXHANDLE& parametr, int Int)
{
  if (_constantTable && parametr)
    _constantTable->SetInt(_deviceDX, parametr, Int);
}

void Shader::SetIntArray(const D3DXHANDLE& parametr, const int* Int, UINT num)
{
  if (_constantTable && parametr)
    _constantTable->SetIntArray(_deviceDX, parametr, Int, num);
}

void Shader::SetFloat(const D3DXHANDLE& parametr, float Float)
{
  if (_constantTable && parametr)
    _constantTable->SetFloat(_deviceDX, parametr, Float);
}

void Shader::SetFloatArray(const D3DXHANDLE& parametr, const float* Float, UINT num)
{
  if (_constantTable && parametr)
    _constantTable->SetFloatArray(_deviceDX, parametr, Float, num);
}

void Shader::SetVec4(const D3DXHANDLE& parametr, const Vec4* vec)
{
  if (_constantTable && parametr)
    _constantTable->SetVector(_deviceDX, parametr, (const D3DXVECTOR4*)vec);
}

void Shader::SetVec4Array(const D3DXHANDLE& parametr, const Vec4* vec, UINT num)
{
  if (_constantTable && parametr)
    _constantTable->SetVectorArray(_deviceDX, parametr, (const D3DXVECTOR4*)vec, num);
}

void Shader::SetMatrix(const D3DXHANDLE& parametr, const Matrix* matrix)
{
  if (_constantTable && parametr)
    _constantTable->SetMatrix(_deviceDX, parametr, (const D3DXMATRIX*)matrix);
}

void Shader::SetMatrixArray(const D3DXHANDLE& parametr, const Matrix* matrix, UINT num)
{
  if (_constantTable && parametr)
    _constantTable->SetMatrixArray(_deviceDX, parametr, (const D3DXMATRIX*)matrix, num);
}

VertexShader::VertexShader(const char* path, TypeVertexShader type, const char* fuction) :
  Shader(path, (DWORD)type, fuction),
  _shader(NULL),
  _devWVPMatrix(NULL)
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
    SetMatrix(_devWVPMatrix, &(world * view * projection));
  }
}

bool VertexShader::CompileShader()
{
  Shader::CompileShader();
  if (_shaderBuffer == NULL || 
    FAILED(_deviceDX->CreateVertexShader((DWORD*)_shaderBuffer->GetBufferPointer(), &_shader)))
  {
    std::string buffer("Shader (");
    buffer += _path;
    buffer += ") compilation error: create shader failed";
    Log::GetLog()->WriteToLog(buffer.c_str());
    return false;
  }

  _devWVPMatrix = CreateParametr("devWVPMatrix");
  return true;
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

bool PixelShader::CompileShader()
{
  Shader::CompileShader();
  if (FAILED(_deviceDX->CreatePixelShader((DWORD*)_shaderBuffer->GetBufferPointer(), &_shader)))
  {
    std::string buffer("Shader (");
    buffer += _path;
    buffer += ") compilation error: create shader failed";
    Log::GetLog()->WriteToLog(buffer.c_str());
    return false;
  }

  return true;
}

