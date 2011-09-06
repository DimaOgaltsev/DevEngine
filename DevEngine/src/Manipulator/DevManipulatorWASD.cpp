#include <Manipulator/DevManipulatorWASD.h>

using namespace dev;

ManipulatorWASD::ManipulatorWASD() :
  Manipulator(),
  _mouseX(0),
  _mouseY(0)
{
}

ManipulatorWASD::~ManipulatorWASD()
{
}

void ManipulatorWASD::Update(Camera& camera)
{
  Manipulator::Update(camera);

  float dx = ToRadian((float)_input->GetMouseDeltaX());
  float dy = ToRadian((float)_input->GetMouseDeltaY());
  _mouseX += (float) dx * _sens;
  _mouseY += (float) dy * _sens;
  if (_mouseY > PI_2 - Degree * 0.1f)
    _mouseY = PI_2 - Degree * 0.1f;
  if (_mouseY < -PI_2 + Degree *  0.1f)
    _mouseY = -PI_2 + Degree *  0.1f;
  float mouseZ = (float)ToRadian(_input->GetMouseDeltaZ());

  if (dx || dy)
    camera.SetDirection(dev::Matrix::Rotate(_mouseY, _mouseX, 0) * dev::Vec3(0, 0, 1));

  dev::Vec3 vec(0,0,0);
  if (_input->GetKeyPressed(SC_W))
    vec += camera.GetDirection();
  if (_input->GetKeyPressed(SC_S))
    vec -= camera.GetDirection();
  if (_input->GetKeyPressed(SC_D))
    vec += camera.GetRight();
  if (_input->GetKeyPressed(SC_A))
    vec -= camera.GetRight();
  if (_input->GetKeyPressed(SC_Q))
    vec += camera.GetUp();
  if (_input->GetKeyPressed(SC_Z))
    vec -= camera.GetUp();

  vec.Normalize();
  if (vec != dev::Vec3(0, 0, 0))
    camera.SetMove(vec * _speed);
}
