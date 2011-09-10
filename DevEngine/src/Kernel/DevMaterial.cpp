#include <Kernel/DevMaterial.h>

using namespace dev;

Material::Material(Vec4 ambient, Vec4 diffuse, Vec4 specular, Vec4 emissive, float power) :
  _ambient(ambient),
  _diffuse(diffuse),
  _specular(specular),
  _emissive(emissive),
  _power(power)
{
}

Material::~Material()
{
}

void Material::SetAmbient(const Vec4& ambient)
{
  _ambient = ambient;
}

void Material::SetDiffuse(const Vec4& diffuse)
{
  _diffuse = diffuse;
}

void Material::SetSpecular(const Vec4& specular)
{
  _specular = specular;
}

void Material::SetEmissive(const Vec4& emissive)
{
  _emissive = emissive;
}

void Material::SetPower(const float& power)
{
  _power = power;
}
