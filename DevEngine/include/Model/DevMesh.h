#ifndef DEV_MESH_H
#define DEV_MESH_H

#include <Kernel/DevInclude.h>

#include <Element/DevElement.h>
#include <Model/DevVertex.h>
#include <Shaders/DevShaders.h>
#include <Kernel/DevMaterial.h>
#include <Kernel/DevTextureManager.h>

namespace dev
{
  class Mesh :
    public Element
  {
  public:
    Mesh(const Vec3& position, const Vec3& rotation, const Vec3& scale);
    Mesh();
    virtual ~Mesh();

    void SetVertices(LPVOID vertices, int numberVertex, Vertex::VertexType VT_Type);
    void SetIndexes(LPVOID indexes, int numberIndexes, D3DFORMAT D3DFMT_INDEX);
    
    void SetVerticesFromFile(HANDLE file, int numberVertex, Vertex::VertexType VT_Type);
    void SetIndexesFromFile(HANDLE file, int numberIndexes, D3DFORMAT D3DFMT_INDEX);
    
    virtual void Draw();
    virtual void UpdateParameters();

    void SetVertexShader(const char* path, VertexShader::TypeVertexShader type, const char* funcName = functionShader);
    inline VertexShader* GetVertexShader() const
    {
      return _vShader;
    }

    void SetPixelShader(const char* path, PixelShader::TypePixelShader type, const char* funcName = functionShader);
    inline PixelShader* GetPixelShader() const
    {
      return _pShader;
    }

    void SetOrderNum(int num);
    inline int GetOrderNum() const
    {
      return _orderNum;
    }

    virtual inline Mesh* AsMesh() 
    {
      return this;
    }

    void SetMaterial(Material* material);
    inline Material* GetMaterial() const
    {
      return _material;
    }

    void RemoveTexture(const char* path);
    void SetTexture(const char* path, Texture::TypeTexture type = Texture::TEX_2D);
    inline const TextureList& GetTextureList() const
    {
      return _textures;
    }

  protected:

    void dirtyTextures();

    Vertex::ArrayVertices*  _vertices;
    Vertex::ArrayIndexes*   _indexes;

    VertexShader*           _vShader;
    PixelShader*            _pShader;
    int                     _orderNum;

    Material*               _material;
    TextureList             _textures;
  };

  typedef std::vector<Mesh*> MeshList;
}

#endif