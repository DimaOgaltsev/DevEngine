#include <Model/DevMesh.h>

using namespace dev;

Mesh::Mesh(D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale) :
  Element(position, rotation, scale)
{
  _vertices = new ArrayVertices();
  _indexes = new ArrayIndexes();
}

Mesh::Mesh() :
  Element()
{
  _vertices = new ArrayVertices();
  _indexes = new ArrayIndexes();
}

Mesh::~Mesh()
{
}

void Mesh::SetVertices(Array vertices, int numberVertex, VertexType VT_Type)
{
  _vertices->SetVertices(vertices, numberVertex, GetSizeVertex(VT_Type), Declaration::GetDeclaration(VT_Type));
}

void Mesh::SetIndexes(Array indexes, int sizeArray, D3DFORMAT D3DFMT_INDEX)
{
  _indexes->SetIndexes(indexes, sizeArray, D3DFMT_INDEX);
}

void Mesh::Draw()
{
  Element::Draw();
  _vertices->SetAsSource();
  _indexes->SetAsSource();
  _deviceDX->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _vertices->GetNumberVertices(), 0, _vertices->GetNumberVertices()/3);
}
