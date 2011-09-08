#ifndef DEV_SHADER_MANAGER_H
#define DEV_SHADER_MANAGER_H

#include <Shaders/DevShaders.h>
#include <Kernel/DevSingleton.h>
#include <Model/DevMesh.h>

namespace dev
{
  class ShaderManager : public Object
  {
  public:
    ShaderManager();
    virtual ~ShaderManager();

    void ClearList();
    void AddMesh(Mesh* element);
    void ReplaceMesh(Mesh* element, Mesh* newElement);
    void RemoveMesh(Mesh* element);

    void Update();

  protected:
    inline unsigned int getMeshNum(Mesh* element) const
    {
      for (unsigned int i = 0; i < _meshes.size(); ++i)
      {
        if (_meshes[i] == element) 
          return i;
      }
      return static_cast<unsigned int>(_meshes.size());
    }

    MeshList _meshes;
  };

  class DevShaderManager : public Singleton<ShaderManager>
  {};
}

#endif