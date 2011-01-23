#include <Element/DevElement.h>

#include <Math/DevMatrix.h>

using namespace dev;

Element::Element(Vec3 position, Vec3 rotation, Vec3 scale) :
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

bool Element::GetVisible()
{
  return _visible();
}

void Element::SetVisible(bool value)
{
  _visible = value;
}

Vec3 Element::GetPosition()
{
  return _position();
}

void Element::SetPosition(Vec3 value)
{
  _position = value;
  _updateMatrix = true;
}

Vec3 Element::GetScale()
{
  return _scale();
}

void Element::SetScale(Vec3 value)
{
  _scale = value;
  _updateMatrix = true;
}

Vec3 Element::GetRotation()
{
  return _rotation();
}

void Element::SetRotation(Vec3 value)
{
  _rotation = value;
  _updateMatrix = true;
}

Element* Element::GetParent()
{
  return _parent;
}

void Element::SetParent(Element* parent)
{
  _parent = parent;
}

void Element::ClearParent()
{
  _parent = NULL;
}

Matrix Element::GetMatrix()
{
  if (_parent)
  {
    return (_matrix * _parent->GetMatrix());
  }
  return _matrix;
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
