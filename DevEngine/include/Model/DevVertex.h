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
      VT_P,
      VT_PC32,
      VT_PC128,
      VT_PT,
      VT_PN,
      VT_PNT
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
      ArrayVertices(LPVOID vertices, int numberVertex, int sizeVertex, D3DVERTEXELEMENT9* declaration);
      ArrayVertices();
      virtual ~ArrayVertices();
      void Destroy();

      void SetVertices(LPVOID vertices, int numberVertex, int sizeVertex, D3DVERTEXELEMENT9* declaration);
      void SetAsSource();
      inline int GetNumberVertices() const
      {
        return _numberVertices;
      }

    protected:
      int                          _numberVertices;
      int                          _sizeVertices;
      LPDIRECT3DVERTEXDECLARATION9 _declaration;
      LPDIRECT3DVERTEXBUFFER9      _bufferVertices;
    };

    class ArrayIndexes :
      public Object
    {
    public:
      ArrayIndexes(LPVOID indexes, int sizeArray, D3DFORMAT D3DFMT_INDEX);
      ArrayIndexes();
      virtual ~ArrayIndexes();
      void Destroy();

      void SetIndexes(LPVOID indexes, int sizeArray, D3DFORMAT D3DFMT_INDEX);
      void SetAsSource();

    protected:
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