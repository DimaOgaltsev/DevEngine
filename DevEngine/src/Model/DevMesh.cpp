#include <Model/DevMesh.h>

using namespace dev;

Mesh::Mesh(const Vec3& position, const Vec3& rotation, const Vec3& scale) :
  Element(position, rotation, scale),
  _vertices(NULL),
  _indexes(NULL),
  _vShader(NULL),
  _pShader(NULL)
{
}

Mesh::Mesh() :
  Element(),
  _vertices(NULL),
  _indexes(NULL),
  _vShader(NULL),
  _pShader(NULL)
{
}

Mesh::~Mesh()
{
}

void Mesh::SetVertices(LPVOID vertices, int numberVertex, Vertex::VertexType VT_Type)
{
  _vertices = new Vertex::ArrayVertices(vertices, numberVertex, VT_Type);
}

void Mesh::SetIndexes(LPVOID indexes, int numberIndexes, D3DFORMAT D3DFMT_INDEX)
{
  _indexes = new Vertex::ArrayIndexes(indexes, numberIndexes, D3DFMT_INDEX);
}

void Mesh::SetVerticesFromFile(HANDLE file, int numberVertex, Vertex::VertexType VT_Type)
{
  if (_vertices == NULL)
    _vertices = new Vertex::ArrayVertices();

  _vertices->SetVerticesFromFile(file, numberVertex, VT_Type);
}

void Mesh::SetIndexesFromFile(HANDLE file, int numberIndexes, D3DFORMAT D3DFMT_INDEX)
{
  if (_indexes == NULL)
    _indexes = new Vertex::ArrayIndexes();

  _indexes->SetIndexesFromFile(file, numberIndexes, D3DFMT_INDEX);
}

void Mesh::draw()
{
  if (_vertices == NULL)
    return;

  Element::draw();

  if (_vShader)
    _vShader->SetShader();
  else
    _deviceDX->SetVertexShader(NULL);

  if (_pShader)
    _pShader->SetShader();
  else
    _deviceDX->SetPixelShader(NULL);

  _vertices->SetAsSource();
  if (_indexes == NULL)
  {
    _deviceDX->DrawPrimitive(D3DPT_TRIANGLELIST, 0, _vertices->GetNumberVertices());
  }
  else
  {
    _indexes->SetAsSource();
    _deviceDX->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _indexes->GetNumberIndexes(), 0, _indexes->GetNumberIndexes()/3);
  }
}

void Mesh::SetVertexShader(VertexShader* shader)
{
  _vShader = shader;
}

void Mesh::SetPixelShader(PixelShader* shader)
{
  _pShader = shader;
}