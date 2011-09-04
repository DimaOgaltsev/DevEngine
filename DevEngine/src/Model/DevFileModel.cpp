#include <Model/DevFileModel.h>

#include <Kernel/DevLog.h>

using namespace dev;

FileModel::FileModel(const char* path, const Vec3& position, const Vec3& rotation, const Vec3& scale) :
  Group(position, rotation, scale),
  _path("")
{
  OpenFile(path);
}

FileModel::FileModel(const char* path) :
  Group(),
  _path("")
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
  {
    std::string buffer("File not loaded: ");
    buffer += path;
    Log::GetLog()->WriteToLog(buffer.c_str());
    return false;
  }

  int fileSize = GetFileSize(hFile, 0) - 3 * sizeof(DWORD);

  DWORD ReadValue = 0;
  DWORD _bIndex = 0;
  DWORD _typeVertex = 0;
  ReadFile(hFile, &_bIndex,  sizeof(DWORD), &ReadValue, 0);

  if (_bIndex != Index16File && _bIndex != Index32File && _bIndex != VertexFile)
  {
    CloseHandle(hFile);
    std::string buffer("File not loaded: ");
    buffer += path;
    Log::GetLog()->WriteToLog(buffer.c_str());
    return false;
  }

  ReadFile(hFile, &_meshNumber,  sizeof(DWORD), &ReadValue, 0);
  ReadFile(hFile, &_typeVertex, sizeof(DWORD), &ReadValue, 0);

  for (DWORD i = 0; i < _meshNumber; i++)
  {
    DWORD _vNumber;
    DWORD _fNumber;
    ReadFile(hFile, &_vNumber,  sizeof(DWORD), &ReadValue, 0);
    ReadFile(hFile, &_fNumber,  sizeof(DWORD), &ReadValue, 0);

    Mesh* mesh = new Mesh();

    if (_bIndex == VertexFile)
      _vNumber = _fNumber * 3;
    mesh->SetVerticesFromFile(hFile, _vNumber, (Vertex::VertexType)_typeVertex);

    if (_bIndex == Index16File)
      mesh->SetIndexesFromFile(hFile, _fNumber * 3, D3DFMT_INDEX16);
    else
      if (_bIndex == Index32File)
        mesh->SetIndexesFromFile(hFile, _fNumber * 3, D3DFMT_INDEX32);

    AddElement(mesh);
  }

  CloseHandle(hFile);
  return true;
}
