#ifndef DEV_ELEMENT_H
#define DEV_ELEMENT_H

#include <Kernel/DevInclude.h>
#include <Element/DevProperty.h>
#include <Element/DevObject.h>

namespace dev
{
  class Element : 
    public Object
  {
  public:
    Element(D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3 rotation = D3DXVECTOR3(0, 0, 0), D3DXVECTOR3 scale = D3DXVECTOR3(1, 1, 1));
    virtual ~Element();

    bool GetVisible();
    void SetVisible(bool value);

    D3DXVECTOR3 GetPosition();
    void SetPosition(D3DXVECTOR3 value);

    D3DXVECTOR3 GetScale();
    void SetScale(D3DXVECTOR3 value);

    D3DXVECTOR3 GetRotation();
    void SetRotation(D3DXVECTOR3 value);

    Element* GetParent();
    void SetParent(Element* parent);
    void ClearParent();

    D3DXMATRIX GetMatrix();

    virtual void Update();

  protected:
    virtual void draw();
    virtual void updateMatrix();

    Properties::Bool    _visible;
    Properties::Vector3 _position;
    Properties::Vector3 _scale;
    Properties::Vector3 _rotation;

    bool                _updateMatrix;
    D3DXMATRIX          _matrix;
    D3DXMATRIX          _trMatrix, _rotMatrix, _scMatrix;
    Element*             _parent;
  };
}

#endif