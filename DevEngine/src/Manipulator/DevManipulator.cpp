#include <Manipulator/DevManipulator.h>

using namespace dev;


Manipulator::Manipulator() :
  _insideSpeed(defaultSpeed),
  _speed(0.0f),
  _sens(defaultSens)
{
  _input = SystemInput::Get();
  SystemTimer::Get()->Reset(0);
}

Manipulator::~Manipulator()
{
  if (_input)
  {
    delete _input;
    _input = NULL;
  }
}

void Manipulator::Update(Camera& camera)
{ 
  _speed = _insideSpeed * (float)SystemTimer::Get()->GetDeltaTimeMS(0);
};

void Manipulator::SetSpeed(float speed)
{
  _insideSpeed = speed;
}

void Manipulator::SetSens(float sens)
{
  _sens = sens;
}
