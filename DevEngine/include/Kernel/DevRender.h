#ifndef DEV_RENDER_H
#define DEV_RENDER_H

#include <Kernel/DevInclude.h>

#include <Kernel/DevScene.h>

namespace dev
{
  class Render : 
    public Object
  {
  public:
    Render(HWND hWnd);
    virtual ~Render();

    bool  InitRender(int width, int height, int RefreshHz, bool FullScreenMode);
    void  Destroy();
    const char* GetLastError();

    Scene* GetScene();
    void SetScene(Scene* scene);

    void  Run();

  protected:
    static void  startRender(LPVOID param);
    void  runRender();
    void  stopRender();

    HWND                  _hWnd;
    int                   _width, _height;

    HANDLE                _renderThread;
    bool                  _stopRender;

    D3DDISPLAYMODE        _display;
    D3DPRESENT_PARAMETERS _parametersD3D;
    std::string           _lastError;

    Scene*                _scene;
  };
}

#endif