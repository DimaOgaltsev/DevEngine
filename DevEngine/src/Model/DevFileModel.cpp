#include <Model/DevFileModel.h>

using namespace dev;

FileModel::FileModel(const char* path, const Vec3& position, const Vec3& rotation, const Vec3& scale) :
  Mesh(position, rotation, scale),
  _path(""),
  _typeVertex(NULL),
  _faceCount(NULL)
{
  OpenFile(path);
}

FileModel::FileModel(const char* path) :
  Mesh(),
  _path(""),
  _typeVertex(NULL),
  _faceCount(NULL)
{
  OpenFile(path);
}

FileModel::~FileModel()
{
}

bool FileModel::OpenFile(const char* path)
{
  _path = path;
  
  HANDLE hFile = CreateFile(path, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
  if (hFile == INVALID_HANDLE_VALUE)
    return FALSE;

  DWORD fileSize = GetFileSize(hFile, 0) - 2 * sizeof(DWORD);

  DWORD Face = 0, ReadValue = 0;
  ReadFile(hFile, &_typeVertex, sizeof(DWORD), &ReadValue, 0);
  ReadFile(hFile, &_faceCount, sizeof(DWORD), &ReadValue, 0);

  _vertices = new Vertex::ArrayVertices();
  _vertices->SetVerticesFromFile(hFile, fileSize, Vertex::VT_PNT);

  CloseHandle(hFile);
  return true;
}

const char* FileModel::GetFileName() const
{
  return _path.c_str();
}
