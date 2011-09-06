#include <Kernel/DevTexture.h>

#include <Kernel/DevLog.h>

using namespace dev;

Texture::Texture(const char* path) :
  _path(path),
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

Texture::~Texture()
{
  Destroy();
}

void dev::Texture::Destroy()
{
  if (_texture)
  {
    _texture->Release();
    _texture = NULL;
  }
  _path = "";
}

void Texture::SetTexture(int num)
{
  _deviceDX->SetTexture(num, _texture);
}
