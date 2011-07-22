#include <Model/DevMesh.h>

using namespace dev;

Mesh::Mesh(const Vec3& position, const Vec3& rotation, const Vec3& scale) :
  Element(position, rotation, scale),
  _vertices(NULL),
  _indexes(NULL)
{
}

Mesh::Mesh() :
  Element(),
  _vertices(NULL),
  _indexes(NULL)
{
}

Mesh::~Mesh()
{
}

void Mesh::SetVertices(LPVOID vertices, int numberVertex, Vertex::VertexType VT_Type)
{
  _vertices = new Vertex::ArrayVertices(vertices, numberVertex, GetSizeVertex(VT_Type), Vertex::Declaration::GetDeclaration(VT_Type));
}

void Mesh::SetIndexes(LPVOID indexes, int sizeArray, D3DFORMAT D3DFMT_INDEX)
{
  _indexes = new Vertex::ArrayIndexes(indexes, sizeArray, D3DFMT_INDEX);
}

void Mesh::draw()
{
  if (_vertices == NULL)
    return;

  Element::draw();
  _vertices->SetAsSource();
  if (_indexes == NULL)
  {
    _deviceDX->DrawPrimitive(D3DPT_TRIANGLELIST, 0, _vertices->GetNumberVertices());
  }
  else
  {
    _indexes->SetAsSource();
    _deviceDX->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _vertices->GetNumberVertices(), 0, _vertices->GetNumberVertices()/3);
  }
}
