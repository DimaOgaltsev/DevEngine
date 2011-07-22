#ifndef DEV_MODEL_H
#define DEV_MODEL_H

#include <Kernel/DevInclude.h>

#include <Model/DevMesh.h>

namespace dev
{
  class FileModel :
    public Mesh
  {
  public:
    FileModel(const char* path, const Vec3& position, const Vec3& rotation, const Vec3& scale);
    FileModel(const char* path);
    virtual ~FileModel();

    bool OpenFile(const char* path);
    const char* GetFileName() const;
  
  protected:
    std::string _path;

    DWORD _typeVertex;
    DWORD _faceCount;
  };
}

#endif