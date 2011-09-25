#include <Windows.h>
#include <iostream>
#include "Renderer.hpp"
#include "DataParser.hpp"

HWND ghMainWnd = 0;

Renderer* g_pRenderer;

ATOM MyRegisterClass(HINSTANCE hInstance);
bool InitWindowsApp(HINSTANCE hInstance, int show);

int Run();

LRESULT CALLBACK
  WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, 
  HINSTANCE hPrevInstance,
  PSTR pCmdLine,
  int nShowCmd)
{
	

  MyRegisterClass(hInstance);
  if(!InitWindowsApp(hInstance, nShowCmd))
      return 0;
	g_pRenderer = new Renderer(hInstance, ghMainWnd);
	g_pRenderer->InitDirect3D();
  return g_pRenderer->Run();
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
   WNDCLASS wc;

   wc.style = CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc = WndProc;
   wc.cbClsExtra = 0;
   wc.cbWndExtra = 0;
   wc.hInstance = hInstance;
   wc.hIcon = LoadIcon(0, IDI_APPLICATION);
   wc.hCursor = LoadCursor(0, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
   wc.lpszMenuName = 0;
   wc.lpszClassName = L"LCRenderer";

  return RegisterClass(&wc);
}

bool InitWindowsApp(HINSTANCE hInstance,
  int show)
{
  ghMainWnd = CreateWindow(
    L"LCRenderer", 
    L"LCRenderer", 
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, 
    0, 
    640, 
    480, 
    NULL, 
    NULL, 
    hInstance, 
    NULL);

  ShowWindow(ghMainWnd, show);
  UpdateWindow(ghMainWnd);

  return true;
}

int Run()
{
  MSG msg = {0};

  BOOL bRet = 1;
  while( (bRet = GetMessage(&msg,0,0,0)) != 0)
  {
    if(-1 == bRet)
    {
      MessageBox(0, L"GetMessage FAILED", L"Error", MB_OK);
      break;
    }
    else
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,
  UINT msg,
  WPARAM wParam,
  LPARAM lParam)
{
  return g_pRenderer->WndProc(hWnd, msg, wParam, lParam);
}