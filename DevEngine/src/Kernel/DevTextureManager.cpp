#include <Kernel/DevTextureManager.h>

#include <Kernel/DevLog.h>

using namespace dev;

TextureManager::TextureManager()
{
  _textures.clear();
}

TextureManager::~TextureManager()
{
  for(TextureMap::iterator i = _textures.begin(); i != _textures.end(); i++)
    delete (*i).second.texture;
  _textures.clear();
}

Texture* TextureManager::GetTexture(const char* path, Texture::TypeTexture type)
{
  int hash = getHash(path);
  if (!_textures[hash].texture)
  {
    TextureStruct buffer;
    switch(type)
    {
      case Texture::TEX_2D:
        buffer.texture = new Texture2D(path);
        break;
      case Texture::TEX_CUBE:
        buffer.texture = new TextureCube(path);
        break;
    }
    buffer.count = 1;
    _textures[hash] = buffer;
  }
  else
    _textures[hash].count++;
  return _textures[hash].texture;
}

void dev::TextureManager::RemoveTexture(const char* path)
{
  int hash = getHash(path);
  if (_textures[hash].texture)
  {
    _textures[hash].count--;
    if (_textures[hash].count < 1)
    {
      delete _textures[hash].texture;
      _textures.erase(hash);
    }
  }
}

unsigned int TextureManager::getHash(const char* path)
{
  int hash = 0;
  for(unsigned int i = 0; i < strlen(path); i++)
    hash += (path[i] + i) << (i % 32);
  return hash;
}
