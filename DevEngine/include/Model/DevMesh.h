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
    Mesh(const Vec3& position, const Vec3& rotation, const Vec3& scale);
    Mesh();
    virtual ~Mesh();

    void SetVertices(LPVOID vertices, int numberVertex, Vertex::VertexType VT_Type);
    void SetIndexes(LPVOID indexes, int sizeArray, D3DFORMAT D3DFMT_INDEX);
    
    virtual void draw();

  protected:
    Vertex::ArrayVertices*  _vertices;
    Vertex::ArrayIndexes*   _indexes;
  };
}

#endif