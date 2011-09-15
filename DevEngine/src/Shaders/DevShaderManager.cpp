#include <Shaders/DevShaderManager.h>

using namespace dev;

ShaderManager::ShaderManager()
{
  clearList();
  clearShadersLists();
}

ShaderManager::~ShaderManager()
{
  clearList();

  if (!_vertexShaders.empty())
    for(ShaderMap::iterator i = _vertexShaders.begin(); i != _vertexShaders.end(); i++)
      delete (*i).second.vertexShader;

  if (!_pixelShaders.empty())
    for(ShaderMap::iterator i = _pixelShaders.begin(); i != _pixelShaders.end(); i++)
      delete (*i).second.pixelShader;

  clearShadersLists();
}

void ShaderManager::clearList()
{
  _meshes.clear();
}

void ShaderManager::AddMesh(Mesh* element)
{
  if (!element)
    return;
  
  for (MeshList::iterator i = _meshes.begin(); i != _meshes.end(); ++i)
  {
    if ((*i)->GetOrderNum() >= element->GetOrderNum())
    {
      if ((*i)->GetOrderNum() == element->GetOrderNum())
      {
        if ((*i)->GetMaterial() >= element->GetMaterial())
        {
          if ((*i)->GetMaterial() == element->GetMaterial())
          {
            if ((*i)->GetPixelShader() <= element->GetPixelShader())
            {
              if ((*i)->GetPixelShader() == element->GetPixelShader())
              {
                if ((*i)->GetVertexShader() <= element->GetVertexShader())
                {
                  _meshes.insert(i, element);
                  return;
                }
              }
              else
              {
                _meshes.insert(i, element);
                return;
              }
            }
          }
          else
          {
            _meshes.insert(i, element);
            return;
          }
        }
      }
      else
      {
        _meshes.insert(i, element);
        return;
      }
    }
  }

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
  for (MeshList::iterator i = _meshes.begin(); i != _meshes.end(); ++i)
  {
    (*i)->UpdateParameters();

    if ((*i)->GetVertexShader())
      (*i)->GetVertexShader()->SetShader();
    else
      _deviceDX->SetVertexShader(NULL);

    if ((*i)->GetPixelShader())
      (*i)->GetPixelShader()->SetShader();
    else
      _deviceDX->SetPixelShader(NULL);

    (*i)->Draw();

    (*i)->ReturnParameters();
  }
}

void ShaderManager::clearShadersLists()
{
  _vertexShaders.clear();
  _pixelShaders.clear();
}

VertexShader* ShaderManager::GetVertexShader(const char* path, VertexShader::TypeVertexShader type, const char* funcName)
{
  int hash = getHash(path, type, funcName);
  ShaderMap::iterator i = _vertexShaders.find(hash);
  if (i == _vertexShaders.end())
  {
    ShaderStruct buffer;
    buffer.vertexShader = new VertexShader(path, type, funcName);
    if (!buffer.vertexShader->CompileShader())
    {
      delete buffer.vertexShader;
      return NULL;
    }
    buffer.count = 1;
    _vertexShaders[hash] = buffer;
    return buffer.vertexShader;
  }

  (*i).second.count++;
  return (*i).second.vertexShader;
}

PixelShader* ShaderManager::GetPixelShader(const char* path, PixelShader::TypePixelShader type, const char* funcName)
{
  int hash = getHash(path, type, funcName);
  ShaderMap::iterator i = _pixelShaders.find(hash);
  if (i == _pixelShaders.end())
  {
    ShaderStruct buffer;
    buffer.pixelShader = new PixelShader(path, type, funcName);
    if (!buffer.pixelShader->CompileShader())
    {
      delete buffer.pixelShader;
      return NULL;
    }
    buffer.count = 1;
    _pixelShaders[hash] = buffer;
    return buffer.pixelShader;
  }
  
  (*i).second.count++;
  return (*i).second.pixelShader;
}

void ShaderManager::RemoveVertexShader(VertexShader* shader)
{
  for (ShaderMap::iterator i = _vertexShaders.begin(); i != _vertexShaders.end(); ++i)
  {
    if ((*i).second.vertexShader == shader)
    {
      (*i).second.count--;
      if ((*i).second.count < 1)
      {
        delete (*i).second.vertexShader;
        _vertexShaders.erase(i);
      }
      return;
    }
  }
}

void ShaderManager::RemovePixelShader(PixelShader* shader)
{
  for (ShaderMap::iterator i = _pixelShaders.begin(); i != _pixelShaders.end(); ++i)
  {
    if ((*i).second.pixelShader == shader)
    {
      (*i).second.count--;
      if ((*i).second.count < 1)
      {
        delete (*i).second.pixelShader;
        _pixelShaders.erase(i);
      }
      return;
    }
  }
}

unsigned int ShaderManager::getHash(const char* path, DWORD type, const char* funcName)
{
  unsigned int hash = 0;
  unsigned int len = strlen(funcName);
  for(unsigned int i = 0; i < strlen(path); i++)
    hash += (path[i] + i + type + (funcName[i % len])) << (i % 32);
  return hash;
}
