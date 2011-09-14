#ifndef DEV_TEXTURE_MANAGER_H
#define DEV_TEXTURE_MANAGER_H

#include <Kernel/DevInclude.h>

#include <Kernel/DevSingleton.h>
#include <Kernel/DevTexture.h>
#include <Element/DevObject.h>

namespace dev
{
  class TextureManager :
    public Object
  {
  public:
    TextureManager();
    virtual ~TextureManager();

    void ClearList();

    Texture* GetTexture(const char* path, Texture::TypeTexture type);
    void RemoveTexture(const char* path);

  protected:

    struct TextureStruct
    {
      Texture* texture;
      int      count;
    };

    unsigned int getHash(const char* path);

    typedef std::map<int, TextureStruct> TextureMap;
    TextureMap    _textures;
  };

  class DevTextureManager : public Singleton<TextureManager>
  {
  };
}

#endif