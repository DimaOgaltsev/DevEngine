#include <Model/DevMesh.h>

using namespace dev;

Mesh::Mesh(D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale) :
  Element(position, rotation, scale)
{
  _vertices = new Vertex::ArrayVertices();
  _indexes = new Vertex::ArrayIndexes();
}

Mesh::Mesh() :
  Element()
{
  _vertices = new Vertex::ArrayVertices();
  _indexes = new Vertex::ArrayIndexes();
}

Mesh::~Mesh()
{
}

void Mesh::SetVertices(Vertex::Array vertices, int numberVertex, Vertex::VertexType VT_Type)
{
  _vertices->SetVertices(vertices, numberVertex, GetSizeVertex(VT_Type), Vertex::Declaration::GetDeclaration(VT_Type));
}

void Mesh::SetIndexes(Vertex::Array indexes, int sizeArray, D3DFORMAT D3DFMT_INDEX)
{
  _indexes->SetIndexes(indexes, sizeArray, D3DFMT_INDEX);
}

void Mesh::draw()
{
  Element::draw();
  _vertices->SetAsSource();
  _indexes->SetAsSource();
  _deviceDX->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _vertices->GetNumberVertices(), 0, _vertices->GetNumberVertices()/3);
}
