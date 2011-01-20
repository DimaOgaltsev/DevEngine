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

    void SetVertices(Vertex::Array vertices, int numberVertex, Vertex::VertexType VT_Type);
    void SetIndexes(Vertex::Array indexes, int sizeArray, D3DFORMAT D3DFMT_INDEX);
    
    virtual void draw();

  protected:
    Vertex::ArrayVertices*  _vertices;
    Vertex::ArrayIndexes*   _indexes;
  };
}

#endif