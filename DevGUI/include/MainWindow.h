#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <Windows.h>
#include <Kernel/DevRender.h>
#include <Model/DevMesh.h>

namespace GUI
{
#define NAME_WINDOWCLASS "MainWindow"

  class MainWindow
  {
  public:
    MainWindow();
    virtual ~MainWindow();

    bool Create(HINSTANCE hInst, int PosX, int PosY, int Width, int Height);

    void LoadScene();

    void Frame();

  private:
    void destroy();

    static void Func(LPVOID param, double deltaTime);

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK MsgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

    dev::Render* _render;
    dev::Input*  _input;
    dev::Camera* _camera;
    dev::Scene*  _scene;

    HINSTANCE    _hInst;
    HWND         _hWnd;

    int          _width;
    int          _height;

    float        _mouseX;
    float        _mouseY;
  };
}


#endif