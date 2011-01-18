#ifndef DEV_MESH_H
#define DEV_MESH_H

#include <Kernel/DevInclude.h>

#include <Element/DevElement.h>
#include <Model/DevVertex.h>

namespace dev
{
  class Mesh :
    public Element
  {
  public:
    Mesh(D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale);
    Mesh();
    virtual ~Mesh();

    void SetVertices(Array vertices, int numberVertex, VertexType VT_Type);
    void SetIndexes(Array indexes, int sizeArray, D3DFORMAT D3DFMT_INDEX);
    
    virtual void Draw();

  protected:
    ArrayVertices*  _vertices;
    ArrayIndexes*   _indexes;
  };
}

#endif