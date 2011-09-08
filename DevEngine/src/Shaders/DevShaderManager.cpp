#include <Shaders/DevShaderManager.h>

using namespace dev;

ShaderManager::ShaderManager()
{
  ClearList();
}

ShaderManager::~ShaderManager()
{
  ClearList();
}

void ShaderManager::ClearList()
{
  _meshes.clear();
}

void ShaderManager::AddMesh(Mesh* element)
{
  if (!element)
    return;
  
  _meshes.push_back(element);
}

void ShaderManager::ReplaceMesh(Mesh* element, Mesh* newElement)
{
  if (!element || !newElement)
    return;

  unsigned int num = getMeshNum(element);

  if (num != _meshes.size())
  {
    RemoveMesh(element);
    AddMesh(newElement);
  }
}

void ShaderManager::RemoveMesh(Mesh* element)
{
  if (!element)
    return;

  unsigned int num = getMeshNum(element);
  if (num != _meshes.size())
    _meshes.erase(_meshes.begin() + num);
}

void ShaderManager::Update()
{
  for (MeshList::iterator i = _meshes.begin(); i < _meshes.end(); ++i)
  {
    (*i)->UpdateParameters();

    if ((*i)->GetVertexShader())
      (*i)->GetVertexShader()->SetShader();
    else
      _deviceDX->SetVertexShader(NULL);

    if ((*i)->GetPixelShader())
      (*i)->GetPixelShader()->SetShader();
    else
      _deviceDX->SetVertexShader(NULL);

    (*i)->Draw();
  }
}
