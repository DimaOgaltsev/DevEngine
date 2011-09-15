#include <Model/DevVertex.h>

#include <Kernel/DevLog.h>

using namespace dev::Vertex;

//ArrayVertices
ArrayVertices::ArrayVertices() :
  _declaration(NULL),
  _bufferVertices(NULL),
  _numberVertices(NULL),
  _sizeVertex(NULL)
{
}

ArrayVertices::ArrayVertices(LPVOID vertices, int numberVertex, VertexType VT_Type) :
  _declaration(NULL),
  _bufferVertices(NULL),
  _numberVertices(NULL),
  _sizeVertex(NULL)
{
  SetVertices(vertices, numberVertex, VT_Type);
}

ArrayVertices::~ArrayVertices()
{
  Destroy();
}


void ArrayVertices::Destroy()
{
  _sizeVertex = NULL;
  _numberVertices = NULL;
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

void ArrayVertices::SetVertices(LPVOID vertices, int numberVertices, VertexType VT_Type)
{
  Destroy();

  _numberVertices = numberVertices;
  _sizeVertex     = GetSizeVertex(VT_Type);

  if (!_deviceDX ||
       _deviceDX->CreateVertexBuffer(_numberVertices * _sizeVertex, 0, 0, D3DPOOL_MANAGED, &_bufferVertices, NULL) != D3D_OK ||
       _deviceDX->CreateVertexDeclaration(Declaration::GetDeclaration(VT_Type), &_declaration) != D3D_OK)
  {
    Log::GetLog()->WriteToLog("Array vertices not created!");
    return;
  }

  LPVOID buffer;
  _bufferVertices->Lock(0, 0, (LPVOID*)&buffer, 0);
  memcpy(buffer, vertices, _numberVertices * _sizeVertex);
  _bufferVertices->Unlock();

}

void ArrayVertices::SetVerticesFromFile(HANDLE hFile, int numberVertices, VertexType VT_Type)
{
  Destroy();

  _numberVertices = numberVertices;
  _sizeVertex = GetSizeVertex(VT_Type);

  if (!_deviceDX ||
    _deviceDX->CreateVertexBuffer(_sizeVertex * _numberVertices, 0, 0, D3DPOOL_MANAGED, &_bufferVertices, NULL) != D3D_OK ||
    _deviceDX->CreateVertexDeclaration(Declaration::GetDeclaration(VT_Type), &_declaration) != D3D_OK)
  {
    Log::GetLog()->WriteToLog("Array vertices not created!");
    return;
  }

  LPVOID buffer;
  DWORD ReadValue;

  _bufferVertices->Lock(0, 0, (LPVOID*)&buffer, 0);
  ReadFile(hFile, buffer, _sizeVertex * _numberVertices, &ReadValue, 0);
  _bufferVertices->Unlock();

}

void ArrayVertices::SetAsSource()
{
  _deviceDX->SetStreamSource(0, _bufferVertices, 0, _sizeVertex);
  _deviceDX->SetVertexDeclaration(_declaration);
}

//ArrayIndexes
ArrayIndexes::ArrayIndexes() :
  _bufferIndexes(NULL),
  _sizeIndex(NULL),
  _numberIndexes(NULL)
{
}

ArrayIndexes::ArrayIndexes(LPVOID indexes, int numberIndexes, D3DFORMAT D3DFMT_INDEX) :
  _bufferIndexes(NULL),
  _sizeIndex(NULL),
  _numberIndexes(NULL)
{
  SetIndexes(indexes, numberIndexes, D3DFMT_INDEX);
}

ArrayIndexes::~ArrayIndexes()
{
  Destroy();
}

void ArrayIndexes::Destroy()
{
  _sizeIndex = NULL;
  _numberIndexes = NULL;
  if (_bufferIndexes)
  {
    _bufferIndexes->Release();
    _bufferIndexes = NULL;
  }
}

void ArrayIndexes::SetIndexes(LPVOID indexes, int numberIndexes, D3DFORMAT D3DFMT_INDEX)
{
  Destroy();

  _sizeIndex = D3DFMT_INDEX == D3DFMT_INDEX16 ? 2 : 4;
  _numberIndexes = numberIndexes;

  if (!_deviceDX ||
       _deviceDX->CreateIndexBuffer(_sizeIndex * numberIndexes, 0, D3DFMT_INDEX, D3DPOOL_MANAGED, &_bufferIndexes, NULL) != D3D_OK)
  {
    Log::GetLog()->WriteToLog("Array indexes not created!");
    return;
  }

  LPVOID buffer;
  _bufferIndexes->Lock(0, 0, (LPVOID*)&buffer, 0);
  memcpy(buffer, indexes, _sizeIndex * numberIndexes);
  _bufferIndexes->Unlock();
}

void ArrayIndexes::SetIndexesFromFile(HANDLE hFile, int numberIndexes, D3DFORMAT D3DFMT_INDEX)
{
  Destroy();

  _sizeIndex = D3DFMT_INDEX == D3DFMT_INDEX16 ? 2 : 4;
  _numberIndexes = numberIndexes;

  if (!_deviceDX ||
    _deviceDX->CreateIndexBuffer(_sizeIndex * numberIndexes, 0, D3DFMT_INDEX, D3DPOOL_MANAGED, &_bufferIndexes, NULL) != D3D_OK)
  {
    Log::GetLog()->WriteToLog("Array indexes not created!");
    return;
  }

  LPVOID buffer;
  DWORD ReadValue;

  _bufferIndexes->Lock(0, 0, (LPVOID*)&buffer, 0);
  ReadFile(hFile, buffer, _sizeIndex * numberIndexes, &ReadValue, 0);
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
  case VT_PT2:
    return sizeof(VertexPT2);
  case VT_PT3:
    return sizeof(VertexPT3);
  case VT_PN:
    return sizeof(VertexPN);
  case VT_PNT2:
    return sizeof(VertexPNT2);
  case VT_PNT3:
    return sizeof(VertexPNT3);
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

static D3DVERTEXELEMENT9 vertexPT2[] =
{
  {0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
  {0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
  D3DDECL_END()
};

static D3DVERTEXELEMENT9 vertexPT3[] =
{
  {0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
  {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
  D3DDECL_END()
};

static D3DVERTEXELEMENT9 vertexPN[] =
{
  {0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
  {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
  D3DDECL_END()
};

static D3DVERTEXELEMENT9 vertexPNT2[] =
{
  {0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
  {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
  {0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
  D3DDECL_END()
};

static D3DVERTEXELEMENT9 vertexPNT3[] =
{
  {0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
  {0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
  {0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
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
  case VT_PT2:
    return vertexPT2;
  case VT_PT3:
    return vertexPT3;
  case VT_PN:
    return vertexPN;
  case VT_PNT2:
    return vertexPNT2;
  case VT_PNT3:
    return vertexPNT3;
  }

  return NULL;
}

