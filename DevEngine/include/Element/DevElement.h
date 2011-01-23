#ifndef DEV_ELEMENT_H
#define DEV_ELEMENT_H

#include <Kernel/DevInclude.h>
#include <Element/DevProperty.h>
#include <Element/DevObject.h>
#include <Math/DevMatrix.h>

namespace dev
{
  class Element : 
    public Object
  {
  public:
    Element(Vec3 position = Vec3(0, 0, 0), Vec3 rotation = Vec3(0, 0, 0), Vec3 scale = Vec3(1, 1, 1));
    virtual ~Element();

    bool GetVisible();
    void SetVisible(bool value);

    Vec3 GetPosition();
    void SetPosition(Vec3 value);

    Vec3 GetScale();
    void SetScale(Vec3 value);

    Vec3 GetRotation();
    void SetRotation(Vec3 value);

    Element* GetParent();
    void SetParent(Element* parent);
    void ClearParent();

    Matrix GetMatrix();

    virtual void Update();

  protected:
    virtual void draw();
    virtual void updateMatrix();

    Properties::Bool    _visible;
    Properties::Vector3 _position;
    Properties::Vector3 _scale;
    Properties::Vector3 _rotation;

    bool                _updateMatrix;
    Matrix              _matrix;
    Element*            _parent;
  };
}

#endif