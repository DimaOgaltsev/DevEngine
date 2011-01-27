#include <Element/DevElement.h>

#include <Math/DevMatrix.h>

using namespace dev;

Element::Element(const Vec3& position, const Vec3& rotation, const Vec3& scale) :
  _updateMatrix(true),
  _parent(NULL)
{
  SetVisible(true);
  SetPosition(position);
  SetRotation(rotation);
  SetScale(scale);
}

Element::~Element()
{
}

void Element::SetVisible(bool value)
{
  _visible = value;
}

void Element::SetMove(const float& x, const float& y, const float& z)
{
  _position += Vec3(x, y, z);
  _updateMatrix = true;
}

void Element::SetMove(const Vec3& value)
{
  _position = value;
  _updateMatrix = true;
}

void Element::SetPosition(const float& x, const float& y, const float& z)
{
  _position = Vec3(x, y, z);
  _updateMatrix = true;
}

void Element::SetPosition(const Vec3& value)
{
  _position = value;
  _updateMatrix = true;
}

void Element::SetScale(const float& sx, const float& sy, const float& sz)
{
  _scale = Vec3(sx, sy, sz);
  _updateMatrix = true;
}

void Element::SetScale(const Vec3& value)
{
  _scale = value;
  _updateMatrix = true;
}

void Element::SetRotation(const float& angleX, const float& angleY, const float& angleZ)
{
  _rotation = Vec3(angleX, angleY, angleZ);
  _updateMatrix = true;
}

void Element::SetRotation(const Vec3& value)
{
  _rotation = value;
  _updateMatrix = true;
}

void Element::SetParent(Element* parent)
{
  _parent = parent;
}

void Element::ClearParent()
{
  _parent = NULL;
}

void Element::Update()
{
  if (!_visible())
    return;

  if (_updateMatrix)
  {
    updateMatrix();
    _updateMatrix = false;
  }

  draw();
}

void Element::draw()
{
  _deviceDX->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&_matrix);
}

void Element::updateMatrix()
{
  _matrix.MakeTransform(_position(), _rotation(), _scale());
}
