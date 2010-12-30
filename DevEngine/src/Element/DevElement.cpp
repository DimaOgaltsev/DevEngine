#include <Element/DevElement.h>

#include <Kernel/DevMath.h>

using namespace dev;

Element::Element(D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale):
  _updateMatrix(true)
{
  D3DXMatrixIdentity(&_matrix);
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

D3DXVECTOR3 Element::GetPosition()
{
  return _position();
}

void Element::SetPosition(D3DXVECTOR3 value)
{
  _position = value;
  _trMatrix = Matrix::Translate(&value);
  _updateMatrix = true;
}

D3DXVECTOR3 Element::GetScale()
{
  return _scale();
}

void Element::SetScale(D3DXVECTOR3 value)
{
  _scale = value;
  _scMatrix = Matrix::Scale(&value);
  _updateMatrix = true;
}

D3DXVECTOR3 Element::GetRotation()
{
  return _rotation();
}

void Element::SetRotation(D3DXVECTOR3 value)
{
  _rotation = value;
  _rotMatrix = Matrix::Rotation(&value);
  _updateMatrix = true;
}

void Element::Update()
{
  if (!_visible())
    return;

  if (_updateMatrix)
  {
    UpdateMatrix();
    _updateMatrix = false;
  }

  Draw();
}

void Element::Draw()
{

}

void Element::UpdateMatrix()
{
  _matrix = _scMatrix * _rotMatrix * _trMatrix;
}
