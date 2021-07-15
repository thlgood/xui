#pragma once

#include "xui/view.h"
#include "xui/widget_delegate.h"

namespace xui {
class Label;
}

class MainView : public xui::View, public xui::WidgetDelegate {
 public:
  MainView();

  void Init();
  void Layout() override;

  void OnPaint(xui::Canvas* canvas) override;

  virtual void OnMouseEnter();
  virtual void OnMouseLeave();

  void OnWidgetDestroy() override;

 private:
  View* sub_view_;
  xui::Label* label_view_;
  bool is_hovered_ = false;
};