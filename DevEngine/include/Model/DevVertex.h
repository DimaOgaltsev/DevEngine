#ifndef DEV_VERTEX_H
#define DEV_VERTEX_H

#include <Kernel/DevInclude.h>

#include <Element/DevObject.h>

namespace dev
{
  namespace Vertex
  {
    enum VertexType
    {
      VT_P = 1,
      VT_PT = 3,
      VT_PN = 5,
      VT_PNT = 7,
      VT_PC32 = 9,
      VT_PC128 = 17
    };

    struct VertexP
    {
      float x, y, z;
    };

    struct VertexPC32
    {
      float    x, y, z;
      D3DCOLOR color;
    };

    struct VertexPC128
    {
      float         x, y, z;
      D3DCOLORVALUE color;
    };

    struct VertexPT
    {
      float x, y, z;
      float tu, tv;
    };

    struct VertexPN
    {
      float x, y, z;
      float nx, ny, nz;
    };

    struct VertexPNT
    {
      float x, y, z;
      float nx, ny, nz;
      float tu, tv;
    };

    class ArrayVertices :
      public Object
    {
    public:
      ArrayVertices(LPVOID vertices, int numberVertex, VertexType VT_Type);
      ArrayVertices();
      virtual ~ArrayVertices();
      void Destroy();

      void SetVertices(LPVOID vertices, int numberVertex, VertexType VT_Type);
      void SetVerticesFromFile(HANDLE hFile, int numberVertex, VertexType VT_Type);

      void SetAsSource();
      inline int GetNumberVertices() const
      {
        return _numberVertices;
      }

    protected:
      int                          _numberVertices;
      int                          _sizeVertex;
      LPDIRECT3DVERTEXDECLARATION9 _declaration;
      LPDIRECT3DVERTEXBUFFER9      _bufferVertices;
    };

    class ArrayIndexes :
      public Object
    {
    public:
      ArrayIndexes(LPVOID indexes, int numberVertices, D3DFORMAT D3DFMT_INDEX);
      ArrayIndexes();
      virtual ~ArrayIndexes();
      void Destroy();

      void SetIndexes(LPVOID indexes, int numberVertices, D3DFORMAT D3DFMT_INDEX);
      void SetIndexesFromFile(HANDLE hFile, int numberVertices, D3DFORMAT D3DFMT_INDEX);
      
      void SetAsSource();
      inline int GetNumberIndexes() const
      {
        return _numberIndexes;
      }

    protected:
      int                     _numberIndexes;
      int                     _sizeIndex;
      LPDIRECT3DINDEXBUFFER9  _bufferIndexes;
    };

    int GetSizeVertex(VertexType VT_type);

    namespace Declaration
    {
      D3DVERTEXELEMENT9* GetDeclaration(VertexType VT_type);
    }
  }
}

#endif