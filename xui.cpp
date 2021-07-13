
#include "xui.h"

#include <windows.h>

#include "framework.h"
#include "main_view.h"
#include "xui\render\gdiplus_wrap.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow) {
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  GdiplusWrap _;

  MainView main_view;
  main_view.Init();

  MSG msg;

  // 主消息循环:
  while (GetMessage(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int)msg.wParam;
}