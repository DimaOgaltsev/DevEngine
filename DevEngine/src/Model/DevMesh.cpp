#include <Model/DevMesh.h>

using namespace dev;

Mesh::Mesh(const Vec3& position, const Vec3& rotation, const Vec3& scale) :
  Element(position, rotation, scale),
  _vertices(NULL),
  _indexes(NULL),
  _vShader(NULL),
  _pShader(NULL),
  _orderNum(0),
  _material(0)
{
  dirtyTextures();
}

Mesh::Mesh() :
  Element(),
  _vertices(NULL),
  _indexes(NULL),
  _vShader(NULL),
  _pShader(NULL),
  _orderNum(0),
  _material(0)
{
  dirtyTextures();
}

Mesh::~Mesh()
{
  dirtyTextures();
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

void Mesh::Draw()
{
  if (_vertices == NULL)
    return;

  Element::Draw();

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
  if (!shader)
    return;

  _vShader = shader;
  _vShader->CompileShader();
}

void Mesh::SetPixelShader(PixelShader* shader)
{
  if (!shader)
    return;

  _pShader = shader;
  _pShader->CompileShader();
  if (!_material)
    _material = new Material();
}

void Mesh::SetOrderNum(int num)
{
  _orderNum = num;
}

void Mesh::SetMaterial(Material* material)
{
  _material = material;
}

void Mesh::UpdateParameters()
{
  Element::UpdateParameters();
  if (_material)
  {
    if (_pShader == NULL)
      _deviceDX->SetMaterial(&_material->GetAsD3DMaterial());
  }

  for(int i = 0; i < MAX_NUM_TEXTURES; i++)
  {
    if (_texture[i])
      _texture[i]->SetTexture(i);
    else
      _deviceDX->SetTexture(i, NULL);
  }
}

void Mesh::SetTexture(Texture* texture, int num)
{
  if (num < MAX_NUM_TEXTURES)
    _texture[num] = texture;
}

void Mesh::dirtyTextures()
{
  _texture.clear();
  for(int i = 0; i < MAX_NUM_TEXTURES; i++)
    _texture.push_back(NULL);
}
