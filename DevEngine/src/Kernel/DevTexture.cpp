#include <Kernel/DevTexture.h>

#include <Kernel/DevLog.h>

using namespace dev;

Texture::Texture(const char* path) :
  _path(path)
{
}

Texture::~Texture()
{
  Destroy();
}

void Texture::Destroy()
{
  _path.clear();
}

void Texture::SetTexture(int num)
{
}

Texture2D::Texture2D(const char* path) :
  Texture(path),
  _texture(NULL)
{
  //replace load texture
  //if (FAILED(_deviceDX->CreateTexture(128, 128, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &_texture, NULL)))
  //example png: http://code.google.com/p/nvidia-texture-tools/source/browse/tags/2.0.0/src/nvimage/DirectDrawSurface.cpp
  if (FAILED(D3DXCreateTextureFromFile(_deviceDX, path, &_texture)))
  {
    std::string buf("Texture not loaded: ");
    buf += path;
    Log::GetLog()->WriteToLog(buf.c_str());
    Destroy();
  }
}

Texture2D::~Texture2D()
{
  Destroy();
}

void Texture2D::Destroy()
{
  Texture::Destroy();
  if (_texture)
  {
    _texture->Release();
    _texture = NULL;
  }
}

void Texture2D::SetTexture(int num)
{
  _deviceDX->SetSamplerState(num, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
  _deviceDX->SetSamplerState(num, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
  _deviceDX->SetSamplerState(num, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
  _deviceDX->SetTexture(num, _texture);
}

CubeTexture::CubeTexture(const char* path) :
  Texture(path),
  _texture(NULL)
{
  if (FAILED(D3DXCreateCubeTextureFromFile(_deviceDX, path, &_texture)))
  {
    std::string buf("Texture not loaded: ");
    buf += path;
    Log::GetLog()->WriteToLog(buf.c_str());
    Destroy();
  }
}

CubeTexture::~CubeTexture()
{
  Destroy();
}

void CubeTexture::Destroy()
{
  Texture::Destroy();
  if (_texture)
  {
    _texture->Release();
    _texture = NULL;
  }
}

void CubeTexture::SetTexture(int num)
{
  _deviceDX->SetSamplerState(num, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
  _deviceDX->SetSamplerState(num, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
  _deviceDX->SetSamplerState(num, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
  _deviceDX->SetTexture(num, _texture);
}
