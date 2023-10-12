#include "widget.h"

#include "view.h"
#include "widget_delegate.h"
#include "win32/win32_utils.h"

namespace xui {

void Widget::Init(InitParams init_params) {
  init_params_ = std::move(init_params);
  init_params_.root_view_->widget_ = this;
}

void Widget::Create(const Rect& rect) {
  RECT rc_rect = {rect.x, rect.y, rect.x + rect.width, rect.y + rect.height};
  CWindowImpl<Widget, CWindow, CFrameWinTraits>::Create(nullptr, &rc_rect);
}

void Widget::Show() { ShowWindow(SW_SHOW); }

void Widget::Hide() { ShowWindow(SW_HIDE); }

void Widget::InvalidateAll() { 
  Invalidate(FALSE); 
}

void Widget::InvalidateRect(const Rect& rect) {
  RECT client_rect = {rect.x, rect.y, rect.x + rect.width,
                      rect.y + rect.height};
  CWindowImpl<Widget, CWindow, CFrameWinTraits>::InvalidateRect(&client_rect,
                                                                FALSE);
}

void Widget::OnFinalMessage(_In_ HWND /*hWnd*/) { delete this; }

LRESULT Widget::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam,
                         BOOL& bHandled) {
  RECT client_rect;
  GetClientRect(&client_rect);
  Rect rect(0, 0, RcWidth(client_rect), RcHeight(client_rect));
  init_params_.root_view_->SetBounds(rect);

  SetMouseTrace();

  return 0;
}

LRESULT Widget::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam,
                        BOOL& bHandled) {
  CRect rect;
  GetClientRect(&rect);

  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(&ps);
  HDC hMemDC = CreateCompatibleDC(hdc);
  HBITMAP hMemBitmap = CreateCompatibleBitmap(hdc, rect.Width(), rect.Height());
  HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hMemBitmap);

  Canvas canvas(hMemDC, rect.Width(), rect.Height());
  init_params_.root_view_->Paint(&canvas);
  BitBlt(hdc, 0, 0, rect.Width(), rect.Height(), hMemDC, 0, 0, SRCCOPY);

  SelectObject(hMemDC, hOldBitmap);
  DeleteObject(hMemBitmap);
  DeleteDC(hMemDC);

  EndPaint(&ps);
  return 0;
}

LRESULT Widget::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam,
                       BOOL& bHandled) {
  RECT client_rect;
  GetClientRect(&client_rect);
  Rect rect(0, 0, RcWidth(client_rect), RcHeight(client_rect));
  init_params_.root_view_->SetBounds(rect);
  return 0;
}

LRESULT Widget::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam,
                            BOOL& bHandled) {
  SetMouseTrace();
  DWORD x = GET_X_LPARAM(lParam);
  DWORD y = GET_Y_LPARAM(lParam);

  View* hited_view = init_params_.root_view_->FindViewByPoint(Point(x, y));
  auto get_point = [&]() -> Point {
    Point pos = current_hovered_view_->GetPosInRootView();
    return Point(x, y) - pos;
  };

  auto leave_old = [&]() -> void {
    current_hovered_view_->OnMouseLeave();
    current_hovered_view_ = nullptr;
  };

  auto entry_new = [&]() -> void {
    current_hovered_view_ = hited_view;
    current_hovered_view_->OnMouseEnter();

    Point pt = get_point();
    current_hovered_view_->OnMouseMove(pt);
  };

  auto move_current = [&]() -> void {
    Point pt = get_point();
    current_hovered_view_->OnMouseMove(pt);
  };

  if (!hited_view && !current_hovered_view_) {
    return 0;
  } else if (hited_view && !current_hovered_view_) {
    entry_new();
  } else if (!hited_view && current_hovered_view_) {
    leave_old();
  } else if (hited_view == current_hovered_view_) {
    move_current();
  } else if (hited_view != current_hovered_view_) {
    leave_old();
    entry_new();
  }

  return 0;
}

LRESULT Widget::OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam,
                             BOOL& bHandled) {
  mouse_trace_flag_ = false;
  if (current_hovered_view_) {
    current_hovered_view_->OnMouseLeave();
    current_hovered_view_ = nullptr;
  }
  return 0;
}

LRESULT Widget::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam,
                          BOOL& bHandled) {
  if (init_params_.widget_delegate_) {
    init_params_.widget_delegate_->OnWidgetDestroy();
  }
  return 0;
}

LRESULT Widget::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam,
                        BOOL& bHandled) {
  if (init_params_.widget_delegate_) {
    init_params_.widget_delegate_->OnWidgetClosing();
  }
  DestroyWindow();
  return 0;
}

void Widget::OnViewWasRemovedFromTree(View* v) {
  if (v == current_hovered_view_) {
    current_hovered_view_ = nullptr;
  }
}

void Widget::SetMouseTrace() {
  if (!mouse_trace_flag_) {
    TRACKMOUSEEVENT tme = {sizeof(TRACKMOUSEEVENT)};
    tme.dwFlags = TME_LEAVE;
    tme.hwndTrack = m_hWnd;
    ::TrackMouseEvent(&tme);
    mouse_trace_flag_ = TRUE;
  }
}

}  // namespace xui