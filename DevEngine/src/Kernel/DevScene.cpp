#include <Kernel/DevScene.h>

#include <Kernel/DevMath.h>

using namespace dev;

Scene::Scene() :
  _cameraActive(NULL),
  _device(NULL)
{
  _mainGroup = new Group();
}

Scene::Scene(Camera* camera)
{
  SetActivCamera(camera);
  _mainGroup = new Group();
}

Scene::~Scene()
{
  delete _mainGroup;
}

void Scene::SetActivCamera(Camera* camera)
{
  _cameraActive = camera;
}

Camera* Scene::GetActivCamera()
{
  return _cameraActive;
}

LPDIRECT3DDEVICE9 Scene::GetDevice()
{
  return _device;
}

void Scene::SetDevice(LPDIRECT3DDEVICE9 device)
{
  _device = device;
}

void Scene::Update()
{
  if (_cameraActive)
  {
    D3DXMATRIX m1 = _cameraActive->GetViewMatrix();
    D3DXMATRIX m2 = _cameraActive->GetProjectionMatrix();
    _device->SetTransform(D3DTS_WORLD, &Matrix::Identity());
    _device->SetTransform(D3DTS_VIEW, &_cameraActive->GetViewMatrix());
    _device->SetTransform(D3DTS_PROJECTION, &_cameraActive->GetProjectionMatrix());
  }
  _mainGroup->Update();
}

void Scene::AddElement(Element* element)
{
  _mainGroup->AddElement(element);
}

void Scene::RemoveElement(Element* element)
{
  _mainGroup->RemoveElement(element);
}
