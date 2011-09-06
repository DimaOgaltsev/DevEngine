#ifndef DEV_MANIPULATOR_H
#define DEV_MANIPULATOR_H

#include <Kernel/DevInsideLib.h>

namespace dev
{
  class Camera;

  class Manipulator
  {
  public:
    Manipulator();

    virtual ~Manipulator();

    virtual void Update(Camera& camera);


    inline const float GetSpeed() const
    {
      return _insideSpeed;
    }
    void SetSpeed(float speed);

    inline const float GetSens() const
    {
      return _sens;
    }
    void SetSens(float sens);

  protected:
    float   _speed;
    float   _sens;
    Input*  _input;
  
  protected:
    float _insideSpeed;
  };
}

#endif