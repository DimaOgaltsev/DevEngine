#ifndef DEV_SHADERS_H
#define DEV_SHADERS_H

#include <Kernel/DevInclude.h>
#include <Element/DevElement.h>

namespace dev
{
  class Shader : public Object
  {
  public:
    enum TypeShader
    {
      VS_1_1,
      VS_2_0,
      VS_2_a,
      VS_2_SW,
      VS_3_0,
      VS_3_SW,

      PS_1_0,
      PS_1_1,
      PS_1_2,
      PS_1_3,
      PS_1_4,
      PS_2_0,
      PS_2_a,
      PS_2_b,
      PS_2_SW,
      PS_3_0,
      PS_3_SW
    };

    Shader(const char* path, TypeShader type, const char* fuction = functionShader);
    virtual ~Shader();

    virtual void CompileShader();

    inline const char* GetPath() const
    {
      return _path.c_str();
    }

    inline const TypeShader* GetType() const
    {
      return &_type;
    }

    inline const char* GetFunction() const
    {
      return _function.c_str();
    }

  protected:

    const char* getCharType();
    bool supportTypeShader();

    ID3DXConstantTable* _constantTable;
    ID3DXBuffer*        _shader;
    std::string         _path;
    TypeShader          _type;
    std::string         _function;
  };
}

#endif