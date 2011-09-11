#ifndef DEV_MESH_H
#define DEV_MESH_H

#include <Kernel/DevInclude.h>

#include <Element/DevElement.h>
#include <Model/DevVertex.h>
#include <Shaders/DevShaders.h>
#include <Kernel/DevMaterial.h>
#include <Kernel/DevTexture.h>

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

    void SetVertexShader(VertexShader* shader);
    inline VertexShader* GetVertexShader() const
    {
      return _vShader;
    }

    void SetPixelShader(PixelShader* shader);
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

    void SetTexture(const char* path, int num);
    inline Texture* GetTexture(int num) const
    {
      if (num < MAX_NUM_TEXTURES)
        return _texture[num];

      return NULL;
    }

  protected:

    void dirtyTextures();

    Vertex::ArrayVertices*  _vertices;
    Vertex::ArrayIndexes*   _indexes;

    VertexShader*           _vShader;
    PixelShader*            _pShader;
    int                     _orderNum;

    Material*               _material;
    std::vector<Texture*>   _texture;
  };

  typedef std::vector<Mesh*> MeshList;
}

#endif