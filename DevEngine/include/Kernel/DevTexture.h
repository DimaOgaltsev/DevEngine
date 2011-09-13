#ifndef DEV_TEXTURE_H
#define DEV_TEXTURE_H

#include <Kernel/DevInclude.h>

#include <Element/DevObject.h>

#define MAX_NUM_TEXTURES 8

namespace dev
{
  //base class texture
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
    virtual void SetTexture(int num);

  protected:
    virtual void Destroy();

    std::string _path;
  };

  //class texture2D
  class Texture2D : 
    public Texture
  {
  public:
    Texture2D(const char* path);
    virtual ~Texture2D();

    virtual void SetTexture(int num);

  protected:

    virtual void Destroy();

    LPDIRECT3DTEXTURE9 _texture;
  };

  //class CubeTexture
  class CubeTexture :
    public Texture
  {
    CubeTexture(const char* path);
    virtual ~CubeTexture();

    virtual void SetTexture(int num);

  protected:

    virtual void Destroy();

    LPDIRECT3DCUBETEXTURE9 _texture;
  };
}

#endif