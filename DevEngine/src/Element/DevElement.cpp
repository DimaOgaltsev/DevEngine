#include <Element/DevElement.h>

#include <Kernel/DevMath.h>

using namespace dev;

Element::Element():
  _updatematrix(true)
{
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
  _updatematrix = true;
}

D3DXVECTOR3 Element::GetScale()
{
  return _scale();
}

void Element::SetScale(D3DXVECTOR3 value)
{
  _scale = value;
  _updatematrix = true;
}

D3DXVECTOR3 Element::GetRotation()
{
  return _rotation();
}

void Element::SetRotation(D3DXVECTOR3 value)
{
  _rotation = value;
  _updatematrix = true;
}

void Element::Update()
{
  if (!_visible())
    return;

  if (_updatematrix)
  {
    _matrix = Matrix::Scale(_scale());
    D3DXMatrixMultiply(&_matrix, &_matrix, &Matrix::Rotation(_rotation()));
    D3DXMatrixMultiply(&_matrix, &_matrix, &Matrix::Translate(_position()));
    _updatematrix = false;
  }

  Draw();
}

void Element::Draw()
{

}
