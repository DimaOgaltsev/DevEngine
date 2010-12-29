#ifndef DEV_ELEMENT_H
#define DEV_ELEMENT_H

#include <Kernel/DevInclude.h>
#include <Element/DevProperty.h>

namespace dev
{
  class Element
  {
  public:
    Element();
    virtual ~Element();

    bool GetVisible();
    void SetVisible(bool value);

    D3DXVECTOR3 GetPosition();
    void SetPosition(D3DXVECTOR3 value);

    D3DXVECTOR3 GetScale();
    void SetScale(D3DXVECTOR3 value);

    D3DXVECTOR3 GetRotation();
    void SetRotation(D3DXVECTOR3 value);

  protected:
    virtual void Update();
    virtual void Draw();

    Properties::Bool    _visible;
    Properties::Vector3 _position;
    Properties::Vector3 _scale;
    Properties::Vector3 _rotation;

    bool                _updatematrix;
    D3DXMATRIX          _matrix;
  };
}

#endif