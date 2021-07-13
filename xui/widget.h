#pragma once

#include <atlbase.h>
#include <atltypes.h>
#include <atlwin.h>

#include "../targetver.h"
#include "types.h"

namespace xui {
class View;
class WidgetDelegate;

class Widget : public CWindowImpl<Widget, CWindow, CFrameWinTraits> {
 public:
  DECLARE_WND_CLASS(L"xui_win")

  struct InitParams {
    View* root_view_ = nullptr;
    WidgetDelegate* widget_delegate_ = nullptr;
  };

  BEGIN_MSG_MAP(Widget)
  MESSAGE_HANDLER(WM_CREATE, OnCreate)
  MESSAGE_HANDLER(WM_PAINT, OnPaint)
  MESSAGE_HANDLER(WM_SIZE, OnSize)
  MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
  MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
  MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
  MESSAGE_HANDLER(WM_CLOSE, OnClose)
  END_MSG_MAP()

  void Init(InitParams init_params);

  void Create(const Rect& rect);
  void Show();
  void Hide();

  void InvalidateAll();
  void InvalidateRect(const Rect& rect);

  virtual void OnFinalMessage(_In_ HWND /*hWnd*/);

 private:
  LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
  LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

  void OnViewWasRemovedFromTree(View* v);
  void SetMouseTrace();

 private:
  friend class View;
  InitParams init_params_;

  View* current_hovered_view_ = nullptr;
  bool mouse_trace_flag_ = false;
};

}  // namespace xui
