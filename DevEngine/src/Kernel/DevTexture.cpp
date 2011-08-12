#include <Kernel/DevTexture.h>

#include <Kernel/DevLog.h>

using namespace dev;

Texture::Texture(const char* path) :
  _path(path),
  _texture(NULL)
{
  if (FAILED(_deviceDX->CreateTexture(128, 128, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &_texture, NULL)))
  {
    Log::GetLog()->WriteToLog("Texture not loaded: ");
    Log::GetLog()->WriteToLog(path);
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
