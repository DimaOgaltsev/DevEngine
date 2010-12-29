#include <Element/DevProperty.h>

using namespace dev::Properties;

void Property::Save() 
{
};

void Property::Load() 
{
};

//Bool
void Bool::operator = (const bool& value)
{
  _value = value;
}

const bool& Bool::operator () () const
{
  return _value;
}

//Float
void Float::operator = (const float& value)
{
  _value = value;
}

const float& Float::operator () () const
{
  return _value;
}

//Vector2
void Vector2::operator = (const D3DXVECTOR2& value)
{
  _value = value;
}

const D3DXVECTOR2& Vector2::operator () () const
{
  return _value;
}

//Vector3
void Vector3::operator = (const D3DXVECTOR3& value)
{
  _value = value;
}

const D3DXVECTOR3& Vector3::operator () () const
{
  return _value;
}

//Vector4
void Vector4::operator = (const D3DXVECTOR4& value)
{
  _value = value;
}

const D3DXVECTOR4& Vector4::operator () () const
{
  return _value;
}

//Path
void Path::operator = (const char* value)
{
  _value = value;
}

const char* Path::operator () () const
{
  return _value.c_str();
}
