#include <Element/DevProperty.h>

using namespace dev;
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

//Float
void Float::operator = (const float& value)
{
  _value = value;
}

void Float::operator += (const float& value)
{
  _value += value;
}

//Vector2
void Vector2::operator = (const Vec2& value)
{
  _value = value;
}

void Vector2::operator += (const Vec2& value)
{
  _value += value;
}

//Vector3
void Vector3::operator = (const Vec3& value)
{
  _value = value;
}

void Vector3::operator += (const Vec3& value)
{
  _value += value;
}


//Vector4
void Vector4::operator = (const Vec4& value)
{
  _value = value;
}

void Vector4::operator += (const Vec4& value)
{
  _value += value;
}

//Path
void Path::operator = (const char* value)
{
  _value = value;
}
