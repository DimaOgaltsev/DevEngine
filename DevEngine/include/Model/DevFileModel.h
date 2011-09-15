#ifndef DEV_MODEL_H
#define DEV_MODEL_H

#include <Kernel/DevInclude.h>

#include <Element/DevGroup.h>
#include <Model/DevMesh.h>

namespace dev
{
  class FileModel :
    public Group
  {
  public:

    enum FileID
    {
      VertexFile = 0xF1A2B400,
      Index32File = 0xE1A2B400,
      Index16File = 0xD1A2B400
    };

    FileModel(const char* path, const Vec3& position, const Vec3& rotation, const Vec3& scale);
    FileModel(const char* path);
    virtual ~FileModel();

    bool OpenFile(const char* path);
    
    inline const char* GetFileName() const
    {
      return _path.c_str();
    }
    
    inline DWORD GetMeshCount() const 
    {
      return _meshNumber;
    }

    inline Mesh* GetMesh(const char* name) const
    {
      for(unsigned int i = 0; i < _elements.size(); i++)
      {
        Mesh* mesh = _elements[i]->AsMesh();
        if (mesh && !strcmp(mesh->GetName(), name))
          return mesh;
      }

      return NULL;
    }

    inline Mesh* GetMeshByNum(unsigned int num) const
    {
      if (_elements.size() > num)
        return _elements[num]->AsMesh();

      return NULL;
    }
  
  protected:
    std::string _path;

    DWORD _meshNumber;
  };
}

#endif