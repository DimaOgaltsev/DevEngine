#ifndef DEV_ELEMENT_H
#define DEV_ELEMENT_H

#include <Kernel/DevInclude.h>
#include <Element/DevProperty.h>
#include <Element/DevObject.h>
#include <Math/DevMatrix.h>

namespace dev
{
  class Mesh;
  class Group;

  class Element : 
    public Object
  {
  public:
    Element(const Vec3& position = Vec3(0, 0, 0), const Vec3& rotation = Vec3(0, 0, 0), const Vec3& scale = Vec3(1, 1, 1));
    virtual ~Element();

    void SetVisible(bool value);
    inline bool GetVisible() const
    {
      return _visible();
    }

    void SetMove(const float& x, const float& y, const float& z);
    void SetMove(const Vec3& value);

    void SetPosition(const float& x, const float& y, const float& z);
    void SetPosition(const Vec3& value);
    inline const Vec3& GetPosition() const
    {
      return _position();
    }

    void SetScale(const float& sx, const float& sy, const float& sz);
    void SetScale(const Vec3& value);
    inline const Vec3& GetScale() const
    {
      return _scale();
    }

    void SetRotation(const float& angleX, const float& angleY, const float& angleZ);
    void SetRotation(const Vec3& value);
    inline const Vec3& GetRotation() const
    {
      return _rotation();
    }

    void SetParent(Element* parent);
    inline const Element* GetParent() const
    {
      return _parent;
    }
    void ClearParent();

    inline Matrix GetMatrix() const
    {
      return _matrix;
    }

    virtual void Update();
    virtual void UpdateWorldMatrix();
    virtual void UpdateParameters();
    virtual void Draw();

    virtual inline Mesh* AsMesh() 
    {
      return NULL;
    }

    virtual inline Group* AsGroup() 
    {
      return NULL;
    }

  protected:
    virtual void updateMatrix();

    Properties::Bool    _visible;
    Properties::Vector3 _position;
    Properties::Vector3 _scale;
    Properties::Vector3 _rotation;

    bool                _updateMatrix;
    Matrix              _matrix;
    Element*            _parent;
  };

  typedef std::vector<Element*> ElementList;
}

#endif