#ifndef DEV_MATERIAL_H
#define DEV_MATERIAL_H

#include <Kernel/DevInclude.h>
#include <Math/DevVec4.h>

namespace dev
{
  class Material
  {
  public:
    Material(Vec4 ambient   = Vec4(0.25f, 0.25f, 0.25f, 1.0f), 
             Vec4 diffuse   = Vec4(0.75f, 0.75f, 0.75f, 1.0f), 
             Vec4 specular  = Vec4(1.00f, 1.00f, 1.00f, 1.0f), 
             Vec4 emissive  = Vec4(0.00f, 0.00f, 0.00f, 1.0f), 
             float power    = 1.0f);
    virtual ~Material();

    void SetAmbient(const Vec4& ambient);
    inline const Vec4& GetAmbient() const
    {
      return _ambient;
    }

    void SetDiffuse(const Vec4& diffuse);
    inline const Vec4& GetDiffuse() const
    {
      return _diffuse;
    }

    void SetSpecular(const Vec4& specular);
    inline const Vec4& GetSpecular() const
    {
      return _specular;
    }

    void SetEmissive(const Vec4& emissive);
    inline const Vec4& GetEmissive() const
    {
      return _emissive;
    }

    void SetPower(const float& power);
    inline const float& GetPower() const
    {
      return _power;
    }

    inline const D3DMATERIAL9& GetAsD3DMaterial() const 
    {
      return _material;
    }

  protected:

    union 
    {
      struct 
      {
        Vec4  _ambient;
        Vec4  _diffuse;
        Vec4  _specular;
        Vec4  _emissive;
        float _power;
      };
      D3DMATERIAL9 _material;
    };
     
    
  };
}

#endif