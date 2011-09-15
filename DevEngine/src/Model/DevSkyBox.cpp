#include <Model/DevSkyBox.h>

using namespace dev;

SkyBox::SkyBox(const char* name) :
  Mesh(name),
  _camera(NULL)
{
  dev::Vertex::VertexPT3 arrayVertex[] = 
  {
    { 10.0f,  -10.0f,  -10.0f,   1.0f,  -1.0f,  -1.0f},
    { 10.0f,   10.0f,  -10.0f,   1.0f,   1.0f,  -1.0f},
    {-10.0f,   10.0f,  -10.0f,  -1.0f,   1.0f,  -1.0f},
    {-10.0f,  -10.0f,  -10.0f,  -1.0f,  -1.0f,  -1.0f},
                             
    {-10.0f,  -10.0f,  -10.0f,  -1.0f,  -1.0f,  -1.0f},
    {-10.0f,   10.0f,  -10.0f,  -1.0f,   1.0f,  -1.0f},
    {-10.0f,   10.0f,   10.0f,  -1.0f,   1.0f,   1.0f},
    {-10.0f,  -10.0f,   10.0f,  -1.0f,  -1.0f,   1.0f},
                             
    {-10.0f,  -10.0f,   10.0f,  -1.0f,  -1.0f,   1.0f},
    {-10.0f,   10.0f,   10.0f,  -1.0f,   1.0f,   1.0f},
    { 10.0f,   10.0f,   10.0f,   1.0f,   1.0f,   1.0f},
    { 10.0f,  -10.0f,   10.0f,   1.0f,  -1.0f,   1.0f},
                             
    { 10.0f,  -10.0f,   10.0f,   1.0f,  -1.0f,   1.0f},
    { 10.0f,   10.0f,   10.0f,   1.0f,   1.0f,   1.0f},
    { 10.0f,   10.0f,  -10.0f,   1.0f,   1.0f,  -1.0f},
    { 10.0f,  -10.0f,  -10.0f,   1.0f,  -1.0f,  -1.0f},
                             
    { 10.0f,  -10.0f,  -10.0f,   1.0f,  -1.0f,  -1.0f},
    {-10.0f,  -10.0f,  -10.0f,  -1.0f,  -1.0f,  -1.0f},
    {-10.0f,  -10.0f,   10.0f,  -1.0f,  -1.0f,   1.0f},
    { 10.0f,  -10.0f,   10.0f,   1.0f,  -1.0f,   1.0f},
                             
    { 10.0f,   10.0f,   10.0f,   1.0f,   1.0f,   1.0f},
    {-10.0f,   10.0f,   10.0f,  -1.0f,   1.0f,   1.0f},
    {-10.0f,   10.0f,  -10.0f,  -1.0f,   1.0f,  -1.0f},
    { 10.0f,   10.0f,  -10.0f,   1.0f,   1.0f,  -1.0f}
  };
  
  const unsigned short arrayIndex[] =
  {
    0,1,2,    2,3,0,
    4,5,6,    6,7,4,
    8,9,10,   10,11,8,
    12,13,14, 14,15,12,
    16,17,18, 18,19,16,
    20,21,22, 22,23,20
  };

  SetVertices((LPVOID)arrayVertex, 24, dev::Vertex::VT_PT3);
  SetIndexes((LPVOID)arrayIndex, 36, D3DFMT_INDEX16);
}

SkyBox::~SkyBox()
{
}

void SkyBox::SetCamera(Camera* camera)
{
  _camera = camera;
}

void SkyBox::UpdateParameters()
{
  Mesh::UpdateParameters();
  _deviceDX->SetRenderState(D3DRS_ZENABLE, false);
}

void SkyBox::ReturnParameters()
{
  _deviceDX->SetRenderState(D3DRS_ZENABLE, true);
  Mesh::ReturnParameters();
}

void SkyBox::Update()
{
  if (_camera)
    SetPosition(_camera->GetPosition());
  Mesh::Update();
}
