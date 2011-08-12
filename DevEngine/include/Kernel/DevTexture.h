#ifndef DEV_TEXTURE_H
#define DEV_TEXTURE_H

#include <Kernel/DevInclude.h>

#include <Element/DevObject.h>

namespace dev
{
  class Texture : 
    public Object
  {
  public:
    Texture(const char* path);
    virtual ~Texture();

    const char* GetPath() const
    {
      return _path.c_str();
    }

    void SetTexture(int num);

  protected:

    void Destroy();

    std::string _path;
    LPDIRECT3DTEXTURE9 _texture;
  };
}

#endif