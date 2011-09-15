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

    void AddMesh(Mesh* element);
    void ReplaceMesh(Mesh* element, Mesh* newElement);
    void RemoveMesh(Mesh* element);

    void Update();

  protected:
    void clearList();

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

  //init Shaders
  public:
    void clearShadersLists();

    VertexShader* GetVertexShader(const char* path, VertexShader::TypeVertexShader type, const char* funcName);
    PixelShader* GetPixelShader(const char* path, PixelShader::TypePixelShader type, const char* funcName);
    void RemoveVertexShader(VertexShader* shader);
    void RemovePixelShader(PixelShader* shader);

  protected:

    struct ShaderStruct
    {
      union
      {
        VertexShader*   vertexShader;
        PixelShader*    pixelShader;
      };
      int       count;
    };

    unsigned int getHash(const char* path, DWORD type, const char* funcName);

    typedef std::map<unsigned int, ShaderStruct> ShaderMap;
    ShaderMap _vertexShaders;
    ShaderMap _pixelShaders;
  };

  class DevShaderManager : public Singleton<ShaderManager>
  {};
}

#endif