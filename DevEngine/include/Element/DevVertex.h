#ifndef DEV_VERTEX_H
#define DEV_VERTEX_H

#include <Kernel/DevInclude.h>

#include <Element/DevObject.h>

namespace dev
{
  typedef void* Array;

  struct VertexPos
  {
    float x, y, z;
  };

  struct VertexNormal
  {
    float nx, ny, nz;
  };

  struct VertexTexCoord
  {
    float tv, tu;
  };

  struct VertexColor32
  {
    byte r, g, b, a;
  };

  struct VertexColor128
  {
    float r, g, b, a;
  };

  struct VertexPC32 :
    public VertexPos,
    public VertexColor32
  {
  };

  struct VertexPC128 :
    public VertexPos,
    public VertexColor128
  {
  };

  struct VertexPN :
    public VertexPos,
    public VertexNormal
  {
  };

  struct VertexPNT :
    public VertexPos,
    public VertexNormal,
    public VertexTexCoord
  {
  };

  class ArrayVertices :
    public Object
  {
  public:
    ArrayVertices(Array vertices, int numberVertex, int sizeVertex, D3DVERTEXELEMENT9* declaration);
    ArrayVertices();
    virtual ~ArrayVertices();
    void Destroy();

    void SetVertices(Array vertices, int numberVertex, int sizeVertex, D3DVERTEXELEMENT9* declaration);
    void SetAsSource();
    inline int GetNumberVertices()
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
    ArrayIndexes(Array indexes, int sizeArray, D3DFORMAT D3DFMT_INDEX);
    ArrayIndexes();
    virtual ~ArrayIndexes();
    void Destroy();

    void SetIndexes(Array indexes, int sizeArray, D3DFORMAT D3DFMT_INDEX);
    void SetAsSource();

  protected:
    LPDIRECT3DINDEXBUFFER9	_bufferIndexes;
  };
}

#endif