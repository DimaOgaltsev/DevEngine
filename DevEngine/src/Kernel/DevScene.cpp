#include <Kernel/DevScene.h>

#include <Math/DevMatrix.h>

using namespace dev;

Scene::Scene() :
  _cameraActive(NULL)
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

void Scene::Update()
{
  if (_cameraActive)
  {
    _cameraActive->Update();
    _deviceDX->SetTransform(D3DTS_VIEW,       (D3DMATRIX*)&_cameraActive->GetViewMatrix());
    _deviceDX->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&_cameraActive->GetProjectionMatrix());
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
