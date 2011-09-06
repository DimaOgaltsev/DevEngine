#include <Manipulator/DevManipulator.h>

using namespace dev;


Manipulator::Manipulator() :
  _insideSpeed(0.01f),
  _speed(0.0f),
  _sens(0.1f)
{
  _input = SystemInput::Get();
  SystemTimer::Get()->Reset(0);
}

Manipulator::~Manipulator()
{

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
