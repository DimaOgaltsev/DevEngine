#include <Model/DevVertex.h>

#include <Kernel/DevLog.h>

using namespace dev::Vertex;

//ArrayVertices
ArrayVertices::ArrayVertices() :
  _declaration(NULL),
  _bufferVertices(NULL),
  _numberVertices(NULL),
  _sizeVertices(NULL)
{
}

ArrayVertices::ArrayVertices(LPVOID vertices, int numberVertex, int sizeVertex, D3DVERTEXELEMENT9* declaration) :
  _declaration(NULL),
  _bufferVertices(NULL),
  _numberVertices(NULL),
  _sizeVertices(NULL)
{
  SetVertices(vertices, numberVertex, sizeVertex, declaration);
}

ArrayVertices::~ArrayVertices()
{
  Destroy();
}


void ArrayVertices::Destroy()
{
  if (_declaration)
  {
    _declaration->Release();
    _declaration = NULL;
  }
  if (_bufferVertices)
  {
    _bufferVertices->Release();
    _bufferVertices = NULL;
  }
}

void ArrayVertices::SetVertices(LPVOID vertices, int numberVertex, int sizeVertex, D3DVERTEXELEMENT9* declaration)
{
  Destroy();
  if (!_deviceDX ||
       _deviceDX->CreateVertexBuffer(numberVertex * sizeVertex, 0, 0, D3DPOOL_MANAGED, &_bufferVertices, NULL) != D3D_OK ||
       _deviceDX->CreateVertexDeclaration(declaration, &_declaration) != D3D_OK)
  {
    Log::GetLog()->WriteToLog("Array vertices not created!");
    return;
  }

  LPVOID buffer;
  _bufferVertices->Lock(0, 0, (LPVOID*)&buffer, 0);
  memcpy(buffer, vertices, numberVertex * sizeVertex);
  _bufferVertices->Unlock();

  _numberVertices = numberVertex;
  _sizeVertices   = sizeVertex;
}

void ArrayVertices::SetAsSource()
{
  _deviceDX->SetStreamSource(0, _bufferVertices, 0, _sizeVertices);
  _deviceDX->SetVertexDeclaration(_declaration);
}

//ArrayIndexes
ArrayIndexes::ArrayIndexes() :
  _bufferIndexes(NULL)
{
}

ArrayIndexes::ArrayIndexes(LPVOID indexes, int sizeArray, D3DFORMAT D3DFMT_INDEX) :
  _bufferIndexes(NULL)
{
  SetIndexes(indexes, sizeArray, D3DFMT_INDEX);
}

ArrayIndexes::~ArrayIndexes()
{
  Destroy();
}

void ArrayIndexes::Destroy()
{
  if (_bufferIndexes)
  {
    _bufferIndexes->Release();
    _bufferIndexes = NULL;
  }
}

void ArrayIndexes::SetIndexes(LPVOID indexes, int sizeArray, D3DFORMAT D3DFMT_INDEX)
{
  Destroy();
  if (!_deviceDX ||
       _deviceDX->CreateIndexBuffer(sizeArray, 0, D3DFMT_INDEX, D3DPOOL_MANAGED, &_bufferIndexes, NULL) != D3D_OK)
  {
    Log::GetLog()->WriteToLog("Array vertices not created!");
    return;
  }

  LPVOID buffer;
  _bufferIndexes->Lock(0, 0, (LPVOID*)&buffer, 0);
  memcpy(buffer, indexes, sizeArray);
  _bufferIndexes->Unlock();
}

void ArrayIndexes::SetAsSource()
{
  _deviceDX->SetIndices(_bufferIndexes);
}

int dev::Vertex::GetSizeVertex(VertexType VT_type)
{
  switch(VT_type)
  {
  case VT_P:
    return sizeof(VertexP);
  case VT_PC32:
    return sizeof(VertexPC32);
  case VT_PC128:
    return sizeof(VertexPC128);
  case VT_PT:
    return sizeof(VertexPT);
  case VT_PN:
    return sizeof(VertexPN);
  case VT_PNT:
    return sizeof(VertexPNT);
  }

  return 0;
}


//declarations
static D3DVERTEXELEMENT9 vertexP[] =
{
  {0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
  D3DDECL_END()
};

static D3DVERTEXELEMENT9 vertexPC32[] =
{
  {0, 0,  D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
  {0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0},
  D3DDECL_END()
};

static D3DVERTEXELEMENT9 vertexPC128[] =
{
  {0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
  {0, 12, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0},
  D3DDECL_END()
};

static D3DVERTEXELEMENT9 vertexPT[] =
{
  {0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
  {0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
  D3DDECL_END()
};

static D3DVERTEXELEMENT9 vertexPN[] =
{
  {0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
  {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
  D3DDECL_END()
};

static D3DVERTEXELEMENT9 vertexPNT[] =
{
  {0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
  {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
  {0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,   0},
  D3DDECL_END()
};

D3DVERTEXELEMENT9* Declaration::GetDeclaration(VertexType VT_type)
{
  switch(VT_type)
  {
  case VT_P:
    return vertexP;
  case VT_PC32:
    return vertexPC32;
  case VT_PC128:
    return vertexPC128;
  case VT_PT:
    return vertexPT;
  case VT_PN:
    return vertexPN;
  case VT_PNT:
    return vertexPNT;
  }

  return NULL;
}
