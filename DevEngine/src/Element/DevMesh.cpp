#include <Element/DevMesh.h>

using namespace dev;

static D3DVERTEXELEMENT9 vertexElement[] =
{
  {0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
    D3DDECL_END()
};

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

void Mesh::SetVertices(Array vertices, int numberVertex, int sizeVertex)
{
  _vertices->SetVertices(vertices, numberVertex, sizeVertex, vertexElement);
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
