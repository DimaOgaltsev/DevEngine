#ifndef DEV_RENDER_H
#define DEV_RENDER_H

#include <Kernel/DevInclude.h>

#include <Kernel/DevScene.h>
#include <GUI/DevWindow.h>
#include <Kernel/DevInput.h>

namespace dev
{
  class Render : 
    public Object
  {
  public:
    Render();
    Render(HWND hWnd);
    Render(HINSTANCE hInstance, int PosX, int PosY, int Width, int Height);
    virtual ~Render();

    bool  InitRender(int width, int height, int RefreshHz, bool FullScreenMode);
    void  Destroy();

    void SetScene(Scene* scene);
    inline Scene* GetScene() const
    {
      return _scene;
    }

    void  Run();
    void  Frame();

  protected:
    Window*               _wnd;
    HWND                  _hWnd;
    int                   _width, _height;

    D3DDISPLAYMODE        _display;
    D3DPRESENT_PARAMETERS _parametersD3D;

    Scene*                _scene;
  };
}

#endif